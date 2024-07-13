
--------------- Gate Xor2 ------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateXor2 IS
	PORT (x0, x1: IN STD_LOGIC;
			y		: OUT STD_LOGIC);
END gateXor2;

ARCHITECTURE logicFunction OF gateXor2 IS
BEGIN	
	y <= x0 XOR x1;
END logicFunction;

--------------- Parallel Encoder ------------------

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY parallel_encoder IS
	PORT ( m1,m2,m3,m4 : in STD_LOGIC;					-- mensagem inicial (4 bits - m1,m2,m3,m4)
			 x0,x1,x2,x3,x4,x5,x6,x7 : out STD_LOGIC	-- mensagem codificada com redundancia (8 bits - x0...x7)
			);
	
END parallel_encoder;

ARCHITECTURE structure OF parallel_encoder IS

SIGNAL  sig_xor2, sig_xor4, sig_xor6 : STD_LOGIC;

COMPONENT gateXor2 
	PORT (x0, x1 : IN STD_LOGIC;
			y		 : OUT STD_LOGIC);
END COMPONENT;

BEGIN
	-- In this version: 
	--	 Decreased the x-ors from 12 to 7
	--  1 x-or propagation time delays in the worst case (instead of 3) 

	x0 <= m4; -- x0 = m4
	
	xor1 : gateXor2 PORT MAP (m1, m4, x1);		-- x1 = m1 xor m4
	
	xor2 : gateXor2 PORT MAP (m2, m4, sig_xor2);		-- x2 = m2 xor m4 
	
	xor3 : gateXor2 PORT MAP (m1, sig_xor2, x3); 	-- x3 = m1 xor m2 xor m4 = m1 xor x2
	
	xor4 : gateXor2 PORT MAP (m3,m4,sig_xor4);		-- x4 = m3 xor m4;
	
	xor5 : gateXor2 PORT MAP (m1,sig_xor4,x5); 	-- x5 = m1 xor m3 xor m4 = m1 xor x4
	
	xor6 : gateXor2 PORT MAP (m2,sig_xor4,sig_xor6);		-- x6 = m2 xor m3 xor m4 = m2 xor x4
	
	xor7 : gateXor2 PORT MAP (m1,sig_xor6,x7);		-- x7 = m1 xor m2 xor m3 xor m4 = m1 xor x6
	
	x2 <= sig_xor2;
	x4 <= sig_xor4;
	x6 <= sig_xor6;

END structure;