cmake_minimum_required(VERSION 3.5.0)
project(LearnOpenGL VERSION 0.0.1)



set(CMAKE_CXX_STANDARD 17)

include_directories(include)
include_directories(vender)


set(LIB_DIR ${PROJECT_SOURCE_DIR}/lib)

link_libraries(
    ${LIB_DIR}/glfw/libglfw.3.dylib
)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(VENDER_DIR ${PROJECT_SOURCE_DIR}/vender)

add_executable(${PROJECT_NAME} 
    ${SRC_DIR}/main.cpp 
    ${SRC_DIR}/glad.c 
    ${SRC_DIR}/shader.cpp
    ${SRC_DIR}/texture.cpp
    ${SRC_DIR}/camera.cpp
    ${VENDER_DIR}/stb_image/stb_image.cpp
)


# 链接系统的 OpenGL 框架
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()


