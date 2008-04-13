#include <StarGraphics/StarApplication.h>
#include <StarInput.h>

namespace Star
{
  /*******************************************************************************/
  Application::Application(int resx, int resy, const std::string& name,
                           bool fullscreen)
    : m_width(resx), m_height(resy), m_name(name),
      m_finish(false), m_exitCode(0),
      m_currentFrame(0)
  {
    setFullscreen(fullscreen);
  }


  /*******************************************************************************/
  int
  Application::run()
  {
    setupVideo();
    init();
    while(!m_finish) {
      processEvents();
      g_StarMouse.updateState();
      idle();
      render(0);
      swapBuffer();
      m_currentFrame++;
    }
    quit();
    delete &g_StarMouse;
    exitVideo();
    return m_exitCode;
  }
}
