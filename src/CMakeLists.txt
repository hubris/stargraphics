set(StarGraphicsSDL_SOURCES StarApplicationSDL.cpp)
set(HEADERS_SDL ../include/StarGraphics/StarApplicationSDL.h)

set(HEADERS ../include/StarGraphics/StarApplication.h)

if(WIN32)
  set(HEADERS_DX10 ../include/StarGraphics/StarApplicationDX10.h)
  set(StarGraphicsDX10_SOURCES StarApplicationDX10.cpp)

  include_directories($ENV{DXSDK_DIR}/Include)
  link_directories($ENV{DXSDK_DIR}/Lib)

  set(D3D10_LIB d3d10)
endif(WIN32)

source_group(Headers\\StarGraphics FILES ${HEADERS} ${HEADERS_SDL} ${HEADERS_DX10})
source_group(Headers FILES ../include/StarGraphics.h)

add_library(StarGraphics StarApplication.cpp ${StarGraphicsSDL_SOURCES} ${HEADERS_SDL}
                                             ${StarGraphicsDX10_SOURCES} ${HEADERS_DX10}
                                             ${HEADERS} ../include/StarGraphics.h)

target_link_libraries(StarGraphics ${SDL_LIBRARY} StarInput StarUtils ${D3D10_LIB})
