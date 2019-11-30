#include "stdafx.h"

using namespace std;

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	IplImage* gray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	IplImage* canny = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCvtColor(src, gray, CV_BGR2GRAY);
//	CvMemStorage* storage = cvCreateMemStorage(0);
//	cvSmooth(gray, gray, CV_GAUSSIAN, 3, 3);
//	cvCanny(gray, canny, 100, 150, 3);
//	cvNamedWindow("gray");
//	cvShowImage("gray", gray);
//	CvSeq* results = cvHoughCircles(gray, storage, CV_HOUGH_GRADIENT, 2, 200);
//	for (int i = 0; i < results->total; i++) {
//		float* p = (float*)cvGetSeqElem(results, i);
//		CvPoint pt = cvPoint(cvRound(p[0]), cvRound(p[1]));
//		cvCircle(src, pt, cvRound(p[2]), CV_RGB(0xff, 0xff, 0xff));
//	}
//
//	cvNamedWindow("Hough Circle");
//	cvShowImage("Hough Circle", src);
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&gray);
//	cvReleaseMemStorage(&storage);
//	cvDestroyAllWindows();
//
//	return 0;
//}