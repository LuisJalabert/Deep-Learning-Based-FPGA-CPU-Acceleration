-- ==============================================================
-- File generated on Thu Apr 04 23:06:49 CEST 2019
-- Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
-- SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
-- IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity LoopOracle_FCW5_rom is 
    generic(
             DWIDTH     : integer := 32; 
             AWIDTH     : integer := 9; 
             MEM_SIZE    : integer := 384
    ); 
    port (
          addr0      : in std_logic_vector(AWIDTH-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DWIDTH-1 downto 0);
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of LoopOracle_FCW5_rom is 

signal addr0_tmp : std_logic_vector(AWIDTH-1 downto 0); 
type mem_array is array (0 to MEM_SIZE-1) of std_logic_vector (DWIDTH-1 downto 0); 
signal mem : mem_array := (
    0 => "00111011011011111001011000100101", 
    1 => "10111101000001011010001111100100", 
    2 => "00111101001011001110100110100011", 
    3 => "10111011100000001000100100100111", 
    4 => "10111011101010101001100110011100", 
    5 => "00111101100100100100100111100100", 
    6 => "10111101001101001110010001000011", 
    7 => "00111101100100000111010010100111", 
    8 => "00111101100100001110000010101000", 
    9 => "10111100111011110100011110110110", 
    10 => "10111011001101000001011111001010", 
    11 => "00111100101001111100101111110111", 
    12 => "10111101001111111110100011101110", 
    13 => "10111011101000001000000111101011", 
    14 => "00111100100110111000001000111101", 
    15 => "00111101100011010110000100101100", 
    16 => "10111101001001001100101001001111", 
    17 => "10111101100010001000010100001010", 
    18 => "10111100010110001011000111011101", 
    19 => "00111101100001011010110001000111", 
    20 => "00111101000101000000010001100100", 
    21 => "10111101010010000001011111111100", 
    22 => "00111001101000111110100001111101", 
    23 => "00111101100100110010101001001001", 
    24 => "00111111100000100111000111011110", 
    25 => "10111101001100011110010010110100", 
    26 => "10111100111100000101101001110001", 
    27 => "10111101010000101010111111011110", 
    28 => "00111101011100111111001100010111", 
    29 => "00111101110101000111101011100001", 
    30 => "10111110000011000000000001010100", 
    31 => "10111101110100010001100111001110", 
    32 => "10111101001111010101010001010100", 
    33 => "10111100101101000111010000010000", 
    34 => "00111101001111001101101110111110", 
    35 => "10111101010011110101111101001110", 
    36 => "10111101010011111010000001010001", 
    37 => "00111101000100010110101110011000", 
    38 => "00111100110011110010000001100100", 
    39 => "00111100011010110100001000000011", 
    40 => "10111101000001111111000000100100", 
    41 => "10111101010100010111100000101101", 
    42 => "10111100011100000110011100000110", 
    43 => "00111100101001010000111110000100", 
    44 => "00111101100001011101111010011100", 
    45 => "10111100000011101111110000011100", 
    46 => "10111101100100001011111110100001", 
    47 => "00111101001010101110001010010111", 
    48 => "10111110101101100100110101111111", 
    49 => "10111110001001101011011110101010", 
    50 => "10111101100000010000101101100011", 
    51 => "10111101111100100111011001110101", 
    52 => "10111110000001011001011101001110", 
    53 => "10111110001110110010110101001101", 
    54 => "10111100111001010110011010001100", 
    55 => "10111100111110001110000110010011", 
    56 => "00111110000111110000111011010100", 
    57 => "00111101011110110011100001010000", 
    58 => "00111100000010011011001101110011", 
    59 => "00111100100010100011010100001101", 
    60 => "00111101101110001111111011101111", 
    61 => "10111011111000111011111010000001", 
    62 => "10111100111111110011110011110111", 
    63 => "00111001101110100011111110000001", 
    64 => "00111100111100001001101101110100", 
    65 => "00111101000000000010101011111110", 
    66 => "00111011000101110111101011011011", 
    67 => "00111100111111100111011111010101", 
    68 => "00111100101001101110000100010101", 
    69 => "10111100001011010001000001101111", 
    70 => "10111101010101011110001010001011", 
    71 => "00111101001011010010011001110100", 
    72 => "10111101000110101110010011110011", 
    73 => "00111100010111100011001100100111", 
    74 => "10111101100100001010101010101000", 
    75 => "00111110000111111010000110100001", 
    76 => "00111011111110101000000100111011", 
    77 => "10111100101000011010000011001111", 
    78 => "10111101111101010100100111111001", 
    79 => "10111110000001111101101010100101", 
    80 => "00111100001110100100110101101110", 
    81 => "00111100011111111101111001110010", 
    82 => "10111100011010100111110011100001", 
    83 => "10111101010001000000001010001110", 
    84 => "00111101100110101100110001001111", 
    85 => "00111101001010001111110000001101", 
    86 => "10111100101010010011100011011110", 
    87 => "00111100101101111110110101000010", 
    88 => "00111101011010101010111100110110", 
    89 => "00111101001110110111001100001000", 
    90 => "00111101100110110100000000101101", 
    91 => "10111101100110110100101000100011", 
    92 => "10111100110011011001111010000100", 
    93 => "00111100001111010001101010101000", 
    94 => "10111101100101111110011001110001", 
    95 => "10111101011100110101000010001111", 
    96 => "10111111001101010000010111010001", 
    97 => "10111110000111110011111000000011", 
    98 => "10111110000111011001110100110100", 
    99 => "00111110111010001110100010100111", 
    100 => "00111110101011011001111010000100", 
    101 => "00111110101000110100100101111011", 
    102 => "00111110100100110010011101100111", 
    103 => "00111101101101111011101111111001", 
    104 => "10111100110011101101100100010111", 
    105 => "10111110000111101001011000111110", 
    106 => "00111110000111110010101110101010", 
    107 => "00111011110001110110000101010011", 
    108 => "10111101000011011001110101110111", 
    109 => "10111011111000100101010011110100", 
    110 => "00111101000011011110001010101100", 
    111 => "00111110101001101001101011010100", 
    112 => "00111101001010100110010011000011", 
    113 => "00111110000101111010101000100110", 
    114 => "00111100101111000111100100101101", 
    115 => "10111101000100010001010110011100", 
    116 => "00111011111001101011110001100010", 
    117 => "00111110100100111101100001011010", 
    118 => "00111100011010010100111011100100", 
    119 => "00111101111001011000111101110001", 
    120 => "10111101010000000100000100000011", 
    121 => "00111011110110101010100001011000", 
    122 => "10111011010100010110100111101010", 
    123 => "00111101100110011011000110111000", 
    124 => "00111110000000111111111001011101", 
    125 => "00111101111010101101001011011101", 
    126 => "10111101010100110110110101100101", 
    127 => "00111100111100001001011101000010", 
    128 => "00111110000001110001110111100111", 
    129 => "00111100100101001101111110001011", 
    130 => "00111101011111010001001001000101", 
    131 => "00111011110101001101000010100111", 
    132 => "00111011101001001000000001111101", 
    133 => "00111101100011000010010110001101", 
    134 => "10111101011100110100101001000101", 
    135 => "00111101000001110011011110010111", 
    136 => "10111011110110010000110001110110", 
    137 => "00111101010101110001001010100001", 
    138 => "00111100111000001011000010101111", 
    139 => "10111100010111110101110011110010", 
    140 => "10111101000101101000111010000010", 
    141 => "00111101111000000111010111110111", 
    142 => "00111101010101101111001000011111", 
    143 => "10111101001000111101101100111100", 
    144 => "00111111000001111010011110000111", 
    145 => "10111110110000001110101010011110", 
    146 => "10111110001110100011110000100001", 
    147 => "10111101001000111011101010111010", 
    148 => "10111110111010101000000001001001", 
    149 => "10111101111111010000011111001000", 
    150 => "00111011111000101001100110111110", 
    151 => "10111101111100110110110011011111", 
    152 => "00111110100000000000011010001110", 
    153 => "00111100010101010010110000010111", 
    154 => "00111100011000100001110110010111", 
    155 => "10111100010001100100111111011011", 
    156 => "00111101101101110000000011001110", 
    157 => "00111101101101011000100001011101", 
    158 => "10111110001010111110000011011111", 
    159 => "00111100010010001101100111111001", 
    160 => "00111011110111010111110001000111", 
    161 => "10111101111101011110011101000011", 
    162 => "00111101100001101100010011000110", 
    163 => "10111101101111101010001101011001", 
    164 => "10111110000110001011000001001011", 
    165 => "00111100011110000111001001101101", 
    166 => "00111100110010100000010111011110", 
    167 => "10111101110110010010011001000010", 
    168 => "10111111010010010011110100110010", 
    169 => "10111110100100011101101111001011", 
    170 => "10111100111100001011111100011010", 
    171 => "10111101111001001110110011101010", 
    172 => "00111100110100001000100100011010", 
    173 => "00111101101011100000010000111010", 
    174 => "00111110000001110010110110100001", 
    175 => "00111101001010011001011000110001", 
    176 => "00111110001101110100011010001000", 
    177 => "10111101100100010101010000000000", 
    178 => "00111011100011111111111011100110", 
    179 => "00111101001011111101110110101001", 
    180 => "10111101000110010111101100110001", 
    181 => "00111101100010100000011111110110", 
    182 => "10111100101011110011011111111100", 
    183 => "10111100010000000110111000011010", 
    184 => "00111101100010100100101110011001", 
    185 => "00111100011010110001110001000011", 
    186 => "10111011101000100110001101101101", 
    187 => "00111000111011111101111101001011", 
    188 => "00111101011011010110111011001110", 
    189 => "10111101001001000111100110010010", 
    190 => "00111101100000111101010111111110", 
    191 => "00111101011100110110010110001000", 
    192 => "10111101000010011101111100010001", 
    193 => "00111101010101101010001001101110", 
    194 => "10111101000001000011011011111100", 
    195 => "00111100101000010111110100101000", 
    196 => "00111101100001101111100010101101", 
    197 => "00111100110111011011110110110110", 
    198 => "00111100110100001010101010101000", 
    199 => "10111010001010001111101100001011", 
    200 => "00111101100001110101010101111010", 
    201 => "00111101010111110111101001001110", 
    202 => "10111100000000001011011101001011", 
    203 => "10111100010101111110010001011000", 
    204 => "10111101000011110000110110000100", 
    205 => "00111100100101000001101001101001", 
    206 => "00111011111101101111110111111001", 
    207 => "10111100100000110001001001101111", 
    208 => "10111100110110011011101000011011", 
    209 => "10111100101010111000011000101011", 
    210 => "10111101000000100101010010100100", 
    211 => "10111101011011110010101001011010", 
    212 => "10111011011101011101101110111010", 
    213 => "10111100100001000010010100101001", 
    214 => "00111100001110111110100001111001", 
    215 => "10111100010111101110011110000010", 
    216 => "10111111100001011110100111100010", 
    217 => "10111101001101111100100010001110", 
    218 => "00111101101010011110011011101111", 
    219 => "00111110000001110000011001001111", 
    220 => "10111100011000010000100011000100", 
    221 => "00111101100111001000000100001010", 
    222 => "00111110000001101110011011011010", 
    223 => "00111101111100100111000100110111", 
    224 => "00111110010101110101111000100000", 
    225 => "00111101010000001010110100000100", 
    226 => "10111100011101000111111110011001", 
    227 => "10111101100110000110100110000011", 
    228 => "00111101000100110101101110010010", 
    229 => "00111010101101011000010110001000", 
    230 => "00111100110111111110010101000011", 
    231 => "10111101100000001110100101001111", 
    232 => "00111101100000001100000101110110", 
    233 => "10111100010111001010110100010101", 
    234 => "00111011100111001011100000110010", 
    235 => "00111100101111100111110100010011", 
    236 => "10111101100001000100111110100000", 
    237 => "00111101000111001101000010111011", 
    238 => "00111100010001101111011110100001", 
    239 => "00111100010101011011111011100100", 
    240 => "00111110100111001100001110100000", 
    241 => "00111110001000111101110001001000", 
    242 => "00111110001100110000100101000010", 
    243 => "10111101010100001010110011000001", 
    244 => "00111100000010101010100100111100", 
    245 => "00111110000101001101101111100000", 
    246 => "00111101010101001011111100001010", 
    247 => "10111101110000000100011101001110", 
    248 => "00111101110101111110011001110001", 
    249 => "10111101001010010000010101111101", 
    250 => "10111100111111111011100010110010", 
    251 => "10111101000000101110001000110011", 
    252 => "10111101000000010100010100001111", 
    253 => "10111100110010001001101100001111", 
    254 => "00111100001000001111101100100010", 
    255 => "10111101101011011111000011010100", 
    256 => "00111101001001000111010101100000", 
    257 => "10111100101000001011100000000110", 
    258 => "10111101101101110001110010010111", 
    259 => "10111100101110010000011001000110", 
    260 => "00111101001010100001101101011100", 
    261 => "00111100110111000110011111100000", 
    262 => "00111101110010101111011100001010", 
    263 => "10111101111110101011011101010110", 
    264 => "00111110001000011111100111110000", 
    265 => "00111101110100101111000110101010", 
    266 => "00111100100001011010010011110000", 
    267 => "10111110011101100001000100110100", 
    268 => "10111101101010000110000011011101", 
    269 => "10111100111100111111010100110000", 
    270 => "00111110010100101001010111101010", 
    271 => "00111101101000001011000110111100", 
    272 => "00111100111111110101000111110000", 
    273 => "10111101101011011110101110010110", 
    274 => "00111100010101110011100001100001", 
    275 => "10111100110011110100111010000111", 
    276 => "10111101111001100100110000110000", 
    277 => "10111110000000101001011100111001", 
    278 => "10111101011010010001100101101001", 
    279 => "10111101010000001000010000011111", 
    280 => "10111101100000011001001100101101", 
    281 => "00111011001111101011000010101010", 
    282 => "10111101010011110010000101110001", 
    283 => "00111100010111001111000000110000", 
    284 => "10111100011111111001001011110011", 
    285 => "00111101100110010111011001111001", 
    286 => "00111101001100111101011011000111", 
    287 => "10111100101010010101110010000101", 
    288 => "00111111000100100100101111011100", 
    289 => "00111110100100010000010011010101", 
    290 => "00111101110110101010111101111001", 
    291 => "10111110111111010101101110101011", 
    292 => "10111110011011111011001010101011", 
    293 => "10111101101111110001010010011000", 
    294 => "10111101101101011001000000111010", 
    295 => "00111101011011100110110010001111", 
    296 => "00111110001001000001101100110011", 
    297 => "10111110000111001001110001001110", 
    298 => "10111101111010111100111010000101", 
    299 => "00111101100011000001001000100111", 
    300 => "00111101101010001001011111101010", 
    301 => "00111101011110110101110100000011", 
    302 => "10111101001101101000110111111100", 
    303 => "10111110011100011100000110010100", 
    304 => "10111101111000001000000001110011", 
    305 => "10111101110011011100001100110111", 
    306 => "10111011100101101000011110010110", 
    307 => "10111101011101101001100001111000", 
    308 => "00111101100010011011001100000111", 
    309 => "10111110100011011001101010010101", 
    310 => "00111101000101101111110110101000", 
    311 => "00111101000100111001000000000000", 
    312 => "00111101010010111110010000000100", 
    313 => "00111101111000110110100011110001", 
    314 => "00111101101011011011101011010100", 
    315 => "00111101011001000111010101100000", 
    316 => "00111101000110001100101100001000", 
    317 => "10111101101011010010011011111010", 
    318 => "00111101101010100000011011101010", 
    319 => "00111011011101100111000100001011", 
    320 => "10111100110101010101110001010011", 
    321 => "00111101001000000010101001111000", 
    322 => "00111011101101100001101000000011", 
    323 => "00111101110101100101001010111101", 
    324 => "00111101100111100011110010010111", 
    325 => "10111101000000111101111011101000", 
    326 => "10111101110010010000110001001110", 
    327 => "00111100011000110001100100111111", 
    328 => "00111101100011100100110000001110", 
    329 => "00111101011111110000110111000111", 
    330 => "00111011011000101111101000110110", 
    331 => "10111101000010110011011100000000", 
    332 => "10111100010010000111100110000001", 
    333 => "00111100111001011010001101011101", 
    334 => "00111011011011110000001010000010", 
    335 => "00111100101111001111111101100101", 
    336 => "10111111000001001000100101001100", 
    337 => "00111110101010011111111010000111", 
    338 => "00111110010101111100011011111100", 
    339 => "10111101100100001110001101000111", 
    340 => "00111110110111011001011010100111", 
    341 => "00111101100010110011111101100100", 
    342 => "00111110000010110110110110000111", 
    343 => "00111011010100111000111010001000", 
    344 => "10111110101111100100011110011001", 
    345 => "00111100000011010100010111001110", 
    346 => "10111110001001110110011101001101", 
    347 => "10111110011010000001011011110000", 
    348 => "00111101110000111101110101010101", 
    349 => "10111100111100100100010100101100", 
    350 => "10111101101101100000000101111001", 
    351 => "00111101000100011011011100010111", 
    352 => "10111101100000000111000010111001", 
    353 => "10111100001001101110111111000011", 
    354 => "00111101001110011100011000101010", 
    355 => "10111101010100000100011100001011", 
    356 => "00111101110011110101110000101001", 
    357 => "10111110010001010010000101010111", 
    358 => "10111101110111001111101010101101", 
    359 => "00111001111001010001111001111101", 
    360 => "00111111001101110001110010010111", 
    361 => "00111110001011100110100001011110", 
    362 => "00111101100100110000001011110111", 
    363 => "00111110001110011010010000010110", 
    364 => "00111101000101011101110001000000", 
    365 => "00111100100000100001101011111000", 
    366 => "10111110010011110100010010010001", 
    367 => "10111101001010011011010010011010", 
    368 => "10111110010011000100100110111010", 
    369 => "00111101001110101101110000001010", 
    370 => "00111100100010010111111010011001", 
    371 => "00111100111000110111011110011111", 
    372 => "00111100111101010001100010110001", 
    373 => "10111100000100011010101111111010", 
    374 => "10111101000111110001111000001000", 
    375 => "00111101010101011101111101100101", 
    376 => "10111100011010011101000011101010", 
    377 => "00111100101100010101110101110000", 
    378 => "10111100100100100101011110000110", 
    379 => "00111101111000000110011000111100", 
    380 => "10111101000110101110000111001110", 
    381 => "10111100111101110001100001100101", 
    382 => "10111100110010100110001000100100", 
    383 => "10111101000101101110110111101110" );


begin 


memory_access_guard_0: process (addr0) 
begin
      addr0_tmp <= addr0;
--synthesis translate_off
      if (CONV_INTEGER(addr0) > mem_size-1) then
           addr0_tmp <= (others => '0');
      else 
           addr0_tmp <= addr0;
      end if;
--synthesis translate_on
end process;

p_rom_access: process (clk)  
begin 
    if (clk'event and clk = '1') then
        if (ce0 = '1') then 
            q0 <= mem(CONV_INTEGER(addr0_tmp)); 
        end if;
    end if;
end process;

end rtl;

Library IEEE;
use IEEE.std_logic_1164.all;

entity LoopOracle_FCW5 is
    generic (
        DataWidth : INTEGER := 32;
        AddressRange : INTEGER := 384;
        AddressWidth : INTEGER := 9);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of LoopOracle_FCW5 is
    component LoopOracle_FCW5_rom is
        port (
            clk : IN STD_LOGIC;
            addr0 : IN STD_LOGIC_VECTOR;
            ce0 : IN STD_LOGIC;
            q0 : OUT STD_LOGIC_VECTOR);
    end component;



begin
    LoopOracle_FCW5_rom_U :  component LoopOracle_FCW5_rom
    port map (
        clk => clk,
        addr0 => address0,
        ce0 => ce0,
        q0 => q0);

end architecture;

