#ifndef STARCUBE_H
#define STARCUBE_H

#include <StarGraphics/objects/StarObject.h>
#include <StarGraphics/StarRenderableInterface.h>

namespace Star
{
  class Cube : public Object, RenderableInterface
  {
  public:
    /**
     * Create a cube
     * @param size is the cube size
     */
    Cube(float size);

    virtual void render();        
    virtual boxf getBoundingBox();

  private:
    float m_size;
  };
}

#endif