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
#include "cocann.h"

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

uint8_t dummy_gs_register_1B[22] = {
    0x00,   // gs[0]
    0xFF,   // gs[1]
    0x00,   // gs[2]
    0xFF,   // gs[3]
    0x00,   // gs[4]
    0xFF,   // gs[5]
    0x00,   // gs[6]
    0xFF,   // gs[7]
    0x00,   // gs[8]
    0xFF,   // gs[9]
    0x00,   // gs[10]
    0xFF,   // gs[11]
    0x00,   // gs[12]
    0xFF,   // gs[13]
    0x00,   // gs[14]
    0xFF,   // gs[15]
    0x00,   // gs[16]
    0xFF,   // gs[17]
    0x00,   // gs[18]
    0xFF,   // gs[19]
    0x00,   // gs[20]
    0xFF    // gs[21]
};

uint16_t dummy_gs_register_2B[22] = {
    0x0111, // gs[0]
    0x0000, // gs[1]
    0x0222, // gs[2]
    0x0000, // gs[3]
    0x0333, // gs[4]
    0x0000, // gs[5]
    0x0444, // gs[6]
    0x0000, // gs[7]
    0x0555, // gs[8]
    0x0000, // gs[9]
    0x0666, // gs[10]
    0x0000, // gs[11]
    0x0777, // gs[12]
    0x0000, // gs[13]
    0x0888, // gs[14]
    0x0000, // gs[15]
    0x0999, // gs[16]
    0x0000, // gs[17]
    0x0AAA, // gs[18]
    0x0000, // gs[19]
    0x0BBB, // gs[20]
    0x0000  // gs[21]
};

uint8_t dummy_cs_register[36] = {
    0x00,   // csr[0]
    0x00,   // csr[1]
    0x00,   // csr[2]
    0x00,   // csr[3]
    0x00,   // csr[4]
    0x00,   // csr[5]
    0x00,   // csr[6]
    0x00,   // csr[7]
    0x00,   // csr[8]
    0x00,   // csr[9]
    0x00,   // csr[10]
    0x00,   // csr[11]
    0x00,   // csr[12]
    0x00,   // csr[13]
    0x00,   // csr[14]
    0x00,   // csr[15]
    0x00,   // csr[16]
    0x00,   // csr[17]
    0x00,   // csr[18]
    0x00,   // csr[19]
    0x00,   // csr[20]
    0x00,   // csr[21]
    0x00,   // csr[22]
    0x00,   // csr[23]
    0x00,   // csr[24]
    0x00,   // csr[25]
    0x00,   // csr[26]
    0x00,   // csr[27]
    0x00,   // csr[28]
    0x00,   // csr[29]
    0x00,   // csr[30]
    0x00,   // csr[31]
    0x00,   // csr[32]
    0x00,   // csr[33]
    0x00,   // csr[34]
    0x00    // csr[35]
    
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
