/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Adam Electronics, Inc.

  @File Name
    cocann.c

  @Summary
    cocann.c source file

  @Description
    ::todo::
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "tlc59xx.h"

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: File Scope or Global Data                                         */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */
/** Descriptive Data Item Name

  @Summary
    Brief one-line summary of the data item.
    
  @Description
    Full description, explaining the purpose and usage of data item.
    <p>
    Additional description in consecutive paragraphs separated by HTML 
    paragraph breaks, as necessary.
    <p>
    Type "JavaDoc" in the "How Do I?" IDE toolbar for more information on tags.
    
  @Remarks
    Any additional remarks

int global_data;

 */

uint8_t tlc5947_dummy_gs_register_1B[TLC5947_NO_OF_CHIPS*TLC5947_NO_OF_ACTIVE_CHANNELS] = {
//  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15  ch16  ch17  ch18  ch19  ch20  ch21
    0x11, 0x00, 0x22, 0x00, 0x33, 0x00, 0x44, 0x00, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00, 0x88, 0x00, 0x99, 0x00, 0xAA, 0x00, 0xBB, 0x00  // chip00
//  0x11, 0x00, 0x22, 0x00, 0x33, 0x00, 0x44, 0x00, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00, 0x88, 0x00, 0x99, 0x00, 0xAA, 0x00, 0xBB, 0x00,  // chip01
//  0x11, 0x00, 0x22, 0x00, 0x33, 0x00, 0x44, 0x00, 0x55, 0x00, 0x66, 0x00, 0x77, 0x00, 0x88, 0x00, 0x99, 0x00, 0xAA, 0x00, 0xBB, 0x00   // chip01
};
uint16_t tlc5947_dummy_gs_register_2B[TLC5947_NO_OF_CHIPS*TLC5947_NO_OF_ACTIVE_CHANNELS] = {
//  ch00    ch01    ch02    ch03    ch04    ch05    ch06    ch07    ch08    ch09    ch10    ch11    ch12    ch13    ch14    ch15    ch16    ch17    ch18    ch19    ch20    ch21
    0x0111, 0x0000, 0x0222, 0x0000, 0x0333, 0x0000, 0x0444, 0x0000, 0x0555, 0x0000, 0x0666, 0x0000, 0x0777, 0x0000, 0x0888, 0x0000, 0x0999, 0x0000, 0x0AAA, 0x0000, 0x0BBB, 0x0000  // chip00
//  0x0111, 0x0000, 0x0222, 0x0000, 0x0333, 0x0000, 0x0444, 0x0000, 0x0555, 0x0000, 0x0666, 0x0000, 0x0777, 0x0000, 0x0888, 0x0000, 0x0999, 0x0000, 0x0AAA, 0x0000, 0x0CCC, 0x0000,  // chip01
//  0x0111, 0x0000, 0x0222, 0x0000, 0x0333, 0x0000, 0x0444, 0x0000, 0x0555, 0x0000, 0x0666, 0x0000, 0x0777, 0x0000, 0x0888, 0x0000, 0x0999, 0x0000, 0x0AAA, 0x0000, 0x0DDD, 0x0000  // chip02
};

uint8_t tlc5941q1_dummy_dc_register[TLC5941Q1_NO_OF_CHIPS*TLC5941Q1_NO_OF_ACTIVE_CHANNELS] = {
//  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15
    0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16,  // chip00
//    0x17, 0x18, 0x19, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x30, 0x31, 0x32   // chip01
};
uint8_t tlc5941q1_dummy_gs_register_1B[TLC5941Q1_NO_OF_CHIPS*TLC5941Q1_NO_OF_ACTIVE_CHANNELS] = {
//  ch00  ch01  ch02  ch03  ch04  ch05  ch06  ch07  ch08  ch09  ch10  ch11  ch12  ch13  ch14  ch15
    0x12, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCD, // chip00
//    0x34, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF  // chip01
};
uint16_t tlc5941q1_dummy_gs_register_2B[TLC5941Q1_NO_OF_CHIPS*TLC5941Q1_NO_OF_ACTIVE_CHANNELS] = {
//  ch00    ch01    ch02    ch03    ch04    ch05    ch06    ch07    ch08    ch09    ch10    ch11    ch12    ch13    ch14    ch15
    0x0111, 0x0222, 0x0333, 0x0444, 0x0555, 0x0666, 0x0777, 0x0888, 0x0999, 0x0AAA, 0x0BBB, 0x0CCC, 0x0DDD, 0x0EEE, 0x0FFF, 0x0000 // chip00
//    0x0111, 0x0000, 0x0222, 0x0000, 0x0333, 0x0000, 0x0444, 0x0000, 0x0555, 0x0000, 0x0666, 0x0000, 0x0777, 0x0000, 0x0888, 0x0000, // chip01
};

/* ************************************************************************** */
/* ************************************************************************** */
// Section: Local Functions                                                   */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

/* ************************************************************************** */

/** 
  @Function
    int ExampleLocalFunctionName ( int param1, int param2 ) 

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

static int ExampleLocalFunction(int param1, int param2) {
    return 0;
}

 */


/* ************************************************************************** */
/* ************************************************************************** */
// Section: Interface Functions                                               */
/* ************************************************************************** */
/* ************************************************************************** */

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************

/** 
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.

int ExampleInterfaceFunction(int param1, int param2) {
    return 0;
}

 */

/* *****************************************************************************
 End of File
 */
