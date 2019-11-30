#include "stdafx.h"
#include <iostream>
using namespace std;

//int main() {
//	IplImage* src = cvLoadImage("D:\\lin\\vs\\images\\long8.jpg");
//	IplImage* gray = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCvtColor(src, gray, CV_BGR2GRAY);
//
//	IplImage* canny = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 1);
//	cvCanny(gray, canny, 20, 200, 3);
//
//	CvMemStorage* storage = cvCreateMemStorage(0);
//	CvSeq* lines = cvHoughLines2(canny, storage, CV_HOUGH_PROBABILISTIC, 1, CV_PI / 180, 80, 200, 10);//第一个参数必须是二值图像
//
//	IplImage* dst = cvCreateImage(cvGetSize(src), IPL_DEPTH_8U, 3);
//	cvCvtColor(gray, dst, CV_GRAY2BGR);
//
//	for (int i = 0; i < lines->total; i++) {
//		CvPoint* line = (CvPoint*)cvGetSeqElem(lines, i);
//		cvLine(dst, line[0], line[1], CV_RGB(255, 0, 0), 1, 8);
//	}
//
//	cvNamedWindow("src", 1);
//	cvNamedWindow("canny", 1);
//	cvNamedWindow("hough", 1);
//	cvShowImage("src", src);
//	cvShowImage("canny", canny);
//	cvShowImage("hough", dst);
//
//	cvWaitKey(0);
//	cvReleaseImage(&src);
//	cvReleaseImage(&dst);
//	cvReleaseImage(&gray);
//	cvReleaseImage(&canny);
//	cvReleaseMemStorage(&storage);
//
//
//	return 0;
//}