#include "stdafx.h"
#include "Main.h"
#include "OBJLoader.h"
#include "GL/GL.h"
#include "GL/GLU.h"
#include <MMSystem.h>
#include "3DEngine.h"
#include "MyEngine.h"
//*********************************************************************************

#define WDCLASS_NAME "MainWdClass"

#define REFERENCE_TIME	0.016f

#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC         ((USHORT) 0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE        ((USHORT) 0x02)
#endif

RAWINPUTDEVICE Rid[1];

//*********************************************************************************

HINSTANCE g_hAppInstance;
HWND g_hAppWnd;
HDC g_hDC;
HGLRC g_hGLContext;
BOOL g_bRun = TRUE;
C3DEngine *C3DEngine::g_pRendererInstance = new MyEngine();

//*********************************************************************************

ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE hInstance, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int width=0,height=0;


void SetupOpenGL(void);
void ShutdownOpenGL(void);

//*********************************************************************************
// Application entry point
//
int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG Msg;
	DWORD u32Time, u32PrevTime;
	RECT R;
	float fDT;
	
	if (!C3DEngine::GetInstance())
	{
		MessageBox(NULL, "No 3D renderer defined", "3D error", MB_OK | MB_ICONSTOP);
		return(0);
	}


	//--- Register custom window class

	RegisterWindowClass(hInstance);

	//--- Initialize application

	if (!InitInstance (hInstance, nCmdShow))
		return(FALSE);

	//--- Load scene files

	C3DEngine::GetInstance()->Setup(g_hAppWnd);

	//--- Main message loop

	fDT = 0;
	u32PrevTime = timeGetTime();

	while (g_bRun)
	{
		//--- Messages handling

		while (PeekMessage(&Msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		//--- Scene refresh

		GetClientRect(g_hAppWnd, &R);
		C3DEngine::GetInstance()->Render(R.right, R.bottom);

		//--- Scene update

		u32Time = timeGetTime();
		fDT += (u32Time - u32PrevTime)/1000.f;
		while (fDT >= REFERENCE_TIME)
		{
			C3DEngine::GetInstance()->Update(REFERENCE_TIME);
			fDT -= REFERENCE_TIME;
		}

		u32PrevTime = u32Time;

		//--- Buffers swapping

		SwapBuffers(g_hDC);
	}

	//--- Shutdown renderer

	C3DEngine::GetInstance()->Shutdown();

	//--- Terminate application

	return((int)Msg.wParam);
}

//*********************************************************************************
// Custom window registration
//
ATOM RegisterWindowClass(HINSTANCE hInstance)
{
	WNDCLASSEX Class;

	Class.cbSize = sizeof(WNDCLASSEX);

	Class.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Class.lpfnWndProc = WndProc;
	Class.cbClsExtra = 0;
	Class.cbWndExtra = 0;
	Class.hInstance = hInstance;
	Class.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_Main));
	Class.hCursor = LoadCursor(NULL, IDC_ARROW);
	Class.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	Class.lpszMenuName = NULL;
	Class.lpszClassName	= WDCLASS_NAME;
	Class.hIconSm = LoadIcon(Class.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return(RegisterClassEx(&Class));
}

//*********************************************************************************
// Application initialization
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	g_hAppInstance = hInstance;

	HMONITOR hmon = MonitorFromWindow(g_hAppWnd,
		MONITOR_DEFAULTTONEAREST);
	MONITORINFO mi = { sizeof(mi) };
	//--- Create window

	g_hAppWnd = CreateWindow(WDCLASS_NAME, "3D scene renderer", WS_OVERLAPPEDWINDOW, 0, 0, CW_USEDEFAULT, 0, NULL, NULL, g_hAppInstance, NULL);
	MONITORINFO monitor_info;
	monitor_info.cbSize = sizeof(monitor_info);
	GetMonitorInfo(MonitorFromWindow(g_hAppWnd, MONITOR_DEFAULTTONEAREST),
		&monitor_info);


	SetWindowLong(g_hAppWnd, GWL_STYLE,
		GetWindowLong(g_hAppWnd, GWL_STYLE) & ~(WS_CAPTION | WS_THICKFRAME));

	SetWindowLong(g_hAppWnd, GWL_EXSTYLE,
		GetWindowLong(g_hAppWnd, GWL_EXSTYLE) & ~(WS_EX_DLGMODALFRAME |
		WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
	width = monitor_info.rcMonitor.right - monitor_info.rcMonitor.left;
	height = monitor_info.rcMonitor.bottom - monitor_info.rcMonitor.top;
	SetWindowPos(g_hAppWnd, NULL, monitor_info.rcMonitor.left, monitor_info.rcMonitor.top,
		width,
		height,
		SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
	if (!g_hAppWnd)
		return(FALSE);


	Rid[0].usUsagePage = HID_USAGE_PAGE_GENERIC; 
	Rid[0].usUsage = HID_USAGE_GENERIC_MOUSE; 
	Rid[0].dwFlags = RIDEV_INPUTSINK;   
	Rid[0].hwndTarget = g_hAppWnd;
	RegisterRawInputDevices(Rid, 1, sizeof(Rid[0]));

	SetupOpenGL();

	//--- Display window

	ShowWindow(g_hAppWnd, nCmdShow);
	UpdateWindow(g_hAppWnd);

	return(TRUE);
}

//*********************************************************************************
// Setup OpenGL renderer
//
void SetupOpenGL(void)
{
	PIXELFORMATDESCRIPTOR PFD;
	int s32PixelIndex;

	//--- Retrieve window DC

	g_hDC = ::GetDC(g_hAppWnd);
	if (!g_hDC)
		return;

	//--- Init desired pixel format

	memset(&PFD, 0, sizeof(PFD));

	PFD.nSize = sizeof(PFD);
	PFD.nVersion = 1;
	PFD.dwFlags = PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_GENERIC_ACCELERATED | PFD_DOUBLEBUFFER;
	PFD.iPixelType = PFD_TYPE_RGBA;
	PFD.cColorBits = 24;
	PFD.cAlphaBits = 8;
	PFD.cDepthBits = 24;
	PFD.iLayerType = PFD_MAIN_PLANE;

	//--- Try to match the desired pixel format

	s32PixelIndex = ChoosePixelFormat(g_hDC, &PFD);
	if (!s32PixelIndex)
		s32PixelIndex = 1;	

	//--- Get pixel format description

	memset(&PFD, 0, sizeof(PFD));
	if (!DescribePixelFormat(g_hDC, s32PixelIndex, sizeof(PFD), &PFD))
		return;

	//--- Set pixel format

	if (s32PixelIndex != GetPixelFormat(g_hDC))
		if (!SetPixelFormat(g_hDC, s32PixelIndex, &PFD))
			return;

	//--- Create GL render context

	g_hGLContext = (HGLRC)wglCreateContext(g_hDC);

	//--- Activate render context

	wglMakeCurrent(g_hDC, g_hGLContext);
}

//*********************************************************************************
// Shutdown OpenGL renderer
//
void ShutdownOpenGL(void)
{
	//--- Release GL context

	if (g_hGLContext)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(g_hGLContext);
	}

	//--- Free up DC

	if (g_hDC)
		ReleaseDC(g_hAppWnd, g_hDC);
}

//*********************************************************************************
// Application message handler
//

bool setCursorPos = false;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT PS;
	HDC hDC;
	POINT Pt;


	switch (message)
	{
	case WM_PAINT:
		//--- Window refresh notification

		hDC = BeginPaint(hWnd, &PS);
		EndPaint(hWnd, &PS);
		break;

	case WM_CLOSE:
		//--- Close window notification

		ShutdownOpenGL();
		DestroyWindow(g_hAppWnd);
		break;

	case WM_DESTROY:
		//--- Window destruction notification

		PostQuitMessage(0);
		g_bRun = FALSE;
		break;

	case WM_MOUSEWHEEL:
		//--- Mouse wheel notification

		C3DEngine::GetInstance()->MouseWheel(((float)(short)HIWORD(wParam))/WHEEL_DELTA);
		break;

		/*case WM_MOUSEMOVE:
		//--- Mouse move notification
		POINT p;
		p.x = (int)(1.*width /2);
		p.y = (int)(1.*height/2);
		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);

		C3DEngine::GetInstance()->MouseMove(Pt);

		break;*/
	case WM_LBUTTONDOWN:
		//--- Left mouse button down notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->LButtonDown(Pt);
		break;

	case WM_LBUTTONUP:
		//--- Left mouse button up notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->LButtonUp(Pt);
		break;

	case WM_RBUTTONDOWN:
		//--- Right mouse button down notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->RButtonDown(Pt);
		break;

	case WM_RBUTTONUP:
		//--- Right mouse button up notification

		Pt.x = (short)LOWORD(lParam);
		Pt.y = (short)HIWORD(lParam);
		C3DEngine::GetInstance()->RButtonUp(Pt);
		break;

	case WM_KEYDOWN:
		C3DEngine::GetInstance()->KeyDown((int)wParam);
		break;
	case WM_KEYUP:
		C3DEngine::GetInstance()->KeyUp((int)wParam);
		break;

	case WM_INPUT: 
		{
			UINT dwSize = 40;
			static BYTE lpb[40];

			GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
				lpb, &dwSize, sizeof(RAWINPUTHEADER));

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEMOUSE) 
			{
				POINT p;
				p.x = raw->data.mouse.lLastX;
				p.y = raw->data.mouse.lLastY;

				C3DEngine::GetInstance()->MouseMove(p);
			} 
			break;
		}
	default:
		//--- Default message handling

		return(DefWindowProc(hWnd, message, wParam, lParam));
	}

	return(0);
}

