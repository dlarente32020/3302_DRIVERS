/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Adam Electronics, Inc.

  @File Name
    tlc5947.c

  @Summary
    TLC5947, Texas Instruments PWM controller IC source file

  @Description
    tlc5947 source file
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
  status_t TLC5947InitStruct(tlc5947_t *driver, tlc5947_interface_t *interface)

@Summary
  initialization function for the tlc5947_t data structure

@Description
  this function is used to initialize a tlc5947_t data structure based on a tlc5947_interface_t data structure
  <p>

@Precondition
  the tlc5947_interface_t data structure has to be initialized

@Parameters
  @param *driver - pointer to a tlc5947_t data structure

  @param *interface - pointer to a tlc5947_interface_t data structure

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5947InitStructure(&tlc5947_driver, &tlc5947_interface);
*/
status_t TLC5947InitStruct(tlc5947_t *driver, tlc5947_interface_t *interface)
{
    driver->xlat = interface->xlat;
    driver->blank = interface->blank;
    driver->sercom_instance = interface->sercom_instance;
    
    switch (driver->sercom_instance)
    {
        case SERCOM0:
#ifdef PLIB_SERCOM0_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM0_SPI_WriteRead;
#endif
            break;
            
        case SERCOM1:
#ifdef PLIB_SERCOM1_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM1_SPI_WriteRead;
#endif
            break;
            
        case SERCOM2:
#ifdef PLIB_SERCOM2_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM2_SPI_WriteRead;
#endif
            break;
            
        case SERCOM3:
#ifdef PLIB_SERCOM3_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM3_SPI_WriteRead;
#endif
            break;

        case SERCOM4:
#ifdef PLIB_SERCOM4_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM4_SPI_WriteRead;
#endif
            break;
            
        case SERCOM5:
#ifdef PLIB_SERCOM5_SPI_MASTER_H
            driver->SPI_WriteRead = &SERCOM5_SPI_WriteRead;
#endif
            break;
    }

    // set all channels GS to minimum (disable)
    TLC5947SetCommonShiftRegisterToValue(driver, TLC5947_GS_DATA_MIN_VALUE);
    
    // write initial data to the chips
    TLC5947WriteData(driver);
    
    return STATUS_OK;
}


/**
@Function
  status_t TLC5947SetCommonShiftRegisterToValue(tlc5947_t *driver, uint16_t new_value)

@Summary
  populate the CSR with a specific value

@Description
  the CSR locations (one for each output channel) will be overwritten by the new_value
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5947_t data structure

  @param new_value - 16-bit value that will be written to each output channel of the CSR

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5947SetCommonShiftRegisterToValue(&tlc5947_driver, 0x0FFF);
*/
status_t TLC5947SetCommonShiftRegisterToValue(tlc5947_t *driver, uint16_t new_value) {
    uint16_t chip_id, cindex;
    uint16_t disabled_value = TLC5947_GS_DATA_MIN_VALUE;
    uint8_t disabled_channels;
    
    // make sure the inserted value is not bigger than the max value
    if (new_value > TLC5947_GS_DATA_MAX_VALUE) {
        new_value = TLC5947_GS_DATA_MAX_VALUE;
    }
    
    // apply user limit on GS
    if (new_value > TLC5947_MAX_GS_VALUE) {
        new_value = TLC5947_MAX_GS_VALUE;
    }
    
    // if inverted, update the value
    if (TLC5947_IS_GS_DATA_INVERTED) {
        new_value = TLC5947_GS_DATA_INVERT(new_value);
        disabled_value = TLC5947_GS_DATA_MAX_VALUE;
    }
    
    for (chip_id = 0; chip_id < TLC5947_NO_OF_CHIPS; chip_id++) {
        disabled_channels = TLC5947_NO_OF_CHANNELS_PER_CHIP - TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP;
        
        for (cindex = chip_id * TLC5947_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5947_NO_OF_BYTES_PER_CSR + TLC5947_NO_OF_BYTES_PER_CSR; cindex += 3) {
            if (disabled_channels >= 2) {
                driver->common_shift_register[cindex] = disabled_value >> 4;
                driver->common_shift_register[cindex+1] = (disabled_value >> 8) + (disabled_value << 4);
                driver->common_shift_register[cindex+2] = disabled_value;
                
                disabled_channels = disabled_channels - 2;
            }
            else if (disabled_channels == 1) {
                driver->common_shift_register[cindex] = disabled_value >> 4;
                driver->common_shift_register[cindex+1] = (new_value >> 8) + (disabled_value << 4);
                driver->common_shift_register[cindex+2] = new_value;
                
                disabled_channels = disabled_channels - 1;
            }
            else {
                driver->common_shift_register[cindex] = new_value >> 4;
                driver->common_shift_register[cindex+1] = (new_value >> 8) + (new_value << 4);
                driver->common_shift_register[cindex+2] = new_value;
            }
        }
    }
    
    return STATUS_OK;
}

/**
@Function
  status_t TLC5947UpdateCommonShiftRegister(tlc5947_t *driver, void *data_register)

@Summary
  populate the CSR with the values hold by a data register (one location for each active channel)

@Description
  the CSR locations (one for each output channel) will be overwritten by the appropriate value in the data register
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5947_t data structure

  @param *data_register - pointer to the data register holding the values that need to be written to the CSR

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5941Q1UpdateCommonShiftRegister(&tlc5947_driver, &data_register);
*/
status_t TLC5947UpdateCommonShiftRegister(tlc5947_t *driver, void *gs_data_register) {
    uint16_t chip_id, aindex, cindex;
    uint8_t disabled_channels;
    
    uint16_t gvalue_hi, gvalue_lo;
    
    // todo: bug fix: check if value greater than maximum value
    
    for (chip_id = 0; chip_id < TLC5947_NO_OF_CHIPS; chip_id++) {
        aindex = (TLC5947_NO_OF_CHIPS - chip_id) * TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP - 1;
        disabled_channels = TLC5947_NO_OF_CHANNELS_PER_CHIP - TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP;
        
        for (cindex = chip_id * TLC5947_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5947_NO_OF_BYTES_PER_CSR + TLC5947_NO_OF_BYTES_PER_CSR; cindex += 3) {
            if (disabled_channels >= 2) {
                gvalue_hi = TLC5947_GS_DATA_MIN_VALUE;
                gvalue_lo = TLC5947_GS_DATA_MIN_VALUE;
                
                if (TLC5947_IS_GS_DATA_INVERTED) {
                    gvalue_hi = TLC5947_GS_DATA_MAX_VALUE;
                    gvalue_lo = TLC5947_GS_DATA_MAX_VALUE;
                }
                
                disabled_channels = disabled_channels - 2;
                
            }
            else if (disabled_channels == 1) {
                gvalue_hi = TLC5947_GS_DATA_MIN_VALUE;
                
                if (TLC5947_GS_DATA_SIZE == GS_SIZE_1B) {
                    gvalue_lo = ((uint8_t *)gs_data_register)[aindex--];
                    
                }
                else { // GS_SIZE_2B
                    gvalue_lo = ((uint16_t *)gs_data_register)[aindex--];
                }
                
                // impose user upper limit
                if (gvalue_lo > TLC5947_MAX_GS_VALUE) {
                    gvalue_lo = TLC5947_MAX_GS_VALUE;   
                }
                
                if (TLC5947_IS_GS_DATA_INVERTED) {
                    gvalue_hi = TLC5947_GS_DATA_MAX_VALUE;
                    gvalue_lo = TLC5947_GS_DATA_INVERT(gvalue_lo);
                }
                
                disabled_channels = disabled_channels - 1;
                
            }
            else {
                if (TLC5947_GS_DATA_SIZE == GS_SIZE_1B) {
                    gvalue_hi = ((uint8_t *)gs_data_register)[aindex--];
                    gvalue_lo = ((uint8_t *)gs_data_register)[aindex--];
                    
                }
                else { // GS_SIZE_2B
                    gvalue_hi = ((uint16_t *)gs_data_register)[aindex--];
                    gvalue_lo = ((uint16_t *)gs_data_register)[aindex--];
                    
                }
                
                // impose user upper limit
                if (gvalue_hi > TLC5947_MAX_GS_VALUE) {
                    gvalue_hi = TLC5947_MAX_GS_VALUE;
                }
                if (gvalue_lo > TLC5947_MAX_GS_VALUE) {
                    gvalue_lo = TLC5947_MAX_GS_VALUE;   
                }
                
                if (TLC5947_IS_GS_DATA_INVERTED) {
                    gvalue_hi = TLC5947_GS_DATA_INVERT(gvalue_hi);
                    gvalue_lo = TLC5947_GS_DATA_INVERT(gvalue_lo);
                }
                
            }
            
            if (TLC5947_GS_DATA_SIZE==GS_SIZE_1B) { // size = 1 byte = 8 bit    
                driver->common_shift_register[cindex] = gvalue_hi;
                driver->common_shift_register[cindex+1] = (gvalue_lo >> 4) + ((TLC5947_IS_GS_DATA_INVERTED ? TLC5947_GS_DATA_MAX_VALUE : TLC5947_GS_DATA_MIN_VALUE) << 4);
                driver->common_shift_register[cindex+2] = ((TLC5947_IS_GS_DATA_INVERTED ? TLC5947_GS_DATA_MAX_VALUE : TLC5947_GS_DATA_MIN_VALUE) >> 4) + (gvalue_lo << 4);
                
            }
            else { // size = 2 byte = 16 bit
                driver->common_shift_register[cindex] = gvalue_hi >> 4;
                driver->common_shift_register[cindex+1] = (gvalue_lo >> 8) + (gvalue_hi << 4);
                driver->common_shift_register[cindex+2] = gvalue_lo;
                
            }
        }
    }
    
    return STATUS_OK;
}


/**
@Function
  status_t TLC5947WriteData(tlc5947_t *driver)

@Summary
  sends the CSR content to the chip/s via the selected SPI module

@Description
  the previously set up SERCOM SPI module is used to write the contents of CSR to the chip/s and at the same time to read what comes back
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5947_t data structure

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5941Q1WriteData(&tlc5947_driver);
*/
status_t TLC5947WriteData(tlc5947_t *driver)
{
    // BLANK -> HIGH
    PORT_PinSet(driver->blank);
    _nop();

    driver->SPI_WriteRead(driver->common_shift_register, TLC5947_NO_OF_BYTES_PER_DAISY_CSR, driver->receive_register, TLC5947_NO_OF_BYTES_PER_DAISY_CSR);
    
    // XLAT -> HIGH
    PORT_PinSet(driver->xlat);
    _nop();
    
    // BLANK -> LOW
    PORT_PinClear(driver->blank);
    _nop();
    
    // XLAT -> LOW
    PORT_PinClear(driver->xlat);
    _nop();
    
    return STATUS_OK;
}


/* *****************************************************************************
 End of File
 */
