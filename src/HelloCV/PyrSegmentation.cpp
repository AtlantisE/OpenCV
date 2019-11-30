#include "stdafx.h"
using namespace std;

//void doPrySegmentation(IplImage* src, IplImage* dst) {
//	assert(src->width % 2 == 0 && src->height % 2 == 0);
//
//	CvMemStorage* storage = cvCreateMemStorage(0);
//	CvSeq* comp = NULL;
//
//	int level = 3;
//	double threshold1 = 150;
//	double threshold2 = 30;
//	cvPyrSegmentation(src, dst, storage, &comp, level, threshold1, threshold2);
//}

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long6.jpeg");
//	IplImage* dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	doPrySegmentation(src, dst);
//	cvNamedWindow("Src");
//	cvShowImage("Src", src);
//	cvNamedWindow("Dst");
//	cvShowImage("Dst", dst);
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dst);
//	cvDestroyAllWindows();
//	return 0;
//}