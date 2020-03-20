/*
 * UC8151.c
 *
 * Created: 3/14/2020 10:43:50 PM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "UC8151.h"
#include "UC8151_SPI_driver.h"

static struct UC8151_param uc8151;
static void UC8151_definition(void)
{
	uc8151.busy_pin=uc_spi.busy_pin;
	uc8151.cs_pin  =uc_spi.cs_pin;
	uc8151.rst_pin =uc_spi.rst_pin;
	uc8151.dc_pin  =uc_spi.dc_pin;
	uc8151.height  =uc_spi.height;
	uc8151.width   =uc_spi.width;
	uc8151.data_size=1;
	uc8151.spi_driver_type=uc_spi.spi_driver_type;
}
	int  UC8151_Init()
	{
		UC8151_definition();
		UC8151_Reset();
		UC8151_SendCommand(BOOSTER_SOFT_START);
		UC8151_SendData(0x17);
		UC8151_SendData(0x17);
		UC8151_SendData(0x17);

		UC8151_SendCommand(POWER_SETTING);
		UC8151_SendData(0x03);
		UC8151_SendData(0x00);
		UC8151_SendData(0x2B);
		UC8151_SendData(0x2B);
		UC8151_SendData(0x09);
		    
		UC8151_SendCommand(POWER_ON);
		UC8151_WaitUntilIdle();

		UC8151_SendCommand(PANEL_SETTING);
		UC8151_SendData(0xCF);

		UC8151_SendCommand(TCON_RESOLUTION);
		UC8151_SendData(0x98);
		UC8151_SendData(0x01);
		UC8151_SendData(0x28);
		    
		UC8151_SendCommand(VCOM_AND_DATA_INTERVAL_SETTING);
		UC8151_SendData(0xF7);
		return 0;
	}
	void UC8151_SendCommand(uint8_t command)
	{
		uc8151.data[0]=command;
		set_UC8151_SPI_driver_pin(uc8151.dc_pin,false);
		spi_send_cmd(&uc8151);
	}
	void UC8151_SendData(uint8_t data)
	{
		uc8151.data[0]=data;
		set_UC8151_SPI_driver_pin(uc8151.dc_pin,true);
		spi_send_cmd(&uc8151);
	}
	void UC8151_WaitUntilIdle(void)
	{
		/*dangerous function with polled (while) loop inside
		  must be replaced by IRQ function with escape mechanism*/
		while (get_UC8151_SPI_driver_pin(uc8151.busy_pin) == StatusBusy)
		{
			dtime_delay_ms(100);
		}
	}
	void UC8151_Reset(void)
	{
		set_UC8151_SPI_driver_pin(uc8151.rst_pin,false);
		dtime_delay_ms(200);
		set_UC8151_SPI_driver_pin(uc8151.rst_pin,true);
		dtime_delay_ms(200);
		
	}
	void UC8151_SetPartialWindow(const uint8_t* buffer_black, const uint8_t* buffer_red, int x, int y, int w, int l)
	{
		UC8151_SendCommand(PARTIAL_IN);
		UC8151_SendCommand(PARTIAL_WINDOW);
		UC8151_SendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
		UC8151_SendData(((x & 0xf8) + w  - 1) | 0x07);
		UC8151_SendData(y >> 8);
		UC8151_SendData(y & 0xff);
		UC8151_SendData((y + l - 1) >> 8);
		UC8151_SendData((y + l - 1) & 0xff);
		UC8151_SendData(0x01);         // Gates scan both inside and outside of the partial window. (default)
		dtime_delay_ms(2);
		UC8151_SendCommand(DATA_START_TRANSMISSION_1);
		if (buffer_black != NULL) {
			for(int i = 0; i < w  / 8 * l; i++) {
				UC8151_SendData(buffer_black[i]);
			}
			} else {
			for(int i = 0; i < w  / 8 * l; i++) {
				UC8151_SendData(0x00);
			}
		}
		dtime_delay_ms(2);
		UC8151_SendCommand(DATA_START_TRANSMISSION_2);
		if (buffer_red != NULL) {
			for(int i = 0; i < w  / 8 * l; i++) {
				UC8151_SendData(buffer_red[i]);
			}
			} else {
			for(int i = 0; i < w  / 8 * l; i++) {
				UC8151_SendData(0x00);
			}
		}
		dtime_delay_ms(2);
		UC8151_SendCommand(PARTIAL_OUT);
	}
	void UC8151_SetPartialWindowBlack(const uint8_t* buffer_black, int x, int y, int w, int l)
	{
		    UC8151_SendCommand(PARTIAL_IN);
		    UC8151_SendCommand(PARTIAL_WINDOW);
		    UC8151_SendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
		    UC8151_SendData(((x & 0xf8) + w  - 1) | 0x07);
		    UC8151_SendData(y >> 8);
		    UC8151_SendData(y & 0xff);
		    UC8151_SendData((y + l - 1) >> 8);
		    UC8151_SendData((y + l - 1) & 0xff);
		    UC8151_SendData(0x01);         // Gates scan both inside and outside of the partial window. (default)
		    dtime_delay_ms(2);
		    UC8151_SendCommand(DATA_START_TRANSMISSION_1);
		    if (buffer_black != NULL) {
			    for(int i = 0; i < w  / 8 * l; i++) {
				    UC8151_SendData(buffer_black[i]);
			    }
			    } else {
			    for(int i = 0; i < w  / 8 * l; i++) {
				    UC8151_SendData(0x00);
			    }
		    }
		    dtime_delay_ms(2);
		    UC8151_SendCommand(PARTIAL_OUT);
	}
	void UC8151_SetPartialWindowRed(const uint8_t* buffer_red, int x, int y, int w, int l)
	{
		    UC8151_SendCommand(PARTIAL_IN);
		    UC8151_SendCommand(PARTIAL_WINDOW);
		    UC8151_SendData(x & 0xf8);     // x should be the multiple of 8, the last 3 bit will always be ignored
		    UC8151_SendData(((x & 0xf8) + w  - 1) | 0x07);
		    UC8151_SendData(y >> 8);
		    UC8151_SendData(y & 0xff);
		    UC8151_SendData((y + l - 1) >> 8);
		    UC8151_SendData((y + l - 1) & 0xff);
		    UC8151_SendData(0x01);         // Gates scan both inside and outside of the partial window. (default)
		    dtime_delay_ms(2);
		    UC8151_SendCommand(DATA_START_TRANSMISSION_2);
		    if (buffer_red != NULL) {
			    for(int i = 0; i < w  / 8 * l; i++) {
				    UC8151_SendData(buffer_red[i]);
			    }
			    } else {
			    for(int i = 0; i < w  / 8 * l; i++) {
				    UC8151_SendData(0x00);
			    }
		    }
		    dtime_delay_ms(2);
		    UC8151_SendCommand(PARTIAL_OUT);
	}
	void UC8151_DisplayFrame(const uint8_t* frame_buffer_black, const uint8_t* frame_buffer_red)
	{
		   if (frame_buffer_black != NULL) {
			   UC8151_SendCommand(DATA_START_TRANSMISSION_1);
			   dtime_delay_ms(2);
			   for (uint16_t i = 0; i < uc8151.width * uc8151.height / 8; i++) {
				   UC8151_SendData(frame_buffer_black[i]);
			   }
			   dtime_delay_ms(2);
		   }
		   if (frame_buffer_red != NULL) {
			   UC8151_SendCommand(DATA_START_TRANSMISSION_2);
			   dtime_delay_ms(2);
			   for (unsigned int i = 0; i < uc8151.width * uc8151.height / 8; i++) {
				   UC8151_SendData(frame_buffer_red[i]);
			   }
			   dtime_delay_ms(2);
		   }
		   UC8151_SendCommand(DISPLAY_REFRESH);
		   UC8151_WaitUntilIdle();
	}
	void UC8151_DisplayFrame_SRAM(void)
	{
		UC8151_SendCommand(DISPLAY_REFRESH);
		UC8151_WaitUntilIdle();
	}
	void UC8151_ClearFrame(void)
	{
		UC8151_SendCommand(DATA_START_TRANSMISSION_1);
		dtime_delay_ms(2);
		for(unsigned int i = 0; i < uc8151.width * uc8151.height / 8; i++) {
			UC8151_SendData(0xFF);
		}
		dtime_delay_ms(2);
		UC8151_SendCommand(DATA_START_TRANSMISSION_2);
		dtime_delay_ms(2);
		for(unsigned int i = 0; i < uc8151.width * uc8151.height / 8; i++) {
			UC8151_SendData(0xFF);
		}
		dtime_delay_ms(2);
	}
	void UC8151_Sleep(void)
	{
		UC8151_SendCommand(POWER_OFF);
		UC8151_WaitUntilIdle();
		UC8151_SendCommand(DEEP_SLEEP);
		UC8151_SendData(0xa5);
	}