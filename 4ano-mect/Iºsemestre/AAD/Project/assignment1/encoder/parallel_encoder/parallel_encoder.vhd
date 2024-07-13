LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY parallel_encoder IS
    PORT(m: IN STD_LOGIC_VECTOR(3 DOWNTO 0);
         x_out: OUT STD_LOGIC_VECTOR(7 DOWNTO 0));
END parallel_encoder;

ARCHITECTURE structure OF parallel_encoder IS
    SIGNAL x0, x1, x2, x3, x4, x5, x6, x7: STD_LOGIC;
BEGIN
    x7 <= m(0);
    x6 <= m(3) xor m(0);
    x5 <= m(2) xor m(0);
    x4 <= m(3) xor x5;
    x3 <= m(1) xor m(0);
    x2 <= m(3) xor x3;
    x1 <= m(2) xor x3;
    x0 <= m(3) xor x1;
    x_out <= x7 & x6 & x5 & x4 & x3 & x2 & x1 & x0;
END structure;