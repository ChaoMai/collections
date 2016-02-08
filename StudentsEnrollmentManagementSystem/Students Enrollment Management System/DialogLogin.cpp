// DialogLogin.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Students Enrollment Management System.h"
#include "DialogLogin.h"
#include "afxdialogex.h"


// CDialogLogin �Ի���

IMPLEMENT_DYNAMIC(CDialogLogin, CDialogEx)

CDialogLogin::CDialogLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogLogin::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIconW(IDI_ICON1);
}

CDialogLogin::~CDialogLogin()
{
}

void CDialogLogin::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_USERNAME, m_editControlUserName);
    DDX_Control(pDX, IDC_EDIT_PASSWORD, m_editControlPassword);
}

BOOL CDialogLogin::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    return TRUE;
}


BEGIN_MESSAGE_MAP(CDialogLogin, CDialogEx)
    ON_BN_CLICKED(ID_LOGIN, &CDialogLogin::OnBnClickedLogin)
END_MESSAGE_MAP()


// CDialogLogin ��Ϣ�������


void CDialogLogin::OnBnClickedLogin()
{
    //todo finish login
    CString cstringBuf;
    m_editControlUserName.GetWindowTextW(cstringBuf);
    std::string name = CStringTostring(cstringBuf);

    m_editControlPassword.GetWindowTextW(cstringBuf);
    std::string password = CStringTostring(cstringBuf);

    //User user;
    //user.setName(name);
    //user.setPassword(password);

    //if (pAppControl->verifyUser(user))
    //{
    //    AfxGetMainWnd()->SendMessage(WM_CLOSE);

    //    CStudentsEnrollmentManagementSystemDlg dlg;
    //    dlg.DoModal();
    //}
    //else
    //{
    //    MessageBox(L"�û������������");
    //}
}
