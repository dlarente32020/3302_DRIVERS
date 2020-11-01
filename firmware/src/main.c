/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include "tlc59xx.h"


// *****************************************************************************
// *****************************************************************************
// Section: Defines
// *****************************************************************************
// *****************************************************************************

// uncomment the drivers that will be used in your project
#define USE_TLC5941Q1_DRIVER
//#define USE_TLC5947_DRIVER


// *****************************************************************************
// *****************************************************************************
// Section: Local Variables
// *****************************************************************************
// *****************************************************************************

// todo: add here the local variables
bool new_period_trigger = false;

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
#ifdef USE_TLC5941Q1_DRIVER
    uint8_t dc_data_register[TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP] = {
    //  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15
        0x11, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,     // chip00
        0x22, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,     // chip01
        0x11, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,     // chip02
        0x22, 0x00, 0x00, 0x00, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F,     // chip03
    };

    uint8_t gs_data_register[TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP] = {
    //  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15
        0x00, 0x22, 0x00, 0x44, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,     // chip00
        0x00, 0x22, 0x00, 0x44, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,     // chip01
        0x00, 0x22, 0x00, 0x44, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00,     // chip02
        0x00, 0x22, 0x00, 0x44, 0x00, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF,     // chip03
    };

    tlc5941q1_interface_t tlc5941q1_interface;
    tlc5941q1_t tlc5941q1_driver;

#endif

#ifdef USE_TLC5947_DRIVER
    uint8_t gs_data_register[TLC5947_NO_OF_CHIPS * TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP] = {
    //  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15  ch16  ch17  ch18  ch19  ch20  ch21
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x33, 0x66, 0x99, 0xCC, 0xFF, 0x00, 0x00,     // chip00
    };

    tlc5947_interface_t tlc5947_interface;
    tlc5947_t tlc5947_driver;

#endif

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // start systick timer @ 1ms period
    SYSTICK_TimerStart();
    
#ifdef USE_TLC5941Q1_DRIVER
    tlc5941q1_interface.blank = BLANK_PIN;
    tlc5941q1_interface.xlat = XLAT_PIN;
    tlc5941q1_interface.mode = MODE_PIN;
    tlc5941q1_interface.spi_mosi = SPI5_MOSI_PIN;
    tlc5941q1_interface.spi_sclk = SPI5_SCLK_PIN;
    tlc5941q1_interface.spi_miso = SPI5_MISO_PIN;
    
    tlc5941q1_interface.sercom_instance = SERCOM5;
    TLC5941Q1InitStruct(&tlc5941q1_driver, &tlc5941q1_interface);
#endif
    
#ifdef USE_TLC5947_DRIVER
    tlc5947_interface.blank = BLANK_PIN;
    tlc5947_interface.xlat = XLAT_PIN;
    
    tlc5947_interface.sercom_instance = SERCOM5;
    
    TLC5947InitStruct(&tlc5947_driver, &tlc5947_interface);
    
    TLC5947UpdateCommonShiftRegister(&tlc5947_driver, gs_data_register);
    TLC5947WriteData(&tlc5947_driver);
#endif
    
    while ( true )
    {
#ifdef USE_TLC5941Q1_DRIVER
      if (new_period_trigger == true) {
          TLC5941Q1UpdateCommonShiftRegister(&tlc5941q1_driver, MODE_GS, gs_data_register);
          TLC5941Q1WriteData(&tlc5941q1_driver, MODE_GS);
          
          new_period_trigger = false;
      }
#endif

    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

