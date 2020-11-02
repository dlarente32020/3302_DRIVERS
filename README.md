AdamElectronics3302MPLABX

The driver library consists of three files:
- tlc59xx.h
- tlc5941q1.c
- tlc5947.c

!!! PLEASE DON'T MODIFY THE FILES !!! The only section that you are allowed to modify can be found in the tlc59xx.h and  placed in between:
===== USER DATA - MODIFY ACCORDING TO YOUR NEEDS =========================
and
===== DRIVER DATA !!! DO NOT TOUCH !!! ===================================

Getting started:
1. add the files to your project

2. open Harmony 2 Configurator and set up the neede resources:
	A. for TLC5941Q1 driver:
		a.1. XLAT, MODE, BLANK - IO pins as outputs
		a.2. one GSCLK channel
		a.3. one SPI module

	B. for TLC5947 driver:
		a.1. XLAT, BLANK - IO pins as outputs
		a.2. one SPI module

	* assign custom names for each of the pins, while defining them

3. for each driver you use, do the following:
	A. set up the needed no. of chips, no. of active channels, gs data size and if the gs data is inverted using the macros inside tlc59xx.h (USER DATA section!!!)

	B. in the main program: define one instance for the interface and one for the actual driver (e.g. tlc5941q1_interface_t interface and tlc5941q1_t driver)

	C. instantiate the interface members

	D. Call the structure initialization routine (e.g. TLC5941Q1InitStruct())

	E. Writing data is a two step process:
		e.1. call the update common shift register routine to load your data from a buffer (the buffer needs to be [no_of_chips * no_of_active_channels] long)
		e.g. TLC5941Q1UpdateCommonShiftRegister()

		e.2. call the write function
		e.g. TLC5941Q1WriteData()

		* please keep in mind that TLC5947 knows to repeat the data for ever or until you perform a new write, but the TLC5941-Q1 needs periodic writes in order to keep running.
		The update period should be 4096/Fgsclk