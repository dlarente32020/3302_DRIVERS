/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Cocan Nicolae PFA

  @File Name
    cocann.h

  @Summary
    cocann.h header file

  @Description
  ::todo::

 */
/* ************************************************************************** */

#ifndef _COCANN_H    /* Guard against multiple inclusion */
#define _COCANN_H


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
#define TLC5947_NO_OF_CHIPS             (1u)
#define TLC5947_NO_OF_CHANNELS          (24u)
#define TLC5947_NO_OF_ACTIVE_CHANNELS   (22u)    
    
#define TLC5941Q1_NO_OF_CHIPS           (1u)
#define TLC5941Q1_NO_OF_CHANNELS        (16u)
#define TLC5941Q1_NO_OF_ACTIVE_CHANNELS (16u)    

extern uint8_t tlc5947_dummy_gs_register_1B[];
extern uint16_t tlc5947_dummy_gs_register_2B[];

extern uint8_t tlc5941q1_dummy_dc_register[];
extern uint8_t tlc5941q1_dummy_gs_register_1B[];
extern uint16_t tlc5941q1_dummy_gs_register_2B[];
extern bool trigger;

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
    FALSE       = 0u,
    TRUE        = 1u
            
} bool_t;

typedef enum {
    STATUS_OK   = 0u,
    STATUS_NOK  = 1u
            
} status_t;

typedef enum {
    SERCOM0     = 0u,
    SERCOM1     = 1u,
    SERCOM2     = 2u,
    SERCOM3     = 3u,
    SERCOM4     = 4u,
    SERCOM5     = 5u
            
} sercom_instance_t;

typedef enum {
    GS_SIZE_1B = (1u),
    GS_SIZE_2B = (2u)
            
} gs_size_t;

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


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _COCANN_H */

/* *****************************************************************************
 End of File
 */
