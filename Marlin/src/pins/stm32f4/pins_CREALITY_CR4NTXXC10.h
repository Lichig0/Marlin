/**
 * Marlin 3D Printer Firmware
 * Copyright (c) 2023 MarlinFirmware [https://github.com/MarlinFirmware/Marlin]
 *
 * Based on Sprinter and grbl.
 * Copyright (c) 2011 Camiel Gubbels / Erik van der Zalm
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

/**
 * Creality CREALITY_CR4NTXXC10 (STM32F401RET6) board pin assignments
 *
 * Sold as "E3 Free-runs Silent Motherboard"
 */
#include "env_validate.h"

#if HOTENDS > 1 || E_STEPPERS > 1
  #error "CR4NT220622C10 only supports one hotend / E-stepper."
#endif

#if !AXIS_DRIVER_TYPE_X(TMC2209) || !AXIS_DRIVER_TYPE_Y(TMC2209) || !AXIS_DRIVER_TYPE_Z(TMC2209) || !AXIS_DRIVER_TYPE_E0(TMC2209)
  #error "This board has onboard TMC2209 drivers for X, Y, Z, and E0."
#endif

#ifndef BOARD_INFO_NAME
  #define BOARD_INFO_NAME      "CR4NT220622C10"
#endif
#ifndef DEFAULT_MACHINE_NAME
  #define DEFAULT_MACHINE_NAME "Ender-3 Series"
#endif
#define BOARD_WEBSITE_URL      "www.creality.com"

#define BOARD_NO_NATIVE_USB
//#undef DISABLE_DEBUG                            // DISABLE_(DEBUG|JTAG) is not supported for STM32F4.
//#define DISABLE_JTAG

//
// EEPROM
//
#if NO_EEPROM_SELECTED
  #define IIC_BL24CXX_EEPROM                      // EEPROM on I2C-0
  //#define SDCARD_EEPROM_EMULATION
  #undef NO_EEPROM_SELECTED
#endif

#if ENABLED(IIC_BL24CXX_EEPROM)
  #define IIC_EEPROM_SDA                    PA11
  #define IIC_EEPROM_SCL                    PA12
  #define MARLIN_EEPROM_SIZE                0x800  // 2K (24C16)
#elif ENABLED(SDCARD_EEPROM_EMULATION)
  #define MARLIN_EEPROM_SIZE                0x800  // 2K
#endif

//
// Servos
//
#define SERVO0_PIN                          PB0   // BLTouch PWM-OUT PIN (TOUCH pins in the schematic have changed)

//
// Limit Switches
//
#define X_STOP_PIN                          PA5
#define Y_STOP_PIN                          PA6

#if ENABLED(BLTOUCH)
  #define Z_MIN_PIN                         PB1   // BLTouch IN PIN (TOUCH pins in the schematic have changed)
  #define Z_MAX_PIN                         PA7
#else
  #define Z_STOP_PIN                        PA7   // Z-axis limit switch
#endif

#ifndef Z_MIN_PROBE_PIN
  #define Z_MIN_PROBE_PIN                   PB1   // BLTouch IN
#endif

//
// Filament Runout Sensor
//
#ifndef FIL_RUNOUT_PIN
  #define FIL_RUNOUT_PIN                    PA4   // "Pulled-high"
#endif

//
// Steppers
//
#define X_ENABLE_PIN                        PC3
#define X_STEP_PIN                          PC2
#define X_DIR_PIN                           PB9

#define Y_ENABLE_PIN               X_ENABLE_PIN
#define Y_STEP_PIN                          PB8
#define Y_DIR_PIN                           PB7

#define Z_ENABLE_PIN               X_ENABLE_PIN
#define Z_STEP_PIN                          PB6
#define Z_DIR_PIN                           PB5

#define E0_ENABLE_PIN              X_ENABLE_PIN
#define E0_STEP_PIN                         PB4
#define E0_DIR_PIN                          PB3

//
// Temperature Sensors
//
#define TEMP_0_PIN                          PC5   // TH1
#define TEMP_BED_PIN                        PC4   // TB1

//
// Heaters / Fans
//
#define HEATER_0_PIN                        PA1   // HEATER1
#define HEATER_BED_PIN                      PB10  // HOT BED

#ifndef FAN0_PIN
  #define FAN0_PIN                          PA0   // FAN
#endif
#if PIN_EXISTS(FAN0)
  #define FAN_SOFT_PWM
#endif

#if HAS_TMC_UART
  // Reduce baud rate to improve software serial reliability
  #define TMC_BAUD_RATE 19200

  /**
   * TMC2208/TMC2209 stepper drivers
   *
   * Hardware serial communication ports.
   * If undefined software serial is used according to the pins below
   */
  #define X_HARDWARE_SERIAL  Serial6
  #define Y_HARDWARE_SERIAL  X_HARDWARE_SERIAL
  #define Z_HARDWARE_SERIAL  X_HARDWARE_SERIAL
  #define E0_HARDWARE_SERIAL X_HARDWARE_SERIAL

  #ifndef X_SLAVE_ADDRESS
    #define X_SLAVE_ADDRESS                   0
  #endif
  #ifndef Y_SLAVE_ADDRESS
    #define Y_SLAVE_ADDRESS                   1
  #endif
  #ifndef Z_SLAVE_ADDRESS
    #define Z_SLAVE_ADDRESS                   2
  #endif
  #ifndef E0_SLAVE_ADDRESS
    #define E0_SLAVE_ADDRESS                  3
  #endif

  // Software serial

  #define X_SERIAL_TX_PIN                   PC6
  #define X_SERIAL_RX_PIN                   PC7

  #define Y_SERIAL_TX_PIN        X_SERIAL_TX_PIN
  #define Y_SERIAL_RX_PIN        X_SERIAL_RX_PIN

  #define Z_SERIAL_TX_PIN        X_SERIAL_TX_PIN
  #define Z_SERIAL_RX_PIN        X_SERIAL_RX_PIN

  #define E0_SERIAL_TX_PIN       X_SERIAL_TX_PIN
  #define E0_SERIAL_RX_PIN       X_SERIAL_RX_PIN

  #define E1_SERIAL_TX_PIN       X_SERIAL_TX_PIN
  #define E1_SERIAL_RX_PIN       X_SERIAL_RX_PIN

  #define X_DIAG_PIN                        PC13
  #define Y_DIAG_PIN                        PC14
  #define Z_DIAG_PIN                        PC15
  #define E0_DIAG_PIN                       PA15

#endif // HAS_TMC_UART

//
// SD Card
//
#define SD_DETECT_PIN                       PC1
#define SDCARD_CONNECTION                ONBOARD
#define ONBOARD_SPI_DEVICE                     1
//#define ONBOARD_SD_CS_PIN                 PA4   // SDSS
#define SDIO_SUPPORT
#define NO_SD_HOST_DRIVE                  // This board's SD is only seen by the printer

#if ENABLED(CR10_STOCKDISPLAY)

  #if ENABLED(RET6_12864_LCD)
    // RET6 12864 LCD
    #define LCD_PINS_RS                     PB12
    #define LCD_PINS_EN                     PB15
    #define LCD_PINS_D4                     PB13

    #define BTN_ENC                         PB2
    #define BTN_EN1                         PA2
    #define BTN_EN2                         PB14

    #ifndef HAS_PIN_27_BOARD
      #define BEEPER_PIN                    PC0
    #endif

  #elif ENABLED(VET6_12864_LCD)
    // VET6 12864 LCD
    #define LCD_PINS_RS                     PA4
    //#define LCD_PINS_EN                   PA7
    #define LCD_PINS_D4                     PA5

    #define BTN_ENC                         PC5
    #define BTN_EN1                         PB10
    #define BTN_EN2                         PA6

  #else
    #error "Define RET6_12864_LCD or VET6_12864_LCD to select pins for CR10_STOCKDISPLAY with the CREALITY_CR4NTXXC10 controller."
  #endif

#elif ENABLED(DWIN_CREALITY_LCD)

  // RET6 DWIN ENCODER LCD
  #define BTN_ENC                           PB14
  #define BTN_EN1                           PB15
  #define BTN_EN2                           PB12

  //#define LCD_LED_PIN                     PB2
  #ifndef BEEPER_PIN
    #define BEEPER_PIN                      PB13
    #undef SPEAKER
  #endif

#elif ENABLED(DWIN_VET6_CREALITY_LCD)

  // VET6 DWIN ENCODER LCD
  #define BTN_ENC                           PA6
  //#define BTN_EN1                         PA7
  #define BTN_EN2                           PA4

  #define BEEPER_PIN                        PA5

#endif

//
// M3/M4/M5 - Spindle/Laser Control
//
#if HAS_CUTTER
  //#undef HEATER_0_PIN
  //#undef HEATER_BED_PIN
  //#undef FAN0_PIN
  #define SPINDLE_LASER_ENA_PIN             PC0   // FET 1
  #define SPINDLE_LASER_PWM_PIN             PC0   // Bed FET
  #define SPINDLE_DIR_PIN                   PC0   // FET 4
  //#define LASER_SOFT_PWM_PIN              PC0
#endif
