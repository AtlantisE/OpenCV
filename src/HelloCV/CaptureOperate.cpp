#include "stdafx.h"

using namespace std;
//
//int main() {
//	
//	IplImage* pFrame = NULL;
//
//	CvCapture* pCapture = cvCreateCameraCapture(-1);
//
//	cvNamedWindow("video", 1);
//	
//	while (1) {
//		pFrame = cvQueryFrame(pCapture);
//		if (!pFrame) {
//			break;
//		}
//		cvShowImage("video", pFrame);
//		if (cvWaitKey(33) == 27) {
//			break;
//		}
//	}
//
//	cvReleaseCapture(&pCapture);
//	cvDestroyWindow("video");
//
//	return 0;
//}