#ifndef STARRENDERDEVICEDX10_H
#define STARRENDERDEVICEDX10_H

#include <StarGraphics/StarRenderDevice.h>
#include <StarMath/StarVec4.h>
#include <StarUtils/StarSingleton.h>

#include <d3d10.h>

namespace Star {
  class RenderDeviceDX10 : public RenderDevice, public Singleton<RenderDeviceDX10>
  {
  public:  
    /**Constructor*/    
    RenderDeviceDX10();

    /**
     * Init the d3d10 device. Must be called
     * before everything else.
     */      
    void init(HWND hWnd);

    /**
     * Destructor
     */
    virtual ~RenderDeviceDX10();

    /** Create the swap chain */
    void createSwapChain(int resX, int resY, bool fullscreen);

    /** Create and set the default render target view */
    void createRenderTargetView();

    /** Return the d3d interface */
    inline ID3D10Device* getD3dDevice() const { return m_d3dDevice; }

    /** Swap buffers */
    void present() const;
  
    /** Clear with specified color */
    void clearRenderTargetView(const float4& color);

    /** Resize the swap chain */
    void resizeSwapChain(int resX, int resY);

  private:
    /** Release the target view */
    void releaseTargetView();

    ID3D10Device* m_d3dDevice;
    IDXGISwapChain* m_swapChain;
    HWND m_hWnd;
    ID3D10RenderTargetView* m_renderTargetView;
  };
}

#define g_StarRenderDeviceDX10 (*Star::RenderDeviceDX10::getInstance())

#endif