/*
 * UC8151_SPI_driver.c
 *
 * Created: 3/14/2020 11:06:03 PM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "hal_spi_m_sync.h"
#include "UC8151_SPI_driver.h"
#include "utils.h"
#include "driver_init.h"
#include <hal_io.h>
#include <hal_gpio.h>
//const uint32_t UC8151_spi_baudrate  = 1000000;
struct io_descriptor *io_UC8151_spi;

void    UC8151_SPI_driver_init(struct UC8151_param *driver)
{
		printf("here0\r\n");
		uc_spi.busy_pin=driver->busy_pin;
		uc_spi.cs_pin  =driver->cs_pin;
		uc_spi.dc_pin  =driver->dc_pin;
		uc_spi.rst_pin =driver->rst_pin;
		uc_spi.height  =driver->height;
		uc_spi.width   =driver->width;
        uc_spi.spi_driver_type=driver_spi_m_sync;
		printf("here1\r\n");
//	    spi_m_sync_set_baudrate(&SPI_Display,UC8151_spi_baudrate);
        /*in default the driver is sync spi*/
		/*don't forget to set the height and width of the display*/
		driver->spi_driver_type = driver_spi_m_sync;
		spi_m_sync_get_io_descriptor(&SPI_Display, &io_UC8151_spi);
		spi_m_sync_enable(&SPI_Display);	
}
void    set_UC8151_SPI_driver_pin(uint8_t pin,uint8_t status)
{
	gpio_set_pin_level(pin,status);
}
uint8_t get_UC8151_SPI_driver_pin(uint8_t pin)
{
	return gpio_get_pin_level(pin);
}
void    dtime_delay_ms(uint16_t dtime)
{
	delay_ms(dtime);
}
void    spi_send_cmd(struct UC8151_param *driver)
{

	if (driver->spi_driver_type == driver_spi_m_sync)
	{
          // printf(".");
		   set_UC8151_SPI_driver_pin(driver->cs_pin, false);
		   io_write(io_UC8151_spi,driver->data, driver->data_size);
		   set_UC8151_SPI_driver_pin(driver->cs_pin, true);
	}
}