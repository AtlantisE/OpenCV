#include "stdafx.h"
using namespace std;

//int main() {
//	IplImage* p = cvLoadImage("D:\\lin\\vs\\images\\long1.jpg", CV_WINDOW_AUTOSIZE);
//	cvNamedWindow("Src");
//	cvShowImage("Src", p);
//
//	IplConvKernel* model = cvCreateStructuringElementEx(5, 5, 3, 3, CV_SHAPE_RECT);
//
//	IplImage* erode = cvCreateImage(cvGetSize(p), IPL_DEPTH_8U, 3);
//	cvErode(p, erode, model, 1);
//	cvNamedWindow("Erode");
//	cvShowImage("Erode", erode);
//
//	IplImage* dilate = cvCreateImage(cvGetSize(p), IPL_DEPTH_8U, 3);
//	cvDilate(p, dilate, model, 1);
//	cvNamedWindow("Dilate");
//	cvShowImage("Dilate", dilate);
//
//	IplImage* erodeThenDilate = cvCreateImage(cvGetSize(p), IPL_DEPTH_8U, 3);
//	cvDilate(erode, erodeThenDilate, model, 1);
//	cvNamedWindow("First Erode Then Dilate");
//	cvShowImage("First Erode Then Dilate", erodeThenDilate);
//
//	IplImage* dilateThenErode = cvCreateImage(cvGetSize(p), IPL_DEPTH_8U, 3);
//	cvErode(dilate, dilateThenErode, model, 1);
//	cvNamedWindow("First Dilate Then Erode");
//	cvShowImage("First Dilate Then Erode", dilateThenErode);
//
//	
//
//	cvWaitKey(0);
//	cvReleaseImage(&p);
//	cvReleaseImage(&erode);
//	cvReleaseImage(&dilate);
//	cvReleaseImage(&erodeThenDilate);
//	cvReleaseImage(&dilateThenErode);
//	cvDestroyAllWindows();
//
//	return 0;
//}