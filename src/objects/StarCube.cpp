#include <StarGraphics/objects/StarCube.h>

namespace Star
{
  /***************************************************************************/
  Cube::Cube(float size)
    : m_size(size)
  {
  }

  /***************************************************************************/
  void Cube::render()
  {
  }

  /***************************************************************************/
  boxf
  Cube::getBoundingBox()
  {
    float half = m_size/2.f;
    return boxf(float3(-half, -half, -half), float3(half, half, half));
  }
}