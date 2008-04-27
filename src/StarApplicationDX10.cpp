#include <StarGraphics/StarApplicationDX10.h>

#include <StarGraphics/StarRenderDeviceDX10.h>
#include <StarUtils/StarExceptions.h>
#include <StarInput/StarMouse.h>
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
    s_instance = this;

    HINSTANCE inst = m_hInstance;
    registerClass(name);	
    m_hWnd = CreateWindow(name.c_str(), name.c_str(), 
                          WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 
                          CW_USEDEFAULT, resx, resy, NULL, NULL, inst, NULL);
    if(!m_hWnd)
      throw Exception("Window::RegisterClass: Window creation failed!\n");	
    g_StarMouse.init(m_hWnd, hInst);
  }

  /*******************************************************************************/
  void
  ApplicationDX10::setupVideo()
  {   
    showWindow();
    m_renderDevice = m_renderDeviceDX10 = new RenderDeviceDX10(m_hWnd);    
    m_renderDeviceDX10->createSwapChain(m_width, m_height);
    m_renderDeviceDX10->createRenderTargetView();

    D3D10_VIEWPORT vp;
    vp.Width = m_width;
    vp.Height = m_height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_renderDeviceDX10->getD3dDevice()->RSSetViewports(1, &vp);
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
    m_renderDeviceDX10->present();
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
