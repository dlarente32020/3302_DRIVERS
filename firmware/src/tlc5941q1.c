/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Adam Electronics, Inc.

  @File Name
    tlc5941q1.c

  @Summary
    TLC5941-Q1, Texas Instruments PWM controller IC source file

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
#include "tlc5941q1.h"

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
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.

int ExampleInterfaceFunction(int param1, int param2) {
    return 0;
}

 */

/**
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
status_t TLC5941Q1InitStruct(tlc5941q1_t *driver, tlc5941q1_interface_t *interface)
{
    driver->xlat = interface->xlat;
    driver->blank = interface->blank;
    driver->mode = interface->mode;
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
    //TLC5941Q1SetCommonShiftRegisterToValue(driver, MODE_GS, TLC5941Q1_GS_DATA_MIN_VALUE);
    // write initial GS data to the chips
    //TLC5941Q1WriteData(driver, MODE_GS);
    
    // set all channels DC to maximum (max. current)
    //TLC5941Q1SetCommonShiftRegisterToValue(driver, MODE_DC, TLC5941Q1_DC_DATA_MAX_VALUE);
    // write initial DC data to the chips
    //TLC5941Q1WriteData(driver, MODE_DC);
    
    return STATUS_OK;
}


/**
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
status_t TLC5941Q1SetCommonShiftRegisterToValue(tlc5941q1_t *driver, input_mode_t mode, uint16_t new_value) {
    uint16_t chip_id, cindex, cindex_upper_limit;
    uint16_t disabled_value;
    uint8_t disabled_channels;
    
    if (mode == MODE_DC) {
        disabled_value = TLC5941Q1_DC_DATA_MIN_VALUE;
        
        // make sure the inserted value is not bigger than the max value
        if (new_value > TLC5941Q1_DC_DATA_MAX_VALUE) {
            new_value = TLC5941Q1_DC_DATA_MAX_VALUE;
            
        }
        
        for (chip_id = 0, cindex_upper_limit = TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u); chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id += 1, cindex_upper_limit += TLC5941Q1_NO_OF_BYTES_PER_CSR) {
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR + TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex += 3) {
                if (cindex < cindex_upper_limit) {
                    driver->common_shift_register[cindex] = disabled_value;
                    driver->common_shift_register[cindex+1] = disabled_value;
                    driver->common_shift_register[cindex+2] = disabled_value;
                    
                }
                else {
                    if (disabled_channels >= 4) {
                        driver->common_shift_register[cindex] = disabled_value;
                        driver->common_shift_register[cindex+1] = disabled_value;
                        driver->common_shift_register[cindex+2] = disabled_value;
                        
                        disabled_channels = disabled_channels - 4;
                        
                    }
                    else if (disabled_channels == 3) {
                        driver->common_shift_register[cindex] = (disabled_value >> 4) + (new_value << 2);
                        driver->common_shift_register[cindex+1] = (disabled_value >> 2) + (disabled_value << 4);
                        driver->common_shift_register[cindex+2] = disabled_value + (disabled_value << 6);

                        disabled_channels = disabled_channels - 3;
                        
                    }
                    else if (disabled_channels == 2) {
                        driver->common_shift_register[cindex] = (new_value >> 4) + (new_value << 2);
                        driver->common_shift_register[cindex+1] = (disabled_value >> 2) + (new_value << 4);
                        driver->common_shift_register[cindex+2] = disabled_value + (disabled_value << 6);
                        
                        disabled_channels = disabled_channels - 2;
                        
                    }
                    else if (disabled_channels == 1) {
                        driver->common_shift_register[cindex] = (new_value >> 4) + (new_value << 2);
                        driver->common_shift_register[cindex+1] = (new_value >> 2) + (new_value << 4);
                        driver->common_shift_register[cindex+2] = disabled_value + (new_value << 6);
                        
                        disabled_channels = disabled_channels - 1;
                        
                    }
                    else {
                        driver->common_shift_register[cindex] = (new_value >> 4) + (new_value << 2);
                        driver->common_shift_register[cindex+1] = (new_value >> 2) + (new_value << 4);
                        driver->common_shift_register[cindex+2] = new_value + (new_value << 6);
                        
                    }
                    
                }
                
            }
            
        }
        
    }
    else { // MODE_GS
        disabled_value = TLC5941Q1_GS_DATA_MIN_VALUE;
        
        // make sure the inserted value is not bigger than the max value
        if (new_value > TLC5941Q1_GS_DATA_MAX_VALUE) {
            new_value = TLC5941Q1_GS_DATA_MAX_VALUE;
            
        }

        // if inverted, update the value
        if (TLC5941Q1_IS_GS_DATA_INVERTED) {
            new_value = TLC5941Q1_GS_DATA_INVERT(new_value);
            disabled_value = TLC5941Q1_GS_DATA_MAX_VALUE;
            
        }

        for (chip_id = 0; chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id++) {
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR + TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex += 3) {
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
        
    }
    
    return STATUS_OK;
}

/**
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
status_t TLC5941Q1UpdateCommonShiftRegister(tlc5941q1_t *driver, input_mode_t mode, void *data_register) {
    uint16_t chip_id, aindex, cindex, cindex_upper_limit;
    uint8_t disabled_channels;
    uint8_t disabled_value;
    
    uint8_t dvalue3, dvalue2, dvalue1, dvalue0;
    uint16_t gvalue_hi, gvalue_lo;
    
    // todo: bug fix: check if value greater than maximum value
    
    if (mode == MODE_DC) {
        disabled_value = TLC5941Q1_DC_DATA_MIN_VALUE;
        
        for (chip_id = 0, cindex_upper_limit = TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u); chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id += 1, cindex_upper_limit += TLC5941Q1_NO_OF_BYTES_PER_CSR) {
            aindex = (TLC5941Q1_NO_OF_CHIPS - chip_id) * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP - 1;
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR + TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex += 3) {
                if (cindex < cindex_upper_limit) {
                    dvalue3 = disabled_value;
                    dvalue2 = disabled_value;
                    dvalue1 = disabled_value;
                    dvalue0 = disabled_value;
                    
                }
                else {
                    if (disabled_channels >= 4) {
                        dvalue3 = disabled_value;
                        dvalue2 = disabled_value;
                        dvalue1 = disabled_value;
                        dvalue0 = disabled_value;

                        disabled_channels = disabled_channels - 4;

                    }
                    else if (disabled_channels == 3) {
                        dvalue3 = disabled_value;
                        dvalue2 = disabled_value;
                        dvalue1 = disabled_value;
                        dvalue0 = ((uint8_t *)data_register)[aindex--];

                        disabled_channels = disabled_channels - 3;

                    }
                    else if (disabled_channels == 2) {
                        dvalue3 = disabled_value;
                        dvalue2 = disabled_value;
                        dvalue1 = ((uint8_t *)data_register)[aindex--];
                        dvalue0 = ((uint8_t *)data_register)[aindex--];

                        disabled_channels = disabled_channels - 2;

                    }
                    else if (disabled_channels == 1) {
                        dvalue3 = disabled_value;
                        dvalue2 = ((uint8_t *)data_register)[aindex--];
                        dvalue1 = ((uint8_t *)data_register)[aindex--];
                        dvalue0 = ((uint8_t *)data_register)[aindex--];

                        disabled_channels = disabled_channels - 1;

                    }
                    else {
                        dvalue3 = ((uint8_t *)data_register)[aindex--];
                        dvalue2 = ((uint8_t *)data_register)[aindex--];
                        dvalue1 = ((uint8_t *)data_register)[aindex--];
                        dvalue0 = ((uint8_t *)data_register)[aindex--];

                    }
                    
                }
                driver->common_shift_register[cindex] = (dvalue2 >> 4) + (dvalue3 << 2);
                driver->common_shift_register[cindex+1] = (dvalue1 >> 2) + (dvalue2 << 4);
                driver->common_shift_register[cindex+2] = dvalue0 + (dvalue1 << 6);
                
            }
        }
        
    }
    else { // MODE_GS
        for (chip_id = 0; chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id += 1) {
            aindex = (TLC5941Q1_NO_OF_CHIPS - chip_id) * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP - 1;
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex < chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR + TLC5941Q1_NO_OF_BYTES_PER_CSR; cindex += 3) {
                if (disabled_channels >= 2) {
                    gvalue_hi = TLC5941Q1_GS_DATA_MIN_VALUE;
                    gvalue_lo = TLC5941Q1_GS_DATA_MIN_VALUE;

                    if (TLC5941Q1_IS_GS_DATA_INVERTED) {
                        gvalue_hi = TLC5941Q1_GS_DATA_MAX_VALUE;
                        gvalue_lo = TLC5941Q1_GS_DATA_MAX_VALUE;

                    }

                    disabled_channels = disabled_channels - 2;

                }
                else if (disabled_channels == 1) {
                    gvalue_hi = TLC5941Q1_GS_DATA_MIN_VALUE;
                    gvalue_lo = (TLC5941Q1_GS_DATA_SIZE == GS_SIZE_1B) ? (((uint8_t *)data_register)[aindex--]) : (((uint16_t *)data_register)[aindex--]);

                    if (TLC5941Q1_IS_GS_DATA_INVERTED) {
                        gvalue_hi = TLC5941Q1_GS_DATA_MAX_VALUE;
                        gvalue_lo = TLC5941Q1_GS_DATA_INVERT(gvalue_lo);

                    }

                    disabled_channels = disabled_channels - 1;

                }
                else {
                    gvalue_hi = (TLC5941Q1_GS_DATA_SIZE == GS_SIZE_1B) ? (((uint8_t *)data_register)[aindex--]) : (((uint16_t *)data_register)[aindex--]);
                    gvalue_lo = (TLC5941Q1_GS_DATA_SIZE == GS_SIZE_1B) ? (((uint8_t *)data_register)[aindex--]) : (((uint16_t *)data_register)[aindex--]);

                    if (TLC5941Q1_IS_GS_DATA_INVERTED) {
                        gvalue_hi = TLC5941Q1_GS_DATA_INVERT(gvalue_hi);
                        gvalue_lo = TLC5941Q1_GS_DATA_INVERT(gvalue_lo);

                    }

                }
                
                if (TLC5941Q1_GS_DATA_SIZE==GS_SIZE_1B) { // size = 1 byte = 8 bit    
                    driver->common_shift_register[cindex] = gvalue_hi;
                    driver->common_shift_register[cindex+1] = (gvalue_lo >> 4) + ((TLC5941Q1_IS_GS_DATA_INVERTED ? TLC5941Q1_GS_DATA_MAX_VALUE : TLC5941Q1_GS_DATA_MIN_VALUE) << 4);
                    driver->common_shift_register[cindex+2] = ((TLC5941Q1_IS_GS_DATA_INVERTED ? TLC5941Q1_GS_DATA_MAX_VALUE : TLC5941Q1_GS_DATA_MIN_VALUE) >> 4) + (gvalue_lo << 4);

                }
                else { // size = 2 byte = 16 bit
                    driver->common_shift_register[cindex] = gvalue_hi >> 4;
                    driver->common_shift_register[cindex+1] = (gvalue_lo >> 8) + (gvalue_hi << 4);
                    driver->common_shift_register[cindex+2] = gvalue_lo;

                }
            }
        }   
    }
    
    return STATUS_OK;
}


/**
  @Function
    int ExampleInterfaceFunctionName ( int param1, int param2 ) 

  @Summary
    Brief one-line description of the function.

  @Remarks
    Refer to the example_file.h interface header for function usage details.
 */
status_t TLC5941Q1WriteData(tlc5941q1_t *driver, input_mode_t mode)
{
    // BLANK -> HIGH
    PORT_PinSet(driver->blank);
    _nop();
    
    if (mode == MODE_DC) {
        PORT_PinSet(driver->mode);
    }

    driver->SPI_WriteRead(driver->common_shift_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR, driver->receive_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR);
    
    // XLAT -> HIGH
    PORT_PinSet(driver->xlat);
    _nop();
    
    // BLANK -> LOW
    PORT_PinClear(driver->blank);
    _nop();
    
    // XLAT -> LOW
    PORT_PinClear(driver->xlat);
    _nop();
    
    if (mode == MODE_DC) {
        PORT_PinClear(driver->mode);
    }
    
    return STATUS_OK;
}


/* *****************************************************************************
 End of File
 */
