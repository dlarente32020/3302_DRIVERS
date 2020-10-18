/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Adam Electronics, Inc.

  @File Name
    tlc5941q1.h

  @Summary
    TLC5941-Q1, Texas Instruments PWM controller IC header file

  @Description
    ::todo::

 */
/* ************************************************************************** */

#ifndef _TLC5941Q1_H    /* Guard against multiple inclusion */
#define _TLC5941Q1_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <xc.h>

#include "definitions.h"
#include "tlc59xx.h"

/* Provide C++ Compatibility */
#ifdef __cplusplus
extern "C" {
#endif


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Constants                                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */


/* ************************************************************************** */
/** Descriptive Constant Name

  @Summary
    Brief one-line summary of the constant.

  @Description
    Full description, explaining the purpose and usage of the constant.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Remarks
    Any additional remarks

#define EXAMPLE_CONSTANT 0
    
*/
/* ===== USER DATA ===========================================================*/
// no of daisy-chained chips
#define TLC5941Q1_NO_OF_CHIPS                     (1u)
//
#define TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP  (16u)
    
// size of gs data register location (GS_SIZE_1B for 8-bit or GS_SIZE_2B for 16-bit)
#define TLC5941Q1_GS_DATA_SIZE                    (GS_SIZE_2B)
// is gs inverted? (inverted = max value corresponds to minimum duty-cycle))
#define TLC5941Q1_IS_GS_DATA_INVERTED             (FALSE)
/* ========================================================================== */

/* ===== DRIVER DATA - DO NOT TOUCH ==========================================*/
// no of output channels per chip
#define TLC5941Q1_NO_OF_CHANNELS_PER_CHIP         (16u)

// no of bits used to represent gs data per channel
#define TLC5941Q1_NO_OF_GS_BITS_PER_CHANNEL       (12u)
// no of bits used to represent dc data per channel
#define TLC5941Q1_NO_OF_DC_BITS_PER_CHANNEL       (6u)

#define TLC5941Q1_NO_OF_BITS_PER_CSR              (TLC5941Q1_NO_OF_CHANNELS_PER_CHIP * TLC5941Q1_NO_OF_GS_BITS_PER_CHANNEL)
#define TLC5941Q1_NO_OF_BYTES_PER_CSR             (TLC5941Q1_NO_OF_BITS_PER_CSR / (8u))
// total number of bytes per common shift register (CSR))
#define TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR       (TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_BYTES_PER_CSR)

// gs data register length
#define TLC5941Q1_GS_DATA_REGISTER_LENGTH         (TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP)

#define TLC5941Q1_DC_DATA_MIN_VALUE               (0x00U)
#define TLC5941Q1_DC_DATA_MAX_VALUE               (0x3FU)
#define TLC5941Q1_GS_DATA_MIN_VALUE               (0x000U)
#define TLC5941Q1_GS_DATA_MAX_VALUE               (0xFFFU)
    
#define TLC5941Q1_GS_DATA_INVERT(crt_value)       (TLC5941Q1_GS_DATA_MAX_VALUE-crt_value)
/* ========================================================================== */
    
// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */


// *****************************************************************************

/** Descriptive Data Type Name

  @Summary
    Brief one-line summary of the data type.

  @Description
    Full description, explaining the purpose and usage of the data type.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Remarks
    Any additional remarks
    <p>
    Describe enumeration elements and structure and union members above each 
    element or member.

typedef struct _example_struct_t {
    // Describe structure member.
    int some_number;

    // Describe structure member.
    bool some_flag;

} example_struct_t;

*/

typedef enum {
    MODE_GS = (0u),
    MODE_DC = (1u)
            
} input_mode_t;
    
typedef struct _tlc5941q1_interface_t {
    // PORT_PIN_PAxx or PORT_PIN_PBxx, where xx is the pin number (e.g. PORT_PIN_PA04, PORT_PIN_PB15)
    PORT_PIN xlat;
    PORT_PIN blank;
    PORT_PIN mode;
    
    // SERCOM0 to SERCOM5 (for ATSAMC21J18A)
    sercom_instance_t sercom_instance;

} tlc5941q1_interface_t;

typedef struct _tlc5941q1_t {
    
    PORT_PIN xlat;
    PORT_PIN blank;
    PORT_PIN mode;
    
    sercom_instance_t sercom_instance;
    bool (*SPI_WriteRead) (void*, size_t, void*, size_t);
    
    uint8_t common_shift_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR];
    uint8_t receive_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR];
   
} tlc5941q1_t;

// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************
/**
  @Function
    int ExampleFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Description
    Full description, explaining the purpose and usage of the function.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.

  @Precondition
    List and describe any required preconditions. If there are no preconditions,
    enter "None."

  @Parameters
    @param param1 Describe the first parameter to the function.

    @param param2 Describe the second parameter to the function.

  @Returns
    List (if feasible) and describe the return values of the function.
    <ul>
      <li>1   Indicates an error occurred
      <li>0   Indicates an error did not occur
    </ul>

  @Remarks
    Describe any special behavior not described above.
    <p>
    Any additional remarks.

  @Example
    @code
    if(ExampleFunctionName(1, 2) == 0)
    {
        return 3;
    }

int ExampleFunction(int param1, int param2);

*/

// init the tlc5941q1 data structure
status_t TLC5941Q1InitStruct(tlc5941q1_t *driver, tlc5941q1_interface_t *interface);

// build the CSR from a value
status_t TLC5941Q1SetCommonShiftRegisterToValue(tlc5941q1_t *driver, input_mode_t mode, uint16_t new_value);

// build the CSR from an array of values
status_t TLC5941Q1UpdateCommonShiftRegister(tlc5941q1_t *driver, input_mode_t mode, void *data_register);

// writes the gs data into tlc5947q1 chip via SPI
status_t TLC5941Q1WriteData(tlc5941q1_t *driver, input_mode_t mode);

/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _TLC5941Q1_H */

/* *****************************************************************************
 End of File
 */
