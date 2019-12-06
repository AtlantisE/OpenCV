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

	int Chapter2_ReadImage(const string& strImgFile);
	int Chapter2_ReadVideo(const string& strVideoFile);
	int Chapter2_addTrackbarSlideInVideo(const string& strVideoFile);
	int Chapter2_GaussianBlur(const cv::Mat& image);
	int Chapter2_PyrDown(const cv::Mat& image);
	int Chapter2_Canny(const Mat& img_color);


};