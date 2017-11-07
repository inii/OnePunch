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

	//1. ���崰����ṹ
	WNDCLASSEX wc;
	memset(&wc, 0, sizeof(wc));
	wc.hIcon = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));
	wc.hIconSm = LoadIcon(hIns, MAKEINTRESOURCE(IDI_ICON1));//small
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpfnWndProc = (WNDPROC)wndProc;//���ڵ���Ϣ������ָ��
	wc.hInstance = hIns;
	wc.hCursor = LoadCursorFromFile(".\\cursor\\Arrow.ani");
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszClassName = "sss";
	wc.lpszMenuName = "";
	RegisterClassEx(&wc);//2. ע�ᴰ����

	int w = GetSystemMetrics(0);//��ȡ�ֱ��ʿ�
	int h = GetSystemMetrics(1);//��ȡ�ֱ��ʸ�

	auto line = CCmdLine::getInstance();
	int winW = line.getScreenW();
	int winH = line.getScreenH();

	//3. �������� 
	mHwnd = CreateWindow("sss", //��������
		"һȭ����",      //���ڱ�����
		WS_OVERLAPPEDWINDOW,//���ڵķ��
		(w - winW) / 2, (h - winH) / 2, winW, winH, //����λ�� �� ���
		NULL,//�����ڵľ��
		NULL,//���ڲ˵�
		hIns,//��ǰӦ�ó���ľ��
		NULL);

	if (!mHwnd) {
		OutputDebugString("��������ʧ�ܣ���\n");
		return false;
	}

	//4.��ʾ����
	ShowWindow(mHwnd, 10);
	//5.���´���
	UpdateWindow(mHwnd);

	return true;
}

//��Ϣ������
LRESULT CALLBACK CMainWnd::wndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_DESTROY:
		PostMessage(hWnd, WM_QUIT, 0, 0);
		return S_OK;
	}
	return DefWindowProc(hWnd, message, wp, lp);//Ĭ����Ϣ������
}