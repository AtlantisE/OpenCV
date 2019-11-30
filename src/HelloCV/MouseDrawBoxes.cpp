// HelloCV.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

//鼠标绘制矩形回调函数
void my_mouse_callback(int event, int x, int y, int flags, void* param);

CvRect box;
bool drawing_box = false;

//绘制矩形函数
void draw_box(IplImage* img, CvRect rect) {
	cvRectangle(
		img,
		cvPoint(box.x, box.y),
		cvPoint(box.x+box.width, box.y+box.height),
		cvScalar(0xff, 0x00, 0x00)//red
	);
}

//int main()
//{
//	/*IplImage* image = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("Long", 1);
//	cvShowImage("Long", image);
//	cvWaitKey();
//	cvReleaseImage(&image);
//	cvDestroyWindow("Long");*/
//
//	box = cvRect(-1, -1, 0, 0);
//
//	IplImage* image = cvCreateImage(
//		cvSize(200, 200),
//		IPL_DEPTH_8U,
//		3
//	);
//	cvZero(image);
//	IplImage* temp = cvCloneImage(image);
//
//	cvNamedWindow("Box Example");
//
//	cvSetMouseCallback(
//		"Box Example",
//		my_mouse_callback,
//		(void *)image
//	);
//
//	while (1) {
//		cvCopy(image, temp);
//		if (drawing_box) {
//			draw_box(temp, box);
//		}
//		cvShowImage("Box Example", temp);
//
//		if (cvWaitKey(15) == 27) {
//			break;
//		}
//	}
//
//	cvReleaseImage(&image);
//	cvReleaseImage(&temp);
//	cvDestroyWindow("Box Example");
//
//    return 0;
//}

void my_mouse_callback(int event, int x, int y, int flags, void* param) {
	IplImage* image = (IplImage*)param;

	switch (event)
	{
	case CV_EVENT_MOUSEMOVE:
		if (drawing_box) {
			box.width = x - box.x;
			box.height = y - box.y;
		}
		break;
	case CV_EVENT_LBUTTONDOWN:
		drawing_box = true;
		box = cvRect(x, y, 0, 0);
		break;
	case CV_EVENT_LBUTTONUP:
		drawing_box = false;
		if (box.width < 0) {
			box.x += box.width;
			box.width *= -1;
		}
		if (box.height < 0) {
			box.y += box.height;
			box.height *= -1;
		}
		draw_box(image, box);
		break;
		default:
			break;
	}
}

