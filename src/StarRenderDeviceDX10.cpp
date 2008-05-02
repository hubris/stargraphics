#include <StarGraphics/StarRenderDeviceDX10.h>

#include <StarUtils/StarExceptions.h>

namespace Star {
  /***************************************************************************/
  RenderDeviceDX10::RenderDeviceDX10()
    : m_d3dDevice(NULL),
      m_swapChain(NULL),
      m_hWnd(0),
      m_renderTargetView(NULL)
  {
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::init(HWND hWnd)
  {
    m_hWnd = hWnd;
    if( FAILED( D3D10CreateDevice( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL,
                                   0, D3D10_SDK_VERSION, &m_d3dDevice ) ) )
      throw Exception("RenderDeviceDX10::RenderDeviceDX10: Creating render device failed!\n");
  }
  /***************************************************************************/
  RenderDeviceDX10::~RenderDeviceDX10()
  {
    m_renderTargetView->Release();
    m_renderTargetView = NULL;

    m_swapChain->Release();
    m_swapChain = NULL;

    m_d3dDevice->Release();
    m_d3dDevice = NULL;
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::createSwapChain(int resX, int resY, bool fullscreen)
  {        
    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory( &sd, sizeof(sd) );
    sd.BufferCount = 1;
    sd.BufferDesc.Width = resX;
    sd.BufferDesc.Height = resY;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.Windowed = !fullscreen;
    sd.OutputWindow = m_hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;

    IDXGIFactory * pFactory;
    HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)(&pFactory) );

    if(FAILED(pFactory->CreateSwapChain(m_d3dDevice, &sd, &m_swapChain)))
      throw Exception("RenderDeviceDX10::createSwapChain: Creating swap chain failed!\n");
    pFactory->Release();    
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::resizeSwapChain(int resX, int resY)
  {        
    HRESULT hr;
    releaseTargetView();
    hr = m_swapChain->ResizeBuffers(1, resX, resY, DXGI_FORMAT_R8G8B8A8_UNORM, 0 );
       
    if(FAILED(hr))
      throw Exception("RenderDeviceDX10::resizeSwapChain: Swap chain ResizeBuffers failed!\n");
    createRenderTargetView();
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::createRenderTargetView()
  {        
    // Create a render target view
    ID3D10Texture2D *pBackBuffer;
    if( FAILED( m_swapChain->GetBuffer( 0, __uuidof( ID3D10Texture2D ), (LPVOID*)&pBackBuffer ) ) )
      throw Exception("RenderDeviceDX10::createRenderTargetView: Creating render target view failed!\n");

    HRESULT hr;
    hr = m_d3dDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_renderTargetView );
    pBackBuffer->Release();
    if(FAILED(hr))
      throw Exception("RenderDeviceDX10::createRenderTargetView: Creating render target view failed!\n");
    m_d3dDevice->OMSetRenderTargets( 1, &m_renderTargetView, NULL );
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::releaseTargetView()
  {        
    m_d3dDevice->OMSetRenderTargets( 0, NULL, NULL );
    m_renderTargetView->Release();
    m_renderTargetView = NULL;
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::present() const
  {
    m_swapChain->Present(0, 0);
  }

  /***************************************************************************/
  void
  RenderDeviceDX10::clearRenderTargetView(const float4& color)
  {  
    m_d3dDevice->ClearRenderTargetView(m_renderTargetView, &color[0]);
  }
}

