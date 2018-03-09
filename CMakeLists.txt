cmake_minimum_required(VERSION 2.8)

include(CMakeToolsHelpers OPTIONAL)

project(ginkgo2)

add_definitions(-std=c++11)

# 设置游戏源文件目录
aux_source_directory("src" SRC_LIST)

# 设置引擎头文件目录
INCLUDE_DIRECTORIES("engine/include" "engine/external/include")

# 设置引擎源文件
aux_source_directory("engine/src" ENGINE_SRC_LIST)

# 设置库目录
if(WIN32 AND NOT MINGW)
    message("WIN32 配置还未完成")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/msvc140/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(glfw3)
elseif(WIN32 AND MINGW)
    message("MINGW 配置")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/mingw530/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(glfw3dll Box2D)
elseif(UNIX AND NOT ANDROID)
    message("UNIX 配置")
    LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/engine/external/lib/gcc540/${CMAKE_BUILD_TYPE})
    LINK_LIBRARIES(glfw3 GL GLU dl Box2D  Xcursor X11 Xrandr Xxf86vm pthread Xinerama)
endif()


# 可执行文件
add_executable(${PROJECT_NAME} ${SRC_LIST} ${ENGINE_SRC_LIST})
