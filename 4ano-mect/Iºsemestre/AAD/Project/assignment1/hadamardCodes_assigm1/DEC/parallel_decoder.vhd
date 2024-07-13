LIBRARY ieee;
USE ieee.std_logic_1164.all;

LIBRARY simpleLogic;
USE simpleLogic.all;

LIBRARY decoder3to11;
USE decoder3to11.all;

LIBRARY popCounter_8bitParallel;
USE popCounter_8bitParallel.all;


ENTITY parallel_decoder IS 
	PORT (y0, y1, y2, y3, y4, y5, y6, y7 : IN STD_LOGIC;
			m0,m1,m2,m3 : OUT STD_LOGIC;
			valid 	: OUT STD_LOGIC);

END parallel_decoder;

ARCHITECTURE structure OF parallel_decoder IS

	-- signals m0
	SIGNAL c00, c01, c02, c03     : STD_LOGIC;
	SIGNAL ANDc00_c01, ANDc03_c02, ORc00_c01, ORc02_c03 : STD_LOGIC;
	SIGNAL in0_m0One, in1_m0One, in0_m0Zero, in1_m0Zero   : STD_LOGIC;
	SIGNAL m0_One, m0_Zero, m0_erro, NOTm0_erro  : STD_LOGIC;
	
	-- signals m1
	SIGNAL c10, c11, c12, c13     : STD_LOGIC;
	SIGNAL ANDc10_c11, ANDc13_c12, ORc10_c11, ORc12_c13 : STD_LOGIC;
	SIGNAL in0_m1One, in1_m1One, in0_m1Zero, in1_m1Zero   : STD_LOGIC;
	SIGNAL m1_One, m1_Zero, m1_erro, NOTm1_erro  : STD_LOGIC;
	
	-- signals m2
	SIGNAL c20, c21, c22, c23     : STD_LOGIC;
	SIGNAL ANDc20_c21, ANDc23_c22, ORc20_c21, ORc22_c23 : STD_LOGIC;
	SIGNAL in0_m2One, in1_m2One, in0_m2Zero, in1_m2Zero   : STD_LOGIC;
	SIGNAL m2_One, m2_Zero, m2_erro, NOTm2_erro  : STD_LOGIC;
	
	SIGNAL sigValid : STD_LOGIC;	-- valid
	SIGNAL signal_m0, signal_m1, signal_m2, signal_m3 : STD_LOGIC; -- m0', m1', m2'
	
	
	----- Decoder 3:8 -----
	SIGNAL sig_z0, sig_z1, sig_z2, sig_z3, sig_z4, sig_z5, sig_z6, sig_z7 : STD_LOGIC;
	
	SIGNAL sig_d0, sig_d1, sig_d2, sig_d3, sig_d4, sig_d5, sig_d6, sig_d7 : STD_LOGIC;
	
	----- popCounter_8bit Parallel -----
	
	SIGNAL sig_d  : STD_LOGIC_VECTOR (7 DOWNTO 0);
	SIGNAL sig_c  :  STD_LOGIC_VECTOR (3 DOWNTO 0);
	SIGNAL sigC	: STD_LOGIC; 
	
	
	COMPONENT gateInv IS						-- gateInv
	  PORT (x: IN STD_LOGIC;
			  y: OUT STD_LOGIC);
	END COMPONENT;
	
	
	COMPONENT gateXor2 						-- gateXOR2
		PORT (x0, x1 : IN STD_LOGIC;
				y	    : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT gateAnd2 						-- gateAnd2
		PORT (x0, x1 : IN STD_LOGIC;
				y      : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT gateOr2 						-- gateOR2
		PORT (x0, x1 : IN STD_LOGIC;
				y      : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT gateNOr2 						-- gateNOR2
		PORT (x0, x1 : IN STD_LOGIC;
				y      : OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT gateOr3 						-- gateO3
		PORT (x0, x1, x2: IN STD_LOGIC;
			  y: OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT decoder3to8 					-- Decoder 3:8 
		PORT ( m0, m1, m2 : IN STD_LOGIC;
				 z0, Z1, Z2, Z3, Z4, Z5, Z6, Z7 : OUT STD_LOGIC);

	END COMPONENT;
	
	COMPONENT popCounter_8bitParallel 	  -- 	popCounter_8bitParallel
		PORT (d: IN STD_LOGIC_VECTOR (7 DOWNTO 0);
				c: OUT STD_LOGIC_VECTOR (3 DOWNTO 0));
	END COMPONENT;
	
BEGIN	
	
	-------------------------------- m0 ---------------------------------

	--- Equations for bit m0
	xor_c00 : gateXor2 PORT MAP (y0, y1, c00);
	xor_c01 : gateXor2 PORT MAP (y2, y3, c01);
	xor_c02 : gateXor2 PORT MAP (y4, y5, c02);
	xor_c03 : gateXor2 PORT MAP (y6, y7, c03);
	
	--- Determine m0One
	and_c00_c01: gateAnd2 PORT MAP (c00, c01, ANDc00_c01);
	and_c02_c03: gateAnd2 PORT MAP (c03, c02, ANDc03_c02);
	or_c00_c01:  gateAnd2 PORT MAP (c00, c01, ORc00_c01);
	or_c02_c03:  gateAnd2 PORT MAP (c02, c03, ORc02_c03); 
	
	in0m0One:	gateAnd2 PORT MAP (ANDc00_c01, ORc02_c03, in0_m0One);
	in1m0One:  gateAnd2 PORT MAP (ORc00_c01, ANDc03_c02, in1_m0One);
	m0One : gateOr2 PORT MAP (in0_m0One, in1_m0One, m0_One);				-- m0One
	
	--- Determine m0Zero	
	in0m0Zero:	gateAnd2 PORT MAP (not(ANDc00_c01), not(ORc02_c03), in0_m0Zero);
	in1m0Zero:  gateAnd2 PORT MAP (not(ORc00_c01), not(ANDc03_c02), in1_m0Zero);
	m0Zero   : gateOr2 PORT MAP (in0_m0Zero, in1_m0Zero, m0_Zero);		-- m0Zero
	
	m0erro_tmp: gateOr2 PORT MAP (m0_One, m0_Zero, m0_erro);
	m0erro : gateInv PORT MAP (m0_erro, NOTm0_erro);	-- m0erro = not(m0One + m0Zero)
	
	
	-------------------------------- m1 ---------------------------------
	
	--- Equations for bit m1
	xor_c10 : gateXor2 PORT MAP (y0, y2, c10);
	xor_c11 : gateXor2 PORT MAP (y1, y3, c11);
	xor_c12 : gateXor2 PORT MAP (y4, y6, c12);
	xor_c13 : gateXor2 PORT MAP (y5, y7, c13);
	
	--- Determine m1One
	and_c10_c11: gateAnd2 PORT MAP (c10, c11, ANDc10_c11);
	and_c12_c13: gateAnd2 PORT MAP (c13, c12, ANDc13_c12);
	or_c10_c11:  gateAnd2 PORT MAP (c10, c11, ORc10_c11);
	or_c12_c13:  gateAnd2 PORT MAP (c12, c13, ORc12_c13); 
	
	in0m1One:	gateAnd2 PORT MAP (ANDc10_c11, ORc12_c13, in0_m1One);
	in1m1One:  gateAnd2 PORT MAP (ORc10_c11, ANDc13_c12, in1_m1One);
	m1One : gateOr2 PORT MAP (in0_m1One, in1_m1One, m1_One);				-- m1One
	
	--- Determine m1Zero
	in0m1Zero:	gateAnd2 PORT MAP (not(ANDc10_c11), not(ORc12_c13), in0_m1Zero);
	in1m1Zero:  gateAnd2 PORT MAP (not(ORc10_c11), not(ANDc13_c12), in1_m1Zero);
	m1Zero   : gateOr2 PORT MAP (in0_m1Zero, in1_m1Zero, m1_Zero);						-- m1Zero
	
	m1erro_tmp: gateOr2 PORT MAP (m1_One, m1_Zero, m1_erro);
	m1erro : gateInv PORT MAP (m1_erro, NOTm1_erro); 				-- m1erro = not(m1One + m1Zero)
	
	
	-------------------------------- m2 ---------------------------------
	--- Equations for bit m2
	xor_c20 : gateXor2 PORT MAP (y0, y4, c20);
	xor_c21 : gateXor2 PORT MAP (y1, y5, c21);
	xor_c22 : gateXor2 PORT MAP (y2, y6, c22);
	xor_c23 : gateXor2 PORT MAP (y3, y7, c23);
	
	--- Determine m2One
	and_c20_c21: gateAnd2 PORT MAP (c20, c21, ANDc20_c21);
	and_c22_c23: gateAnd2 PORT MAP (c23, c22, ANDc23_c22);
	or_c20_c21:  gateAnd2 PORT MAP (c20, c21, ORc20_c21);
	or_c22_c23:  gateAnd2 PORT MAP (c22, c23, ORc22_c23); 
	
	in0m2One:	gateAnd2 PORT MAP (ANDc20_c21, ORc22_c23, in0_m2One);
	in1m2One:  gateAnd2 PORT MAP (ORc20_c21, ANDc23_c22, in1_m2One);
	m2One : gateOr2 PORT MAP (in0_m2One, in1_m2One, m2_One);				-- m2One
	
	--- Determine m2Zero
	in0m2Zero:	gateAnd2 PORT MAP (not(ANDc20_c21), not(ORc22_c23), in0_m2Zero);
	in1m2Zero:  gateAnd2 PORT MAP (not(ORc20_c21), not(ANDc23_c22), in1_m2Zero);
	m2Zero   : gateOr2 PORT MAP (in0_m2Zero, in1_m2Zero, m2_Zero);		-- m2Zero
	
	m2erro_tmp: gateOr2 PORT MAP (m2_One, m2_Zero, m2_erro);
	m2erro : gateInv PORT MAP (m2_erro, NOTm2_erro); 				-- m2erro = not(m2One + m2Zero)
	
	--- valid = not (m0erro + m1erro + m2erro)
	signalV: gateOr3 PORT MAP (NOTm0_erro, NOTm1_erro, NOTm2_erro, sigValid);
	valid <= not(sigValid);
	
	-- m0'
	sigM0 : gateAnd2 PORT MAP (m0_One, not(sigValid), signal_m0);
	m0 <= signal_m0;
	
	-- m1'
	sigM1 : gateAnd2 PORT MAP (m1_One, not(sigValid), signal_m1);
	m1 <= signal_m1;
	
	-- m2'
	sigM2 : gateAnd2 PORT MAP (m2_One, not(sigValid), signal_m2);
	m2 <= signal_m2;
	
	
	------------------- DECODER 3:8 ---------------------------
	
	
	dec3to8: decoder3to8 PORT MAP (signal_m0, signal_m1, signal_m2, 
											sig_z0, sig_z1, sig_z2, sig_z3, sig_z4, sig_z5, sig_z6, sig_z7);
											
											
	--------- Verificar se existe erro em função de m3' ----------
	-- 1 - comparar todos os valores z0...z7 com y0...y7
	
	xor_d0 : gateXor2 PORT MAP (sig_z0, y0, sig_d0);
	xor_d1 : gateXor2 PORT MAP (sig_z1, y1, sig_d1);
	xor_d2 : gateXor2 PORT MAP (sig_z2, y2, sig_d2);
	xor_d3 : gateXor2 PORT MAP (sig_z3, y3, sig_d3);
	xor_d4 : gateXor2 PORT MAP (sig_z4, y4, sig_d4);
	xor_d5 : gateXor2 PORT MAP (sig_z5, y5, sig_d5);
	xor_d6 : gateXor2 PORT MAP (sig_z6, y6, sig_d6);
	xor_d7 : gateXor2 PORT MAP (sig_z7, y7, sig_d7);
	
	sig_d(7) <= sig_d0;
	sig_d(6) <= sig_d1;
	sig_d(5) <= sig_d2;
	sig_d(4) <= sig_d3;
	sig_d(3) <= sig_d4;
	sig_d(2) <= sig_d5;
	sig_d(1) <= sig_d6;
	sig_d(0) <= sig_d7;
	
	popCounter8bitP : popCounter_8bitParallel PORT MAP (sig_d, sig_c);
	
	
	-- Check vality of m3' = (c2xorc3) . valid
	c2Xorc3 : gateXor2 PORT MAP (sig_c(1), sig_c(0), sigC);

	
	c2Xorc3AndVal : gateAnd2 PORT MAP (sigC, not(sigValid), signal_m3);
	
	m3 <= signal_m3;	-- Se m3' = 0 -> erro , caso contrario não
	
	
END structure;

