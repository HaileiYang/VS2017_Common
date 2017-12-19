

#include<windows.h>

HINSTANCE	hinst;

LRESULT	CALLBACK	myWndProc(HWND hwnd, 
	UINT	uMsg,
	WPARAM	wParam, 
	LPARAM	lParam)
{
	switch (uMsg)
	{
	case WM_DESTROY:
		ExitThread(0);
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}





/*
在当前目录下生成一个文件，记录了系统目录
*/
int wirteSysDir(void)
{
	HANDLE	hFile;
	DWORD	dwWritten;
	TCHAR	szSystemDir[MAX_PATH];

	GetSystemDirectory(szSystemDir, MAX_PATH);
	hFile = CreateFile(TEXT("systemroot.txt"),
		GENERIC_WRITE,
		0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	if (hFile != INVALID_HANDLE_VALUE) {
		if (!WriteFile(hFile, szSystemDir, lstrlen(szSystemDir), &dwWritten, NULL)) {
			return GetLastError();
		}
	}


	
	return 0;
}

int  WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	if (wirteSysDir() == 0) {
		MessageBox(NULL, TEXT("系统目录已经写入"), TEXT("提示"), MB_OK);
	}

	WNDCLASSEX	wcx;
	HWND	hwnd;
	MSG		msg;
	BOOL	fGotMessage;

	hinst = hInstance;
	wcx.cbSize = sizeof(wcx);
	wcx.style = CS_HREDRAW | CS_VREDRAW;
	wcx.lpfnWndProc = myWndProc;
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;
	wcx.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL,
		IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(
		WHITE_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = TEXT("MainWClass");//MainWClass  要与下文CreatWindow中的第一个参数相同
	wcx.hIconSm = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CXSMICON),
		LR_DEFAULTCOLOR);

	if (!RegisterClassEx(&wcx)) {
		return 1;

	}
	hwnd = CreateWindow(
		TEXT("MainWClass"),
		TEXT("CH 2-3"),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(HWND)NULL,
		(HMENU)NULL,
		hInstance,
		(LPVOID)NULL
		);
	if (!hwnd) {
		return 1;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (
		((fGotMessage = GetMessage(&msg, (HWND)NULL, 0, 0)) != 0)
		&& (fGotMessage != -1))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		
	}
	return msg.wParam;
}







