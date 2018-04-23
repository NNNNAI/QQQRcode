#include <iostream>  
#include <zbar.h>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;
using namespace zbar;
int main()
{

	string str;
	int NUM = 71;
	int b = 0;
	int flag_correct = 0;

	int thregroup[8] = { 50,70,100,130,170,200,230,240 };
	ImageScanner scanner;
	scanner.set_config(ZBAR_NONE, ZBAR_CFG_ENABLE, 1);
	namedWindow("test", CV_WINDOW_NORMAL);
	namedWindow("mid", CV_WINDOW_NORMAL);
	namedWindow("src", CV_WINDOW_NORMAL);
	string  ori, check;

	Mat srcImage, resizeImage, gray, filter, mid;
	int thre = 230, a = 0, flag = 0, flagnum = 10;
	createTrackbar("thre", "test", &thre, 255, 0);

	VideoCapture capture1(0);

	if (!capture1.isOpened())
	{
		cout << "***Could not initialize capturing...***\n";
		return -1;
	}

	while (1)
	{
	
		capture1 >> srcImage;
		resize(srcImage, srcImage, Size(500, 500));
		imshow("src", srcImage);
		cvtColor(srcImage, gray, CV_BGR2GRAY);

		b = 0, flag_correct = 0;
		while (flag_correct == 0 && b < 8)
		{
			thre = thregroup[b];
			gray.copyTo(mid);
			threshold(mid, mid, thre, 255, CV_THRESH_BINARY);
			imshow("mid", mid);
			/*waitKey(0);*/
			int width = mid.cols;
			int height = mid.rows;
			uchar *raw = (uchar *)mid.data;
			Image imageZbar(width, height, "Y800", raw, width * height);
			scanner.scan(imageZbar);
			Image::SymbolIterator symbol = imageZbar.symbol_begin();
			for (flag = 0; flag < flagnum; flag++)
			{
				if (imageZbar.symbol_begin() == imageZbar.symbol_end())
				{
					if (flag == flagnum - 1)
					{
						b++;
					}
					continue;
				}
				for (; symbol != imageZbar.symbol_end(); ++symbol)
				{
					ori = symbol->get_data();
					cout << "type:" << endl << symbol->get_type_name() << endl << endl;
					cout << "code：" << endl << ori << endl << endl;
					cout << "threshold" << b + 1 << endl;
					flag_correct = 1;
				}
				break;
			}

		}
		if (flag_correct == 0)
		{
			cout << "can not detect corrently,please try again" << endl;
		}
		imshow("mid", mid);
		waitKey(30);


	}
	return 0;
}
