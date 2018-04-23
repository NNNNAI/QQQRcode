#include <li_bitmap.h>
//生成BMP图片(无颜色表的位图):在RGB(A)位图数据的基础上加上文件信息头和位图信息头
//filename为生成的BMP储存的路径，bitCountPerPix通常为24与32，建议设为24
//szSourceSring为二维码对应的字符串值，verion为二维码的的版本数，若设置为0，则有代码决定版本数
int GenqrcodeBmp(const char *filename,U8 bitCountPerPix,char *szSourceSring,int version);
//释放GetBmpData分配的空间
void FreeBmpData(U8 *pdata);
//生成长度为len的随机字符串
char *rand_str(char *str, const int len);

char *rand_str(char *str, const int len)
{
	srand(time(NULL));
	int i;
	for (i = 0; i<len; ++i)
	{
		switch ((rand() % 3))
		{
		case 1:
			str[i] = 'A' + rand() % 26;
			break;
		case 2:
			str[i] = 'a' + rand() % 26;
			break;
		default:
			str[i] = '0' + rand() % 10;
			break;
		}
	}
	str[i] = '\0';
	return str;
}

int GenqrcodeBmp(const char *filename,U8 bitCountPerPix,const char *szSourceSring,int version=0)
{
    	U32    unWidth, x, y, l, n, unWidthAdjusted, unDataBytes,filesize;
	unsigned char*  pRGBData, *pSourceData, *pDestData;
	QRcode*         pQRC;
	FILE *fp = fopen(filename, "wb");  
        if(!fp)  
        {  
        printf("fopen failed : %s, %d\n", __FILE__, __LINE__);  
        return 0;  
        }  
        if (pQRC = QRcode_encodeString(szSourceSring, version, QR_ECLEVEL_H, QR_MODE_8, 1))
		{
                        U8 *pData=pQRC->data;
			unWidth = pQRC->width;
			unWidthAdjusted = unWidth * OUT_FILE_PIXEL_PRESCALER * 3;
			if (unWidthAdjusted % 4)
				unWidthAdjusted = (unWidthAdjusted / 4 + 1) * 4;
			unDataBytes = unWidthAdjusted * unWidth * OUT_FILE_PIXEL_PRESCALER;
                        filesize=unDataBytes;
			// Allocate pixels buffer

			 BITMAPFILE bmpfile;  
  
                         bmpfile.bfHeader.bfType = 0x4D42;  
                         bmpfile.bfHeader.bfSize = filesize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  
                         bmpfile.bfHeader.bfReserved1 = 0;  
                         bmpfile.bfHeader.bfReserved2 = 0;  
                         bmpfile.bfHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);  
  
                         bmpfile.biInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);  
                         bmpfile.biInfo.bmiHeader.biWidth = unWidth * OUT_FILE_PIXEL_PRESCALER;  
                         bmpfile.biInfo.bmiHeader.biHeight = -((int)unWidth * OUT_FILE_PIXEL_PRESCALER);  
                         bmpfile.biInfo.bmiHeader.biPlanes = 1;  
                         bmpfile.biInfo.bmiHeader.biBitCount = bitCountPerPix;  
                         bmpfile.biInfo.bmiHeader.biCompression = 0;  
                         bmpfile.biInfo.bmiHeader.biSizeImage = 0;  
                         bmpfile.biInfo.bmiHeader.biXPelsPerMeter = 0;  
                         bmpfile.biInfo.bmiHeader.biYPelsPerMeter = 0;  
                         bmpfile.biInfo.bmiHeader.biClrUsed = 0;  
                         bmpfile.biInfo.bmiHeader.biClrImportant = 0;  
  
                         fwrite(&(bmpfile.bfHeader), sizeof(BITMAPFILEHEADER), 1, fp);  
                         fwrite(&(bmpfile.biInfo.bmiHeader), sizeof(BITMAPINFOHEADER), 1, fp);  
  
    U8 *pEachLinBuf = (U8*)malloc(unDataBytes);  
    memset(pEachLinBuf, 255, unDataBytes);  

     for (y = 0; y < unWidth; y++)
        {
            pDestData = pEachLinBuf + unWidthAdjusted * y * OUT_FILE_PIXEL_PRESCALER;
            for (x = 0; x < unWidth; x++)
            {
                if (*pData & 1)
                {
                    for (l = 0; l < OUT_FILE_PIXEL_PRESCALER; l++)
                    {
                        for (n = 0; n < OUT_FILE_PIXEL_PRESCALER; n++)
                        {
                            *(pDestData + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_B;
                            *(pDestData + 1 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_G;
                            *(pDestData + 2 + n * 3 + unWidthAdjusted * l) = PIXEL_COLOR_R;
                        }
                    }
                }
                pDestData += 3 * OUT_FILE_PIXEL_PRESCALER;
                pData++;
            }
        }


    fwrite(pEachLinBuf, unDataBytes, 1, fp); 

    fclose(fp);  
    FreeBmpData(pEachLinBuf)  ;
    return 1;  
		}
		else
		{
			printf("NULL returned");
			return 0;
		}

}
  

  
//释放GetBmpData分配的空间  
void FreeBmpData(U8 *pdata)  
{  
    if(pdata)  
    {  
        free(pdata);  
        pdata = NULL;  
    }  
}  
 



///以下是一个测试代码，可以自行修改
  
int main()
{
   Mat srcImage;
   int flag;

   char context[256];
   namedWindow("src", WINDOW_NORMAL);
   //生成一个长度为20的char变量并赋值给context
   rand_str(context, 20);
   const char* the_path = OUT_FILE;
   cout << context << endl;
   //若二维码生成成功则读取并显示出来
   if (GenqrcodeBmp(the_path,24, context))
	{
		srcImage = imread(the_path);
		imshow("src", srcImage);
                waitKey(0);
	}
   return 1;
}
