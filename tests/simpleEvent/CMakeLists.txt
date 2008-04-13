include(FindOpenGL)

add_executable(simpleEvent simpleEvent.cpp main.cpp)
target_link_libraries(simpleEvent StarGraphics StarInput StarMath ${OPENGL_LIBRARIES})
