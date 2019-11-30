#include "stdafx.h"

using namespace std;

//int main() {
//
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	IplImage* dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//
//	//cvSobel(src, dst, 1, 1 , 3);
//	cvSobel(src, dst, 1, 1, 3);
//	cvNamedWindow("Sobel");
//	cvShowImage("Sobel", dst);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dst);
//	cvDestroyAllWindows();
//
//	return 0;
//}