#pragma once

#include <sstream>
#include "Utilities.h"
#include "ClassItem.h"
#include "afxwin.h"

// DialogClassInfo �Ի���

class DialogClassInfo : public CDialogEx
{
	DECLARE_DYNAMIC(DialogClassInfo)

public:
	DialogClassInfo(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~DialogClassInfo();
    virtual BOOL OnInitDialog();

// �Ի�������
	enum { IDD = IDD_DIALOG_CLASSES_INFO };

    ViewInfo viewInfo;
    ClassItem classItem;

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
