#ifndef _LI_BITMAP_H_
#define _LI_BITMAP_H_
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <wchar.h>
#include <iostream>
#include <time.h>
#include <zbar.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "qrencode.h"
using namespace cv;
using namespace std;
using namespace zbar;




///OUT_FILE为储存路径，可自己修改
#define OUT_FILE                    "aa.bmp"


#define OUT_FILE_PIXEL_PRESCALER    16
#define PIXEL_COLOR_R               0        
#define PIXEL_COLOR_G               0
#define PIXEL_COLOR_B               0      
#pragma pack(push, 1)
 

//以下为bmp一些相关结构体的定义
typedef unsigned char  U8;
typedef unsigned short U16;
typedef unsigned int   U32;
 
typedef struct tagBITMAPFILEHEADER
{
 
 U16 bfType;
 U32 bfSize;
 U16 bfReserved1;
 U16 bfReserved2;
 U32 bfOffBits;
} BITMAPFILEHEADER;
 
typedef struct tagBITMAPINFOHEADER
{
 U32 biSize;
 U32 biWidth;
 U32 biHeight;
 U16 biPlanes;
 U16 biBitCount;
 U32 biCompression;
 U32 biSizeImage;
 U32 biXPelsPerMeter;
 U32 biYPelsPerMeter;
 U32 biClrUsed;
 U32 biClrImportant;
} BITMAPINFOHEADER;
 
typedef struct tagRGBQUAD
{
 U8 rgbBlue;
 U8 rgbGreen;
 U8 rgbRed;
 U8 rgbReserved;
} RGBQUAD;
 
typedef struct tagBITMAPINFO
{
 BITMAPINFOHEADER bmiHeader;
 RGBQUAD bmiColors[1];
} BITMAPINFO;
 
 
typedef struct tagBITMAP
{
 BITMAPFILEHEADER bfHeader;
 BITMAPINFO biInfo;
}BITMAPFILE;
 
#pragma pack(pop)

#endif
 

