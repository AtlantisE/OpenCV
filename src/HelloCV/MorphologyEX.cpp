#include "stdafx.h"
using namespace std;

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long1.jpg");
//	cvNamedWindow("Src");
//	cvNamedWindow("Open");
//	cvNamedWindow("Close");
//	cvNamedWindow("Gradient");
//	cvNamedWindow("TopHat");
//	cvNamedWindow("BlackHat");
//
//	cvShowImage("Src", src);
//
//	IplImage* temp = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	IplImage* img = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	cvCopy(src, temp);
//	cvCopy(src, img);
//
//	cvMorphologyEx(src, img, temp, 0, CV_MOP_OPEN, 1);
//	cvShowImage("Open", img);
//
//	cvMorphologyEx(src, img, temp, 0, CV_MOP_CLOSE, 1);
//	cvShowImage("Close", img);
//
//	cvMorphologyEx(src, img, temp, 0, CV_MOP_GRADIENT, 1);
//	cvShowImage("Gradient", img);
//
//	cvMorphologyEx(src, img, temp, 0, CV_MOP_TOPHAT, 1);
//	cvShowImage("TopHat", img);
//
//	cvMorphologyEx(src, img, temp, 0, CV_MOP_BLACKHAT, 1);
//	cvShowImage("BlackHat", img);
//
//	cvWaitKey(0);
//
//	cvReleaseImage(&src);
//	cvReleaseImage(&temp);
//	cvReleaseImage(&img);
//	cvDestroyAllWindows();
//
//	return 0;
//}