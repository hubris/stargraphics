project(StarGraphics)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
ENABLE_TESTING()

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
message(FATAL_ERROR "CMake generation is not allowed within the source directory! 
Remove the CMakeCache.txt file and try again from another folder, e.g.: 

   rm CMakeCache.txt 
   cd ..
   mkdir cmake-make 
   cd cmake-make
   cmake -G \"Unix Makefiles\" ../starmath
")
endif(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})

include(FindDoxygen)
include(FindSDL)

if(WIN32)
  add_definitions(/DNOMINMAX)
endif(WIN32)

include_directories(${SDL_INCLUDE_DIR})

add_subdirectory(src)

add_subdirectory(tests)

if (DOXYGEN_FOUND)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
  add_custom_target(doc ${DOXYGEN_EXECUTABLE} ${DOXY_CONFIG})
endif(DOXYGEN_FOUND)
