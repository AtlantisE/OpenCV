#include "stdafx.h"

using namespace std;

//int main() {
//	IplImage* srcImg = cvLoadImage("D:\\lin\\vs\\images\\gesture\\gesture5.jpg");
//	cvNamedWindow("RGB");
//	cvShowImage("RGB", srcImg);
//
//	cvNamedWindow("YCbCr");
//	IplImage* ycbcrImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 3);
//	cvCvtColor(srcImg, ycbcrImg, CV_BGR2YCrCb);
//	cvShowImage("YCbCr", ycbcrImg);
//
//	cvNamedWindow("HSV");
//	IplImage* hsvImg = cvCreateImage(cvGetSize(srcImg), IPL_DEPTH_8U, 3);
//	cvCvtColor(srcImg, hsvImg, CV_BGR2HSV);
//	cvShowImage("HSV", hsvImg);
//	
//	cvWaitKey(0);
//	cvReleaseImage(&srcImg);
//	cvReleaseImage(&ycbcrImg);
//	cvReleaseImage(&hsvImg);
//	cvDestroyAllWindows();
//
//	return 0;
//}