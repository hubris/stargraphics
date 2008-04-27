#ifndef STARRENDERDEVICEDX10_H
#define STARRENDERDEVICEDX10_H

#include <StarGraphics/StarRenderDevice.h>
#include <StarMath/StarVec4.h>

#include <d3d10.h>

namespace Star {
  class RenderDeviceDX10 : public RenderDevice
  {
  public:
    /**
     * Create a d3d10 device
     */
    RenderDeviceDX10(HWND hWnd);

    /**
     * Destructor
     */
    virtual ~RenderDeviceDX10();

    /** Create the swap chain */
    void createSwapChain(int resX, int resY);

    /** Create and set the default render target view */
    void createRenderTargetView();

    /** Return the d3d interface */
    inline ID3D10Device* getD3dDevice() const { return m_d3dDevice; }

    /** Swap buffers */
    void present() const;
  
    /** Clear with specified color */
    void clearRenderTargetView(const float4& color);

  private:    
    ID3D10Device* m_d3dDevice;
    IDXGISwapChain* m_swapChain;
    HWND m_hWnd;
    ID3D10RenderTargetView* m_renderTargetView;
  };
}

#endif