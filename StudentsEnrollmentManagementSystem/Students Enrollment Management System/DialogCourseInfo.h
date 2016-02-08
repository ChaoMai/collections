#pragma once

#include <sstream>
#include "Utilities.h"
#include "CourseItem.h"
#include "afxwin.h"

// DialogCourseInfo �Ի���

class DialogCourseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DialogCourseInfo)

public:
	DialogCourseInfo(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~DialogCourseInfo();
    virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_COURSES_INFO };

    ViewInfo viewInfo;
    CourseItem courseItem;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
    CEdit m_editControlId;
    CEdit m_editControlName;
    CEdit m_editControlNumber;
    CEdit m_editControlSchool;
    CButton m_buttonOK;
    CWnd* cParent;
public:
    afx_msg void OnBnClickedOk();
};
