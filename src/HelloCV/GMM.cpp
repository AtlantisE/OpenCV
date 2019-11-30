//  ���ڻ�ϸ�˹ģ�͵��˶�Ŀ����
//  Author�� www.icvpr.com 
//  Blog�� http://blog.csdn.net/icvpr  
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

		// �˶�ǰ����⣬�����±���
		bgsubtractor->apply(frame, foreground, 0.001);

		// ��ʴ
		erode(foreground, foreground, Mat());

		// ����
		dilate(foreground, foreground, Mat());

		bgsubtractor->getBackgroundImage(background);// ���ص�ǰ����ͼ��  

		imshow("video", foreground);
		imshow("background", background);

		cvWaitKey(30);
	}



	return 0;
}