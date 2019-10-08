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
 * \mainpage
 *
 * The library is a set of primitives for graphic design on display/OLED.
 * The library needs the display management driver (i.e.
 * <a href="https://github.com/warcomeb/SSD1306">SSD1306</a>) and in
 * particular the function that draws the single pixel.
 *
 * \section changelog ChangeLog
 *
 * \li v1.0.0 of 2019/10/30 - First release
 *
 * \section library External Library
 *
 * The library don't use any external library.
 *
 * \section credits Credits
 * \li Marco Giammarini (warcomeb)
 *
 * \section license License
 *
 * \code{.unparsed}
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
 * \endcode
 */

/*!
 * \defgroup GDL
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

#if !defined (GDL_DEFAULT_FONT_WIDTH)
#define GDL_DEFAULT_FONT_WIDTH                   6
#endif
#if !defined (GDL_DEFAULT_FONT_HEIGHT)
#define GDL_DEFAULT_FONT_HEIGHT                  8
#endif

#define GDL_USE_DEFAULT_FONT_SIZE                0xFF
#define GDL_DEFAULT_FONT_SIZE                    1

/*!
 * \defgroup GDL_Core
 * \{
 */

/*!
 * GDL device class.
 */
typedef struct _GDL_Device_t
{
    uint8_t width;                      /*!< Display width in number of pixel */
    uint8_t height;                    /*!< Display height in number of pixel */

    uint16_t model;         /*!< It is a unique code that represent the model */

    bool useCustomFont; /*!< Flag to show if user want use custom font or not */

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

/*!
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
 * \return
 *         \arg \ref GDL_ERRORS_WRONG_POSITION if the dimension plus position of the char
 *         exceeds the width or height of the display
 *         \arg \ref GDL_ERRORS_SUCCESS when the operations success.
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
 * \return
 *         \arg \ref GDL_ERRORS_WRONG_POSITION if the dimension plus position of the picture
 *                   exceeds the width or height of the display
 *         \arg \ref GDL_ERRORS_SUCCESS when the operations success.
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
