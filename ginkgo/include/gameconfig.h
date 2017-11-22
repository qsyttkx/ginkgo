#pragma once

#include <macros.h>
#include <string>

/// <summary>��Ϸ����</summary>
/// <para>��Game����ʱ�������Ϸ����</para>
struct DLL GameConfig
{
    /// <summary>����һ�������</summary>
    /// <para>Ĭ�ϴ���һ��������ͶӰ��������2D�����������Ҫ����͸�Ӿ��󣬿����ڹ�����projectionMatrix���¸�ֵ��</para>
    /// <param name="title">��Ϸ����</param>
    /// <param name="width">���ڿ��</param>
    /// <param name="height">���ڸ߶�</param>
    /// <param name="isFullScreen">�Ƿ�ȫ��</param>
    /// <param name="isVSyncEnabled">�Ƿ�ֱͬ��</param>
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
    /// <summary>��Ϸ����</summary>
    std::string title;
    /// <summary>���ڿ��</summary>
    unsigned int width;
    /// <summary>���ڸ߶�</summary>
    unsigned int height;
    /// <summary>�Ƿ�ȫ��</summary>
    bool isFullScreen;
    /// <summary>�Ƿ�ֱͬ��</summary>
    bool isVSyncEnabled;
};