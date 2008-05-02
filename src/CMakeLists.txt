set(StarGraphicsSDL_SOURCES StarApplicationSDL.cpp)
set(HEADERS_SDL ../include/StarGraphics/StarApplicationSDL.h)

set(HEADERS ../include/StarGraphics/StarApplication.h
            ../include/StarGraphics/StarRenderDevice.h
            ../include/StarGraphics/StarRenderableInterface.h
            ../include/StarGraphics/StarVertex.h
)
set(SOURCES objects/StarCube.cpp StarApplication.cpp)


if(WIN32)
  set(HEADERS_DX10 ../include/StarGraphics/StarApplicationDX10.h
                   ../include/StarGraphics/StarRenderDeviceDX10.h
                   ../include/StarGraphics/StarVertexLayout.h
                   )
  set(StarGraphicsDX10_SOURCES StarApplicationDX10.cpp 
                               StarRenderDeviceDX10.cpp
                               StarVertexLayout.cpp)

  include_directories($ENV{DXSDK_DIR}/Include)
  link_directories($ENV{DXSDK_DIR}/Lib)
endif(WIN32)


#Source groups for visual
set(HEADERS_OBJECTS ../include/StarGraphics/objects/StarCube.h
                    ../include/StarGraphics/objects/StarObject.h)
source_group(Headers\\StarGraphics FILES ${HEADERS} ${HEADERS_SDL} ${HEADERS_DX10})
source_group(Headers\\StarGraphics\\objects FILES ${HEADERS_OBJECTS})
source_group(Headers FILES ../include/StarGraphics.h)

add_library(StarGraphics ${SOURCES} ${StarGraphicsSDL_SOURCES} ${HEADERS_SDL}
                         ${StarGraphicsDX10_SOURCES} ${HEADERS_DX10}
                         ${HEADERS} ../include/StarGraphics.h
                         ${HEADERS_OBJECTS})

target_link_libraries(StarGraphics ${SDL_LIBRARY} StarInput StarUtils ${D3D10_LIB})
