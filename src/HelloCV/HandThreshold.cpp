#include "stdafx.h"

using namespace std;

//otsu实现，先找阈值，然后二值化
//void cvThresholdOtsu(IplImage* src, IplImage* dst) {
//	int height = src->height;
//	int width = src->width;
//
//	if (src->nChannels != 1) {
//		cvCvtColor(src, src, CV_BGR2GRAY);
//	}
//
//	//histogram
//	float histogram[256] = { 0 };
//	for (int i = 0; i < height; i++) {
//		unsigned char* p = (unsigned char*)src->imageData + src->widthStep * i;
//		for (int j = 0; j < width; j++) {
//			if (*(p+j) > 137 && *(p + j) < 175) {//cr值在人肤色范围内
//			}
//			else {//非肤色（背景色），置为黑色
//				*(p + j) = 0;
//			}
//			histogram[*(p + j)]++;
//		}
//	}
//
//	//normalize histogram
//	int size = height*width;
//	for (int i = 0; i < 256; i++) {
//		histogram[i] = histogram[i] / size;
//	}
//
//	//average pixel value
//	float avgValue = 0;
//	for (int i = 0; i < 256; i++) {
//		avgValue += i*histogram[i];
//	}
//
//	int threshold;
//	float maxVariance = 0;
//	float w = 0;
//	float u = 0;
//	for (int i = 0; i < 256; i++) {
//		w += histogram[i];
//		u += i*histogram[i];
//
//		float t = avgValue*w - u;
//		float variance = t*t / (w*(1 - w));
//		if (variance > maxVariance) {
//			maxVariance = variance;
//			threshold = i;
//		}
//	}
//
//	cvThreshold(src, dst, threshold, 255, CV_THRESH_BINARY);
//}
//
//int cvThresholdOtsu(IplImage* src) {
//	int height = src->height;
//	int width = src->width;
//	cout << "width:" << width << "\t height:" << height << endl;
//	if (src->nChannels != 1) {
//		cvCvtColor(src, src, CV_BGR2GRAY);
//	}
//
//	//histogram
//	float histogram[256] = { 0 };
//	for (int i = 0; i < height; i++) {
//		unsigned char* p = (unsigned char*)src->imageData + src->widthStep * i;
//		for (int j = 0; j < width; j++) {
//			histogram[*p++]++;
//		}
//	}
//
//	//normalize histogram
//	int size = height*width;
//	for (int i = 0; i < 256; i++) {
//		histogram[i] = histogram[i] / size;
//	}
//
//	//average pixel value
//	float avgValue = 0;
//	for (int i = 0; i < 256; i++) {
//		avgValue += i*histogram[i];
//	}
//
//	int threshold;
//	float maxVariance = 0;
//	float w = 0;
//	float u = 0;
//	for (int i = 0; i < 256; i++) {
//		w += histogram[i];
//		u += i*histogram[i];
//
//		float t = avgValue*w - u;
//		float variance = t*t / (w*(1 - w));
//		if (variance > maxVariance) {
//			maxVariance = variance;
//			threshold = i;
//		}
//	}
//
//	return threshold;
//}
//
//int main() {
//	//video process
//	/*
//	CvCapture* capture = cvCreateCameraCapture(-1);
//	if (!capture) {
//		cout << "Failed to open camera" << endl;
//		exit(0);
//	}
//
//	int threshold = -1;
//	IplImage* img;
//	while (img = cvQueryFrame(capture)) {
//		cvShowImage("Video", img);
//		cvCvtColor(img, img, CV_BGR2YCrCb);
//
//		IplImage* imgCb = cvCreateImage(cvGetSize(img), 8, 1);
//		cvSplit(img, NULL, NULL, imgCb, NULL);
//		if (threshold < 0) {
//			threshold = cvThresholdOtsu(imgCb);
//		}
//
//		cvThreshold(imgCb, imgCb, threshold, 255, CV_THRESH_BINARY);
//		cvErode(imgCb, imgCb);
//		cvDilate(imgCb, imgCb);
//
//		cvShowImage("Object", imgCb);
//		cvReleaseImage(&imgCb);
//
//		if (cvWaitKey(3) == 27) {
//			break;
//		}
//	}
//
//	cvReleaseCapture(&capture);
//	*/
//
//	//single image process
//	
//	cvNamedWindow("Src");
//	IplImage* img = cvLoadImage("D:\\lin\\vs\\images\\gesture\\gesture11.jpg");
//	cvShowImage("Src", img);
//
//	cvNamedWindow("YCrCb");
//	IplImage* img_y = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
//	IplImage* img_cr = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
//	IplImage* img_cb = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1);
//	cvCvtColor(img, img, CV_BGR2YCrCb);
//	cvShowImage("YCrCb", img);
//
//	cvNamedWindow("YCrCb-Y");
//	cvSplit(img, img_y, NULL, NULL, NULL);
//	cvShowImage("YCrCb-Y", img_y);
//
//	cvNamedWindow("YCrCb-Cr");
//	cvSplit(img, NULL, img_cr, NULL, NULL);
//	cvShowImage("YCrCb-Cr", img_cr);
//
//	cvNamedWindow("YCrCb-Cb");
//	cvSplit(img, NULL, NULL, img_cb, NULL);
//	cvShowImage("YCrCb-Cb", img_cb);
//
//	//肤色检测
//	/*
//	cvNamedWindow("Cr137-175");
//	int height = img_cr->height;
//	int width = img_cr->width;
//
//	if (img_cr->nChannels != 1) {
//		cvCvtColor(img_cr, img_cr, CV_BGR2GRAY);
//	}
//
//	for (int i = 0; i < height; i++) {
//		unsigned char* p = (unsigned char*)img_cr->imageData + img_cr->widthStep * i;
//		for (int j = 0; j < width; j++) {
//			if (p[j] > 137 && p[j] < 175) {
//				p[j] = 255;
//			}
//			else {
//				p[j] = 0;
//			}
//		}
//	}
//	cvShowImage("Cr137-175", img_cr);
//*/
//	//最大类间方差法实现手势的阈值分割
//	cvNamedWindow("YCrCb+Otsu");
//	cvThresholdOtsu(img_cr, img_cr);
//	cvShowImage("YCrCb+Otsu", img_cr);
//
//	//形态学处理：开运算
//	cvNamedWindow("Open");
//	cvErode(img_cr, img_cr);
//	cvDilate(img_cr, img_cr);
//	cvShowImage("Open", img_cr);
//
//	//形态学处理：闭运算
//	/*cvNamedWindow("Close");
//	cvDilate(img_cr, img_cr);
//	cvErode(img_cr, img_cr);
//	cvShowImage("Close", img_cr);*/
//
//	cvWaitKey(0);
//	cvReleaseImage(&img);
//
//	
//
//	/*
//	Mat src, result, tmp;
//	Mat Y, Cr, Cb;
//	vector<Mat> channels;
//
//	namedWindow("Src");
//	src = imread("D:\\lin\\vs\\images\\gesture\\gesture11.jpg");
//	imshow("Src", src);
//
//	namedWindow("YCrCb");
//	cvtColor(src, tmp, CV_BGR2YCrCb);
//	imshow("YCrCb", tmp);
//
//	namedWindow("Result");
//	split(tmp, channels);
//	Y = channels.at(0);
//	Cr = channels.at(1);
//	Cb = channels.at(2);
//
//	result.create(tmp.rows, tmp.cols, CV_8UC1);
//
//		//遍历图像，将符合阈值范围的像素设置为255，其余为0
//		for (int j = 1; j < Y.rows - 1; j++)
//		{
//			uchar* currentCr = Cr.ptr< uchar>(j);
//			uchar* currentCb = Cb.ptr< uchar>(j);
//			uchar* current = result.ptr< uchar>(j);
//			for (int i = 1; i < Y.cols - 1; i++)
//			{
//				//if ((currentCr[i] > 137) && (currentCr[i] < 175) && (currentCb[i] > 100) && (currentCb[i] < 118))
//				if ((currentCr[i] > 137) && (currentCr[i] < 175) && (currentCb[i] > 100) && (currentCb[i] < 140))
//					current[i] = 255;
//				else
//					current[i] = 0;
//			}
//		}
//
//	imshow("Result", result);
//
//	namedWindow("Open");
//	Mat kernal1 = getStructuringElement(MORPH_RECT, cvSize(3, 3));
//	erode(result, result, kernal1);
//	Mat kernal2 = getStructuringElement(MORPH_RECT, cvSize(5, 5));
//	dilate(result, result, kernal2);
//	imshow("Open", result);
//
//	waitKey(0);
//	destroyAllWindows();
//	*/
//
//	return 0;
//}