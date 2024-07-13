LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateAnd2 IS
    PORT(x1, x2: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateAnd2;

ARCHITECTURE logicFunc of gateAnd2 IS
BEGIN
    y <= x1 AND x2;
END logicFunc;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateNand2 IS
    PORT(x1, x2: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateNand2;

ARCHITECTURE logicFunc of gateNand2 IS
BEGIN
    y <= NOT(x1 AND x2);
END logicFunc;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateOr2 IS
    PORT(x1, x2: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateOr2;

ARCHITECTURE logicFunc of gateOr2 IS
BEGIN
    y <= x1 OR x2;
END logicFunc;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateXOr2 IS
    PORT(x1, x2: IN STD_LOGIC;
              y: OUT STD_LOGIC);
END gateXOr2;

ARCHITECTURE logicFunc of gateXOr2 IS
BEGIN
    y <= x1 XOR x2;
END logicFunc;
