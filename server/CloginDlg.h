#pragma once


// CloginDlg 对话框

class CloginDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CloginDlg)

public:
	CloginDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CloginDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CEdit user_Id;
	CEdit user_Passwd;
	bool login_Status;
};
