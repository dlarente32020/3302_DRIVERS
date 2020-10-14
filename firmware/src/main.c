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

#include "cocann.h"
#include "tlc5947.h"


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

uint8_t receiver[36];

tlc5947_interface_t tlc5947_interface;
tlc5947_t tlc5947_driver;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    
    // start systick timer @ 1ms period
    SYSTICK_TimerStart();
    
    // tlc5947 driver init
    tlc5947_interface.xlat = XLAT_PIN;
    tlc5947_interface.blank = BLANK_PIN;
    tlc5947_interface.sercom_instance = SERCOM5;

    TLC5947InitStruct(&tlc5947_driver, &tlc5947_interface);
    
    while ( true )
    {
        TLC5947UpdateCommonShiftRegister(&tlc5947_driver, dummy_gs_register_2B);
        TLC5947WriteData(&tlc5947_driver);
        SYSTICK_DelayMs(1000);
                
        /*
        tlc5947_driver.SPI_WriteRead(common_shift_register, 36u, receiver, 36u);
        SYSTICK_DelayMs(1000);
         */
        
        /*
        PORT_PinToggle(tlc5947_driver.blank);
        
        PORT_PinWrite(tlc5947_driver.blank, TRUE);
        PORT_PinWrite(tlc5947_driver.xlat, FALSE);
        SYSTICK_DelayMs(10);
        
        PORT_PinWrite(tlc5947_driver.blank, FALSE);
        PORT_PinWrite(tlc5947_driver.xlat, TRUE);
        SYSTICK_DelayMs(10);
         */
        
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        //SYS_Tasks ( );
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

