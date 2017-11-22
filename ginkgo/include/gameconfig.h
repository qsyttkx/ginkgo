#pragma once

#include <macros.h>
#include <string>

/// <summary>游戏配置</summary>
/// <para>在Game构造时载入的游戏配置</para>
struct DLL GameConfig
{
    /// <summary>构造一个摄像机</summary>
    /// <para>默认创建一个正交的投影阵，适用于2D场景。如果需要创建透视矩阵，可以在构造后对projectionMatrix重新赋值。</para>
    /// <param name="title">游戏标题</param>
    /// <param name="width">窗口宽度</param>
    /// <param name="height">窗口高度</param>
    /// <param name="isFullScreen">是否全屏</param>
    /// <param name="isVSyncEnabled">是否垂直同步</param>
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
    /// <summary>游戏标题</summary>
    std::string title;
    /// <summary>窗口宽度</summary>
    unsigned int width;
    /// <summary>窗口高度</summary>
    unsigned int height;
    /// <summary>是否全屏</summary>
    bool isFullScreen;
    /// <summary>是否垂直同步</summary>
    bool isVSyncEnabled;
};