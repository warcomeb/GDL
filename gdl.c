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

#include "gdl.h"

#include <stdlib.h>

#define GDL_SWAP_INT16(a,b) do { \
    int16_t t = a;               \
    a = b;                       \
    b = t;                       \
    } while (0);


void GDL_drawLine (GDL_Device* dev,
                   uint16_t xStart,
                   uint16_t yStart,
                   uint16_t xStop,
                   uint16_t yStop,
                   uint8_t color)
{
    int16_t dx = xStop - xStart;
    int16_t dy = yStop - yStart;
    int16_t yStep = 1;
    bool inverte = FALSE;

    if (abs(dx) < abs(dy))
    {
        GDL_SWAP_INT16(xStart, yStart);
        GDL_SWAP_INT16(xStop, yStop);
        inverte = TRUE;
    }

    if (xStart > xStop)
    {
        GDL_SWAP_INT16(xStart, xStop);
        GDL_SWAP_INT16(yStart, yStop);
    }

    // Update dx and dy
    dx = xStop - xStart;
    dy = abs(yStop - yStart);

    yStep = (yStart < yStop) ? 1 : -1;

    int16_t d = 2 * dy - dx;

    for (uint16_t i = 0; i < dx; ++i)
    {
        if (d > 0)
        {
            d = d - 2 * dx + 2 * dy;
            yStart += yStep;
        }
        else
        {
            d = 2 * dy + d;
        }
        xStart++;
        if (!inverte)
            dev->drawPixel(dev,xStart,yStart,color);
        else
            dev->drawPixel(dev,yStart,xStart,color);
    }
}
