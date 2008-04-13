set(StarGraphicsSDL_SOURCES StarApplicationSDL.cpp)

add_library(StarGraphics StarApplication.cpp ${StarGraphicsSDL_SOURCES})

target_link_libraries(StarGraphics ${SDL_LIBRARY} StarInput)
