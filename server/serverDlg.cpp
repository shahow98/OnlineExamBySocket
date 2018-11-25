
// serverDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "server.h"
#include "serverDlg.h"
#include "CloginDlg.h"
#include "afxdialogex.h"




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
public:
	afx_msg void OnBnClickedOk();
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
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CserverDlg 对话框



CserverDlg::CserverDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERVER_DIALOG, pParent)
{
	EnableActiveAccessibility();
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CserverDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CserverDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CserverDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CserverDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CserverDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CserverDlg 消息处理程序

BOOL CserverDlg::OnInitDialog()
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
	if (this->initServer() != 1)
	{
		OnBnClickedButton1();
	}
	//多线程
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CserverDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CserverDlg::OnPaint()
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
HCURSOR CserverDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CAboutDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CserverDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
}


void CserverDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnCancel();
	EndDialog(-1);
}


void CserverDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

	//关闭服务器端
	closesocket(this->sersoc);
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
	else//IDOK
	{
		if (this->initServer() != 1)
			OnBnClickedButton1();
		else
			ShowWindow(SW_SHOW);
	}
		
}


// 服务端初始化
int CserverDlg::initServer()
{
	// TODO: 在此处添加实现代码.
	int flag = 1;
	//=============网络初始化模块==============
	CString log;
	WSAData wsd;
	WSAStartup(MAKEWORD(2, 2), &wsd);
	//--------------创建套接字---------------
	this->sersoc = socket(AF_INET, SOCK_STREAM, 0);
	//失败
	if (this->sersoc == INVALID_SOCKET)
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
		seraddr.sin_addr.s_addr = INADDR_ANY;//设置SERVER IP地址
		seraddr.sin_port = htons(9000);//设置SERVER 端口号

		//-------------绑定套接字-----------------
		//失败
		if (bind(this->sersoc, (const sockaddr*)&seraddr, sizeof(seraddr)) == SOCKET_ERROR)
		{
			flag = WSAGetLastError();
			log.Format(_T("绑定失败: %d\n"), flag);
			AfxMessageBox(log);
			closesocket(this->sersoc);
			WSACleanup();
		}
		//成功
		else
		{
			//-------------监听端口-----------------
			//失败
		
			if (listen(this->sersoc, MAXLISTEN) == SOCKET_ERROR)
				{
					flag = WSAGetLastError();
					log.Format(_T("监听失败: %d\n"), flag);
					AfxMessageBox(log);
					closesocket(this->sersoc);
					WSACleanup();
				}
			//-------------监听端口-----------------
		}
		//-------------绑定套接字-----------------
	}
	//--------------创建套接字---------------
	//=============网络初始化模块==============
	return flag;
}

int fd_array_connect[MAXLISTEN] = { 0 }; //处理所有的连接
void selectThread(void *p)
{
	CserverDlg * dlg = (CserverDlg *)p;//获得CserverDlg对象指针
	CString log;
	int flag = 1;
	 //--------非阻塞模式设定----------
	int nMode = 1;
	if (ioctlsocket(dlg->sersoc, FIONBIO, (u_long FAR*)&nMode) == SOCKET_ERROR)
	{
		flag = WSAGetLastError();
		log.Format(_T("非阻塞模式设置失败: %d\n"), flag);
		AfxMessageBox(log);
		closesocket(dlg->sersoc);
		WSACleanup();
		return ;
	}
	//--------非阻塞模式设定----------
	else
	{
		fd_set fdRead;//处于读就绪状态的集合
		// fd_set fdWrite;//处于写就绪状态的集合
		timeval tv = { 10,0 };//设置等待时间为10秒
		char recvMsg[MAXMESSAGE] = { 0 };//理论上可存储1024英文 512中文
		char responseBuff[MAXMESSAGE 
		
		] = "服务端已经收到";
		SOCKET clientsoc;
		sockaddr_in clientaddr;
		int clientaddrLen = sizeof(clientaddr);
		int rval = 0;
		int i = 0;
		int nConnNum = 0;
		while (true)
		{
			FD_ZERO(&fdRead);//将你的套接字集合清空-----1------
			FD_SET(dlg->sersoc, &fdRead);  //将sersoc放入fdRead集中进行select监听---2----

			for (i = 0; i < MAXLISTEN; i++)
			{
				if (fd_array_connect[i] != 0)
				{
					//printf("连接的套接字[%d]: %d\n", i + 1, fd_array_connect[i]);
					FD_SET(fd_array_connect[i], &fdRead);//将感兴趣的套接字加入到fdRead集合中----5---
				}
			}
			//调用select模式进行监听

			rval = select(0, &fdRead, NULL, NULL, &tv);//检查是否有套接字可读 即是否有套接字处于读就绪状态 select返回可用的套接字个数---3--  6---
			if (rval == 0)
			{
				//printf("超时: %d 秒\n", tv.tv_sec);
				continue; //继续监听
			}
			else if (rval < 0)
			{
				//printf("失败，错误代码: %d\n", WSAGetLastError());
				break;
			}

			//检查所有的可用SOCKET
			//printf("查找可用的SOCKET\n");
			for (i = 0; i < MAXLISTEN; ++i)
			{
				if (FD_ISSET(fd_array_connect[i], &fdRead))//-----7-----检查fd_array_connect[i]是否在fdRead集合中
				{
					memset(recvMsg, 0, sizeof(recvMsg));
					rval = recv(fd_array_connect[i], recvMsg, sizeof(recvMsg) - 1, 0);//读取（接收）数据
					if (rval <= 0)
					{
						//printf("客户端已经关闭.\n");
						closesocket(fd_array_connect[i]);
						//将已经关闭的SOCKET从FD集中删除
						FD_CLR(fd_array_connect[i], &fdRead);//-----8------
						fd_array_connect[i] = 0;
						nConnNum--;
					}
					else
					{
						recvMsg[rval] = '\0';
						//printf("收到数据: %s\n", recvMsg);
						//send(fd_array_connect[i], responseBuff, strlen(responseBuff), 0);
					}
				}
			}//for( i=0; i<MaxListen; ++i )

			//检查是否为新的连接进入
			if (FD_ISSET(dlg->sersoc, &fdRead))//-------4------9--
			{
				//printf("发现一个新的客户连接\n");
				clientsoc = accept(dlg->sersoc, (sockaddr*)&clientaddr, &clientaddrLen);
				if (clientsoc == WSAEWOULDBLOCK)
				{
					//printf("阻塞了\n");
					continue;
				}
				else if (clientsoc == INVALID_SOCKET)
				{
					//printf("接受连接请求失败: %d\n", WSAGetLastError());
					continue;
				}
				//新的连接可以使用,查看待决处理队列
				if (nConnNum < MAXLISTEN)
				{
					for (i = 0; i < MAXLISTEN; ++i)
					{
						if (fd_array_connect[i] == 0)
						{//添加新的可用连接
							fd_array_connect[i] = clientsoc;
							break;
						}
					}
					nConnNum++;
					//printf("新的客户端信息:[%d] 地址：%s端口:%d\n", clientsoc, inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port));
				}
				else
				{
					//printf("服务器端连接数已满: %d\n", clientsoc);
					char  msg[1024] = "服务器端连接数已满,无法连接";
					send(clientsoc, msg, strlen(msg), 0);
					closesocket(clientsoc);
				}


			}//if( FD_ISSET( sersoc, &fdRead) )


		}//while(true)



	}


}