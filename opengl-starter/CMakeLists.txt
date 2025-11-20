cmake_minimum_required(VERSION 3.14)
project(opengl-starter LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

# GLFW
FetchContent_Declare(
  glfw
  GIT_REPOSITORY https://github.com/glfw/glfw.git
  GIT_TAG 3.3.8
)

# glad
FetchContent_Declare(
  glad
  GIT_REPOSITORY https://github.com/Dav1dde/glad.git
  GIT_TAG v0.1.36
)

# glm
FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG 0.9.9.8
)

FetchContent_MakeAvailable(glfw glad glm)

add_executable(opengl-starter src/main.cpp)

target_link_libraries(opengl-starter PRIVATE glfw glad)
target_include_directories(opengl-starter PRIVATE ${glad_SOURCE_DIR}/include)

if(UNIX)
  find_package(X11)
  if(X11_FOUND)
    target_link_libraries(opengl-starter PRIVATE ${X11_LIBRARIES})
  endif()
endif()
