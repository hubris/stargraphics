#ifndef STARAPPLICATION_H
#define STARAPPLICATION_H

#include <string>

namespace Star
{
  class Application
  {
  public:
    Application(int resx, int resy, const std::string& name, bool fullscreen = false);
    virtual ~Application() {}

    /**
     * Start the main loop
     */
    virtual int run();


//     float getFPS() { return fps; }

    /**
     * If set to true the application is run in fullscreen
     */
    virtual void setFullscreen(bool fs) { m_fullscreen = fs; }

  protected:
    /**
     * Force to quit the main loop
     * @param code the value run() will return
     */
    virtual void halt(int code)
    {
      m_exitCode = code;
      m_finish = true;
    }

    /**
     * Called before entering the main loop
     */
    virtual void init() {}

    /**
     * Render the frame
     * @param elapsedTime is the time in second neeeded to render last frame
     */
    virtual void render(float elapsedTime) = 0;

    /**
     * Called before each frame
     */
    virtual void idle() {}

    /**
     * Called when before exiting the main loop
     */
    virtual void quit() {}

    /**
     * Create and display the screen
     */
    virtual void setupVideo() = 0;

    /**
     * Release all resources needed by screen
     */
    virtual void exitVideo() = 0;

    /**
     * Swap front & back buffer
     */
    virtual void swapBuffer() = 0;

    int m_width, m_height;
    bool m_fullscreen;
    std::string m_name;

  private:
    bool m_finish;

    int m_exitCode;

    unsigned int m_currentFrame;
//     static const int NEEDEDFRAMES = 20;
//     float m_fps;
//     float m_renderTime;
//     Timer m_timer;
  };
}

#endif
