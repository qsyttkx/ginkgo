#pragma once

#include <macros.h>
#include <string>
#include <map>
#include <stb_truetype.h>
#include <node.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

namespace ginkgo
{
	struct DLL TextConfig
	{
		// �ֺ�
		float size;
		// ������ɫ
		glm::vec4 color;
		// �����ļ�·�������ΪNULL��ʹ���Ѽ��صĵ�һ������
		std::string font;
		// һ��������ж���������У������Ϊ0������
		float lineWidth;
		// �о�
		float rowSpacing;
		// �о�
		float colSpacing;

        /// <summary>����һ���µ��ı�����</summary>
        /// <param name="size">�����С</param>
        /// <param name="color">������ɫ</param>
        /// <param name="font">�����ļ�·��</param>
        /// <param name="lineWidth">�п���ʾһ��������ж���������У������Ϊ0������</param>
        /// <param name="rowSpacing">�о�</param>
        /// <param name="colSpacing">�о�</param>
		TextConfig(float size = 32, glm::vec4 color = glm::vec4(0, 0, 0, 1), std::string font = "", float lineWidth = 0, float rowSpacing = 2.0f, float colSpacing = 2.0f)
		{
			this->size = size;
			this->color = color;
			this->font = font;
			this->lineWidth = lineWidth;
			this->rowSpacing = rowSpacing;
			this->colSpacing = colSpacing;
		}
	};

	class DLL TTFCharacter :public Node
	{
	public:
		// ����һ��TTF�ַ�
		TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
		// ����ʱ�ͷ�GPU��Դ
		virtual ~TTFCharacter();
		// ����һ�������ļ�
		static void loadFont(const char* filePath);
		// �ͷ�һ�������ļ�
		static void releaseFont(const char* filePath);
		virtual void render();
        int width, height, xoff, yoff;
	protected:
		// ����������ļ�
		static std::map<std::string, stbtt_fontinfo> loadedFonts;
		// �ַ���ͼ��id
		GLuint id;
		GLuint VAO, VBO;
        // �ַ�
        wchar_t code;
	};

	class DLL Text :public Node
	{
	public:
		// ���ַ���->�ַ���(���̰߳�ȫ)
		static	std::string ws2s(const std::wstring& ws);
		// �ַ���->���ַ���(���̰߳�ȫ)
		static std::wstring s2ws(const std::string& s);

		// ����һ���ı������ڵ�, �ı����ݣ�����������
		Text(Node* parent, std::wstring text = L"", TextConfig config = TextConfig());
		void setText(std::wstring text);
		void setText(std::wstring text, TextConfig config);
		void setTextConfig(TextConfig config);
		std::wstring getText();
        glm::vec2 getSize();
        virtual void render();
	protected:
		std::list<TTFCharacter*> characters;
		std::wstring text;
		TextConfig config;
		void updateCharacters();
        glm::vec2 containSize;
	};
}