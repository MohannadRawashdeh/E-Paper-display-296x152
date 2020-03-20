/*
 * UC8151.h
 *
 * Created: 3/14/2020 10:43:35 PM
 *  Author: Mohannad Rawashdeh
 Driver provided by EastRising Technology Co.,LTD  http://www.buydisplay.com
 */ 
/***************************************************
//Web: http://www.buydisplay.com
EastRising Technology Co.,LTD
****************************************************/

#ifndef UC8151_H_
#define UC8151_H_

// Display resolution
#define EPD_WIDTH       152
#define EPD_HEIGHT      296

// EPD2IN9B commands
#define PANEL_SETTING                               0x00
#define POWER_SETTING                               0x01
#define POWER_OFF                                   0x02
#define POWER_OFF_SEQUENCE_SETTING                  0x03
#define POWER_ON                                    0x04
#define POWER_ON_MEASURE                            0x05
#define BOOSTER_SOFT_START                          0x06
#define DEEP_SLEEP                                  0x07
#define DATA_START_TRANSMISSION_1                   0x10
#define DATA_STOP                                   0x11
#define DISPLAY_REFRESH                             0x12
#define DATA_START_TRANSMISSION_2                   0x13
#define PLL_CONTROL                                 0x30
#define TEMPERATURE_SENSOR_COMMAND                  0x40
#define TEMPERATURE_SENSOR_CALIBRATION              0x41
#define TEMPERATURE_SENSOR_WRITE                    0x42
#define TEMPERATURE_SENSOR_READ                     0x43
#define VCOM_AND_DATA_INTERVAL_SETTING              0x50
#define LOW_POWER_DETECTION                         0x51
#define TCON_SETTING                                0x60
#define TCON_RESOLUTION                             0x61
#define GET_STATUS                                  0x71
#define AUTO_MEASURE_VCOM                           0x80
#define VCOM_VALUE                                  0x81
#define VCM_DC_SETTING_REGISTER                     0x82
#define PARTIAL_WINDOW                              0x90
#define PARTIAL_IN                                  0x91
#define PARTIAL_OUT                                 0x92
#define PROGRAM_MODE                                0xA0
#define ACTIVE_PROGRAM                              0xA1
#define READ_OTP_DATA                               0xA2
#define POWER_SAVING                                0xE3

#define StatusBusy       0
#define StatusIdle       1

#define COLORED     0
#define UNCOLORED   1

	int  UC8151_Init();
	void UC8151_SendCommand(uint8_t command);
	void UC8151_SendData(uint8_t data);
	void UC8151_WaitUntilIdle(void);
	void UC8151_Reset(void);
	void UC8151_SetPartialWindow(const uint8_t* buffer_black, const uint8_t* buffer_red, int x, int y, int w, int l);
	void UC8151_SetPartialWindowBlack(const uint8_t* buffer_black, int x, int y, int w, int l);
	void UC8151_SetPartialWindowRed(const uint8_t* buffer_red, int x, int y, int w, int l);
	void UC8151_DisplayFrame(const uint8_t* frame_buffer_black, const uint8_t* frame_buffer_red);
	void UC8151_DisplayFrame_SRAM(void);/*update the display's internal SRAM*/
	void UC8151_ClearFrame(void);
	void UC8151_Sleep(void);
/*	
	unsigned int reset_pin;
	unsigned int dc_pin;
	unsigned int cs_pin;
	unsigned int busy_pin;
	*/

#endif /* UC8151_H_ */
/*
// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3
#include "fonts.h"
// Color inverse. 1 or 0 = set or reset a bit if set a colored pixel
#define IF_INVERT_COLOR     1
	Paint(unsigned char* image, int width, int height);
	void Clear(int colored);
	int  GetWidth(void);
	void SetWidth(int width);
	int  GetHeight(void);
	void SetHeight(int height);
	int  GetRotate(void);
	void SetRotate(int rotate);
	unsigned char* GetImage(void);
	void DrawAbsolutePixel(int x, int y, int colored);
	void DrawPixel(int x, int y, int colored);
	void DrawCharAt(int x, int y, char ascii_char, sFONT* font, int colored);
	void DrawStringAt(int x, int y, const char* text, sFONT* font, int colored);
	void DrawLine(int x0, int y0, int x1, int y1, int colored);
	void DrawHorizontalLine(int x, int y, int width, int colored);
	void DrawVerticalLine(int x, int y, int height, int colored);
	void DrawRectangle(int x0, int y0, int x1, int y1, int colored);
	void DrawFilledRectangle(int x0, int y0, int x1, int y1, int colored);
	void DrawCircle(int x, int y, int radius, int colored);
	void DrawFilledCircle(int x, int y, int radius, int colored);
	
	unsigned char* priv_image;
	int priv_width;
	int priv_height;
	int priv_rotate;
*/


/* END OF FILE */




