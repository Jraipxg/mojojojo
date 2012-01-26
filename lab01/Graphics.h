/*
	File Name: Graphics.h
	Authors: Joshua James and Mohit Taneja
	Initial Creation Date: 9/12/11
	Description: Graphics driver for OLED display
	Lab Number: 3
	TA: Sundeep
	Date of last revision: 9/19/11
	Hardware configuration: On board OLED display
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "utils.h"

#define LOWER 0
#define UPPER 1

extern void Graphics_init(void);
extern void Graphics_clear(uint8_t device);
extern void Graphics_drawPoint(uint8_t device, uint8_t x, uint8_t y, uint8_t color);
extern void Graphics_drawLine(uint8_t device, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t color);
extern void Graphics_drawPolygon(uint8_t device, uint32_t * x_points, uint32_t * y_points, uint32_t num_points, int32_t border_color, int32_t fill_color);
extern void Graphics_drawEllipse(uint8_t device, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint8_t border_color, int16_t fill_color);
extern void Graphics_drawRectangle(uint8_t device, uint32_t x0, uint32_t y0, uint32_t width, uint32_t height, uint32_t border_color, int32_t fill_color);
extern void Graphics_drawString(uint8_t device, uint32_t x, uint32_t y, char *character, uint32_t color);

void RIT128x96x4Clear(void);

#endif
