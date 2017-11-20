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
		// 字号
		int size;
		// 字体颜色
		glm::vec4 color;
		// 字体文件路径，如果为NULL则使用已加载的第一个字体
		const char* font;
		// 一行最多能有多宽（用来换行），如果为0则不限制
		float lineWidth;
		// 行距
		float rowSpacing;
		// 列距
		float colSpacing;
		// 字号、字体颜色、字体文件路径、一行最多能有多宽
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
		// 构造一个TTF字符
		TTFCharacter(wchar_t charcode, int fontSize, const char* font);
		// 析构时释放GPU资源
		~TTFCharacter();
		// 加载一个字体文件
		static void loadFont(const char* filePath);
		// 释放一个字体文件
		static void releaseFont(const char* filePath);
	private:
		// 缓存的字体文件
		static std::list<stbtt_fontinfo> loadedFonts;
		// 字符贴图的id
		GLuint id;
	};

	class DLL Text :public Node
	{
	public:
		// 宽字符串->字符串(非线程安全)
		static	std::string ws2s(const std::wstring& ws);
		// 字符串->宽字符串(非线程安全)
		static std::wstring s2ws(const std::string& s);

		// 构造一个文本（父节点, 文本内容，字体名，）
		Text(Node* parent);
		void setText(std::string text, TextConfig config);
		std::string getText();
	protected:
		std::list<TTFCharacter*> characters;
		std::string text;
	};
}