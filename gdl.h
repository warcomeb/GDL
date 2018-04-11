/******************************************************************************
 * GDL - Graphics Display Library for libohiboard
 * Copyright (C) 2017 Marco Giammarini
 *
 * Authors:
 *  Marco Giammarini <m.giammarini@warcomeb.it>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

#ifndef __WARCOMEB_GDL_H
#define __WARCOMEB_GDL_H

#define WARCOMEB_GDL_LIBRARY_VERSION     "1.0"
#define WARCOMEB_GDL_LIBRARY_VERSION_M   1
#define WARCOMEB_GDL_LIBRARY_VERSION_m   0
#define WARCOMEB_GDL_LIBRARY_TIME        0

#include "libohiboard.h"

/*
 * The user must define these label...
 * The name of the define is:
 *     #define WARCOMEB_GDL_XXX         0
 */
#ifndef __NO_BOARD_H
#include "board.h"
#endif

#if !defined(WARCOMEB_GDL_PARALLEL) & !defined(WARCOMEB_GDL_I2C) & !defined(WARCOMEB_GDL_SPI)
#error "You must define a communication type!"
#endif

#if defined(WARCOMEB_GDL_I2C) & !defined(LIBOHIBOARD_IIC)
#error "You must enable the I2C peripheral"
#endif

#if defined(WARCOMEB_GDL_SPI) & !defined(LIBOHIBOARD_SPI)
#error "You must enable the SPI peripheral"
#endif

typedef enum _GDL_ModelType
{
    GDL_MODELTYPE_SSD1306   = 0x0100,
    GDL_MODELTYPE_SSD1325   = 0x0200,
	GDL_MODELTYPE_SSD1327ZB = 0x0300,
	GDL_MODELTYPE_SSD1325Z2 = 0x0400,

} GDL_ModelType;

typedef enum _GDL_Errors
{
    GDL_ERRORS_OK,
    GDL_ERRORS_WRONG_POSITION,
} GDL_Errors;

typedef struct _GDL_Device
{
    GDL_ModelType model;

#if defined WARCOMEB_GDL_PARALLEL

    Gpio_Pins rd;
    Gpio_Pins dc;
    Gpio_Pins rs;
    Gpio_Pins cs;
    Gpio_Pins wr;

    Gpio_Pins d0;
    Gpio_Pins d1;
    Gpio_Pins d2;
    Gpio_Pins d3;
    Gpio_Pins d4;
    Gpio_Pins d5;
    Gpio_Pins d6;
    Gpio_Pins d7;

#elif defined WARCOMEB_GDL_I2C

    uint8_t address;

    Iic_DeviceHandle dev;

#elif defined WARCOMEB_GDL_SPI

#endif

    uint8_t width;                      /**< Display width in number of pixel */
    uint8_t height;                    /**< Display height in number of pixel */

    uint16_t product;      /**< It is a unique code that represent the device */

    bool chargePump;      /**< Flag to enable or not the internal charge pump */

    bool useCustomFont; /**< Flag to show if user want use custom font or not */
    uint8_t fontSize;             /**< Font size setted by user: 1 is default */

    void (*delayTime)(uint32_t delay);       /**< Function for blocking delay */

    /** Callback for drawPixel function implemented into device implementation */
    GDL_Errors (*drawPixel)(void* dev, uint8_t x, uint8_t y, uint8_t color);

} GDL_Device;

/**
 * The function print a line in the selected position with the selected
 * color.
 * The function use Bresenham's algorithm. You can find on Wikipedia!
 * @see https://it.wikipedia.org/wiki/Algoritmo_della_linea_di_Bresenham
 * @see https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] xStop The ending x position
 * @param[in] yStop The ending y position
 * @param[in] color The color of the line
 */
void GDL_drawLine (GDL_Device* dev,
                   uint16_t xStart,
                   uint16_t yStart,
                   uint16_t xStop,
                   uint16_t yStop,
                   uint8_t color);

/**
 * The function draw a rectangle. It can be fill or not.
 *
 * @param[in] dev The handle of the device
 * @param[in] xStart The starting x position
 * @param[in] yStart The starting y position
 * @param[in] width The ending x position
 * @param[in] height The ending y position
 * @param[in] color The color of the rectangle
 * @param[in] isFill If TRUE the rectangle will be fill
 */
void GDL_drawRectangle (GDL_Device* dev,
                        uint16_t xStart,
                        uint16_t yStart,
                        uint16_t width,
                        uint16_t height,
                        uint8_t color,
                        bool isFill);

/**
 * The function print a char in the selected position with the selected
 * color, background and size.
 * The starting point is the top-left corner of the char.
 *
 * @param[in] dev The handle of the device
 * @param[in] xPos The x position
 * @param[in] yPos The y position
 * @param[in] c The char to be draw
 * @param[in] color The foreground color of the char
 * @param[in] background The background color of the char
 * @param[in] size The size for the char, if 0 use default dimension
 * @return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the char
 *         exceeds the width or height of the display, GDL_ERRORS_OK otherwise.
 */
GDL_Errors GDL_drawChar (GDL_Device* dev,
                         uint16_t xPos,
                         uint16_t yPos,
                         uint8_t c,
                         uint8_t color,
                         uint8_t background,
                         uint8_t size);

#endif /* __WARCOMEB_GDL_H */
