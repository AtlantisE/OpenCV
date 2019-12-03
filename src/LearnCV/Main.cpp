#include<TestCV.h>

int main()
{
	int status = OK;
	TestCV* pTCV = TestCV::getInstance();

	string strImgFile = "..\\..\\resources\\images\\hand.jpg";
	string strVideoFile = "..\\..\\resources\\videos\\dldl8080.mp4";

	/*status = pTCV->Chapter2_ReadImage(strImgFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_ReadImage failed" << endl;
		goto exit;
	}*/

	
	status = pTCV->Chapter2_ReadVideo(strVideoFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_ReadVideo failed!" << endl;
		goto exit;
	}

	exit:
	system("pause");
	return 0;
}