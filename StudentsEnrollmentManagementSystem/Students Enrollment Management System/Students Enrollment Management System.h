
// Students Enrollment Management System.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "DialogLogin.h"


// CStudentsEnrollmentManagementSystemApp: 
// �йش����ʵ�֣������ Students Enrollment Management System.cpp
//

class CStudentsEnrollmentManagementSystemApp : public CWinApp
{
public:
	CStudentsEnrollmentManagementSystemApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CStudentsEnrollmentManagementSystemApp theApp;