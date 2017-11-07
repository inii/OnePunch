#include "MainWnd.h"
#include "CmdLine.h"
#include "resource.h"

CMainWnd::CMainWnd()
{
}

CMainWnd::~CMainWnd()
{
}

BOOL CMainWnd::CreateWnd(HINSTANCE hIns)
{
	mHIns = hIns;

	//1. 定义窗口类结构
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.hIcon = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));//small
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)wndProc;//窗口的消息处理函数指针
	wc.hInstance = hIns;
	wc.hCursor = LoadCursorFromFile(".\\cursor\\Arrow.ani");
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "sss";
	wc.lpszMenuName = "";
	RegisterClassEx(&wc);//2. 注册窗口类

	int w = GetSystemMetrics(0);//获取分辨率宽
	int h = GetSystemMetrics(1);//获取分辨率高

	auto line = CCmdLine::getInstance();
	int winW = line.getScreenW();
	int winH = line.getScreenH();

	//3. 创建窗口 
	mHwnd = CreateWindow("sss", //窗口类名
		"一拳超人",      //窗口标题名
		WS_OVERLAPPEDWINDOW,//窗口的风格
		(w - winW) / 2, (h - winH) / 2, winW, winH, //左上位置 和 宽高
		NULL,//父窗口的句柄
		NULL,//窗口菜单
		hIns,//当前应用程序的句柄
		NULL);

	if (!mHwnd) {
		OutputDebugString("创建窗口失败！！\n");
		return false;
	}

	//4.显示窗口
	ShowWindow(mHwnd, 10);
	//5.更新窗口
	UpdateWindow(mHwnd);

	return true;
}

//消息处理函数
LRESULT CALLBACK CMainWnd::wndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_DESTROY:
		PostMessage(hWnd, WM_QUIT, 0, 0);
		return S_OK;
	}
	return DefWindowProc(hWnd, message, wp, lp);//默认消息处理函数
}