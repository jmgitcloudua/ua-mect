LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY straightF_encoder IS
	PORT ( m : in std_logic_vector(3 downto 0);
			 x : out std_logic_vector(7 downto 0)
			);
	
END straightF_encoder;

ARCHITECTURE structure OF straightF_encoder IS

SIGNAL x0,x1,x2,x3,x4,x5,x6,x7 : std_logic;

BEGIN

	x0 <= m(0);
	x1 <= m(1) xor m(0);
	x2 <= m(2) xor m(0);
	x3 <= m(1) xor m(2) xor m(0);	 -- x3 = m1 xor x2
	x4 <= m(3) xor m(0);				
	x5 <= m(1) xor m(3) xor m(0);	 -- x5 = m1 xor x4
	x6 <= m(2) xor m(3) xor m(0);	 -- x6 = m2 xor x4
	x7 <= m(1) xor m(2) xor m(3) xor m(0); -- x7 = m1 xor x6
	
	x <= x0 & x1 & x2 & x3 & x4 & x5 & x6 & x7;

END structure;

