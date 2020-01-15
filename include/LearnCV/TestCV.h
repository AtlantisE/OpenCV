#pragma once
#include<stdafx.h>

class TestCV;

class TestCV
{
private:
	static TestCV* m_pstTCV;
	TestCV()
	{
		cout << "Class TestCV constructed..." << endl;
	}

public:
	static VideoCapture g_cap;
	static void onTrackbarSlide(int pos, void*);
	static int g_slider_position;
	static int g_run;
	static int g_dontset;

public:

	~TestCV()
	{
		if (m_pstTCV != NULL)
		{
			delete m_pstTCV;
			m_pstTCV = NULL;
		}
	}
	
	static TestCV* getInstance()
	{
		if (m_pstTCV == NULL)
		{
			m_pstTCV = new TestCV();
		}
		return m_pstTCV;
	}

	//Common function

	int Common_Split(const string& strColorImgFile);
	int Common_CvtColorToGrey(const string& strColorImgFile);

	//Chapter 2

	int Chapter2_ReadImage(const string& strImgFile);
	int Chapter2_ReadVideo(const string& strVideoFile);
	int Chapter2_addTrackbarSlideInVideo(const string& strVideoFile);
	int Chapter2_GaussianBlur(const cv::Mat& image);
	int Chapter2_PyrDown(const cv::Mat& image);
	int Chapter2_Canny(const Mat& img_color);
	int Chapter2_VideoWriter(const string& strVideoFile);

	//Chapter 5

	int Chapter5_AddWeighted(const string& strImgFile1,
		const string& strImgFile2,
		const double alpha,
		const double beta,
		const double gamma); 

	//Chapter 10

	int Chapter10_CopyMakeBorder(const string& strSrcImgFile);
	int Chapter10_Threshold(const string& strSrcGrayImgFile);
	int Chapter10_GaussianBlur(const string& strSrcImgFile);
	int Chapter10_BilateralFilter(const string& strSrcImgFile);
	int Chapter10_DilateAndErode(const string& strSrcImgFile);

	//Chapter 11
	int Chapter11_PyDown_Up(const string& strSrcImgFile);
	int Chapter11_BuildPyramid(const string& strSrcImgFile);
	int Chapter11_WarpAffine(const string& strSrcImgFile);
	int Chapter11_WarpPerspective(const string& strSrcImgFile);
	int Chapter11_CartPolar(const string& strSrcImgFile);
	int Chapter11_Remap(const string& strSrcImgFile);
	int Chapter11_Inpaint(const string& strSrcImgFile);
	int Chapter11_FastNlMeanDenoising(const string& strSrcImgFile);

};