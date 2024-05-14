-- ======================================================================
-- SysTick_Example02.ctl generated from SysTick_Example02
-- 05/14/2024 at 13:44
-- This file is auto generated. ANY EDITS YOU MAKE MAY BE LOST WHEN THIS FILE IS REGENERATED!!!
-- ======================================================================

-- TopDesign
-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-044 kit.
-- =============================================================================

-- === UART ===
attribute port_location of \UART:rx(0)\ : label is "PORT(7,0)";
attribute port_location of \UART:tx(0)\ : label is "PORT(7,1)";

-- === I2C ===
attribute port_location of \I2C:scl(0)\ : label is "PORT(4,0)";
attribute port_location of \I2C:sda(0)\ : label is "PORT(4,1)";

-- === RGB LED ===
attribute port_location of LED_Min(0) : label is "PORT(0,6)"; -- RED LED
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(2,6)"; -- GREEN LED
attribute port_location of LED_Sec(0) : label is "PORT(6,5)"; -- BLUE LED

-- === USER SWITCH ===
attribute port_location of REPLACE_WITH_ACTUAL_PIN_NAME(0) : label is "PORT(0,7)";
-- PSoC Clock Editor
-- Directives Editor
-- Analog Device Editor
