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

#ifndef __WARCOMEB_GDL_TYPE_H
#define __WARCOMEB_GDL_TYPE_H

#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \defgroup GDL_Type
 * \ingroup GDL
 * \{
 */

/*!
 * \defgroup GDL_Type_ModelType
 * \{
 */
#define GDL_MODELTYPE_SSD1306                    0x0100
#define GDL_MODELTYPE_SSD1325                    0x0200
#define GDL_MODELTYPE_SSD1327ZB                  0x0300
/*!
 * \}
 */

/*!
 * List of possible errors.
 */
typedef enum _GDL_Errors_t
{
    GDL_ERRORS_SUCCESS,
    GDL_ERRORS_WRONG_POSITION,
    GDL_ERRORS_WRONG_VALUE,
} GDL_Errors_t;

/*!
 * List of picture type.
 * The difference is into color depth per pixel.
 */
typedef enum _GDL_PictureType_t
{
    GDL_PICTURETYPE_1BIT  = 1,
    GDL_PICTURETYPE_4BIT  = 4,
    GDL_PICTURETYPE_8BIT  = 8,
    GDL_PICTURETYPE_24BIT = 24,
} GDL_PictureType_t;

/*!
 * \defgroup GDL_Type_ProtocolType
 * \{
 */
#define GDL_PROTOCOLTYPE_PARALLEL                0
#define GDL_PROTOCOLTYPE_I2C                     1
#define GDL_PROTOCOLTYPE_SPI                     2
/*!
 * \}
 */

/*!
 * \}
 */

#ifdef __cplusplus
}
#endif

#endif // __WARCOMEB_GDL_TYPE_H
