LIBRARY ieee;
USE ieee.std_logic_1164.all;

LIBRARY simpleLogic;
USE simpleLogic.all;

ENTITY decoder3to8 IS
	PORT ( m0, m1, m2 : IN STD_LOGIC;
			 z0, Z1, Z2, Z3, Z4, Z5, Z6, Z7 : OUT STD_LOGIC);

END decoder3to8;

ARCHITECTURE structure OF decoder3to8 IS

	SIGNAL not_m0, not_m1, not_m2 : STD_LOGIC;


	COMPONENT gateInv 					-- gateInv
	  PORT (x: IN STD_LOGIC;
			  y: OUT STD_LOGIC);
	END COMPONENT;
	
	COMPONENT gateAnd3 					-- gateAnd3
		PORT (x0, x1, x2: IN STD_LOGIC;
			   y     : OUT STD_LOGIC);
	END COMPONENT;

BEGIN

	notm0 : gateInv PORT MAP (m0, not_m0);
	notm1 : gateInv PORT MAP (m1, not_m1);
	notm2 : gateInv PORT MAP (m2, not_m2);
	
	and_z7 : gateAnd3 PORT MAP (not_m0, not_m1, not_m2, z7);
	and_z6 : gateAnd3 PORT MAP (not_m0, not_m1, m2, z6);
	and_z5 : gateAnd3 PORT MAP (not_m0, m1, not_m2, z5);
	and_z4 : gateAnd3 PORT MAP (not_m0, m1, m2, z4);
	and_z3 : gateAnd3 PORT MAP (m0, not_m1, not_m2, z3);
	and_z2 : gateAnd3 PORT MAP (m0, not_m1, m2, z2);
	and_z1 : gateAnd3 PORT MAP (m0, m1, not_m2, z1);
	and_z0 : gateAnd3 PORT MAP (m0, m1, m2, z0);
	
	
END structure;