#ifndef SIMPLEAPP_H
#define SIMPLEAPP_H

#include <StarGraphics.h>
#include <StarInput.h>

#include <StarGraphics/objects/StarCube.h>

#include <d3dx10.h>

class SimpleTrackballDX10 : public Star::ApplicationDX10, Star::MouseListener
{
public:
  SimpleTrackballDX10(HINSTANCE hInst, int resx, int resy, const std::string& name,
                  bool fullscreen = false);

  void render(double elapsedTime);

  virtual void mouseMoved(const Star::MouseMoveEvent& e);

protected:
  virtual void init();

private:
  Star::Cube* m_cube;
  ID3D10InputLayout* m_cubeLayout;
  ID3D10Effect* m_cubeEffect;

  ID3D10EffectMatrixVariable* m_worldVariable;
  ID3D10EffectMatrixVariable* m_viewVariable;
  ID3D10EffectMatrixVariable* m_projectionVariable;
  D3DXMATRIX m_world;
  D3DXMATRIX m_view;
  D3DXMATRIX m_projection;

  float alpha;
};

#endif
