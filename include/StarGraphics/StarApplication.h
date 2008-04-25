#ifndef STARAPPLICATION_H
#define STARAPPLICATION_H

#ifdef _WIN32
#include <windows.h>
#endif

#include <StarUtils/StarTimer.h>

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
    virtual void render(double elapsedTime) = 0;

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

    /**
     * Called when window change its size
     */
    virtual void resizeEvent(int width, int height) {}

    /**
     * Process default events (quit,resize...)
     */
    virtual void processEvents() = 0;

    /**
     * Process default events (quit,resize...)
     */
    float getFps() const;

    /** Screen dimensions */
    int m_width, m_height;

    /** True if fullscreen mode*/
    bool m_fullscreen;

    /** Application name */
    std::string m_name;

  private:
    /**
     * Update the fps evaluation.
     * Fps is computed every second
     */
    void updateFpsCounter();

    /** Stop the main loop */
    bool m_finish;

    /** Value returned by run()*/
    int m_exitCode;

    /** The current frame number */
    unsigned int m_currentFrame;

    /** Time elapsed since last fps computation */
    Star::Timer m_elapsedTime;

    /** Number of frame rendered since last fps computation */
    unsigned int m_numFrameRendered;

    /** Fps */
    float m_fps;
  };
}

#endif
