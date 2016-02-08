
// Students Enrollment Management SystemDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"

#include "DialogClasses.h"
#include "DialogCourses.h"
#include "DialogStudents.h"
#include "AppControl.h"
#include "Utilities.h"

// CStudentsEnrollmentManagementSystemDlg �Ի���
class CStudentsEnrollmentManagementSystemDlg : public CDialogEx
{
// ����
public:
	CStudentsEnrollmentManagementSystemDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_STUDENTSENROLLMENTMANAGEMENTSYSTEM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void On32776About();
    CTabCtrl m_tabctrl;
    CDialogStudents m_page_students;
    CDialogClasses m_page_classes;
    CDialogCourses m_page_courses;
    int m_CurSelTab;
    CDialog* pDialog[3];
    afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void On32772Exit();
private:
    AppControl control;
    void DoDataInit();
};
