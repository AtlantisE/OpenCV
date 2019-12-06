#include<TestCV.h>

TestCV* pTCV = TestCV::getInstance();

int testChapter2_ReadImage(const std::string& strFile)
{
	int status = pTCV->Chapter2_ReadImage(strFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_ReadImage failed" << endl;
	}
	return status;
}

int testChapter2_ReadVideo(const std::string& strFile)
{
	int status = pTCV->Chapter2_ReadVideo(strFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_ReadVideo failed!" << endl;
	}
	return status;
}

int testChapter2_ReadVideoWithSlider(const std::string& strFile)
{
	int status = pTCV->Chapter2_addTrackbarSlideInVideo(strFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_addTrackbarSlideInVideo failed!" << endl;
	}
	return status;
}

int testChapter2_GaussianBlur(const std::string& strFile)
{
	Mat image = imread(strFile);
	int status = pTCV->Chapter2_GaussianBlur(image);
	if (status == FALSE)
	{
		cout << "TestCV::hapter2_GaussianBlur failed!" << endl;
	}
	return status;

}

int testChapter2_PyrDown(const std::string& strFile)
{
	Mat image = imread(strFile);
	int status = pTCV->Chapter2_PyrDown(image);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_PyrDown failed!" << endl;
	}
	return status;

}

int testChapter2_Canny(const std::string& strFile)
{
	Mat image = imread(strFile);
	int status = pTCV->Chapter2_Canny(image);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_Canny failed!" << endl;
	}
	return status;

}

int main()
{
	int status = OK;
	
	string strImgFile = "..\\..\\resources\\images\\hand.jpg";
	string strVideoFile = "..\\..\\resources\\videos\\dldl8080.mp4";
	string strGirlImgFile= "..\\..\\resources\\images\\lena.jpg";
	string strGirlColorFile = "..\\..\\resources\\images\\lena_color.jpg";

	/*status = testChapter2_ReadImage(strImgFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	//status = testChapter2_ReadVideo(strVideoFile);
	//if (status == FALSE)
	//{
	//	goto exit;
	//}

	/*status = testChapter2_ReadVideoWithSlider(strVideoFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	/*status = testChapter2_GaussianBlur(strGirlImgFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	/*status = testChapter2_PyrDown(strGirlImgFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	/*status = testChapter2_Canny(strGirlColorFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	//read image from camera
	status = testChapter2_ReadVideo("");
	if (status == FALSE)
	{
		goto exit;
	}

exit:
	system("pause");
	return 0;
}