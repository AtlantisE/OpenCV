#include "stdafx.h"

////int main() {
////	string xmlPath = "D:\\lin\\opencv\\build\\etc\\haarcascades\\haarcascade_frontalface_default.xml";
////	Mat src = imread("D:\\lin\\vs\\images\\friends7.jpg", 1);
////	
////	CascadeClassifier ccf;
////	if (!ccf.load(xmlPath)) {
////		cout << "不能加载指定的xml文件" << endl;
////		return 0;
////	}
////
////	vector<Rect> faces;
////	Mat gray;
////	cvtColor(src, gray, CV_BGR2GRAY);
////	equalizeHist(gray, gray);
////	ccf.detectMultiScale(gray, faces, 1.5, 3, 0, Size(10, 10), Size(100, 100));
////	for (vector<Rect>::const_iterator iter = faces.begin();
////		iter != faces.end(); iter++) {
////		rectangle(src, *iter, Scalar(0, 0, 255), 2, 8);
////	}
////
////	imshow("faces", src);
////	waitKey(0);
////	
////	return 1;
////}