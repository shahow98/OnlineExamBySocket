// CloginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "CloginDlg.h"
#include "afxdialogex.h"


// CloginDlg 对话框

IMPLEMENT_DYNAMIC(CloginDlg, CDialogEx)

CloginDlg::CloginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	
}

CloginDlg::~CloginDlg()
{
}

void CloginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, user_Id);
	DDX_Control(pDX, IDC_EDIT2, user_Passwd);
}


BEGIN_MESSAGE_MAP(CloginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CloginDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CloginDlg 消息处理程序


void CloginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CString user_Id, user_Passwd;
	this->user_Id.GetWindowText(user_Id);
	this->user_Passwd.GetWindowText(user_Passwd);
	if (user_Id == "1" && user_Passwd == "1")
	{
		//关闭这个对话框，并且向DoModal()返回IDOK
		this->login_Status = TRUE;
		CDialog::OnOK();
	}	
	else
		AfxMessageBox(_T("用户名或者密码错误！"));
}
