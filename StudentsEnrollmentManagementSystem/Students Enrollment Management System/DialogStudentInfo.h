#pragma once

#include <sstream>
#include "Utilities.h"
#include "Student.h"
#include "UndergraduateStudent.h"
#include "GraduateStudent.h"
#include "afxwin.h"
#include "afxdtctl.h"

// DialogStudentInfo �Ի���

class DialogStudentInfo : public CDialogEx
{
    DECLARE_DYNAMIC(DialogStudentInfo)

public:
    DialogStudentInfo(CWnd* pParent = NULL);   // ��׼���캯��
    virtual ~DialogStudentInfo();
    virtual BOOL OnInitDialog();

    // �Ի�������
    enum { IDD = IDD_DIALOG_STUDENTS_INFO };

    ViewInfo viewInfo;
    Student student;

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

    DECLARE_MESSAGE_MAP()
private:
    CEdit m_editControlId;
    CEdit m_editControlLastName;
    CEdit m_editControlFirstName;
    CButton m_checkBoxMan;
    CButton m_checkBoxWoman;
    CEdit m_editControlSchool;
    CEdit m_editControlCampusAddress;
    CEdit m_editControlHomeAddress;
    CEdit m_editControlPC;
    CDateTimeCtrl m_dateTimeCtrlAdmissionTime;
    CButton m_checkBoxUG;
    CButton m_checkBoxG;
    CButton m_buttonOK;
    CWnd* cParent;
public:
    afx_msg void OnBnClickedOk();
    afx_msg void OnClickedCheckM();
    afx_msg void OnClickedCheckF();
    afx_msg void OnClickedCheckUG();
    afx_msg void OnClickedCheckG();
};
