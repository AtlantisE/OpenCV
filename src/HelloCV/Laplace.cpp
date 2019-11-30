#include "stdafx.h"

using namespace std;

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\\\gesture\\gesture11.jpg");
//	IplImage* gaussianImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	IplImage* srcLaplaceImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	IplImage* gaussianLaplaceImg = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//
//	cvNamedWindow("Gaussian");
//	cvSmooth(src, gaussianImg, CV_GAUSSIAN, 3, 3);
//	cvShowImage("Gaussian", gaussianImg);
//
//	cvNamedWindow("SRC to Laplace");
//	cvLaplace(src, srcLaplaceImg, 3);
//	cvShowImage("SRC to Laplace", srcLaplaceImg);
//
//	cvNamedWindow("Gaussian to Laplace");
//	cvLaplace(gaussianImg, gaussianLaplaceImg, 3);
//	cvShowImage("Gaussian to Laplace", gaussianLaplaceImg);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&gaussianImg);
//	cvReleaseImage(&srcLaplaceImg);
//	cvReleaseImage(&gaussianLaplaceImg);
//	cvDestroyAllWindows();
//
//	return 0;
//}