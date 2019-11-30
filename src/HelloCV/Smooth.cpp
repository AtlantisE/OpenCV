#include "stdafx.h"
using namespace std;

//int main() {
//	IplImage* pImg = cvLoadImage("D:\\lin\\vs\\images\\long1.jpg", 1);
//
//	cvNamedWindow("Smooth In");
//	cvNamedWindow("Smooth out GAUSSIAN");
//	cvNamedWindow("Smooth out BLUR NO SCALE");
//	cvNamedWindow("Smooth out BLUR");
//	cvNamedWindow("Smooth out MEDIAN");
//	cvNamedWindow("Smooth out BILATERAL");
//
//	cvShowImage("Smooth In",pImg);
//
//	IplImage* out1 = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//	IplImage* out2 = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//	IplImage* out3 = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//	IplImage* out4 = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//	IplImage* out5 = cvCreateImage(cvGetSize(pImg), IPL_DEPTH_8U, 3);
//
//	cvSmooth(pImg, out1, CV_GAUSSIAN, 3, 3);
//	cvSmooth(pImg, out2, CV_BLUR_NO_SCALE, 3, 3);
//	cvSmooth(pImg, out3, CV_BLUR, 3, 3);
//	cvSmooth(pImg, out4, CV_MEDIAN, 3, 3);
//	cvSmooth(pImg, out5, CV_BILATERAL, 3, 3);
//
//	cvShowImage("Smooth out GAUSSIAN", out1);
//	cvShowImage("Smooth out BLUR NO SCALE", out2);
//	cvShowImage("Smooth out BLUR", out3);
//	cvShowImage("Smooth out MEDIAN", out4);
//	cvShowImage("Smooth out BILATERAL", out5);
//
//	cvWaitKey(0);
//	cvReleaseImage(&pImg);
//	cvReleaseImage(&out1);
//	cvReleaseImage(&out2);
//	cvReleaseImage(&out3);
//	cvReleaseImage(&out4);
//	cvReleaseImage(&out5);
//	cvDestroyAllWindows();
//
//	return 0;
//}