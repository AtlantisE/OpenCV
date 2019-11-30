//  基于混合高斯模型的运动目标检测
//  Author： www.icvpr.com 
//  Blog： http://blog.csdn.net/icvpr  
#include "stdafx.h"

int main(int argc, char** argv)
{
	string videoFile = "D:\\lin\\vs\\videos\\bike.avi";

	VideoCapture capture;
	capture.open(videoFile);

	if (!capture.isOpened())
	{
		std::cout << "read video failure" << std::endl;
		return -1;
	}


	Ptr<BackgroundSubtractorMOG2> bgsubtractor = createBackgroundSubtractorMOG2();
	bgsubtractor->setVarThreshold(20);

	Mat foreground;
	Mat background;

	Mat frame;
	long frameNo = 0;
	while (capture.read(frame))
	{
		++frameNo;

		cout <<"Frame No:"<< frameNo << endl;

		// 运动前景检测，并更新背景
		bgsubtractor->apply(frame, foreground, 0.001);

		// 腐蚀
		erode(foreground, foreground, Mat());

		// 膨胀
		dilate(foreground, foreground, Mat());

		bgsubtractor->getBackgroundImage(background);// 返回当前背景图像  

		imshow("video", foreground);
		imshow("background", background);

		cvWaitKey(30);
	}



	return 0;
}