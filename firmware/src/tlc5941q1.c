/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Adam Electronics, Inc.

  @File Name
    tlc5941q1.c

  @Summary
    TLC5941-Q1, Texas Instruments PWM controller IC source file

  @Description
    tlc5941q1 source file
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

static bool dummy_bit;

static uint8_t spi_pins_group;
static uint8_t spi_sclk_pin;
static uint8_t spi_mosi_pin;

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
  status_t TLC5941Q1InitStruct(tlc5941q1_t *driver, tlc5941q1_interface_t *interface)

@Summary
  initialization function for the tlc5941q1_t data structure

@Description
  this function is used to initialize a tlc5941q1_t data structure based on a tlc5941q1_interface_t data structure
  <p>

@Precondition
  the tlc5941q1_interface_t data structure has to be initialized

@Parameters
  @param *driver - pointer to a tlc5941q1_t data structure

  @param *interface - pointer to a tlc5941q1_interface_t data structure

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5941Q1InitStructure(&tlc5941q1_driver, &tlc5941q1_interface);
*/
status_t TLC5941Q1InitStruct(tlc5941q1_t *driver, tlc5941q1_interface_t *interface)
{
    driver->xlat = interface->xlat;
    driver->blank = interface->blank;
    driver->mode = interface->mode;
    driver->spi_mosi = interface->spi_mosi;
    driver->spi_sclk = interface->spi_sclk;
    driver->spi_miso = interface->spi_miso;
    
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
    
    // fill CSR with max DC value
    TLC5941Q1SetCommonShiftRegisterToValue(driver, MODE_DC, TLC5941Q1_DC_DATA_MAX_VALUE);
    // write data
    TLC5941Q1WriteData(driver, MODE_DC);

    return STATUS_OK;
}


/**
@Function
  status_t TLC5941Q1SetCommonShiftRegisterToValue(tlc5941q1_t *driver, input_mode_t mode, uint16_t new_value)

@Summary
  populate the CSR with a specific value

@Description
  the CSR locations (one for each output channel) will be overwritten by the new_value
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5941q1_t data structure

  @param mode - specifies if the CSR is written with either DC or GS data

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
  TLC5941Q1SetCommonShiftRegisterToValue(&tlc5941q1_driver, MODE_GS, 0x0FFF);
  or
  TLC5941Q1SetCommonShiftRegisterToValue(&tlc5941q1_driver, MODE_DC, 0x003F);
*/
status_t TLC5941Q1SetCommonShiftRegisterToValue(tlc5941q1_t *driver, input_mode_t mode, uint16_t new_value) {
    uint16_t chip_id, cindex;
    uint16_t disabled_value;
    uint8_t disabled_channels;
    
    if (mode == MODE_DC) {
        disabled_value = TLC5941Q1_DC_DATA_MIN_VALUE;
        
        // make sure the inserted value is not bigger than the max value
        if (new_value > TLC5941Q1_DC_DATA_MAX_VALUE) {
            new_value = TLC5941Q1_DC_DATA_MAX_VALUE;
            
        }
        
        for (chip_id = 0; chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id += 1) {
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u); cindex < (chip_id + 1) * (TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u)); cindex += 3) {
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
  status_t TLC5941Q1UpdateCommonShiftRegister(tlc5941q1_t *driver, input_mode_t mode, void *data_register)

@Summary
  populate the CSR with the values hold by a data register (one location for each active channel)

@Description
  the CSR locations (one for each output channel) will be overwritten by the appropriate value in the data register
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5941q1_t data structure

  @param mode - specifies if the CSR is written with either DC or GS data

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
  TLC5941Q1UpdateCommonShiftRegister(&tlc5941q1_driver, MODE_GS, &gs_data_register);
  or
  TLC5941Q1UpdateCommonShiftRegister(&tlc5941q1_driver, MODE_DC, &dc_data_register);
*/
status_t TLC5941Q1UpdateCommonShiftRegister(tlc5941q1_t *driver, input_mode_t mode, void *data_register) {
    uint16_t chip_id, aindex, cindex;
    uint8_t disabled_channels;
    uint8_t disabled_value;
    
    uint8_t dvalue3, dvalue2, dvalue1, dvalue0;
    uint16_t gvalue_hi, gvalue_lo;
    
    if (mode == MODE_DC) {
        disabled_value = TLC5941Q1_DC_DATA_MIN_VALUE;
        
        for (chip_id = 0; chip_id < TLC5941Q1_NO_OF_CHIPS; chip_id += 1) {
            aindex = (TLC5941Q1_NO_OF_CHIPS - chip_id) * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP - 1;
            disabled_channels = TLC5941Q1_NO_OF_CHANNELS_PER_CHIP - TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP;

            for (cindex = chip_id * TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u); cindex < (chip_id + 1) * (TLC5941Q1_NO_OF_BYTES_PER_CSR / (2u)); cindex += 3) {
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
  status_t TLC5941Q1WriteData(tlc5941q1_t *driver, input_mode_t mode)

@Summary
  sends the CSR content to the chip/s via the selected SPI module

@Description
  the previously set up SERCOM SPI module is used to write the contents of CSR to the chip/s and at the same time to read what comes back
  depending on the mode value, appropriate control signals will be generated in order to move the input data to the corresponding registers (GS or DC)
  <p>

@Precondition
  none

@Parameters
  @param *driver - pointer to a tlc5941q1_t data structure

  @param mode - specifies if the CSR is written with either DC or GS data

@Returns
  <ul>
    <li>STATUS_NOK - indicates an error occurred
    <li>STATUS_OK - indicates an error did not occur
  </ul>

@Remarks
  none

@Example
  @code
  TLC5941Q1WriteData(&tlc5941q1_driver, MODE_GS);
  or
  TLC5941Q1WriteData(&tlc5941q1_driver, MODE_DC);
*/
status_t TLC5941Q1WriteData(tlc5941q1_t *driver, input_mode_t mode)
{   
    if (mode == MODE_DC) {
        // BLANK -> HIGH
        PORT_PinSet(driver->blank);
        _nop();
        
        // MODE -> HIGH
        PORT_PinSet(driver->mode);
        _nop();

        // write data
        driver->SPI_WriteRead(driver->common_shift_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR / (2u), driver->receive_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR / (2u));

        // XLAT -> HIGH
        PORT_PinSet(driver->xlat);
        _nop();

        // XLAT -> LOW
        PORT_PinClear(driver->xlat);
        _nop();

        // MODE -> LOW
        PORT_PinClear(driver->mode);
        _nop();

        // fill CSR with min GS value
        TLC5941Q1SetCommonShiftRegisterToValue(driver, MODE_GS, TLC5941Q1_GS_DATA_MIN_VALUE);

        // write data
        driver->SPI_WriteRead(driver->common_shift_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR, driver->receive_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR);

        // XLAT -> HIGH
        PORT_PinSet(driver->xlat);
        _nop();

        // XLAT -> LOW
        PORT_PinClear(driver->xlat);
        _nop();

        // update dummy bit
        dummy_bit = (driver->common_shift_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR - 1] & 0xFE) ? true : false;
        
        // BLANK -> LOW
        PORT_PinClear(driver->blank);
        _nop();
        
    }
    else { // MODE_GS
        spi_pins_group = (driver->spi_sclk < 32) ? (0u) : (1u);
        spi_sclk_pin = driver->spi_sclk % 32;
        spi_mosi_pin = driver->spi_mosi % 32;
    
        // generate extra SCLK pulse after the XLAT of first GS write following the DC write
        {
            // disable peripheral control for spi_sclk_pin and spi_mosi_pin
            PORT_REGS->GROUP[spi_pins_group].PORT_PINCFG[spi_sclk_pin] = 0x0;
            PORT_REGS->GROUP[spi_pins_group].PORT_PINCFG[spi_mosi_pin] = 0x0;

            // spi_sclk_pin and spi_mosi_pin direction = output
            PORT_REGS->GROUP[spi_pins_group].PORT_DIRSET = (1u) << spi_sclk_pin;
            PORT_REGS->GROUP[spi_pins_group].PORT_DIRSET = (1u) << spi_mosi_pin;

            // set mosi value as last spi transmited bit
            PORT_PinWrite(driver->spi_mosi, dummy_bit);
            _nop();

            // spi sclk high
            PORT_PinSet(driver->spi_sclk);
            _nop();

            // spi sclk low
            PORT_PinClear(driver->spi_sclk);
            _nop();

            // spi mosi high
            PORT_PinSet(driver->spi_mosi);
            _nop();

            // spi_sclk_pin and spi_mosi_pin direction = input
            PORT_REGS->GROUP[spi_pins_group].PORT_DIRCLR = (1u) << spi_sclk_pin;
            PORT_REGS->GROUP[spi_pins_group].PORT_DIRCLR = (1u) << spi_mosi_pin;

            // enable peripheral control for spi_sclk_pin and spi_mosi_pin
            PORT_REGS->GROUP[spi_pins_group].PORT_PINCFG[spi_sclk_pin] = 0x1;
            PORT_REGS->GROUP[spi_pins_group].PORT_PINCFG[spi_mosi_pin] = 0x1;
        }
        
        // write data
        driver->SPI_WriteRead(driver->common_shift_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR, driver->receive_register, TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR);

        // update dummy bit
        dummy_bit = (driver->common_shift_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR - 1] & 0xFE) ? true : false;
        
        // BLANK -> HIGH
        PORT_PinSet(driver->blank);
        _nop();

        // XLAT -> HIGH
        PORT_PinSet(driver->xlat);
        _nop();

        // XLAT -> LOW
        PORT_PinClear(driver->xlat);
        _nop();

        // BLANK -> LOW
        PORT_PinClear(driver->blank);
        _nop();
        
    }    
    
    return STATUS_OK;
}


/* *****************************************************************************
 End of File
 */
