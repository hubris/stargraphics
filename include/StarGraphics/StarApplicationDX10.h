#ifndef STARAPPLICATIONDX10_H
#define STARAPPLICATIONDX10_H

#include <StarGraphics/StarApplication.h>
#include <StarGraphics/StarRenderDeviceDX10.h>
#include <windows.h>

namespace Star
{
  class ApplicationDX10 : public Application
  {
  public:
    ApplicationDX10(HINSTANCE hInst, int resx, int resy, 
                    const std::string& name, bool fullscreen = false);
    virtual ~ApplicationDX10() {}

  protected:
    /**
     * Called when window change its size.
     * Reset the viewport.
     */
    virtual void resizeEvent(int width, int height);

    /**
     * Create and display the screen
     */
    virtual void setupVideo();

    /**
     * Release all resources needed by screen
     */
    virtual void exitVideo();

    /**
     * Swap front & back buffer
     */
    virtual void swapBuffer();

    /**
     * Process default events (quit,resize...)
     */
    virtual void processEvents();

    /** The window handle */
    HWND m_hWnd;
        
    /** DX10 render device*/
    RenderDeviceDX10* m_renderDeviceDX10;

  private:    
    /** Display the window */
    void showWindow();
    
    /** Windows register class */
    void registerClass(const std::string& name);

    /** windows message queue */
    static LRESULT CALLBACK globalWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

    /** Non static windows message queue */
    LRESULT CALLBACK wndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

    /** Pointer to the unique instance of ApplicationDX10 */
    static ApplicationDX10* s_instance;
  };
}

#endif
