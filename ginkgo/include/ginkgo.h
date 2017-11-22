#pragma once

/*�������������ͷ�ļ�*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/*����ginkgo��ͷ�ļ�*/
#include <macros.h>
#include <scene.h>
#include <gameconfig.h>
#include <sprite2d.h>
#include <text.h>

namespace ginkgo
{
    /// <summary>��Ϸ����</summary>
    /// <para>�����ʼ�����ֽӿڡ�����ginkgo�����С������л����¼������ȡ�����run�����Ϳ���������Ϸ��</para>
	class DLL Game {
	public:
        /// <summary>����һ����Ϸ</summary>
        /// <param name="config">��Ϸ���ã�������ΪĬ������</param>
		Game(GameConfig config = GameConfig());
        /// <summary>�����������ͷ�������Դ</summary>
		~Game();
        /// <summary>������Ϸ����ѭ����</summary>
        /// <returns>�����������0</returns>
		int run();
        /// <summary>��ȡ��Ϸ���á�Ϊ��̬��������Ϊ�����ֻ֧�ִ���һ��Game�������У����Ծ͸ɴ�ֱ�Ӱ���Щ������Ϊ��̬�����ˣ�</summary>
        /// <returns>����ֵΪ��Ϸ����</returns>
		static GameConfig getConfigurations();
        /// <summary>��ȡGLFWwindow*���Ա��ڶԴ��ڽ�����ز������߼����¼��ȡ�Ϊ��̬����</summary>
        /// <returns>����ֵGLFWwindow*</returns>
		static GLFWwindow* getWindow();
        /// <summary>�л�����</summary>
        /// <param name="s">���л��ĳ���</param>
        /// <param name="releaseLastScene">�Ƿ��ͷ���һ������</param>
		static void replaceScene(Scene* s, bool releaseLastScene = true);
        /// <summary>��ȡ��ǰ��Ϸ����</summary>
        /// <returns>����ֵScene*Ϊ��ǰ���е���Ϸ����</returns>
		static Scene* getCurrentScene();
        /// <summary>��ȡ��ǰ��֡��</summary>
        /// <returns>����ֵintΪ��ǰ��FPS</returns>
		static int getFPS();
	private:
        /// <summary>��Ϸ����</summary>
		static GameConfig config;
        /// <summary>��Ϸ���á���GLFWwindow��Ϊȫ�ֱ���������á���������һ�����ǵĳ����ֻ֧�ֵ���������
        /// ��ʵ���ϼ��㲻���ó�ȫ�ֱ������������ط��������ֵ�ǰ�����ĵ�д�����жര��Ҳ�ǻ������=_=!��</summary>
		static GLFWwindow* window;
        /// <summary>��ǰ��ĳ���</summary>
		static Scene* currentScene;
        /// <summary>�����滻�����ĳ���</summary>
		static Scene* nextScene;
        /// <summary>�����滻����ʱ�Ƿ��ͷŵ����滻�ĳ���</summary>
		static bool releaseLastScene;
        /// <summary>ȫ���л������ڴ�ʱ��û���¼�����������Ū����ʱ������һ��</summary>
		bool fullscreenSwitched;
        /// <summary>�л�ȫ��״̬</summary>
		void switchFullscreen();
        /// <summary>����FPS</summary>
		void countFPS();
        /// <summary>֡��</summary>
		static int FPS;
	};

}
