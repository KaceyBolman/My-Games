
// puzzle.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CpuzzleApp:
// �йش����ʵ�֣������ puzzle.cpp
//

class CpuzzleApp : public CWinApp
{
public:
	CpuzzleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CpuzzleApp theApp;