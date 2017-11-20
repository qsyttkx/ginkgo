#pragma once

#include <macros.h>
#include <string>
#include <list>
#include <stb_truetype.h>
#include <node.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace ginkgo
{
	struct DLL TextConfig
	{
		// �ֺ�
		int size;
		// ������ɫ
		glm::vec4 color;
		// �����ļ�·�������ΪNULL��ʹ���Ѽ��صĵ�һ������
		const char* font;
		// һ��������ж���������У������Ϊ0������
		float lineWidth;
		// �о�
		float rowSpacing;
		// �о�
		float colSpacing;
		// �ֺš�������ɫ�������ļ�·����һ��������ж��
		TextConfig(int size = 16, glm::vec4 color = glm::vec4(0,0,0,1), const char* font = NULL, float lineWidth = 0, float rowSpacing = 0, float colSpacing = 0)
		{
			this->size = size;
			this->color = color;
			this->font = font;
			this->lineWidth = lineWidth;
			this->rowSpacing = rowSpacing;
			this->colSpacing = colSpacing;
		}
	};

	class TTFCharacter :public Node
	{
	public:
		// ����һ��TTF�ַ�
		TTFCharacter(wchar_t charcode, int fontSize, const char* font);
		// ����ʱ�ͷ�GPU��Դ
		~TTFCharacter();
		// ����һ�������ļ�
		static void loadFont(const char* filePath);
		// �ͷ�һ�������ļ�
		static void releaseFont(const char* filePath);
	private:
		// ����������ļ�
		static std::list<stbtt_fontinfo> loadedFonts;
		// �ַ���ͼ��id
		GLuint id;
	};

	class DLL Text :public Node
	{
	public:
		// ���ַ���->�ַ���(���̰߳�ȫ)
		static	std::string ws2s(const std::wstring& ws);
		// �ַ���->���ַ���(���̰߳�ȫ)
		static std::wstring s2ws(const std::string& s);

		// ����һ���ı������ڵ�, �ı����ݣ�����������
		Text(Node* parent);
		void setText(std::string text, TextConfig config);
		std::string getText();
	protected:
		std::list<TTFCharacter*> characters;
		std::string text;
	};
}