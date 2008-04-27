include(FindOpenGL)

add_executable(simpleEventDX10 simpleEventDX10.cpp main.cpp)
target_link_libraries(simpleEventDX10 StarGraphics StarInput StarMath ${D3D10_LIB} ${SDL_LIBRARY})
