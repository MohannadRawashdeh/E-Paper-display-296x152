/*
 * Raw_GFX.c
 *
 * Created: 3/15/2020 9:59:51 PM
 *  Author: Mohannad Rawashdeh
 */ 
#include "atmel_start.h"
#include "Raw_GFX.h"
#include "Font/fonts.h"
void Raw_GFX_init(struct Raw_GFX_param *gfx)
{
	/*just check if everything is ok*/
}

void Raw_GFX_Clear(struct Raw_GFX_param *gfx,int colored)
{
	for (uint16_t x_axis=0;x_axis < gfx->width;x_axis++)
	{
		for (uint16_t y_axis=0; y_axis < gfx->height ;y_axis++)
		{
			Raw_GFX_DrawAbsolutePixel(gfx,x_axis,y_axis,colored);
		}
	}
}

	void Raw_GFX_DrawAbsolutePixel(struct Raw_GFX_param *gfx,int x, int y, int colored)
	{
		if (x < 0 || x >= gfx->width || y < 0 || y >= gfx->height) 
		   {
			return;
		   }
		   
		    if (IF_INVERT_COLOR) {
			    if (colored) {
				    gfx->image[(x + y * (gfx->width)) / 8] |= 0x80 >> (x % 8);
				    } 
					else {
				    gfx->image[(x + y * (gfx->width)) / 8] &= ~(0x80 >> (x % 8));
			    }
			    } else {
			    if (colored) {
				    gfx->image[(x + y * gfx->width) / 8] &= ~(0x80 >> (x % 8));
				    } 
					else {
				    gfx->image[(x + y * gfx->width) / 8] |= 0x80 >> (x % 8);
			    }
		    }   
	}
	
	void Raw_GFX_DrawPixel(struct Raw_GFX_param *gfx,int x, int y, int colored)
	{
		int point_temp;
		if (gfx->rotation == ROTATE_0) {
			if(x < 0 || x >= gfx->width || y < 0 || y >= gfx->height) {
				return;
			}
			Raw_GFX_DrawAbsolutePixel(gfx,x, y, colored);
			} else if (gfx->rotation == ROTATE_90) {
			if(x < 0 || x >= gfx->height || y < 0 || y >= gfx->width) {
				return;
			}
			point_temp = x;
			x = gfx->width - y;
			y = point_temp;
			Raw_GFX_DrawAbsolutePixel(gfx,x, y, colored);
			} else if (gfx->rotation == ROTATE_180) {
			if(x < 0 || x >= gfx->width || y < 0 || y >= gfx->height) {
				return;
			}
			x = gfx->width - x;
			y = gfx->height - y;
			Raw_GFX_DrawAbsolutePixel(gfx,x, y, colored);
			} else if (gfx->rotation == ROTATE_270) {
			if(x < 0 || x >= gfx->height || y < 0 || y >= gfx->width) {
				return;
			}
			point_temp = x;
			x = y;
			y = gfx->height - point_temp;
			Raw_GFX_DrawAbsolutePixel(gfx,x, y, colored);
		}
	}
	
	void Raw_GFX_DrawCharAt(struct Raw_GFX_param *gfx,int x, int y, char ascii_char,sFONT *font, int colored)
	{
		int i, j;	
		unsigned int char_offset = (ascii_char - ' ') * font->Height * (font->Width / 8 + (font->Width % 8 ? 1 : 0));
		const unsigned char* ptr = &font->table[char_offset];
      //  printf("char %c\r\n",ascii_char);
		for (j = 0; j < font->Height; j++) {
			for (i = 0; i < font->Width; i++) {
				//if (pgm_read_byte(ptr) & (0x80 >> (i % 8))) {
        // printf("ft[%d]=%d\r\n",char_offset,font->table[char_offset]);
				if ((font->table[char_offset]) & (0x80 >> (i % 8))) {
					Raw_GFX_DrawPixel(gfx,x + i, y + j, colored);
				}
				if (i % 8 == 7) {
					ptr++;
                   char_offset++;
				}
			}
			if (font->Width % 8 != 0) {
				ptr++;
				char_offset++;
			}
		}
	}
	
	void Raw_GFX_DrawStringAt(struct Raw_GFX_param *gfx,int x, int y, const char* text, sFONT* font, int colored)
	 {
		const char* p_text = text;
		unsigned int counter = 0;
		int refcolumn = x;
		
		/* Send the string character by character on EPD */
		while (*p_text != 0) {
			/* Display one character on EPD */
			Raw_GFX_DrawCharAt(gfx,refcolumn, y, *p_text, font, colored);
			/* Decrement the column position by 16 */
			refcolumn += font->Width;
			/* Point on the next character */
			p_text++;
			counter++;
		}
	}
	
	void Raw_GFX_DrawLine(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored) {
		/* Bresenham algorithm */
		int dx = x1 - x0 >= 0 ? x1 - x0 : x0 - x1;
		int sx = x0 < x1 ? 1 : -1;
		int dy = y1 - y0 <= 0 ? y1 - y0 : y0 - y1;
		int sy = y0 < y1 ? 1 : -1;
		int err = dx + dy;

		while((x0 != x1) && (y0 != y1)) {
			Raw_GFX_DrawPixel(gfx,x0, y0 , colored);
			if (2 * err >= dy) {
				err += dy;
				x0 += sx;
			}
			if (2 * err <= dx) {
				err += dx;
				y0 += sy;
			}
		}
	}
	void Raw_GFX_DrawHorizontalLine(struct Raw_GFX_param *gfx,int x, int y, int line_width, int colored) {
		int i;
		for (i = x; i < x + line_width; i++) {
			Raw_GFX_DrawPixel(gfx,i, y, colored);
		}
	}
	
	void Raw_GFX_DrawVerticalLine(struct Raw_GFX_param *gfx,int x, int y, int line_height, int colored)
	{
		int i;
		for (i = y; i < y + line_height; i++) {
			Raw_GFX_DrawPixel(gfx,x, i, colored);
		}
	}
	void Raw_GFX_DrawRectangle(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored)
	 {
		int min_x, min_y, max_x, max_y;
		min_x = x1 > x0 ? x0 : x1;
		max_x = x1 > x0 ? x1 : x0;
		min_y = y1 > y0 ? y0 : y1;
		max_y = y1 > y0 ? y1 : y0;
		
		Raw_GFX_DrawHorizontalLine(gfx,min_x, min_y, max_x - min_x + 1, colored);
		Raw_GFX_DrawHorizontalLine(gfx,min_x, max_y, max_x - min_x + 1, colored);
		Raw_GFX_DrawVerticalLine(gfx,min_x, min_y, max_y - min_y + 1, colored);
		Raw_GFX_DrawVerticalLine(gfx,max_x, min_y, max_y - min_y + 1, colored);
	}
	
	void Raw_GFX_DrawFilledRectangle(struct Raw_GFX_param *gfx,int x0, int y0, int x1, int y1, int colored) {
		int min_x, min_y, max_x, max_y;
		int i;
		min_x = x1 > x0 ? x0 : x1;
		max_x = x1 > x0 ? x1 : x0;
		min_y = y1 > y0 ? y0 : y1;
		max_y = y1 > y0 ? y1 : y0;
		
		for (i = min_x; i <= max_x; i++) {
			Raw_GFX_DrawVerticalLine(gfx,i, min_y, max_y - min_y + 1, colored);
		}
	}
	void Raw_GFX_DrawCircle(struct Raw_GFX_param *gfx,int x, int y, int radius, int colored) {
		/* Bresenham algorithm */
		int x_pos = -radius;
		int y_pos = 0;
		int err = 2 - 2 * radius;
		int e2;

		do {
			Raw_GFX_DrawPixel(gfx,x - x_pos, y + y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x + x_pos, y + y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x + x_pos, y - y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x - x_pos, y - y_pos, colored);
			e2 = err;
			if (e2 <= y_pos) {
				err += ++y_pos * 2 + 1;
				if(-x_pos == y_pos && e2 <= x_pos) {
					e2 = 0;
				}
			}
			if (e2 > x_pos) {
				err += ++x_pos * 2 + 1;
			}
		} while (x_pos <= 0);
	}
	
	void Raw_GFX_DrawFilledCircle(struct Raw_GFX_param *gfx,int x, int y, int radius, int colored){
		/* Bresenham algorithm */
		int x_pos = -radius;
		int y_pos = 0;
		int err = 2 - 2 * radius;
		int e2;

		do {
			Raw_GFX_DrawPixel(gfx,x - x_pos, y + y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x + x_pos, y + y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x + x_pos, y - y_pos, colored);
			Raw_GFX_DrawPixel(gfx,x - x_pos, y - y_pos, colored);
			Raw_GFX_DrawHorizontalLine(gfx,x + x_pos, y + y_pos, 2 * (-x_pos) + 1, colored);
			Raw_GFX_DrawHorizontalLine(gfx,x + x_pos, y - y_pos, 2 * (-x_pos) + 1, colored);
			e2 = err;
			if (e2 <= y_pos) {
				err += ++y_pos * 2 + 1;
				if(-x_pos == y_pos && e2 <= x_pos) {
					e2 = 0;
				}
			}
			if(e2 > x_pos) {
				err += ++x_pos * 2 + 1;
			}
		} while(x_pos <= 0);
	}
	#if E_paper_display == 1
	void epd_set_frame(struct Raw_GFX_param *gfx,uint8_t* image, int width,int height,int8_t rotation)
	{
		gfx->height=height;
		gfx->width=width;
		gfx->rotation=rotation;
		gfx->image=image;
	}
	int  epd_GetWidth(void)
	{
		return 0;
	}
	void epd_SetWidth(struct Raw_GFX_param *gfx,int width)
	{
		gfx->width=width;
		gfx->width = width % 8 ? width + 8 - (width % 8) : width;
	}
	int  epd_GetHeight(void)
	{
		return 0;
	}
	void epd_SetHeight(struct Raw_GFX_param *gfx,int height)
	{
		gfx->height=height;
	}
	uint8_t* epd_GetImage(void)
	{
		return 0; 
	}
	uint16_t Raw_GFX_Lib_version()
	{
		return 100;  /*initial Version 1.0.0 March 2020*/
	}
	#endif