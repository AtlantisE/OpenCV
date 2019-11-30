#include "stdafx.h"
using namespace std;

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	IplImage* graySrc = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCvtColor(src, graySrc, CV_BGR2GRAY);
//
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//
//	cvNamedWindow("Gray Src");
//	cvShowImage("Gray Src", graySrc);
//
//	IplImage* dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCanny(graySrc, dst, 100, 150, 3);
//	cvNamedWindow("Canny");
//	cvShowImage("Canny", dst);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&graySrc);
//	cvReleaseImage(&dst);
//	cvDestroyAllWindows();
//
//	return 0;
//}