#include "simpleTrackballDX10.h"

#include <StarMath/StarVec4.h>
#include <StarGraphics/StarVertexLayout.h>
#include <StarUtils/StarExceptions.h>

#include <iostream>
#include <d3dx10.h>
#include <cmath>

/******************************************************************************/
SimpleTrackballDX10::SimpleTrackballDX10(HINSTANCE hInst, int resx, int resy, 
                                 const std::string& name,
                                 bool fullscreen) 
 : ApplicationDX10(hInst, resx, resy, name, fullscreen)
{
  g_StarMouse.addListener(this);
}

/******************************************************************************/
void
SimpleTrackballDX10::init()
{
  alpha = 0.f;
  HRESULT hr;
  hr = D3DX10CreateEffectFromFile("C:/Users/gandalf/Documents/devel/cpp/starengine/stargraphics/tests/simpleTrackballDX10/cube.fx", 
                                  NULL, NULL, "fx_4_0",
                                  D3D10_SHADER_ENABLE_STRICTNESS, 0, 
                                  g_StarRenderDeviceDX10.getD3dDevice(), 
                                  NULL, NULL, &m_cubeEffect,
                                  NULL, NULL);
 
  if(FAILED(hr))
    throw Star::Exception("SimpleTrackballDX10::init: can't create effect");

  m_cube = new Star::Cube(1.0f);

  ID3D10EffectTechnique* tech = m_cubeEffect->GetTechniqueByIndex(0);

  D3D10_PASS_DESC passDesc;
  hr = tech->GetPassByIndex(0)->GetDesc(&passDesc);
  if(FAILED(hr))
    throw Star::Exception("SimpleTrackballDX10::init: can't get pass description");

  m_cubeLayout = m_cube->createInputLayout(passDesc);
  g_StarRenderDeviceDX10.getD3dDevice()->IASetInputLayout(m_cubeLayout);
     
  m_worldVariable = m_cubeEffect->GetVariableByName("World")->AsMatrix();
  m_viewVariable = m_cubeEffect->GetVariableByName("View")->AsMatrix();
  m_projectionVariable = m_cubeEffect->GetVariableByName("Projection")->AsMatrix();
}

/******************************************************************************/
void
SimpleTrackballDX10::render(double elapsedTime)
{  
  Star::float4 color(0.f, 1.f, 0.f, 1.f);  
  m_renderDeviceDX10->clearRenderTargetView(color);  

  D3DXVECTOR3 eye = D3DXVECTOR3(0, 0, -3);
  D3DXVECTOR3 lookAt = D3DXVECTOR3(0, 0, 0);
  D3DXVECTOR3 up = D3DXVECTOR3(0, 1, 0);

  //One turn every 4 seconds
  float da = 2*3.14159265358979323846f/(4/elapsedTime);
  alpha += da;
  
  D3DXMatrixRotationY(&m_world, alpha);
  D3DXMatrixLookAtLH(&m_view, &eye, &lookAt, &up);
  D3DXMatrixPerspectiveFovLH(&m_projection, D3DXToRadian(60.f), m_width/float(m_height), 0.001f, 100.f);

  m_worldVariable->SetMatrix( (float*)&m_world );
  m_viewVariable->SetMatrix( (float*)&m_view );
  m_projectionVariable->SetMatrix( (float*)&m_projection );

  ID3D10EffectTechnique* tech = m_cubeEffect->GetTechniqueByIndex(0);
  tech->GetPassByIndex(0)->Apply(0);
  m_cube->begin();
  m_cube->render();  
  m_cube->end();
}

/******************************************************************************/
void
SimpleTrackballDX10::mouseMoved(const Star::MouseMoveEvent& e)
{
  int x, y;
  int relX, relY;
  e.getPosition(x, y);
  e.getRelativePosition(relX, relY);
  std::cout << "Mouse position: " << x << " " << y << " ";
  std::cout << "Mouse relative move: " << relX << " " << relY << std::endl;
}

/******************************************************************************/
Star::Application*
createApplication(int argc, char** argv, HINSTANCE hInst)
{ 
  return new SimpleTrackballDX10(hInst, 800, 600, "Trackball", false);   
}
