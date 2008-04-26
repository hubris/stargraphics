#include <StarGraphics/StarApplicationDX10.h>

#include <StarUtils/StarExceptions.h>
#include <cassert>

namespace Star
{
  ApplicationDX10* ApplicationDX10::s_instance = NULL;

  /*******************************************************************************/
  void
  ApplicationDX10::showWindow()
  {
	  ShowWindow(m_hWnd, SW_SHOW);
	  UpdateWindow(m_hWnd);
  }

  /*******************************************************************************/
  LRESULT CALLBACK 
  ApplicationDX10::globalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
  {
  	return s_instance->wndProc(hWnd, uMsg, wParam, lParam);
  }

  /*******************************************************************************/
  void
  ApplicationDX10::registerClass(const std::string& name)
  {
    WNDCLASSEX wc;
    memset(&wc, 0, sizeof(WNDCLASSEX));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = (WNDPROC)globalWndProc;
    wc.hInstance = m_hInstance;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszClassName = name.c_str();
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);

    if(RegisterClassEx(&wc) == 0)		
      throw Exception("ApplicationDX10::RegisterClass: Registering window class failed!\n");
  }

  /*******************************************************************************/
  ApplicationDX10::ApplicationDX10(HINSTANCE hInst, int resx, int resy,
                                   const std::string& name,
                                   bool fullscreen)
    : Application(resx, resy, name, fullscreen)
  {
    assert(s_instance == NULL);
    m_hInstance= hInst;

    HINSTANCE inst = m_hInstance;
    registerClass(name);	
    m_hWnd = CreateWindow(name.c_str(), name.c_str(), 
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
                          CW_USEDEFAULT, resx, resy, NULL, NULL, inst, NULL);
    if(!m_hWnd)
      throw Exception("Window::RegisterClass: Window creation failed!\n");		
  }

  /*******************************************************************************/
  void
  ApplicationDX10::setupVideo()
  {   
  }

  /*******************************************************************************/
  void
  ApplicationDX10::exitVideo()
  {
  }

  /*******************************************************************************/
  void
  ApplicationDX10::swapBuffer()
  {
  }

  /*******************************************************************************/
  LRESULT CALLBACK
  ApplicationDX10::wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
  {
    switch(msg) {
      case WM_CLOSE:
        halt(0);			
        DestroyWindow(m_hWnd);
        break;

      case WM_DESTROY:	
        halt(0);			
        PostQuitMessage(0);
        break;
      case WM_SIZE:
        if(wParam == SIZE_MINIMIZED)
          break;
        //getAppInstance()->resetD3DDevice();
        resizeEvent(LOWORD(lParam), HIWORD(lParam));
        break;
      default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
  }

  /*******************************************************************************/
  void
  ApplicationDX10::processEvents()
  {
    MSG msg = {0};
    while( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
    {
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
  }
}
