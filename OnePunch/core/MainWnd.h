#pragma once
#include <windows.h>

//Ö÷´°¿ÚÀà
class CMainWnd
{
	CMainWnd();
public:
	~CMainWnd();

	static CMainWnd& getInstance() {
		static CMainWnd s;
		return s;
	}

	BOOL CreateWnd(HINSTANCE hIns);

	HWND getMainWnd() { return mHwnd; }
	HINSTANCE getMainInst() { return mHIns; }

private:

	static LRESULT CALLBACK wndProc(HWND hWnd, UINT message, WPARAM wp, LPARAM lp);

	HWND mHwnd;
	HINSTANCE mHIns;
};

