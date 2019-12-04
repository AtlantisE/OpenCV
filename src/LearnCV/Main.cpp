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

int main()
{
	int status = OK;
	
	string strImgFile = "..\\..\\resources\\images\\hand.jpg";
	string strVideoFile = "..\\..\\resources\\videos\\dldl8080.mp4";

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

	status = testChapter2_ReadVideoWithSlider(strVideoFile);
	if (status == FALSE)
	{
		goto exit;
	}

exit:
	system("pause");
	return 0;
}