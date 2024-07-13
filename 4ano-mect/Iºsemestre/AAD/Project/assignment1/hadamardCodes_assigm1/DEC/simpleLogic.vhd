LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateInv IS							-- gateInv
  PORT (x: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateInv;

ARCHITECTURE logicFunction OF gateInv IS
BEGIN
  y <= NOT x;
END logicFunction;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateAnd2 IS						-- gateAnd2
  PORT (x0, x1: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateAnd2;

ARCHITECTURE logicFunction OF gateAnd2 IS
BEGIN
  y <= x0 AND x1;
END logicFunction;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateAnd3 IS						-- gateAnd3
  PORT (x0, x1, x2: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateAnd3;

ARCHITECTURE logicFunction OF gateAnd3 IS
BEGIN
  y <= x0 AND x1 AND x2;
END logicFunction;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateOr2 IS							-- gateOR2
  PORT (x0, x1: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateOr2;

ARCHITECTURE logicFunction OF gateOr2 IS
BEGIN
  y <= x0 OR x1;
END logicFunction;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateOr3 IS							-- gateO3 
  PORT (x0, x1, x2: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateOr3;

ARCHITECTURE logicFunction OF gateOr3 IS
BEGIN
  y <= x0 OR x1 OR x2;
END logicFunction;

LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateNOr2 IS							-- gateNOR2
  PORT (x0, x1: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateNOr2;

ARCHITECTURE logicFunction OF gateNOr2 IS
BEGIN
  y <= NOT (x0 OR x1); 
END logicFunction;


LIBRARY ieee;
USE ieee.std_logic_1164.all;

ENTITY gateXOr2 IS						-- gateXOR2
  PORT (x0, x1: IN STD_LOGIC;
        y: OUT STD_LOGIC);
END gateXOr2;

ARCHITECTURE logicFunction OF gateXOr2 IS
BEGIN
  y <= x0 XOR x1;
END logicFunction;
