#include "stdafx.h"
using namespace std;

//int main() {
//	double threshold = 100;
//	int threshold_type = CV_THRESH_BINARY;
//	int adaptive_method = CV_ADAPTIVE_THRESH_GAUSSIAN_C;
//	int block_size = 5;
//	double offset = 5.0;
//
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//
//	IplImage* Igray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCvtColor(src, Igray, CV_BGR2GRAY);
//	cvNamedWindow("Gray");
//	cvShowImage("Gray", Igray);
//
//	IplImage* It = cvCreateImage(cvGetSize(Igray), IPL_DEPTH_8U, 1);
//	IplImage* Iat = cvCreateImage(cvGetSize(Igray), IPL_DEPTH_8U, 1);
//	cvThreshold(Igray, It, threshold, 255, threshold_type);
//	cvNamedWindow("Threshold", 1);
//	cvShowImage("Threshold", It);
//
//	cvAdaptiveThreshold(Igray, Iat, 255, adaptive_method, threshold_type, block_size, offset);
//	cvNamedWindow("Adaptive Threshold");
//	cvShowImage("Adaptive Threshold", Iat);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&Igray);
//	cvReleaseImage(&It);
//	cvReleaseImage(&Iat);
//	cvDestroyAllWindows();
//	return 0;
//
//}