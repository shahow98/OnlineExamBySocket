\
// clientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "afxdialogex.h"
#include "CloginDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
	EnableActiveAccessibility();
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CclientDlg 对话框



CclientDlg::CclientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLIENT_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CclientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CclientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CclientDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CclientDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CclientDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CclientDlg 消息处理程序

BOOL CclientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	if (this->initServer() != 1)//与服务器连接失败，退出报错并至重新登录界面。
	{
		OnBnClickedButton1();
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CclientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CclientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CclientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CclientDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CclientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	EndDialog(-1);
}


void CclientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	closesocket(this->clientsoc);
	WSACleanup();
	//先把本对话框隐藏
	ShowWindow(SW_HIDE);
	//再弹出登录对话框
	CloginDlg dlg;
	//最后重新显示本对话框，如果没有登录成功，用户点了“取消”，那么由于登录对话框返回IDCANCEL，EndDialog(-1);能够退出整个程序
	if (IDCANCEL == dlg.DoModal())
	{
		EndDialog(-1);
	}
	else
	{
		if (this->initServer() != 1)
			OnBnClickedButton1();
		else
			ShowWindow(SW_SHOW);
	}
		
}


int CclientDlg::initServer()
{
	// TODO: 在此处添加实现代码.
	int flag = 1;
	//=============网络初始化模块==============
	CString log;
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	//--------------创建套接字---------------
	this->clientsoc = socket(AF_INET, SOCK_STREAM, 0);
	//失败
	if (this->clientsoc == INVALID_SOCKET)
	{
		flag = WSAGetLastError();
		log.Format(_T("创建套接字失败: %d\n"), flag);
		AfxMessageBox(log);
		WSACleanup();
	}
	//成功
	else
	{
		sockaddr_in seraddr;
		seraddr.sin_family = AF_INET;
		seraddr.sin_addr.s_addr = INADDR_ANY;
		inet_pton(seraddr.sin_family, "127.0.0.1", &seraddr.sin_addr.s_addr);//设置SERVER IP地址
		seraddr.sin_port = htons(9000);//设置SERVER 端口号

		//-------------绑定套接字-----------------
		//失败
		if (connect(this->clientsoc, (const sockaddr *)&seraddr, sizeof(seraddr)) == SOCKET_ERROR)
		{
			flag = WSAGetLastError();
			log.Format(_T("连接失败: %d\n"), flag);
			AfxMessageBox(log);
			closesocket(this->clientsoc);
			WSACleanup();
		}
		else
		{
			AfxMessageBox(_T("successful"));
		}
		//-------------绑定套接字-----------------
	}
	//--------------创建套接字---------------
	//=============网络初始化模块============
	return flag;
}
