#pragma once
#include "afxwin.h"
#include "Students Enrollment Management SystemDlg.h"


// CDialogLogin �Ի���

class CDialogLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogLogin)

public:
	CDialogLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogLogin();

// �Ի�������
	enum { IDD = IDD_DIALOG_LOGIN };

protected:
    HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
private:
    // ָ��Control
    AppControl* pAppControl;

    CEdit m_editControlUserName;
    CEdit m_editControlPassword;
public:
    afx_msg void OnBnClickedLogin();
};
