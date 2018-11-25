
// client.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "client.h"
#include "clientDlg.h"
#include "CloginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CclientApp

BEGIN_MESSAGE_MAP(CclientApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CclientApp 构造

CclientApp::CclientApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
	
}


// 唯一的 CclientApp 对象

CclientApp theApp;


// CclientApp 初始化

BOOL CclientApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));


	//============登录模块1===========
	//在主程序窗口运行前首先弹出登录对话框
		CloginDlg login_Dlg;
		INT_PTR nReturn;
		while (TRUE)
		{
			//模态对话框
			nReturn = login_Dlg.DoModal();//返回IDOK或IDCANCEL。如果返回的是IDCANCEL，则要调用WindowsCommDlgExtendedError函数来确定是否发生了一个错误。IDOK和IDCANCEL都是常量，它表明用户选择的是OK按钮还是Cancel按钮
			if (nReturn == IDCANCEL) 
			{//点击关闭退出
				return FALSE;
			}
			if (login_Dlg.login_Status == TRUE) 
			{//若验证通过则退出循环
				break;
			}
			/*if (nReturn == IDOK) 
			{//点击登录
				//=========账号密码验证============
				HWND login_Hwnd = GetDlgItem(login_Dlg, IDD_DIALOG1);//获得句柄，不知道意义
				CString user_Id = login_Dlg.user_Id;
				CString user_Passwd = login_Dlg.user_Passwd;
				if (!(user_Id == "admin" && user_Passwd == "123")) {//如果用户名密码不是admin/admin，则报错，提示重新输入，直至正确为止。
					if (IDOK == MessageBox(NULL, _T("用户ID或密码错误！\n 请重新输入！"), _T("登录失败！"), MB_OKCANCEL | MB_ICONERROR))
						continue;
					else
						return FALSE;
				}
				else
					break;
				//==========账号密码验证============
			}*/
		}
		//============登录模块===========

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CclientDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}

	// 删除上面创建的 shell 管理器。
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

int CclientApp::ExitInstance()
{
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}
