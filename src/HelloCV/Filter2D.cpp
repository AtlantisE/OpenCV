#include "stdafx.h"

using namespace std;

//int main() {
//
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	IplImage* dst;
//
//	float k[9] = { 1.0, -2.0, 1.0,
//					2.0, -4.0, 2.0,
//					1.0, -2.0, 1.0 };
//	CvMat km = cvMat(3, 3, CV_32FC1, k);
//
//	dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	
//	cvNamedWindow("Src", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Src", src);
//
//	cvFilter2D(src, dst, &km, cvPoint(-1, -1));
//	cvNamedWindow("Filtering", CV_WINDOW_AUTOSIZE);
//	cvShowImage("Filtering", dst);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dst);
//	cvDestroyAllWindows();
//
//	return 0;
//}