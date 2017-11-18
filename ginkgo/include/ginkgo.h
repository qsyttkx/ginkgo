#pragma once

/*�������������ͷ�ļ�*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

/*����ginkgo��ͷ�ļ�*/
#include <scene.h>
#include <gameconfig.h>
#include <sprite2d.h>

namespace ginkgo
{
	// ��Ϸ����
	class DLL Game {
	public:
		Game(GameConfig config = GameConfig());
		~Game();
		int run();
		static GameConfig getConfigurations();
		static GLFWwindow* getWindow();
		void setCurrentScene(Scene* s);
		static Scene* getCurrentScene();
		void init(GameConfig config);
	private:
		static GameConfig config;
		// ��GLFWwindow��Ϊȫ�ֱ�����������ã���������һ�����ǵĳ����ֻ֧��
		// ���������ˣ�ʵ���ϼ��㲻���ó�ȫ�ֱ������������ط��������ֵ�ǰ���ڵ�
		// д�����жര��Ҳ�ǻ������=_=!��
		static GLFWwindow* window;
		static Scene* currentScene;

		// ȫ���л������ڻ�û���¼�����������Ū����ʱ������һ��
		bool fullscreenSwitched;
	};

}
