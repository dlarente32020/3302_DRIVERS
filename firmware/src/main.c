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
#include "tlc5947.h"
#include "tlc5941q1.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

//#define LED_BOARD_DEMO 
#define MOTOR_BOARD_DEMO 

#ifdef LED_BOARD_DEMO
tlc5941q1_interface_t tlc5941q1_interface;
tlc5941q1_t tlc5941q1_driver;
#endif

#ifdef MOTOR_BOARD_DEMO
tlc5947_interface_t tlc5947_interface;
tlc5947_t tlc5947_driver;
#endif

bool trigger = true;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // start systick timer @ 1ms period
    SYSTICK_TimerStart();

#ifdef LED_BOARD_DEMO
    tlc5941q1_interface.xlat = XLAT_PIN;
    tlc5941q1_interface.blank = BLANK_PIN;
    tlc5941q1_interface.mode = MODE_PIN;
    tlc5941q1_interface.sercom_instance = SERCOM5;
    
    TLC5941Q1InitStruct(&tlc5941q1_driver, &tlc5941q1_interface);
#endif
    
#ifdef MOTOR_BOARD_DEMO
    // tlc5947 driver init
    tlc5947_interface.xlat = XLAT_PIN;
    tlc5947_interface.blank = BLANK_PIN;
    tlc5947_interface.sercom_instance = SERCOM5;
    
    TLC5947InitStruct(&tlc5947_driver, &tlc5947_interface);
#endif
    
    while ( true )
    {

#ifdef LED_BOARD_DEMO
        if (trigger == true) {
            TLC5941Q1UpdateCommonShiftRegister(&tlc5941q1_driver, MODE_GS, tlc5941q1_dummy_gs_register_2B);
            TLC5941Q1WriteData(&tlc5941q1_driver, MODE_GS);
            
            trigger = false;
        }
#endif
        
#ifdef MOTOR_BOARD_DEMO
        TLC5947UpdateCommonShiftRegister(&tlc5947_driver, tlc5947_dummy_gs_register_2B);
        TLC5947WriteData(&tlc5947_driver);
#endif
        //SYSTICK_DelayMs(1000);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

