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
    /// <summary>�ı�����</summary>
	struct DLL TextConfig
	{
        /// <summary>�ֺ�</summary>
		float size;
        /// <summary>������ɫ</summary>
		glm::vec4 color;
        /// <summary>�����ļ�·��</summary>
		std::string font;
        /// <summary>һ��������ж���������У������Ϊ0������</summary>
		float lineWidth;
        /// <summary>�о�</summary>
		float rowSpacing;
        /// <summary>�о�</summary>
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

    /// <summary>TTF�ַ�</summary>
	class DLL TTFCharacter :public Node
	{
	public:
        /// <summary>����һ��TTF�ַ�</summary>
        /// <param name="parent">���ڵ�</param>
        /// <param name="charcode">������</param>
        /// <param name="fontSize">�����С</param>
        /// <param name="color">��ɫ</param>
        /// <param name="font">������</param>
		TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
        /// <summary>����ʱ�ͷ�GPU��Դ</summary>
		virtual ~TTFCharacter();
        /// <summary>����һ�������ļ�</summary>
        /// <param name="filePath">�����ļ�·��</param>
		static void loadFont(const char* filePath);
        /// <summary>�ͷ�һ�������ļ�</summary>
        /// <param name="filePath">�����ļ�·��</param>
		static void releaseFont(const char* filePath);
        /// <summary>��Ⱦ</summary>
		virtual void render();
        /// <summary>���ߣ���ƫ��������ƫ����</summary>
        int width, height, xoff, yoff;
	protected:
        /// <summary>����������ļ�</summary>
		static std::map<std::string, stbtt_fontinfo> loadedFonts;
        /// <summary>�ַ���ͼ��id</summary>
		GLuint id;
        /// <summary>�������顢�������</summary>
		GLuint VAO, VBO;
        /// <summary>�ַ���</summary>
        wchar_t code;
	};

	class DLL Text :public Node
	{
	public:
        /// <summary>���ַ���->�ַ���(���̰߳�ȫ)</summary>
        /// <param name="ws">��ת���Ŀ��ַ���</param>
        /// <returns>�����ַ���</returns>
		static	std::string ws2s(const std::wstring& ws);
        /// <summary>�ַ���->���ַ���(���̰߳�ȫ)</summary>
        /// <param name="s">��ת�����ַ���</param>
        /// <returns>���ؿ��ַ���</returns>
		static std::wstring s2ws(const std::string& s);
        /// <summary>����һ���ı�</summary>
        /// <param name="text">�ı�����</param>
        /// <param name="config">�ı�����</param>
		Text(Node* parent, std::wstring text = L"", TextConfig config = TextConfig());
        /// <summary>�����ı����ݣ��������ʱ�䷴�����ô˷�������Ӱ��Ч�ʣ�</summary>
        /// <param name="text">�ı�����</param>
		void setText(std::wstring text);
        /// <summary>�����ı����ݣ��������ʱ�䷴�����ô˷�������Ӱ��Ч�ʣ�</summary>
        /// <param name="text">�ı�����</param>
        /// <param name="config">�ı�����</param>
		void setText(std::wstring text, TextConfig config);
        /// <summary>�����ı����ã��������ʱ�䷴�����ô˷�������Ӱ��Ч�ʣ�</summary>
        /// <param name="config">�ı�����</param>
		void setTextConfig(TextConfig config);
        /// <summary>�ı�����</summary>
		std::wstring getText();
        /// <summary>��ȡ�ı�ռ�ݵĴ�С</summary>
        glm::vec2 getSize();
	protected:
        /// <summary>�ַ�list</summary>
		std::list<TTFCharacter*> characters;
        /// <summary>���ַ��ı�</summary>
		std::wstring text;
        /// <summary>�ı�����</summary>
		TextConfig config;
        /// <summary>�����ַ����������ı����ݻ������ú����ô˷�����</summary>
		void updateCharacters();
        /// <summary>�ı�ռ�ݵĴ�С</summary>
        glm::vec2 containSize;
	};
}