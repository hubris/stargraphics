#ifndef STARRENDERABLE_H
#define STARRENDERABLE_H

#include <StarMath/StarBox.h>

namespace Star
{
  class RenderableInterface
  {
  public:
    /** Setup object before render */
    virtual void begin() {}
    
    /** Clear state after render */
    virtual void end() {}

    /** Render the object */
    virtual void render() = 0;        

    /** Return the bounding box */
    virtual boxf getBoundingBox() = 0;
  };
}

#endif