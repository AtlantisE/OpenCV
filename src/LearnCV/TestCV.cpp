#include<TestCV.h>

int TestCV::Chapter2_ReadImage(const string& strImgFile)
{
	int status = OK;
	Mat image;

	image = imread(strImgFile);
	if (image.empty())
	{
		cout << "Read Error" << endl;
		status = FALSE;
		goto exit;
	}

	cout << "This image is " << image.rows << " x " << image.cols << endl;

	namedWindow("Original Image", WINDOW_AUTOSIZE);
	imshow("Original Image", image);

	exit:
	waitKey(0);
	destroyWindow("Original Image");
	return status;
}

int TestCV::Chapter2_ReadVideo(const string& strVideoFile)
{
	int status = OK;
	Mat frame;
	VideoCapture cap;
	int count = 0;//count frame number

	namedWindow("Video", WINDOW_AUTOSIZE);
	cap.open(strVideoFile);
	if (cap.isOpened() == false)
	{
		cout << "Video <" << strVideoFile << "> open failed!" << endl;
		status = FALSE;
		goto exit;
	}

	
	for (;;)
	{
		count++;
		cap >> frame;
		if (frame.empty())
		{
			cout << "The " << count << " frame image read failed!" << endl;
			status = FALSE;
			goto exit;
		}
		imshow("Video", frame);
		if (waitKey(33) >= 0)
		{
			break;
		}
	}

exit:
	destroyWindow("Video");
	return status;
}

TestCV* TestCV::m_pstTCV = NULL;