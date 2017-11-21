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
		// 字号
		float size;
		// 字体颜色
		glm::vec4 color;
		// 字体文件路径，如果为NULL则使用已加载的第一个字体
		std::string font;
		// 一行最多能有多宽（用来换行），如果为0则不限制
		float lineWidth;
		// 行距
		float rowSpacing;
		// 列距
		float colSpacing;

        /// <summary>构造一个新的文本配置</summary>
        /// <param name="size">字体大小</param>
        /// <param name="color">字体颜色</param>
        /// <param name="font">字体文件路径</param>
        /// <param name="lineWidth">行宽，表示一行最多能有多宽（用来换行），如果为0则不限制</param>
        /// <param name="rowSpacing">行距</param>
        /// <param name="colSpacing">列距</param>
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
		// 构造一个TTF字符
		TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
		// 析构时释放GPU资源
		virtual ~TTFCharacter();
		// 加载一个字体文件
		static void loadFont(const char* filePath);
		// 释放一个字体文件
		static void releaseFont(const char* filePath);
		virtual void render();
        int width, height, xoff, yoff;
	protected:
		// 缓存的字体文件
		static std::map<std::string, stbtt_fontinfo> loadedFonts;
		// 字符贴图的id
		GLuint id;
		GLuint VAO, VBO;
        // 字符
        wchar_t code;
	};

	class DLL Text :public Node
	{
	public:
		// 宽字符串->字符串(非线程安全)
		static	std::string ws2s(const std::wstring& ws);
		// 字符串->宽字符串(非线程安全)
		static std::wstring s2ws(const std::string& s);

		// 构造一个文本（父节点, 文本内容，字体名，）
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