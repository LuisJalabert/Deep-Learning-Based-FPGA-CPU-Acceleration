-- ==============================================================
-- File generated on Thu Apr 04 23:06:48 CEST 2019
-- Vivado(TM) HLS - High-Level Synthesis from C, C++ and SystemC v2018.3 (64-bit)
-- SW Build 2405991 on Thu Dec  6 23:36:41 MST 2018
-- IP Build 2404404 on Fri Dec  7 01:43:56 MST 2018
-- Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
-- ==============================================================
library ieee; 
use ieee.std_logic_1164.all; 
use ieee.std_logic_unsigned.all;

entity LoopOracle_C2W2_rom is 
    generic(
             DWIDTH     : integer := 32; 
             AWIDTH     : integer := 5; 
             MEM_SIZE    : integer := 32
    ); 
    port (
          addr0      : in std_logic_vector(AWIDTH-1 downto 0); 
          ce0       : in std_logic; 
          q0         : out std_logic_vector(DWIDTH-1 downto 0);
          clk       : in std_logic
    ); 
end entity; 


architecture rtl of LoopOracle_C2W2_rom is 

signal addr0_tmp : std_logic_vector(AWIDTH-1 downto 0); 
type mem_array is array (0 to MEM_SIZE-1) of std_logic_vector (DWIDTH-1 downto 0); 
signal mem : mem_array := (
    0 => "00111110100000000010011101010010", 
    1 => "00111111000100010000011000100101", 
    2 => "00111011011010111110110111111010", 
    3 => "00111110110010111110000011011111", 
    4 => "00111101101111110001010000010010", 
    5 => "10111110010101101101010111010000", 
    6 => "10111110101101010000101100001111", 
    7 => "00111101101111001001111011101101", 
    8 => "00111101100101111100000110111110", 
    9 => "00111110010111011001011111110110", 
    10 => "10111110001100011111100010100001", 
    11 => "10111110101010100111000111011110", 
    12 => "00111111000101010110110101011101", 
    13 => "00111110101011111100010100000101", 
    14 => "10111101100011010001101101110001", 
    15 => "10111110101110111011001011111111", 
    16 => "10111110011001111010000011111001", 
    17 => "10111110100011101011111011100000", 
    18 => "10111110001010110000001000001100", 
    19 => "10111110010100000100100000010111", 
    20 => "10111110100100111011011001000110", 
    21 => "10111110000001011011110000000010", 
    22 => "10111110100111010010000111111111", 
    23 => "10111110100001110100010100111001", 
    24 => "10111110101101100001111001001111", 
    25 => "10111110001100001011111000001110", 
    26 => "10111110110001100010010011011101", 
    27 => "00111110111000110000010101010011", 
    28 => "10111111000000001111111110010111", 
    29 => "00111101100001100101100101001011", 
    30 => "00111110111010000000100111010101", 
    31 => "00111110000111000000111010111111" );


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

entity LoopOracle_C2W2 is
    generic (
        DataWidth : INTEGER := 32;
        AddressRange : INTEGER := 32;
        AddressWidth : INTEGER := 5);
    port (
        reset : IN STD_LOGIC;
        clk : IN STD_LOGIC;
        address0 : IN STD_LOGIC_VECTOR(AddressWidth - 1 DOWNTO 0);
        ce0 : IN STD_LOGIC;
        q0 : OUT STD_LOGIC_VECTOR(DataWidth - 1 DOWNTO 0));
end entity;

architecture arch of LoopOracle_C2W2 is
    component LoopOracle_C2W2_rom is
        port (
            clk : IN STD_LOGIC;
            addr0 : IN STD_LOGIC_VECTOR;
            ce0 : IN STD_LOGIC;
            q0 : OUT STD_LOGIC_VECTOR);
    end component;



begin
    LoopOracle_C2W2_rom_U :  component LoopOracle_C2W2_rom
    port map (
        clk => clk,
        addr0 => address0,
        ce0 => ce0,
        q0 => q0);

end architecture;


