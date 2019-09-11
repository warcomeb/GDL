/*
 * GDL - Graphics Display Library for libohiboard
 * Copyright (C) 2017-2019 Marco Giammarini
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
 */

#ifndef __WARCOMEB_GDL_H
#define __WARCOMEB_GDL_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup GDL
 * \{
 */

/*!
 * \defgroup GDL_Core
 * \{
 */

#define WARCOMEB_GDL_LIBRARY_VERSION_MAJOR       (0x1ul)
#define WARCOMEB_GDL_LIBRARY_VERSION_MINOR       (0x0ul)
#define WARCOMEB_GDL_LIBRARY_VERSION_BUG         (0x0ul)
#define WARCOMEB_GDL_LIBRARY_VERSION             ((WARCOMEB_GDL_LIBRARY_VERSION_MAJOR << 16)\
                                                 |(WARCOMEB_GDL_LIBRARY_VERSION_MINOR << 8 )\
                                                 |(WARCOMEB_GDL_LIBRARY_VERSION_BUG        ))
#define WARCOMEB_GDL_LIBRARY_TIME                0

#ifndef __NO_PROFILES
#include "board.h"
#include "firmware.h"
#endif

#include "gdltype.h"

#if !defined(GDL_DEFAULT_PROTOCOLTYPE)
#error "GDL Error: You must define a communication type!"
#endif

#if ((GDL_DEFAULT_PROTOCOLTYPE == GDL_PROTOCOLTYPE_I2C) && !defined(LIBOHIBOARD_IIC))
#error "GDL Error: You must enable the I2C peripheral"
#endif

#if ((GDL_DEFAULT_PROTOCOLTYPE == GDL_PROTOCOLTYPE_SPI) && !defined(LIBOHIBOARD_SPI))
#error "GDL Error: You must enable the SPI peripheral"
#endif

#if !defined (GDL_DEFAULT_FONT_WIDTH)
#define GDL_DEFAULT_FONT_WIDTH                   6
#endif
#if !defined (GDL_DEFAULT_FONT_HEIGHT)
#define GDL_DEFAULT_FONT_HEIGHT                  8
#endif

typedef struct _GDL_Device_t
{
    GDL_ModelType_t model;

#if (GDL_DEFAULT_PROTOCOLTYPE == GDL_PROTOCOLTYPE_PARALLEL)

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

#elif (GDL_DEFAULT_PROTOCOLTYPE == GDL_PROTOCOLTYPE_I2C)

    uint8_t address;

    Iic_DeviceHandle dev;

#elif (GDL_DEFAULT_PROTOCOLTYPE == GDL_PROTOCOLTYPE_SPI)

#endif

    uint8_t width;                      /*!< Display width in number of pixel */
    uint8_t height;                    /*!< Display height in number of pixel */

    uint16_t product;      /*!< It is a unique code that represent the device */

    bool chargePump;      /*!< Flag to enable or not the internal charge pump */

    bool useCustomFont; /*!< Flag to show if user want use custom font or not */
    uint8_t fontSize;             /*!< Font size setted by user: 1 is default */

#if (LIBOHIBOARD_VERSION < 0x00020000)
    void (*delayTime)(uint32_t delay);       /*!< Function for blocking delay */
#endif

    /*! Callback for drawPixel function implemented into device implementation */
    GDL_Errors_t (*drawPixel)(void* dev, uint8_t x, uint8_t y, uint8_t color);

} GDL_Device_t, *GDL_DeviceHandle_t;

/*!
 * The function print a line in the selected position with the selected
 * color.
 * The function use Bresenham's algorithm. You can find on Wikipedia!
 * \see https://it.wikipedia.org/wiki/Algoritmo_della_linea_di_Bresenham
 * \see https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
 *
 * \param[in]    dev: The handle of the device
 * \param[in] xStart: The starting x position
 * \param[in] yStart: The starting y position
 * \param[in]  xStop: The ending x position
 * \param[in]  yStop: The ending y position
 * \param[in]  color: The color of the line
 */
void GDL_drawLine (GDL_DeviceHandle_t dev,
                   uint16_t xStart,
                   uint16_t yStart,
                   uint16_t xStop,
                   uint16_t yStop,
                   uint8_t color);

/**
 * The function draw a rectangle. It can be fill or not.
 *
 * \param[in]    dev: The handle of the device
 * \param[in] xStart: The starting x position
 * \param[in] yStart: The starting y position
 * \param[in]  width: The ending x position
 * \param[in] height: The ending y position
 * \param[in]  color: The color of the rectangle
 * \param[in] isFill: If TRUE the rectangle will be fill
 */
void GDL_drawRectangle (GDL_DeviceHandle_t dev,
                        uint16_t xStart,
                        uint16_t yStart,
                        uint16_t width,
                        uint16_t height,
                        uint8_t color,
                        bool isFill);

/*!
 * The function print a char in the selected position with the selected
 * color, background and size.
 * The starting point is the top-left corner of the char.
 *
 * \param[in]        dev: The handle of the device
 * \param[in]       xPos: The x position
 * \param[in]       yPos: The y position
 * \param[in]          c: The char to be draw
 * \param[in]      color: The foreground color of the char
 * \param[in] background: The background color of the char
 * \param[in]       size: The size for the char, if 0 use default dimension
 * \return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the char
 *         exceeds the width or height of the display, GDL_ERRORS_OK otherwise.
 */
GDL_Errors_t GDL_drawChar (GDL_DeviceHandle_t dev,
                           uint16_t xPos,
                           uint16_t yPos,
                           uint8_t c,
                           uint8_t color,
                           uint8_t background,
                           uint8_t size);

/*!
 * The function print a picture from an array of pixel, in the selected
 * position.
 * Every pixel can be described from 1, 4, 8 or 24 bit.
 * The starting point is the top-left corner of the picture.
 *
 * \param[in]       dev: The handle of the device
 * \param[in]      xPos: The x position
 * \param[in]      yPos: The y position
 * \param[in]     width: The picture dimension along the x axis
 * \param[in]    height: The picture dimension along the y axis
 * \param[in]   picture: The array of picture to be printed
 * \param[in] pixelType: The number of bit for each pixel. This value represent the
 *                       number of color
 * \return GDL_ERRORS_WRONG_POSITION if the dimension plus position of the picture
 *         exceeds the width or height of the display, GDL_ERRORS_OK otherwise.
 */
GDL_Errors_t GDL_drawPicture (GDL_DeviceHandle_t dev,
                              uint16_t xPos,
                              uint16_t yPos,
                              uint16_t width,
                              uint16_t height,
                              const uint8_t* picture,
                              GDL_PictureType_t pixelType);

/*!
 * \}
 */

/*!
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif // __WARCOMEB_GDL_H
