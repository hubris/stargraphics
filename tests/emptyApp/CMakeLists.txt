include(FindOpenGL)

add_executable(emptyApp emptyApp.cpp main.cpp)
target_link_libraries(emptyApp StarGraphics ${OPENGL_LIBRARIES})
