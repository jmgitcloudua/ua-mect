LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateAnd2 IS
    PORT(x0, x1: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateAnd2;

ARCHITECTURE logicFunc of gateAnd2 IS
BEGIN
    y <= x AND x1;
END logicFunc;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateOr2 IS
    PORT(x0, x1: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateOr2;

ARCHITECTURE logicFunc of gateOr2 IS
BEGIN
    y <= x OR x1;
END logicFunc;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateXOr2 IS
    PORT(x0, x1: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateXOr2;

ARCHITECTURE logicFunc of gateXOr2 IS
BEGIN
    y <= x XOR x1;
END logicFunc;
