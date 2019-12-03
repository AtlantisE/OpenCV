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


};