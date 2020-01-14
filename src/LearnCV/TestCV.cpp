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

int TestCV::Chapter2_VideoWriter(const string& strVideoFile)
{
	int status = OK;
	
	VideoWriter vwriter;
	VideoCapture cap;
	double fps = 0;
	Size size;
	Mat logpolar_frame, bgr_frame;

	cap.open(0);//open camera
	if (cap.isOpened() == false)
	{
		cout << "Error:Camera open failed!" << endl;
		status = FALSE;
		goto exit;
	}

	fps = cap.get(CAP_PROP_FPS);
	size.width = cap.get(CAP_PROP_FRAME_WIDTH);
	size.height = cap.get(CAP_PROP_FRAME_HEIGHT);
	vwriter.open(strVideoFile, 0, fps, size);

	namedWindow("Color", WINDOW_AUTOSIZE);
	namedWindow("LogPolar", WINDOW_AUTOSIZE);
	for (;;)
	{
		cap >> bgr_frame;
		if (bgr_frame.empty())
		{
			cout << "Error: get frame failed from CaptureVideo!" << endl;
			status = FALSE;
			goto exit;
		}
		imshow("Color", bgr_frame);

		logPolar(bgr_frame, logpolar_frame, Point2f(bgr_frame.cols / 4, bgr_frame.rows / 4),
			40, WARP_FILL_OUTLIERS);
		imshow("LogPolar", logpolar_frame);
		vwriter << logpolar_frame;
		if (waitKey(10) == 27)
			break;

	}

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter5_AddWeighted(const string& strImgFile1,
	const string& strImgFile2,
	const double alpha,
	const double beta,
	const double gamma)
{

	int status = OK;
	Mat src1 = imread(strImgFile1);
	Mat src2 = imread(strImgFile2);
	Mat out;
	//check img whether empty
	if (src1.empty() || src2.empty())
	{
		cout << "Error:Mat src1 or src2 is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	
	addWeighted(src1, alpha, src2, beta, gamma, out);
	cout << "weighted image: width=" << out.cols << ", height=" << out.rows << endl;
	imwrite("..\\..\\resources\\images\\chapter5\\weight.bmp", out);
	namedWindow("AddWeight", WINDOW_AUTOSIZE);
	imshow("AddWeight", out);
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter10_CopyMakeBorder(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat dstImg;
	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);

	copyMakeBorder(srcImg, dstImg, 10, 10, 10, 10, cv::BORDER_CONSTANT);
	
	if (dstImg.empty())
	{
		cout << "Error:Mat dstImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "dstImg cols=" << dstImg.cols << ", rows=" << dstImg.rows << endl;

	namedWindow("Border Image", WINDOW_AUTOSIZE);
	imshow("Border Image", dstImg);
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Common_CvtColorToGrey(const string& strColorImgFile)
{
	int status = OK;
	Mat srcColorImg = imread(strColorImgFile);
	Mat grayImg;

	//check img whether empty
	if (srcColorImg.empty())
	{
		cout << "Error:Mat srcColorImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Color Image", WINDOW_AUTOSIZE);
	imshow("Src Color Image", srcColorImg);

	cvtColor(srcColorImg, grayImg, COLOR_BGR2GRAY);

	if (grayImg.empty())
	{
		cout << "Error:Mat grayImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Gray Image", WINDOW_AUTOSIZE);
	imshow("Gray Image", grayImg);
	imwrite("../../resources/images/lena_gray.bmp", grayImg);
	cout << "gray image rows=" << grayImg.rows << ", cols=" << grayImg.cols << ", channels=" << grayImg.channels() << endl;

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Common_Split(const string& strColorImgFile)
{
	int status = OK;
	Mat srcColorImg = imread(strColorImgFile);
	vector<Mat> splitImg;
	Mat bImg, gImg, rImg;

	//check img whether empty
	if (srcColorImg.empty())
	{
		cout << "Error:Mat srcColorImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	split(srcColorImg, splitImg);

	namedWindow("Src Color Image", WINDOW_AUTOSIZE);
	imshow("Src Color Image", srcColorImg);

	bImg = splitImg[0];
	gImg = splitImg[1];
	rImg = splitImg[2];

	if (bImg.empty() || gImg.empty() || rImg.empty())
	{
		cout << "Error:Mat bImg or gImg or rImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	
	namedWindow("Blue Image", WINDOW_AUTOSIZE);
	imshow("Blue Image", bImg);

	namedWindow("Green Image", WINDOW_AUTOSIZE);
	imshow("Green Image", gImg);

	namedWindow("Red Image", WINDOW_AUTOSIZE);
	imshow("Red Image", rImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter10_Threshold(const string& strSrcGrayImgFile)
{
	int status = OK;
	Mat srcGrayImg = imread(strSrcGrayImgFile);
	Mat thresImg;
	double thres_otsu = 0.0;

	//check img whether empty
	if (srcGrayImg.empty())
	{
		cout << "Error:Mat srcGrayImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Gray Image", WINDOW_AUTOSIZE);
	imshow("Src Gray Image", srcGrayImg);
	
	adaptiveThreshold(srcGrayImg, thresImg, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 3, 10);
	//thres_otsu = threshold(srcGrayImg, thresImg, 0, 255, THRESH_OTSU);
	//cout << "otsu threshold value=" << thres_otsu << endl;

	//threshold(srcGrayImg, thresImg, thres_otsu, 255, THRESH_BINARY);

	if (thresImg.empty())
	{
		cout << "Error:Mat thresImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Threshold Image", WINDOW_AUTOSIZE);
	imshow("Threshold Image", thresImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter10_GaussianBlur(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat gaussianBlurImg;
	double sigmaX = 0;
	double sigmaY = 0;
	Size kernel_size = { 3,3 };

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;
	GaussianBlur(srcImg, gaussianBlurImg, kernel_size, sigmaX, sigmaY, BORDER_REFLECT101);

	if (gaussianBlurImg.empty())
	{
		cout << "Error:Mat gaussianBlurImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "gaussian image rows=" << gaussianBlurImg.rows << ", cols=" << gaussianBlurImg.cols << endl;
	namedWindow("GaussianBlur Image", WINDOW_AUTOSIZE);
	if (gaussianBlurImg.channels() == 3)
	{
		Mat grayImg;
		cvtColor(gaussianBlurImg, grayImg, COLOR_RGB2GRAY);
		imwrite("..\\..\\resources\\images\\gaussian_3x3.bmp", grayImg);
	}
	
	imshow("GaussianBlur Image", gaussianBlurImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter10_BilateralFilter(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat bilateralImg;
	
	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;
	bilateralFilter(srcImg, bilateralImg, -1, 50, 10, BORDER_REFLECT101);

	if (bilateralImg.empty())
	{
		cout << "Error:Mat bilateralImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "bilateral image rows=" << bilateralImg.rows << ", cols=" << bilateralImg.cols << endl;
	namedWindow("BilateralFilter Image", WINDOW_AUTOSIZE);

	imshow("BilateralFilter Image", bilateralImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter10_DilateAndErode(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile, CV_8U);
	Mat dilateImg, erodeImg, kernel, gradImg;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << ", channels="<< srcImg.channels()<< endl;
	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	for (int row = 0; row < kernel.rows; row++)
	{
		for (int col = 0; col < kernel.cols; col++)
		{
			cout << int(kernel.at<uchar>(row, col)) << "\t";
		}
		cout << endl;
	}

	erode(srcImg, erodeImg, kernel, Point(-1, -1), 1, BORDER_CONSTANT, 0);
	if (erodeImg.empty())
	{
		cout << "Error:Mat erodeImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	imwrite("../../resources/images/erode.bmp", erodeImg);
	cout << "erode image rows=" << erodeImg.rows << ", cols=" << erodeImg.cols << ", channels=" << erodeImg.channels() << endl;

	namedWindow("Erode Image", WINDOW_AUTOSIZE);

	imshow("Erode Image", erodeImg);

	dilate(srcImg, dilateImg, kernel, Point(-1, -1), 1, BORDER_CONSTANT, 0);
	imwrite("../../resources/images/dilate.bmp", dilateImg);
	if (dilateImg.empty())
	{
		cout << "Error:Mat dilateImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "dilate image rows=" << dilateImg.rows << ", cols=" << dilateImg.cols << ", channels=" << dilateImg.channels() << endl;

	namedWindow("Dilate Image", WINDOW_AUTOSIZE);

	imshow("Dilate Image", dilateImg);

	gradImg = dilateImg - erodeImg;
	if (gradImg.empty())
	{
		cout << "Error:Mat gradImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "gradient image rows=" << gradImg.rows << ", cols=" << gradImg.cols << ", channels=" << gradImg.channels() << endl;

	namedWindow("Gradient Image", WINDOW_AUTOSIZE);

	imshow("Gradient Image", gradImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_PyDown_Up(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile, CV_8U);
	Mat pyDownImg, pyUpImg, diffImg, addImg;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;
	
	pyrDown(srcImg, pyDownImg);
	if (pyDownImg.empty())
	{
		cout << "Error:Mat pyDownImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "PyrDown image rows=" << pyDownImg.rows << ", cols=" << pyDownImg.cols << endl;
	namedWindow("PyDown Image", WINDOW_AUTOSIZE);
	imshow("PyDown Image", pyDownImg);

	//pyrUp(srcImg, pyUpImg);
	pyrUp(pyDownImg, pyUpImg);
	if (pyUpImg.empty())
	{
		cout << "Error:Mat pyUpImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	cout << "PyUp image rows=" << pyUpImg.rows << ", cols=" << pyUpImg.cols << endl;
	namedWindow("PyUp Image", WINDOW_AUTOSIZE);
	imshow("PyUp Image", pyUpImg);
	imwrite("../../resources/images/pydown_up.bmp", pyUpImg);

	diffImg = srcImg - pyUpImg;
	namedWindow("srcImg - Up(Down(srcImg))", WINDOW_AUTOSIZE);
	imshow("srcImg - Up(Down(srcImg))", diffImg);

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_BuildPyramid(const string& strSrcImgFile)

{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile, CV_8U);
	vector<Mat> vecPyrImg;
	vector<Mat>::iterator iterPyrImg;
	int i = 0;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;

	buildPyramid(srcImg, vecPyrImg, 3);

	if (vecPyrImg.empty())
	{
		cout << "Error:vector<Mat> vecPyrImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	iterPyrImg = vecPyrImg.begin();
	for (; iterPyrImg != vecPyrImg.end(); iterPyrImg++)
	{
		stringstream ss;
		ss << "PyDown Image " << i;
		cout << ss.str() <<" rows=" << iterPyrImg->rows << ", cols=" << iterPyrImg->cols << endl;
		namedWindow(ss.str(), WINDOW_AUTOSIZE);
		imshow(ss.str(), *iterPyrImg);
		i++;
	}
	
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_WarpAffine(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile, CV_8U);
	Point2f srcPoints[3], dstPoints[3];
	Mat warpMat, dstImg;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;

	srcPoints[0] = { 0, 0 };
	srcPoints[1] = { 0, float(srcImg.cols) };
	srcPoints[2] = { float(srcImg.rows), 0 };

	dstPoints[0] = { 0, 0 };
	dstPoints[1] = { 50, float(srcImg.cols - 50) };
	dstPoints[2] = { float(srcImg.rows - 50), 50 };
	
	warpMat = getAffineTransform(srcPoints, dstPoints);
	if (warpMat.empty())
	{
		cout << "Error:Mat warpMat is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	warpAffine(srcImg, dstImg, warpMat, srcImg.size()*2, INTER_LINEAR, BORDER_CONSTANT, 0);
	if (dstImg.empty())
	{
		cout << "Error:vMat dstImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Dst Image", WINDOW_AUTOSIZE);
	imshow("Dst Image", dstImg);
	cout << "Dst image rows=" << dstImg.rows << ", cols=" << dstImg.cols << endl;
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_WarpPerspective(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile, CV_8U);
	Point2f srcPoints[4], dstPoints[4];
	Mat warpMat, dstImg;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;

	srcPoints[0] = { 0, 0 };
	srcPoints[1] = { 0, float(srcImg.cols-1) };
	srcPoints[3] = { float(srcImg.rows-1), 0 };
	srcPoints[2] = { float(srcImg.rows-1), float(srcImg.cols-1) };

	dstPoints[0] = { 0, 0 };
	dstPoints[1] = { 90, float(srcImg.cols - 1) };
	dstPoints[3] = { float(srcImg.rows - 1), 0 };
	dstPoints[2] = { float(srcImg.rows - 1),  float(srcImg.cols - 1) };

	warpMat = getPerspectiveTransform(srcPoints, dstPoints);
	if (warpMat.empty())
	{
		cout << "Error:Mat warpMat is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	warpPerspective(srcImg, dstImg, warpMat, srcImg.size() * 2, INTER_LINEAR, BORDER_CONSTANT, 0);
	if (dstImg.empty())
	{
		cout << "Error:vMat dstImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("WarpPerspective Image", WINDOW_AUTOSIZE);
	imshow("WarpPerspective Image", dstImg);
	cout << "Dst image rows=" << dstImg.rows << ", cols=" << dstImg.cols << endl;
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_CartPolar(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat dstLogPolarImg, dstLinPolarImg;
	Point2f pointCenter;
	double maxRadius = 0;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;
	pointCenter.x = srcImg.rows * 0.5f;
	pointCenter.y = srcImg.cols * 0.5f;

	maxRadius = srcImg.rows * 0.1f;
	logPolar(srcImg, dstLogPolarImg, pointCenter, maxRadius, INTER_LINEAR | WARP_FILL_OUTLIERS);
	if (dstLogPolarImg.empty())
	{
		cout << "Error:Mat dstLogPolarImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("LogPolar Image", WINDOW_AUTOSIZE);
	imshow("LogPolar Image", dstLogPolarImg);
	cout << "LogPolar image rows=" << dstLogPolarImg.rows << ", cols=" << dstLogPolarImg.cols << endl;

	maxRadius = srcImg.rows * 0.5f;
	linearPolar(srcImg, dstLinPolarImg, pointCenter, maxRadius, INTER_LINEAR | WARP_FILL_OUTLIERS);
	if (dstLinPolarImg.empty())
	{
		cout << "Error:vMat dstLinPolarImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("LinearPolar Image", WINDOW_AUTOSIZE);
	imshow("LinearPolar Image", dstLinPolarImg);
	cout << "LinearPolar image rows=" << dstLinPolarImg.rows << ", cols=" << dstLinPolarImg.cols << endl;
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_Remap(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat dstImg, xMapImg, yMapImg;
	int i = 0, j = 0;

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	xMapImg = Mat(srcImg.size(), CV_32FC1);
	yMapImg = Mat(srcImg.size(), CV_32FC1);

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;
	
	for (int j = 0; j < srcImg.rows; j++)
	{
		for (int i = 0; i < srcImg.cols; i++)
		{
			xMapImg.at<float>(j, i) = srcImg.cols - i;//flip x
			//yMapImg.at<float>(j, i) = srcImg.rows - j;//flip y
			yMapImg.at<float>(j, i) = j;
			//cout << xMapImg.at<float>(j, i) << ends;
		}
		//cout << endl;
	}

	//namedWindow("XMap Image", WINDOW_AUTOSIZE);
	//imshow("XMap Image", xMapImg);
	//cout << "XMap image rows=" << xMapImg.rows << ", cols=" << xMapImg.cols << endl;

	//namedWindow("YMap Image", WINDOW_AUTOSIZE);
	//imshow("YMap Image", yMapImg);
	//cout << "YMap image rows=" << yMapImg.rows << ", cols=" << yMapImg.cols << endl;

	remap(srcImg, dstImg, xMapImg, yMapImg, INTER_LINEAR, BORDER_CONSTANT, 0);
	if (dstImg.empty())
	{
		cout << "Error:Mat dstImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Remap Image", WINDOW_AUTOSIZE);
	imshow("Remap Image", dstImg);
	cout << "Remap image rows=" << dstImg.rows << ", cols=" << dstImg.cols << endl;
	
	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

int TestCV::Chapter11_Inpaint(const string& strSrcImgFile)
{
	int status = OK;
	Mat srcImg = imread(strSrcImgFile);
	Mat dstImg, maskImg, srcGrayImg;
	int i = 0, j = 0;
	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

	//check img whether empty
	if (srcImg.empty())
	{
		cout << "Error:Mat srcImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Src Image", WINDOW_AUTOSIZE);
	imshow("Src Image", srcImg);
	cout << "src image rows=" << srcImg.rows << ", cols=" << srcImg.cols << endl;

	if (srcImg.channels() == 3)
	{
		cvtColor(srcImg, srcGrayImg, COLOR_BGR2GRAY);
	}
	else
	{
		srcGrayImg = srcImg.clone();
	}

	namedWindow("Gray Image", WINDOW_AUTOSIZE);
	imshow("Gray Image", srcGrayImg);
	cout << "Gray image rows=" << srcGrayImg.rows << ", cols=" << srcGrayImg.cols << endl;

	maskImg = Mat(srcImg.size(), CV_8UC1, Scalar(0));
	if (maskImg.empty())
	{
		cout << "Error:Mat maskImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}
	threshold(srcGrayImg, maskImg, 240, 255, THRESH_BINARY);
	dilate(maskImg, maskImg, kernel);

	namedWindow("Mask Image", WINDOW_AUTOSIZE);
	imshow("Mask Image", maskImg);
	cout << "Mask image rows=" << maskImg.rows << ", cols=" << maskImg.cols << endl;

	inpaint(srcImg, maskImg, dstImg, 5.0, INPAINT_TELEA);
	if (dstImg.empty())
	{
		cout << "Error:Mat dstImg is empty!" << endl;
		status = FALSE;
		goto exit;
	}

	namedWindow("Inpaint Image", WINDOW_AUTOSIZE);
	imshow("Inpaint Image", dstImg);
	cout << "Inpaint image rows=" << dstImg.rows << ", cols=" << dstImg.cols << endl;

	waitKey(0);

exit:
	destroyAllWindows();
	return status;
}

TestCV* TestCV::m_pstTCV = NULL;
int TestCV::g_dontset = 0;
int TestCV::g_run = 1;
int TestCV::g_slider_position = 0;
VideoCapture TestCV::g_cap;