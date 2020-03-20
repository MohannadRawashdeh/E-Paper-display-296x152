/*
 * Raw_GFX.h
 *
 * Created: 3/15/2020 9:59:37 PM
 *  Author: Mohannad Rawashdeh
 */ 


#ifndef RAW_GFX_H_
#define RAW_GFX_H_
#include "Font/fonts.h"
/*if you want to use e-paper dipslay enable this line*/
#ifndef E_paper_display
#define E_paper_display   1
#endif
// Display orientation
#define ROTATE_0            0
#define ROTATE_90           1
#define ROTATE_180          2
#define ROTATE_270          3

struct Raw_GFX_param
{
	uint16_t height;
	uint16_t width;
	uint8_t rotation;
	uint8_t *image;
};
// Color inverse. 1 or 0 = set or reset a bit if set a colored pixel
#define IF_INVERT_COLOR     1

	//Paint(uint8_t* image, int width, int height);
	//void Raw_GFX_init(uint16_t display_width,uint16_t display_height);
	void Raw_GFX_init(struct Raw_GFX_param *gfx);
	void Raw_GFX_Clear(struct Raw_GFX_param *gfx,int colored);
	#if E_paper_display == 1
	struct E_paper_param
	{
	   uint16_t	height;
	   uint16_t width;
	   uint8_t rotation;
	   uint8_t* imageBuf;
	};
	void epd_set_frame(struct Raw_GFX_param *gfx,uint8_t* image, int width,int height,int8_t rotation);
	int  epd_GetWidth(void);
	void epd_SetWidth(struct Raw_GFX_param *gfx,int width);
	int  epd_GetHeight(void);
	void epd_SetHeight(struct Raw_GFX_param *gfx,int height);
	 uint8_t* epd_GetImage(void);
	 #endif
	int  Raw_GFX_GetRotate(void);
	void Raw_GFX_SetRotate(struct Raw_GFX_param *gfx,int rotate);
	int  Raw_GFX_GetWidth(void);
	void Raw_GFX_SetWidth(struct Raw_GFX_param *gfx,int width);
	int  Raw_GFX_GetHeight(void);
	void Raw_GFX_SetHeight(struct Raw_GFX_param *gfx,int height);
	void Raw_GFX_DrawAbsolutePixel(struct Raw_GFX_param *gfx,int x, int y, int colored);
	void Raw_GFX_DrawPixel(struct Raw_GFX_param *gfx,int x, int y, int colored);
	void Raw_GFX_DrawCharAt(struct Raw_GFX_param *gfx,int x, int y, char ascii_char, sFONT* font, int colored);
	void Raw_GFX_DrawStringAt(struct Raw_GFX_param *gfx,int x, int y, const char* text, sFONT* font, int colored);
	void Raw_GFX_DrawLine(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored);
	void Raw_GFX_DrawHorizontalLine(struct Raw_GFX_param *gfx,int x, int y, int line_width, int colored);
	void Raw_GFX_DrawVerticalLine(struct Raw_GFX_param *gfx,int x, int y, int line_height, int colored);
	void Raw_GFX_DrawRectangle(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored);
	void Raw_GFX_DrawFilledRectangle(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored);
	void Raw_GFX_DrawCircle(struct Raw_GFX_param *gfx,int x, int y, int radius, int colored);
	void Raw_GFX_DrawFilledCircle(struct Raw_GFX_param *gfx,int x, int y, int radius, int colored);
	uint16_t Raw_GFX_Lib_version();




#endif /* RAW_GFX_H_ */