#pragma once

#include <macros.h>
#include <string>

//游戏配置
//在Game构造时载入的游戏配置
struct DLL GameConfig
{
    //构造一个摄像机
    //默认创建一个正交的投影阵，适用于2D场景。如果需要创建透视矩阵，可以在构造后对projectionMatrix重新赋值。
    //游戏标题
    //窗口宽度
    //窗口高度
    //是否全屏
    //是否垂直同步
    GameConfig(
        std::string title = "Ginkgo",
        unsigned int width = 1280,
        unsigned int height = 720,
        bool isFullScreen = false,
        bool isVSyncEnabled = true)
    {
        this->title = title;
        this->width = width;
        this->height = height;
        this->isFullScreen = isFullScreen;
        this->isVSyncEnabled = isVSyncEnabled;
    }
    //游戏标题
    std::string title;
    //窗口宽度
    unsigned int width;
    //窗口高度
    unsigned int height;
    //是否全屏
    bool isFullScreen;
    //是否垂直同步
    bool isVSyncEnabled;
};