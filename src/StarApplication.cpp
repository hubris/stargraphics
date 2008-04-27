#include <StarGraphics/StarApplication.h>
#include <StarGraphics/StarRenderDevice.h>
#include <StarInput.h>
#include <StarUtils/StarExceptions.h>

namespace Star
{
  /*******************************************************************************/
  Application::Application(int resx, int resy, const std::string& name,
                           bool fullscreen)
    : m_renderDevice(NULL),
      m_width(resx), m_height(resy), m_name(name),
      m_finish(false), m_exitCode(0),
      m_currentFrame(0)
  {
    setFullscreen(fullscreen);
  }

  /*******************************************************************************/
  Application::~Application()
  {
    delete m_renderDevice;
    m_renderDevice = NULL;
  }

  /*******************************************************************************/
  int
  Application::run()
  {
    Star::Timer timer;
    double previousRenderTime = 0;
    setupVideo();
    init();
    m_elapsedTime.start();
    while(!m_finish) {
      timer.start();
      processEvents();
      g_StarMouse.updateState();
      idle();
      render(previousRenderTime);
      swapBuffer();
      updateFpsCounter();
      previousRenderTime = timer.getElapsedSeconds();
    }
    quit();
    delete &g_StarMouse;
    exitVideo();
    return m_exitCode;
  }

  /*******************************************************************************/
  float
  Application::getFps() const
  {
    return m_fps;
  }

  /*******************************************************************************/
  void
  Application::updateFpsCounter()
  {
    m_currentFrame++;
    m_numFrameRendered++;
    float elp = m_elapsedTime.getElapsedSeconds();
    if ( elp >= 1.0f )
    {
      m_fps = m_numFrameRendered/elp;
      m_elapsedTime.start();
      m_numFrameRendered = 0;
    }
  }
}

#ifdef WIN32
INT WINAPI
WinMain( HINSTANCE hInst, HINSTANCE, LPSTR, INT nCmdShow)
{
  Star::Application* app = NULL;
  try
  {
    app = createApplication(0, NULL, hInst);    
    app->run();
  } catch(Star::Exception& e)
  {
    e.show();
  }

  delete app;

  return 0;
}
#endif

#ifdef main
#undef main
#endif
int
main(int argc, char** argv)
{  
  Star::Application* app = NULL;
  try
  {
    HINSTANCE hInstance = (HINSTANCE) GetModuleHandle (NULL);
    app = createApplication(argc, argv, hInstance);

    app->run();
  } catch(Star::Exception& e)
  {
    e.show();
  }

  delete app;

  return 0;
}