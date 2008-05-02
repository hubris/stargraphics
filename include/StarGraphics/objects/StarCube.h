#ifndef STARCUBE_H
#define STARCUBE_H

#include <StarGraphics/objects/StarObject.h>
#include <StarGraphics/StarRenderableInterface.h>

#include <d3d10.h>

namespace Star
{
  class Cube : public Object, public RenderableInterface
  {
  public:
    /**
     * Create a cube
     * @param size is the cube size
     */
    Cube(float size);

    virtual ~Cube();
  
    /** Setup the vertexbuffer */
    virtual void begin();
  
    virtual void render();        
    virtual boxf getBoundingBox();

    ID3D10InputLayout* createInputLayout(const D3D10_PASS_DESC& passDesc);

  private:
    float m_size;
    ID3D10Buffer* m_vb;
  };
}

#endif