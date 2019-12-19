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

int testChapter2_VideoWriter(const std::string& strFile)
{
	int status = pTCV->Chapter2_VideoWriter(strFile);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter2_VideoWriter failed!" << endl;
	}
	return status;
}

int testChapter5_AddWeighted(const std::string& strFile1, const std::string& strFile2)
{
	int status = pTCV->Chapter5_AddWeighted(strFile1, strFile2, 0.1, 0.9, 0.0);
	if (status == FALSE)
	{
		cout << "TestCV::Chapter5_addWeighted failed!" << endl;
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
	string strSavedVideoFile = "..\\..\\resources\\videos\\video.avi";
	string strSrcImgFile1 = "..\\..\\resources\\images\\chapter5\\gray125.bmp";
	string strSrcImgFile2 = "..\\..\\resources\\images\\chapter5\\gray25.bmp";

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
	/*status = testChapter2_ReadVideo("");
	if (status == FALSE)
	{
		goto exit;
	}*/

	//read image from camera and save it
	/*status = testChapter2_VideoWriter(strSavedVideoFile);
	if (status == FALSE)
	{
		goto exit;
	}*/

	status = testChapter5_AddWeighted(strSrcImgFile1, strSrcImgFile2);
	if (status == FALSE)
	{
		goto exit;
	}

	//Point2i p(2, 3);
	//cout << "Point:x=" << p.x << ", y=" << p.y << endl;
	//Vec2i vecP = (Vec2i)p;
	//cout << "Point:x=" << vecP[0] << ", y=" << vecP[1] << endl;

	//Scalar s(1, 2, 3, 4);
	//cout << "Scalar:" << s[0] << "," << s[1] << "," << s[2] << "," << s[3] << endl;

	//Mat mat(3, 10, CV_32FC3, Scalar(1.0f, 0.0f, 1.0f));
	//cout << "rows=" << mat.rows << ",cols=" << mat.cols << ";channels=" << mat.channels() << ",dims=" << mat.dims << endl;
	//cout << mat.data << endl;

	//Mat m = Mat::eye(10, 10, CV_32FC2);
	//cout << "row:3, col:3, c:0 = " << m.at<Vec2f>(3, 3)[0] << ", c:1=" << m.at<Vec2f>(3, 3)[1] << endl;
	//cout<<"row 2 data:"<<*(m.ptr<Vec2f>(2)+2)<<endl;

	//const int n_mat_size = 5;
	//const int n_mat_sz[] = { n_mat_size, n_mat_size, n_mat_size };
	//Mat n_mat0(3, n_mat_sz, CV_32FC1);
	//Mat n_mat1(3, n_mat_sz, CV_32FC1);

	//RNG rng;
	//rng.fill(n_mat0, RNG::UNIFORM, 0.f, 1.f);
	//rng.fill(n_mat1, RNG::UNIFORM, 0.f, 1.f);

	//Mat* arrays[] = { &n_mat0, &n_mat1, 0 };
	//Mat my_planes[2];
	//NAryMatIterator it((const Mat **)arrays, my_planes);

	//double s1 = 0.f;
	//int n = 0;
	//for (int p = 0; p < it.nplanes; p++, ++it)
	//{
	//	cout <<p<<":"<<it.planes->size() << endl;
	//	//cout << p << ":" << it.nplanes << endl;
	//	cout << it.planes[0] << endl;
	//	cout <<"planes[0]"<< it.planes[0].size() << endl;
	//	cout << "planes[1]:" << it.planes[1].size() << endl;
	//	s1 = s1 + sum(it.planes[0])[0];
	//	s1 = s1 + sum(it.planes[1])[0];
	//	n++;
	//}

	//cout << "sum:" << s1 << endl;


exit:
	system("pause");
	return 0;
}