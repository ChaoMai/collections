#pragma once

#include <sstream>
#include "Utilities.h"
#include "AppControl.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"
#include "DialogStudentInfo.h"
#include "afxcmn.h"

// CDialogStudents �Ի���

class CDialogStudents : public CDialogEx
{
    DECLARE_DYNAMIC(CDialogStudents)

public:
    CDialogStudents(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~CDialogStudents();

// �Ի�������
    enum { IDD = IDD_DIALOG_STUDENTS };

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
    virtual BOOL OnInitDialog();

    DECLARE_MESSAGE_MAP()
private:
    CListCtrl m_listctrl;

    // ָ��Control
    AppControl* pAppControl;
    void DoDataInit();
    void AddItem(CListCtrl &ctrl, Student student);
    void AdjustColumnWidth();
    int getSelectedItemIndex();
    std::string getSelectedItemColumn(int cloumn);
public:
    afx_msg void OnBnClickedButtonStudentsInfo();
    afx_msg void OnBnClickedButtonStudentsDeleteSelcet();
    afx_msg void OnBnClickedButtonStudentsUpdate();
    afx_msg void OnBnClickedButtonStudentsAdd();
protected:
    afx_msg LRESULT OnUpdateStudentinfo(WPARAM wParam, LPARAM lParam);
    afx_msg LRESULT OnStudentsDataInit(WPARAM wParam, LPARAM lParam);
};
