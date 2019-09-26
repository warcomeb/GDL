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

/*!
 * \file  /gdl.c
 * \brief
 */

#include "gdl.h"

#include <stdlib.h>

/** Generic font */
static const char GDL_BASIC_FONT[256][6]=
{
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x00
    {0x00,0x7C,0xA2,0x8A,0xA2,0x7C},    // 0x01
    {0x00,0x7C,0xD6,0xF6,0xD6,0x7C},    // 0x02
    {0x00,0x38,0x7C,0x3E,0x7C,0x38},    // 0x03
    {0x00,0x18,0x3C,0x7E,0x3C,0x18},    // 0x04
    {0x00,0x0C,0x6C,0xFE,0x6C,0x0C},    // 0x05
    {0x00,0x18,0x3A,0x7E,0x3A,0x18},    // 0x06
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x07
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x08
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x09
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x0A
    {0x00,0x0C,0x12,0x52,0x6C,0x70},    // 0x0B
    {0x00,0x60,0x94,0x9E,0x94,0x60},    // 0x0C
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x0D
    {0x00,0x06,0x7E,0x50,0xAC,0xFC},    // 0x0E
    {0x00,0x54,0x38,0x6C,0x38,0x54},    // 0x0F
    {0x00,0x00,0xFE,0x7C,0x38,0x10},    // 0x10
    {0x00,0x10,0x38,0x7C,0xFE,0x00},    // 0x11
    {0x00,0x28,0x6C,0xFE,0x6C,0x28},    // 0x12
    {0x00,0x00,0xFA,0x00,0xFA,0x00},    // 0x13
    {0x00,0x60,0x90,0xFE,0x80,0xFE},    // 0x14
    {0x00,0x44,0xB2,0xAA,0x9A,0x44},    // 0x15
    {0x00,0x06,0x06,0x06,0x06,0x00},    // 0x16
    {0x00,0x28,0x6D,0xFF,0x6D,0x28},    // 0x17
    {0x00,0x20,0x60,0xFE,0x60,0x20},    // 0x18
    {0x00,0x08,0x0C,0xFE,0x0C,0x08},    // 0x19
    {0x00,0x10,0x10,0x7C,0x38,0x10},    // 0x1A
    {0x00,0x10,0x38,0x7C,0x10,0x10},    // 0x1B
    {0x00,0x1E,0x02,0x02,0x02,0x02},    // 0x1C
    {0x00,0x10,0x7C,0x10,0x7C,0x10},    // 0x1D
    {0x00,0x0C,0x3C,0xFC,0x3C,0x0C},    // 0x1E
    {0x00,0xC0,0xF0,0xFC,0xF0,0xC0},    // 0x1F
    {0x00,0x00,0x00,0x00,0x00,0x00},    // 0x20
    {0x00,0x00,0x60,0xFA,0x60,0x00},    // 0x21
    {0x00,0xE0,0xC0,0x00,0xE0,0xC0},    // 0x22
    {0x00,0x24,0x7E,0x24,0x7E,0x24},    // 0x23
    {0x00,0x24,0xD4,0x56,0x48,0x00},    // 0x24
    {0x00,0xC6,0xC8,0x10,0x26,0xC6},    // 0x25
    {0x00,0x6C,0x92,0x6A,0x04,0x0A},    // 0x26
    {0x00,0x00,0xE0,0xC0,0x00,0x00},    // 0x27
    {0x00,0x00,0x7C,0x82,0x00,0x00},    // 0x28
    {0x00,0x00,0x82,0x7C,0x00,0x00},    // 0x29
    {0x00,0x10,0x7C,0x38,0x7C,0x10},    // 0x2A
    {0x00,0x10,0x10,0x7C,0x10,0x10},    // 0x2B
    {0x00,0x00,0x07,0x06,0x00,0x00},    // 0x2C
    {0x00,0x10,0x10,0x10,0x10,0x10},    // 0x2D
    {0x00,0x00,0x06,0x06,0x00,0x00},    // 0x2E
    {0x00,0x04,0x08,0x10,0x20,0x40},    // 0x2F
    {0x00,0x7C,0x8A,0x92,0xA2,0x7C},    // 0x30
    {0x00,0x00,0x42,0xFE,0x02,0x00},    // 0x31
    {0x00,0x46,0x8A,0x92,0x92,0x62},    // 0x32
    {0x00,0x44,0x92,0x92,0x92,0x6C},    // 0x33
    {0x00,0x18,0x28,0x48,0xFE,0x08},    // 0x34
    {0x00,0xF4,0x92,0x92,0x92,0x8C},    // 0x35
    {0x00,0x3C,0x52,0x92,0x92,0x0C},    // 0x36
    {0x00,0x80,0x8E,0x90,0xA0,0xC0},    // 0x37
    {0x00,0x6C,0x92,0x92,0x92,0x6C},    // 0x38
    {0x00,0x60,0x92,0x92,0x94,0x78},    // 0x39
    {0x00,0x00,0x36,0x36,0x00,0x00},    // 0x3A
    {0x00,0x00,0x37,0x36,0x00,0x00},    // 0x3B
    {0x00,0x10,0x28,0x44,0x82,0x00},    // 0x3C
    {0x00,0x24,0x24,0x24,0x24,0x24},    // 0x3D
    {0x00,0x00,0x82,0x44,0x28,0x10},    // 0x3E
    {0x00,0x40,0x80,0x9A,0x90,0x60},    // 0x3F
    {0x00,0x7C,0x82,0xBA,0xAA,0x78},    // 0x40
    {0x00,0x7E,0x88,0x88,0x88,0x7E},    // 0x41
    {0x00,0xFE,0x92,0x92,0x92,0x6C},    // 0x42
    {0x00,0x7C,0x82,0x82,0x82,0x44},    // 0x43
    {0x00,0xFE,0x82,0x82,0x82,0x7C},    // 0x44
    {0x00,0xFE,0x92,0x92,0x92,0x82},    // 0x45
    {0x00,0xFE,0x90,0x90,0x90,0x80},    // 0x46
    {0x00,0x7C,0x82,0x92,0x92,0x5E},    // 0x47
    {0x00,0xFE,0x10,0x10,0x10,0xFE},    // 0x48
    {0x00,0x00,0x82,0xFE,0x82,0x00},    // 0x49
    {0x00,0x0C,0x02,0x02,0x02,0xFC},    // 0x4A
    {0x00,0xFE,0x10,0x28,0x44,0x82},    // 0x4B
    {0x00,0xFE,0x02,0x02,0x02,0x02},    // 0x4C
    {0x00,0xFE,0x40,0x20,0x40,0xFE},    // 0x4D
    {0x00,0xFE,0x40,0x20,0x10,0xFE},    // 0x4E
    {0x00,0x7C,0x82,0x82,0x82,0x7C},    // 0x4F
    {0x00,0xFE,0x90,0x90,0x90,0x60},    // 0x50
    {0x00,0x7C,0x82,0x8A,0x84,0x7A},    // 0x51
    {0x00,0xFE,0x90,0x90,0x98,0x66},    // 0x52
    {0x00,0x64,0x92,0x92,0x92,0x4C},    // 0x53
    {0x00,0x80,0x80,0xFE,0x80,0x80},    // 0x54
    {0x00,0xFC,0x02,0x02,0x02,0xFC},    // 0x55
    {0x00,0xF8,0x04,0x02,0x04,0xF8},    // 0x56
    {0x00,0xFC,0x02,0x3C,0x02,0xFC},    // 0x57
    {0x00,0xC6,0x28,0x10,0x28,0xC6},    // 0x58
    {0x00,0xE0,0x10,0x0E,0x10,0xE0},    // 0x59
    {0x00,0x8E,0x92,0xA2,0xC2,0x00},    // 0x5A
    {0x00,0x00,0xFE,0x82,0x82,0x00},    // 0x5B
    {0x00,0x40,0x20,0x10,0x08,0x04},    // 0x5C
    {0x00,0x00,0x82,0x82,0xFE,0x00},    // 0x5D
    {0x00,0x20,0x40,0x80,0x40,0x20},    // 0x5E
    {0x01,0x01,0x01,0x01,0x01,0x01},    // 0x5F
    {0x00,0x00,0xC0,0xE0,0x00,0x00},    // 0x60
    {0x00,0x04,0x2A,0x2A,0x2A,0x1E},    // 0x61
    {0x00,0xFE,0x22,0x22,0x22,0x1C},    // 0x62
    {0x00,0x1C,0x22,0x22,0x22,0x14},    // 0x63
    {0x00,0x1C,0x22,0x22,0x22,0xFE},    // 0x64
    {0x00,0x1C,0x2A,0x2A,0x2A,0x10},    // 0x65
    {0x00,0x10,0x7E,0x90,0x90,0x00},    // 0x66
    {0x00,0x18,0x25,0x25,0x25,0x3E},    // 0x67
    {0x00,0xFE,0x20,0x20,0x1E,0x00},    // 0x68
    {0x00,0x00,0x00,0xBE,0x02,0x00},    // 0x69
    {0x00,0x02,0x01,0x21,0xBE,0x00},    // 0x6A
    {0x00,0xFE,0x08,0x14,0x22,0x00},    // 0x6B
    {0x00,0x00,0x00,0xFE,0x02,0x00},    // 0x6C
    {0x00,0x3E,0x20,0x18,0x20,0x1E},    // 0x6D
    {0x00,0x3E,0x20,0x20,0x1E,0x00},    // 0x6E
    {0x00,0x1C,0x22,0x22,0x22,0x1C},    // 0x6F
    {0x00,0x3F,0x22,0x22,0x22,0x1C},    // 0x70
    {0x00,0x1C,0x22,0x22,0x22,0x3F},    // 0x71
    {0x00,0x22,0x1E,0x22,0x20,0x10},    // 0x72
    {0x00,0x10,0x2A,0x2A,0x2A,0x04},    // 0x73
    {0x00,0x20,0x7C,0x22,0x24,0x00},    // 0x74
    {0x00,0x3C,0x02,0x04,0x3E,0x00},    // 0x75
    {0x00,0x38,0x04,0x02,0x04,0x38},    // 0x76
    {0x00,0x3C,0x06,0x0C,0x06,0x3C},    // 0x77
    {0x00,0x36,0x08,0x08,0x36,0x00},    // 0x78
    {0x00,0x39,0x05,0x06,0x3C,0x00},    // 0x79
    {0x00,0x26,0x2A,0x2A,0x32,0x00},    // 0x7A
    {0x00,0x10,0x7C,0x82,0x82,0x00},    // 0x7B
    {0x00,0x00,0x00,0xEE,0x00,0x00},    // 0x7C
    {0x00,0x00,0x82,0x82,0x7C,0x10},    // 0x7D
    {0x00,0x40,0x80,0x40,0x80,0x00},    // 0x7E
    {0x00,0x3C,0x64,0xC4,0x64,0x3C},    // 0x7F
    {0x00,0x78,0x85,0x87,0x84,0x48},    // 0x80
    {0x00,0xBC,0x02,0x04,0xBE,0x00},    // 0x81
    {0x00,0x1C,0x2A,0x2A,0xAA,0x90},    // 0x82
    {0x00,0x04,0xAA,0xAA,0xAA,0x1E},    // 0x83
    {0x00,0x04,0xAA,0x2A,0xAA,0x1E},    // 0x84
    {0x00,0x04,0xAA,0xAA,0x2A,0x1E},    // 0x85
    {0x00,0x04,0xEA,0xAA,0xEA,0x1E},    // 0x86
    {0x00,0x38,0x45,0x47,0x44,0x28},    // 0x87
    {0x00,0x1C,0xAA,0xAA,0xAA,0x10},    // 0x88
    {0x00,0x1C,0xAA,0x2A,0xAA,0x10},    // 0x89
    {0x00,0x1C,0xAA,0xAA,0x2A,0x10},    // 0x8A
    {0x00,0x00,0x80,0x3E,0x82,0x00},    // 0x8B
    {0x00,0x00,0x80,0xBE,0x82,0x00},    // 0x8C
    {0x00,0x00,0x80,0x3E,0x02,0x00},    // 0x8D
    {0x00,0x0E,0x94,0x24,0x94,0x0E},    // 0x8E
    {0x00,0x1E,0xF4,0xA4,0xF4,0x1E},    // 0x8F
    {0x00,0x3E,0x2A,0x2A,0xAA,0xA2},    // 0x90
    {0x00,0x2C,0x2A,0x3E,0x2A,0x1A},    // 0x91
    {0x00,0x7E,0x90,0xFE,0x92,0x92},    // 0x92
    {0x00,0x1C,0xA2,0xA2,0x9C,0x00},    // 0x93
    {0x00,0x1C,0xA2,0x22,0x9C,0x00},    // 0x94
    {0x00,0x9C,0xA2,0x22,0x1C,0x00},    // 0x95
    {0x00,0x3C,0x82,0x84,0xBE,0x00},    // 0x96
    {0x00,0xBC,0x82,0x04,0x3E,0x00},    // 0x97
    {0x00,0x39,0x85,0x06,0xBC,0x00},    // 0x98
    {0x00,0xBC,0x42,0x42,0xBC,0x00},    // 0x99
    {0x00,0x3C,0x82,0x02,0xBC,0x00},    // 0x9A
    {0x01,0x0E,0x16,0x1A,0x1C,0x20},    // 0x9B
    {0x00,0x12,0x7C,0x92,0x92,0x46},    // 0x9C
    {0x00,0x7E,0x86,0xBA,0xC2,0xFC},    // 0x9D
    {0x00,0x44,0x28,0x10,0x28,0x44},    // 0x9E
    {0x00,0x02,0x11,0x7E,0x90,0x40},    // 0x9F
    {0x00,0x04,0x2A,0xAA,0xAA,0x1E},    // 0xA0
    {0x00,0x00,0x00,0xBE,0x82,0x00},    // 0xA1
    {0x00,0x1C,0x22,0xA2,0x9C,0x00},    // 0xA2
    {0x00,0x3C,0x02,0x84,0xBE,0x00},    // 0xA3
    {0x00,0x5E,0x90,0x50,0x8E,0x00},    // 0xA4
    {0x00,0x5E,0x88,0x44,0x9E,0x00},    // 0xA5
    {0x00,0x10,0xAA,0xAA,0xAA,0x7A},    // 0xA6
    {0x00,0x72,0x8A,0x8A,0x72,0x00},    // 0xA7
    {0x00,0x0C,0x12,0xB2,0x02,0x04},    // 0xA8
    {0x7C,0x82,0xBA,0xD2,0xAA,0x7C},    // 0xA9
    {0x20,0x20,0x20,0x20,0x20,0x38},    // 0xAA
    {0x00,0xE8,0x10,0x32,0x56,0x0A},    // 0xAB
    {0x00,0xE8,0x10,0x2C,0x54,0x1E},    // 0xAC
    {0x00,0x00,0x0C,0xBE,0x0C,0x00},    // 0xAD
    {0x00,0x10,0x28,0x00,0x10,0x28},    // 0xAE
    {0x00,0x28,0x10,0x00,0x28,0x10},    // 0xAF
    {0x22,0x88,0x22,0x88,0x22,0x88},    // 0xB0
    {0x55,0xAA,0x55,0xAA,0x55,0xAA},    // 0xB1
    {0xDD,0x77,0xDD,0x77,0xDD,0x77},    // 0xB2
    {0x00,0x00,0x00,0xFF,0x00,0x00},    // 0xB3
    {0x10,0x10,0x10,0xFF,0x00,0x00},    // 0xB4
    {0x00,0x0E,0x14,0xA4,0x94,0x0E},    // 0xB5
    {0x00,0x0E,0x94,0xA4,0x94,0x0E},    // 0xB6
    {0x00,0x0E,0x94,0xA4,0x14,0x0E},    // 0xB7
    {0x7C,0x82,0xBA,0xAA,0x82,0x7C},    // 0xB8
    {0x50,0xDF,0x00,0xFF,0x00,0x00},    // 0xB9
    {0x00,0xFF,0x00,0xFF,0x00,0x00},    // 0xBA
    {0x50,0x5F,0x40,0x7F,0x00,0x00},    // 0xBB
    {0x50,0xD0,0x10,0xF0,0x00,0x00},    // 0xBC
    {0x00,0x18,0x24,0x66,0x24,0x00},    // 0xBD
    {0x00,0x94,0x54,0x3E,0x54,0x94},    // 0xBE
    {0x10,0x10,0x10,0x1F,0x00,0x00},    // 0xBF
    {0x00,0x00,0x00,0xF0,0x10,0x10},    // 0xC0
    {0x10,0x10,0x10,0xF0,0x10,0x10},    // 0xC1
    {0x10,0x10,0x10,0x1F,0x10,0x10},    // 0xC2
    {0x00,0x00,0x00,0xFF,0x10,0x10},    // 0xC3
    {0x10,0x10,0x10,0x10,0x10,0x10},    // 0xC4
    {0x10,0x10,0x10,0xFF,0x10,0x10},    // 0xC5
    {0x00,0x04,0x6A,0xAA,0x6A,0x9E},    // 0xC6
    {0x00,0x0E,0x54,0xA4,0x54,0x8E},    // 0xC7
    {0x00,0xF0,0x10,0xD0,0x50,0x50},    // 0xC8
    {0x00,0x7F,0x40,0x5F,0x50,0x50},    // 0xC9
    {0x50,0xD0,0x10,0xD0,0x50,0x50},    // 0xCA
    {0x50,0x5F,0x40,0x5F,0x50,0x50},    // 0xCB
    {0x00,0xFF,0x00,0xDF,0x50,0x50},    // 0xCC
    {0x50,0x50,0x50,0x50,0x50,0x50},    // 0xCD
    {0x50,0xDF,0x00,0xDF,0x50,0x50},    // 0xCE
    {0x00,0xBA,0x44,0x44,0x44,0xBA},    // 0xCF
    {0x00,0x44,0xAA,0x9A,0x0C,0x00},    // 0xD0
    {0x00,0x10,0xFE,0x92,0x82,0x7C},    // 0xD1
    {0x00,0x3E,0xAA,0xAA,0xAA,0x22},    // 0xD2
    {0x00,0x3E,0xAA,0x2A,0xAA,0x22},    // 0xD3
    {0x00,0x3E,0xAA,0xAA,0x2A,0x22},    // 0xD4
    {0x00,0x00,0x00,0xE0,0x00,0x00},    // 0xD5
    {0x00,0x00,0x22,0xBE,0xA2,0x00},    // 0xD6
    {0x00,0x00,0xA2,0xBE,0xA2,0x00},    // 0xD7
    {0x00,0x00,0xA2,0x3E,0xA2,0x00},    // 0xD8
    {0x10,0x10,0x10,0xF0,0x00,0x00},    // 0xD9
    {0x00,0x00,0x00,0x1F,0x10,0x10},    // 0xDA
    {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF},    // 0xDB
    {0x0F,0x0F,0x0F,0x0F,0x0F,0x0F},    // 0xDC
    {0x00,0x00,0x00,0xEE,0x00,0x00},    // 0xDD
    {0x00,0x00,0xA2,0xBE,0x22,0x00},    // 0xDE
    {0xF0,0xF0,0xF0,0xF0,0xF0,0xF0},    // 0xDF
    {0x00,0x3C,0x42,0xC2,0xBC,0x00},    // 0xE0
    {0x00,0x7F,0x52,0x52,0x2C,0x00},    // 0xE1
    {0x00,0x3C,0xC2,0xC2,0xBC,0x00},    // 0xE2
    {0x00,0xBC,0xC2,0x42,0x3C,0x00},    // 0xE3
    {0x00,0x04,0xAA,0x2A,0xAA,0x1E},    // 0xE4
    {0x00,0x5C,0xA2,0x62,0x9C,0x00},    // 0xE5
    {0x00,0x3F,0x04,0x04,0x38,0x00},    // 0xE6
    {0x00,0x7F,0x55,0x14,0x08,0x00},    // 0xE7
    {0x00,0xFF,0xA5,0x24,0x18,0x00},    // 0xE8
    {0x00,0x3C,0x02,0x82,0xBC,0x00},    // 0xE9
    {0x00,0x3C,0x82,0x82,0xBC,0x00},    // 0xEA
    {0x00,0xBC,0x82,0x02,0x3C,0x00},    // 0xEB
    {0x00,0x39,0x05,0x86,0xBC,0x00},    // 0xEC
    {0x00,0x20,0x10,0x8E,0x90,0x20},    // 0xED
    {0x00,0x00,0x40,0x40,0x40,0x00},    // 0xEE
    {0x00,0x00,0xE0,0xC0,0x00,0x00},    // 0xEF
    {0x00,0x00,0x10,0x10,0x10,0x00},    // 0xF0
    {0x00,0x00,0x24,0x74,0x24,0x00},    // 0xF1
    {0x00,0x24,0x24,0x24,0x24,0x24},    // 0xF2
    {0xA0,0xE8,0x50,0x2C,0x54,0x1E},    // 0xF3
    {0x00,0x60,0x90,0xFE,0x80,0xFE},    // 0xF4
    {0x00,0x44,0xB2,0xAA,0x9A,0x44},    // 0xF5
    {0x00,0x10,0x10,0x54,0x10,0x10},    // 0xF6
    {0x00,0x00,0x10,0x18,0x18,0x00},    // 0xF7
    {0x00,0x60,0x90,0x90,0x60,0x00},    // 0xF8
    {0x00,0x00,0x10,0x00,0x10,0x00},    // 0xF9
    {0x00,0x00,0x10,0x00,0x00,0x00},    // 0xFA
    {0x00,0x40,0xF0,0x00,0x00,0x00},    // 0xFB
    {0x00,0x90,0xF0,0xA0,0x00,0x00},    // 0xFC
    {0x00,0x90,0xB0,0x50,0x00,0x00},    // 0xFD
    {0x00,0x3C,0x3C,0x3C,0x3C,0x00},    // 0xFE
    {0x00,0x00,0x00,0x00,0x00,0x00}     // 0xFF
};

void GDL_drawLine (GDL_DeviceHandle_t dev,
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
        UTILITY_SWAP_INT16(xStart, yStart);
        UTILITY_SWAP_INT16(xStop, yStop);
        inverte = TRUE;
    }

    if (xStart > xStop)
    {
        UTILITY_SWAP_INT16(xStart, xStop);
        UTILITY_SWAP_INT16(yStart, yStop);
    }

    // Update dx and dy
    dx = xStop - xStart;
    dy = abs(yStop - yStart);

    yStep = (yStart < yStop) ? 1 : -1;

    int16_t d = 2 * dy - dx;

    for (uint16_t i = 0; i <= dx; ++i)
    {
        // Print pixel
        if (!inverte)
        {
            dev->drawPixel(dev,xStart,yStart,color);
        }
        else
        {
            dev->drawPixel(dev,yStart,xStart,color);
        }

        // Set next point
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
    }
}

void GDL_drawRectangle (GDL_DeviceHandle_t dev,
                        uint16_t xStart,
                        uint16_t yStart,
                        uint16_t width,
                        uint16_t height,
                        uint8_t color,
                        bool isFill)
{
    uint16_t xStop = xStart + width - 1;
    uint16_t yStop = yStart + height - 1;

    if (!isFill)
    {
        // Draw the border
        GDL_drawLine(dev,xStart,yStart,xStop,yStart,color);
        GDL_drawLine(dev,xStart,yStart,xStart,yStop,color);
        GDL_drawLine(dev,xStart,yStop,xStop,yStop,color);
        GDL_drawLine(dev,xStop,yStart,xStop,yStop,color);
    }
    else
    {
        for (; yStart <= yStop; ++yStart)
        {
            GDL_drawLine(dev,xStart,yStart,xStop,yStart,color);
        }
    }
}

GDL_Errors_t GDL_drawChar (GDL_DeviceHandle_t dev,
                           uint16_t xPos,
                           uint16_t yPos,
                           uint8_t c,
                           uint8_t color,
                           uint8_t background,
                           uint8_t size)
{
    // Use default size
    if (size == GDL_USE_DEFAULT_FONT_SIZE)
    {
        size = GDL_DEFAULT_FONT_SIZE;
    }

    if (!dev->useCustomFont)
    {
        // Check if the char is out of border!
        if(((xPos + GDL_DEFAULT_FONT_WIDTH * size) >= dev->width)  ||
           ((yPos + GDL_DEFAULT_FONT_HEIGHT * size) >= dev->height))
        {
            return GDL_ERRORS_WRONG_POSITION;
        }

        for (uint8_t i=0; i < GDL_DEFAULT_FONT_WIDTH; i++)
        {
            uint8_t line = GDL_BASIC_FONT[c][i];
            for (uint8_t j = 0; j < GDL_DEFAULT_FONT_HEIGHT; ++j, line <<= 1)
            {
                if (line & 0x80)
                {
                    if (size == GDL_DEFAULT_FONT_SIZE)
                    {
                        dev->drawPixel(dev,xPos + i,yPos + j,color);
                    }
                    else
                    {
                        GDL_drawRectangle(dev,(xPos + i * size),(yPos + j * size),size,size,color,TRUE);
                    }
                }
                else
                {
                    if (size == GDL_DEFAULT_FONT_SIZE)
                    {
                        dev->drawPixel(dev,xPos + i,yPos + j,background);
                    }
                    else
                    {
                        GDL_drawRectangle(dev,(xPos + i * size),(yPos + j * size),size,size,background,TRUE);
                    }

                }
            }
        }
        return GDL_ERRORS_SUCCESS;
    }
    else
    {
        return GDL_ERRORS_SUCCESS;
    }
}

GDL_Errors_t GDL_drawPicture (GDL_DeviceHandle_t dev,
                              uint16_t xPos,
                              uint16_t yPos,
                              uint16_t width,
                              uint16_t height,
                              const uint8_t* picture,
                              GDL_PictureType_t pixelType)
{
    ohiassert(((xPos + width) <= dev->width) && ((yPos + height) <= dev->height));

    // Check if the char is out of border!
    if(((xPos + width) > dev->width) || ((yPos + height) > dev->height))
        return GDL_ERRORS_WRONG_POSITION;

    if (pixelType == GDL_PICTURETYPE_1BIT)
    {
        uint16_t x,y;
        uint16_t tempWidth = width/8;

        uint16_t maxWidth = xPos + width;

        if (tempWidth == 0) tempWidth += 1;

        for (y = yPos; y < (yPos + height); y++)
        {
            for (x = 0; x < tempWidth; x++)
            {
                    dev->drawPixel(dev,xPos + (x * 8)    ,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x80) >> 7);
                if ((xPos + (x * 8) + 1) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 1,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x40) >> 6);
                if ((xPos + (x * 8) + 2) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 2,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x20) >> 5);
                if ((xPos + (x * 8) + 3) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 3,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x10) >> 4);
                if ((xPos + (x * 8) + 4) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 4,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x08) >> 3);
                if ((xPos + (x * 8) + 5) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 5,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x04) >> 2);
                if ((xPos + (x * 8) + 6) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 6,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x02) >> 1);
                if ((xPos + (x * 8) + 7) < maxWidth)
                    dev->drawPixel(dev,xPos + (x * 8) + 7,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x01));
            }
        }
        return GDL_ERRORS_SUCCESS;
    }
    else if (pixelType == GDL_PICTURETYPE_4BIT)
    {
        uint16_t tempWidth = width/2;
        uint16_t x,y;

        // FIXME The scanning is not correct!
        for (y = yPos; y < (yPos + height); y++)
        {
            for (x = xPos; x < (xPos + tempWidth); x++)
            {
                dev->drawPixel(dev,(x * 2)    ,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0xF0) >> 4);
                dev->drawPixel(dev,(x * 2) + 1,y,(picture[tempWidth*(y-yPos)+(x-xPos)] & 0x0F));
            }
        }
        return GDL_ERRORS_SUCCESS;
    }
    return GDL_ERRORS_WRONG_VALUE;
}
