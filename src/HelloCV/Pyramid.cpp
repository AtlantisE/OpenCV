#include "stdafx.h"
using namespace std;

//int main() {
//
//	IplImage * src = cvLoadImage("D:\\lin\\vs\\images\\long6.jpeg");
//	IplImage* dst = cvCreateImage(cvSize(src->width / 2, src->height / 2), src->depth, src->nChannels);
//	cvPyrDown(src, dst, CV_GAUSSIAN_5x5);
//
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//
//	cvNamedWindow("Pyr");
//	cvShowImage("Pyr", dst);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dst);
//	cvDestroyAllWindows();
//
//	return 0;
//}