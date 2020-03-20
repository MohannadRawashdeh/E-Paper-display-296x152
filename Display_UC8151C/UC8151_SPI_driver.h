/*
 * UC8151_SPI_driver.h
 *
 * Created: 3/14/2020 11:08:38 PM
 *  Author: Mohannad Rawashdeh
 */ 


#ifndef UC8151_SPI_DRIVER_H_
#define UC8151_SPI_DRIVER_H_
#include "utils.h"
#ifndef driver_spi_m_sync
#define driver_spi_m_sync    1 /*using sync driver for ASF4*/
#endif
#ifndef driver_spi_m_async
#define driver_spi_m_async   2 /*using async driver for ASF4 , 0:disabled , 2: enabled*/
#endif
#ifndef driver_spi_m_RTOS
#define driver_spi_m_RTOS    3 /*using RTOS driver for ASF4,0:disabled , 3: enabled*/
#endif
#ifndef driver_spi_m_DMA
#define driver_spi_m_DMA     4 /*using DMA driver for ASF4,0:disabled , 4: enabled*/
#endif
 
struct UC8151_param
{
	uint8_t cs_pin;
	uint8_t busy_pin;
	uint8_t dc_pin;
	uint8_t rst_pin;
	uint8_t spi_driver_type;
	uint16_t width;
	uint16_t height;
	uint8_t data[1];
	uint16_t data_size;
};
struct UC8151_param  uc_spi;

void    UC8151_SPI_driver_init(struct UC8151_param *driver);
void    set_UC8151_SPI_driver_pin(uint8_t pin,uint8_t status);
uint8_t get_UC8151_SPI_driver_pin(uint8_t pin);
void    dtime_delay_ms(uint16_t dtime);
void    spi_send_cmd(struct UC8151_param *driver);



#endif /* UC8151_SPI_DRIVER_H_ */