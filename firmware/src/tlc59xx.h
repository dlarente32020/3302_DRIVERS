/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Cocan Nicolae PFA

  @File Name
    tlc59xx.h

  @Summary
    cocann.h header file

  @Description
  ::todo::

 */
/* ************************************************************************** */

#ifndef _TLC59XX_H    /* Guard against multiple inclusion */
#define _TLC59XX_H


/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

/* This section lists the other files that are included in this file.
 */

/* TODO:  Include other files here if needed. */
#include "xc.h"
#include "definitions.h"

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
    
/* ===== USER DATA - MODIFY ACCORDING TO YOUR NEEDS ========================= */
// TLC5941-Q1 driver
// no of daisy-chained chips
#define TLC5941Q1_NO_OF_CHIPS                     (2u)
// no of active channels per chip (max. 16)
#define TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP  (16u)

// size of GS data (GS_SIZE_1B for 8-bit or GS_SIZE_2B for 16-bit)
#define TLC5941Q1_GS_DATA_SIZE                    (GS_SIZE_1B)
// is GS inverted? (inverted = max value corresponds to minimum duty-cycle))
#define TLC5941Q1_IS_GS_DATA_INVERTED             (false)



// TLC5947 driver
// no of daisy-chained chips
#define TLC5947_NO_OF_CHIPS                     (1u)
// no of active channels per chip (max. 24)
#define TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP  (22u)

// size of GS data register location (GS_SIZE_1B for 8-bit or GS_SIZE_2B for 16-bit)
#define TLC5947_GS_DATA_SIZE                    (GS_SIZE_1B)
// is GS inverted? (inverted = max value corresponds to minimum duty-cycle))
#define TLC5947_IS_GS_DATA_INVERTED             (true)


/* ===== DRIVER DATA !!! DO NOT TOUCH !!! =================================== */
// TLC5941-Q1 driver
// no of output channels per chip (physical outputs)
#define TLC5941Q1_NO_OF_CHANNELS_PER_CHIP         (16u)

// no of bits used to represent GS data per channel
#define TLC5941Q1_NO_OF_GS_BITS_PER_CHANNEL       (12u)
// no of bits used to represent DC data per channel
#define TLC5941Q1_NO_OF_DC_BITS_PER_CHANNEL       (6u)

// bits/bytes per CSR (per chip)
#define TLC5941Q1_NO_OF_BITS_PER_CSR              (TLC5941Q1_NO_OF_CHANNELS_PER_CHIP * TLC5941Q1_NO_OF_GS_BITS_PER_CHANNEL)
#define TLC5941Q1_NO_OF_BYTES_PER_CSR             (TLC5941Q1_NO_OF_BITS_PER_CSR / (8u))
// bytes per CSR (for the system - all daisy chained chips)
#define TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR       (TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_BYTES_PER_CSR)

// GS data register length (active channels)
#define TLC5941Q1_DC_GS_DATA_REGISTER_LENGTH      (TLC5941Q1_NO_OF_CHIPS * TLC5941Q1_NO_OF_ACTIVE_CHANNELS_PER_CHIP)

// DC data limits
#define TLC5941Q1_DC_DATA_MIN_VALUE               (0x00U)
#define TLC5941Q1_DC_DATA_MAX_VALUE               (0x3FU)

// GS data limits
#define TLC5941Q1_GS_DATA_MIN_VALUE               (0x000U)
#define TLC5941Q1_GS_DATA_MAX_VALUE               (0xFFFU)

// invert GS data
#define TLC5941Q1_GS_DATA_INVERT(crt_value)       (TLC5941Q1_GS_DATA_MAX_VALUE-crt_value)


// TLC5947 driver
// no of output channels per chip (physical outputs)
#define TLC5947_NO_OF_CHANNELS_PER_CHIP         (24u)

// no of bits used to represent GS data per channel
#define TLC5947_NO_OF_GS_BITS_PER_CHANNEL       (12u)

// bits/bytes per CSR (per chip)
#define TLC5947_NO_OF_BITS_PER_CSR              (TLC5947_NO_OF_CHANNELS_PER_CHIP * TLC5947_NO_OF_GS_BITS_PER_CHANNEL)
#define TLC5947_NO_OF_BYTES_PER_CSR             (TLC5947_NO_OF_BITS_PER_CSR / (8u))
// bytes per CSR (for the system - all daisy chained chips)
#define TLC5947_NO_OF_BYTES_PER_DAISY_CSR       (TLC5947_NO_OF_CHIPS * TLC5947_NO_OF_BYTES_PER_CSR)

// GS data register length  (active channels)
#define TLC5947_GS_DATA_REGISTER_LENGTH         (TLC5947_NO_OF_CHIPS * TLC5947_NO_OF_ACTIVE_CHANNELS_PER_CHIP)

// GS data limits
#define TLC5947_GS_DATA_MIN_VALUE               (0x000U)
#define TLC5947_GS_DATA_MAX_VALUE               (0xFFFU)

// invert GS data
#define TLC5947_GS_DATA_INVERT(crt_value)       (TLC5947_GS_DATA_MAX_VALUE-crt_value)


// *****************************************************************************
// *****************************************************************************
// Section: Shared Variables
// *****************************************************************************
// *****************************************************************************
    
extern bool new_period_trigger;


// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */


// *****************************************************************************
/** status_t

  @Summary
    enum datatype use to describe status

  @Description
    this datatype is used to describe or mark the status of a process
    <p>

  @Remarks
    STATUS_OK: operation/execution successful
    <p>
    STATUS_NOK: operation/execution unsuccessful
    <p>
*/
typedef enum {
    STATUS_OK   = 0u,
    STATUS_NOK  = 1u
            
} status_t;


/** sercom_instance_t

  @Summary
    enum datatype use identify the SERCOM instance

  @Description
    this datatype is used to identify the SERCOM instance used throughout the program
    <p>

  @Remarks
    SERCOM0: the first instance of SERCOM peripheral is used
    <p>
    SERCOM1: the second instance of SERCOM peripheral is used
    <p>
    SERCOM2: the third instance of SERCOM peripheral is used
    <p>
    SERCOM3: the fourth instance of SERCOM peripheral is used
    <p>
    SERCOM4: the fifth instance of SERCOM peripheral is used
    <p>
    SERCOM5: the sixth instance of SERCOM peripheral is used
    <p>
*/
typedef enum {
    SERCOM0     = 0u,
    SERCOM1     = 1u,
    SERCOM2     = 2u,
    SERCOM3     = 3u,
    SERCOM4     = 4u,
    SERCOM5     = 5u
            
} sercom_instance_t;


/** gs_size_t

  @Summary
    enum datatype describing if GS data is represented in 8-bit mode or 16-bit mode

  @Description
    this datatype is used to describe how GS data is represented (8-bit or 16-bit)
    if 8-bit mode, the 8 bits will be placed on the MSB position for each channel, leaving the 4 LSB unused
    if 16-bit mode, only the 12 LSB will be used, while the 4 MSB don't matter
    <p>

  @Remarks
    GS_SIZE_1B: GS data represented in 8-bit chunks
    <p>
    GS_SIZE_2B: GS data represented in 16-bit chunks
    <p>
*/
typedef enum {
    GS_SIZE_1B = (1u),
    GS_SIZE_2B = (2u)
            
} gs_size_t;


// tlc5941q1 driver
/** input_mode_t

  @Summary
    enum datatype used to point out what data is currently handled

  @Description
    this datatype is used to point out if the current action is taken for the dot-correction or for the gray-scale data
    <p>

  @Remarks
    MODE_GS: current operation for gray-scale data
    <p>
    MODE_DC: current operation for dot-correction data
    <p>
*/
typedef enum {
    MODE_GS = (0u),
    MODE_DC = (1u)

} input_mode_t;

/** tlc5941q1_interface_t

  @Summary
    data structure describing the physical chip interface

  @Description
    this data structure implements all IO pins and communication module needed to control the chip
    <p>

  @Remarks
    xlat: latch signal pin. when XLAT is high, data from the input shift register is written to either GS register (if MODE=low) or DC register (if MODE=high). when XLAT is low, the data in the GS or DC registers is held constant and does not change
    <p>
    blank: blank pin. when BLANK is high, all outputs are forced off and the GS counter is reset. when BLANK is low, the outputs are controlled by gray-scale PWM control
    <p>
    mode: input-mode change pin. when MODE is low, the device is in GS mode. when MODE is high, the device is in DC mode
    <p>
    sercom_instance: SERCOM instance used to move data in/out of the chip
    <p>
*/
typedef struct _tlc5941q1_interface_t {
    // PORT_PIN_PAxx or PORT_PIN_PBxx, where xx is the pin number (e.g. PORT_PIN_PA04, PORT_PIN_PB15)
    PORT_PIN xlat;
    PORT_PIN blank;
    PORT_PIN mode;
    PORT_PIN spi_mosi;
    PORT_PIN spi_sclk;
    PORT_PIN spi_miso;

    // SERCOM0 to SERCOM5 (for ATSAMC21J18A)
    sercom_instance_t sercom_instance;

} tlc5941q1_interface_t;

/** tlc5941q1_t

  @Summary
 data structure describing the chip

  @Description
    this data structure represents a model of the physical chip
    <p>

  @Remarks
    xlat: latch signal pin. when XLAT is high, data from the input shift register is written to either GS register (if MODE=low) or DC register (if MODE=high). when XLAT is low, the data in the GS or DC registers is held constant and does not change
    <p>
    blank: blank pin. when BLANK is high, all outputs are forced off and the GS counter is reset. when BLANK is low, the outputs are controlled by gray-scale PWM control
    <p>
    mode: input-mode change pin. when MODE is low, the device is in GS mode. when MODE is high, the device is in DC mode
    <p>
    sercom_instance: SERCOM instance used to move data in/out of the chip
    <p>
    SPI_WriteRead: pointer to the write/read function corresponding to the used SERCOM SPI module
    <p>
    common_shift_register: register holding the data that has to be shifted into the chip
    <p>
    receive_register: register holding the data received from the chip
    <p>
*/
typedef struct _tlc5941q1_t {

    PORT_PIN xlat;
    PORT_PIN blank;
    PORT_PIN mode;
    PORT_PIN spi_mosi;
    PORT_PIN spi_sclk;
    PORT_PIN spi_miso;

    sercom_instance_t sercom_instance;
    bool (*SPI_WriteRead) (void*, size_t, void*, size_t);

    uint8_t common_shift_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR];
    uint8_t receive_register[TLC5941Q1_NO_OF_BYTES_PER_DAISY_CSR];

} tlc5941q1_t;


// tlc5947 driver
/** tlc5947_interface_t

  @Summary
    data structure describing the physical chip interface

  @Description
    this data structure implements all IO pins and communication module needed to control the chip
    <p>

  @Remarks
    xlat: latch signal pin. when XLAT is high, data from the input shift register is written to either GS register (if MODE=low) or DC register (if MODE=high). when XLAT is low, the data in the GS or DC registers is held constant and does not change
    <p>
    blank: blank pin. when BLANK is high, all outputs are forced off and the GS counter is reset. when BLANK is low, the outputs are controlled by gray-scale PWM control
    <p>
    sercom_instance: SERCOM instance used to move data in/out of the chip
    <p>
*/
typedef struct _tlc5947_interface_t {
    // PORT_PIN_PAxx or PORT_PIN_PBxx, where xx is the pin number (e.g. PORT_PIN_PA04, PORT_PIN_PB15)
    PORT_PIN xlat;
    PORT_PIN blank;

    // SERCOM0_ID to SERCOM5_ID (for ATSAMC21J18A)
    sercom_instance_t sercom_instance;

} tlc5947_interface_t;

/** tlc5947_t

  @Summary
 data structure describing the chip

  @Description
    this data structure represents a model of the physical chip
    <p>

  @Remarks
    xlat: latch signal pin. when XLAT is high, data from the input shift register is written to either GS register (if MODE=low) or DC register (if MODE=high). when XLAT is low, the data in the GS or DC registers is held constant and does not change
    <p>
    blank: blank pin. when BLANK is high, all outputs are forced off and the GS counter is reset. when BLANK is low, the outputs are controlled by gray-scale PWM control
    <p>
    sercom_instance: SERCOM instance used to move data in/out of the chip
    <p>
    SPI_WriteRead: pointer to the write/read function corresponding to the used SERCOM SPI module
    <p>
    common_shift_register: register holding the data that has to be shifted into the chip
    <p>
    receive_register: register holding the data received from the chip
    <p>
*/
typedef struct _tlc5947_t {

    PORT_PIN xlat;
    PORT_PIN blank;

    sercom_instance_t sercom_instance;
    bool (*SPI_WriteRead) (void*, size_t, void*, size_t);

    uint8_t common_shift_register[TLC5947_NO_OF_BYTES_PER_DAISY_CSR];
    uint8_t receive_register[TLC5947_NO_OF_BYTES_PER_DAISY_CSR];

} tlc5947_t;


// *****************************************************************************
// *****************************************************************************
// Section: Interface Functions
// *****************************************************************************
// *****************************************************************************

/*  A brief description of a section can be given directly below the section
    banner.
 */

// *****************************************************************************
// tlc5941q1 driver
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
status_t TLC5941Q1InitStruct(tlc5941q1_t *driver, tlc5941q1_interface_t *interface);

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
status_t TLC5941Q1SetCommonShiftRegisterToValue(tlc5941q1_t *driver, input_mode_t mode, uint16_t new_value);

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
status_t TLC5941Q1UpdateCommonShiftRegister(tlc5941q1_t *driver, input_mode_t mode, void *data_register);

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
status_t TLC5941Q1WriteData(tlc5941q1_t *driver, input_mode_t mode);

// tlc5947 driver
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
status_t TLC5947InitStruct(tlc5947_t *driver, tlc5947_interface_t *interface);

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
status_t TLC5947SetCommonShiftRegisterToValue(tlc5947_t *driver, uint16_t new_value);

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
status_t TLC5947UpdateCommonShiftRegister(tlc5947_t *driver, void *gs_data_register);

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
status_t TLC5947WriteData(tlc5947_t *driver);


/* Provide C++ Compatibility */
#ifdef __cplusplus
}
#endif

#endif /* _TLC59XX_H */

/* *****************************************************************************
 End of File
 */
