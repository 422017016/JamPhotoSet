
// Car_Detection.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCar_DetectionApp:
// �йش����ʵ�֣������ Car_Detection.cpp
//

class CCar_DetectionApp : public CBCGPWinApp
{
public:
	CCar_DetectionApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCar_DetectionApp theApp;