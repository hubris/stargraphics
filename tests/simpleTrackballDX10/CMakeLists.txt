set(HEADERS simpleTrackballDX10.h)
set(SRC simpleTrackballDX10.cpp)

source_group(Headers ${HEADERS})

add_executable(simpleTrackballDX10 ${HEADERS} ${SRC})
target_link_libraries(simpleTrackballDX10 StarGraphics StarInput StarMath ${D3D10_LIB} ${SDL_LIBRARY} d3dx10)
