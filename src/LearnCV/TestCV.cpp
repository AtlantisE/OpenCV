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
	if (strVideoFile == "")
	{
		cap.open(0);//random a camera opened
	}
	else
	{
		cap.open(strVideoFile);
	}
	
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

void TestCV::onTrackbarSlide(int pos, void*)
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);
	if (!g_dontset)
	{
		g_run = 1;
	}
	g_dontset = 0;
}

int TestCV::Chapter2_addTrackbarSlideInVideo(const string& strVideoFile)
{
	int status = OK;
	namedWindow("Video", cv::WINDOW_AUTOSIZE);
	g_cap.open(strVideoFile);
	int frames = g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);
	cout << "Video have  " << frames << " frames of dimensions(" << tmpw << ", " << tmph << ")." << endl;

	cv::createTrackbar("Position", "Video", &g_slider_position, frames, onTrackbarSlide);

	cv::Mat frame;
	for (;;)
	{
		if (g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty())
			{
				status = FALSE;
				goto exit;
			}
			int current_pos = g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Video", current_pos);
			cv::imshow("Video", frame);

			g_run -= 1;
		}
		char c = waitKey(33);
		if (c == 'S')
		{
			g_run = 1;
			cout << "Single step, run=" << g_run << endl;
		}
		if (c == 'R')
		{
			g_run = -1;
			cout << "Run mode, run = " << g_run << endl;
		}
		if (c == 27)
			break;
	}

exit:
	destroyWindow("Video");
	return status;
}

int TestCV::Chapter2_GaussianBlur(const cv::Mat& image)
{
	int status = OK;
	namedWindow("Origin image", cv::WINDOW_AUTOSIZE);
	namedWindow("Gaussian1 image", cv::WINDOW_AUTOSIZE);
	namedWindow("Gaussian2 image", cv::WINDOW_AUTOSIZE);

	imshow("Origin image", image);
	cout << "origin image size: (" << image.rows << "," << image.cols << ")" << endl;
	Mat out;
	GaussianBlur(image, out, Size(5, 5), 3, 3);
	imshow("Gaussian1 image", out);
	cout << "Gaussian1 image size: (" << out.rows << "," << out.cols << ")" << endl;
	imwrite("..\\..\\resources\\images\\Gaussian1_5x5.jpg", out);
	GaussianBlur(out, out, Size(5, 5), 3, 3);
	imshow("Gaussian2 image", out);

	cout << "Gaussian2 image size: (" << out.rows << "," << out.cols << ")" << endl;
	imwrite("..\\..\\resources\\images\\Gaussian2_5x5.jpg", out);
	if (waitKey(0) == 27)
	{
		goto exit;
	}

exit:
	destroyAllWindows();
	return status;

}

int TestCV::Chapter2_PyrDown(const cv::Mat& image)
{
	int status = OK;
	Mat out;
	
	if (image.empty())
	{
		status = FALSE;
		goto exit;
	}
	namedWindow("Origin image", WINDOW_AUTOSIZE);
	imshow("Origin image", image);
	cout << "origin image size: (" << image.rows << "," << image.cols << ")" << endl;

	
	pyrDown(image, out);
	namedWindow("PyrDown image", WINDOW_AUTOSIZE);
	imshow("PyrDown image", out);
	cout << "PyrDown image size: (" << out.rows << "," << out.cols << ")" << endl;

	if (waitKey(0) == 27)
	{
		goto exit;
	}
exit:
	destroyAllWindows();
	return status;

}
int TestCV::Chapter2_Canny(const Mat& img_color)
{
	int status = OK;
	Mat img_gray, img_out;

	if (img_color.empty())
	{
		status = FALSE;
		goto exit;
	}
	namedWindow("Color", WINDOW_AUTOSIZE);
	imshow("Color", img_color);
	cout << "color image size: (" << img_color.rows << "," << img_color.cols << ")" << endl;

	cvtColor(img_color, img_gray, COLOR_BGR2GRAY);
	namedWindow("Gray", WINDOW_AUTOSIZE);
	imshow("Gray", img_gray);
	cout << "gray image size: (" << img_gray.rows << "," << img_gray.cols << ")" << endl;

	Canny(img_gray, img_out, 10, 100, 3, true);

	namedWindow("Edge", WINDOW_AUTOSIZE);
	imshow("Edge", img_out);
	cout << "edge image size: (" << img_out.rows << "," << img_out.cols << ")" << endl;

	if (waitKey(0) == 27)
	{
		goto exit;
	}

exit:
	destroyAllWindows();
	return status;
}

TestCV* TestCV::m_pstTCV = NULL;
int TestCV::g_dontset = 0;
int TestCV::g_run = 1;
int TestCV::g_slider_position = 0;
VideoCapture TestCV::g_cap;