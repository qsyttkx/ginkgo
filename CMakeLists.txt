cmake_minimum_required(VERSION 2.8)

include(CMakeToolsHelpers OPTIONAL)

project(ginkgo2)

add_definitions(-std=c++11)

# 设置游戏源文件目录
aux_source_directory("src" SRC_LIST)

# 设置引擎头文件目录
INCLUDE_DIRECTORIES("engine/include"
    "engine/external/include"
    "engine/external/include/imgui"
    "engine/external/include/stb")

# 设置引擎源文件
aux_source_directory("engine/src"  ENGINE_SRC_LIST)
aux_source_directory("engine/external/src" ENGINE_EXTERNAL_SRC_LIST)

# 设置库目录
if(WIN32 AND NOT MINGW)
    message("WIN32 配置")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/msvc140/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(opengl32 glfw3 Box2D winmm)
elseif(WIN32 AND MINGW)
    message("MINGW 配置")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/mingw530/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(opengl32 glfw3dll Box2D winmm)

elseif(UNIX AND NOT ANDROID)
    message("UNIX 配置")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/gcc540/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(glfw3 GL GLU dl Box2D  Xcursor X11 Xrandr Xxf86vm pthread Xinerama)
endif()


# 可执行文件
# 如果你想在Windows下看到控制台以便显示调试信息，可以在以下一行中去掉WIN32这项
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${SRC_LIST} ${ENGINE_EXTERNAL_SRC_LIST} ${ENGINE_SRC_LIST})
else()
    add_executable(${PROJECT_NAME} ${SRC_LIST} ${ENGINE_EXTERNAL_SRC_LIST} ${ENGINE_SRC_LIST})
endif()
