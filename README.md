# E-Paper-display-296x152
Library and working code for E-paper display 296x152 based on UC8151 driver using a Atmel ASF4
this libarary will work with any SAM Microcontroller (As long as the RAM is more than 8KB) based on ASF4
you could find the display I used as a reference to test this Libray (https://www.buydisplay.com/red-2-6-inch-e-ink-display-module-296x152-for-arduino-raspberry-pi).
the library using SPI communication bus , will add a support for DMA and ASYNC SPI driver in the near future.
Connection (Based on SAMD21 xplained Pro and SPI SERCOM0)

  SAMD21		->		Dispaly
	PB04			    	Display_BUSY_pin
	PB06			    	Display_RST_pin
	PB07			    	Display_DC_pin
	PA05			    	display_CS
	PA06			    	display SDA
	PA07			    	display SCL
(https://github.com/MohannadRawashdeh/E-Paper-display-296x152/blob/master/Display%20018.JPG)
