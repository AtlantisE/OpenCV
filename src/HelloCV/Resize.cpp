#include "stdafx.h"

using namespace std;
//
//int main() {
//
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long7.jpg");
//	CvSize sz;
//	sz.width = src->width * 0.5;
//	sz.height = src->height * 0.5;
//	IplImage* dist = cvCreateImage(sz, src->depth, src->nChannels);
//
//	cvNamedWindow("Src");
//	cvNamedWindow("Dist");
//	cvResize(src, dist, CV_INTER_NN);
//
//	cvShowImage("Src", src);
//	cvShowImage("Dist", dist);
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dist);
//	cvDestroyAllWindows();
//
//	return 0;
//}