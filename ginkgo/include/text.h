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
    /// <summary>文本配置</summary>
	struct DLL TextConfig
	{
        /// <summary>字号</summary>
		float size;
        /// <summary>字体颜色</summary>
		glm::vec4 color;
        /// <summary>字体文件路径</summary>
		std::string font;
        /// <summary>一行最多能有多宽（用来换行），如果为0则不限制</summary>
		float lineWidth;
        /// <summary>行距</summary>
		float rowSpacing;
        /// <summary>列距</summary>
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

    /// <summary>TTF字符</summary>
	class DLL TTFCharacter :public Node
	{
	public:
        /// <summary>构造一个TTF字符</summary>
        /// <param name="parent">父节点</param>
        /// <param name="charcode">字形码</param>
        /// <param name="fontSize">字体大小</param>
        /// <param name="color">颜色</param>
        /// <param name="font">字体名</param>
		TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
        /// <summary>析构时释放GPU资源</summary>
		virtual ~TTFCharacter();
        /// <summary>加载一个字体文件</summary>
        /// <param name="filePath">字体文件路径</param>
		static void loadFont(const char* filePath);
        /// <summary>释放一个字体文件</summary>
        /// <param name="filePath">字体文件路径</param>
		static void releaseFont(const char* filePath);
        /// <summary>渲染</summary>
		virtual void render();
        /// <summary>宽，高，横偏移量，纵偏移量</summary>
        int width, height, xoff, yoff;
	protected:
        /// <summary>缓存的字体文件</summary>
		static std::map<std::string, stbtt_fontinfo> loadedFonts;
        /// <summary>字符贴图的id</summary>
		GLuint id;
        /// <summary>顶点数组、缓冲对象</summary>
		GLuint VAO, VBO;
        /// <summary>字符码</summary>
        wchar_t code;
	};

	class DLL Text :public Node
	{
	public:
        /// <summary>宽字符串->字符串(非线程安全)</summary>
        /// <param name="ws">待转换的宽字符串</param>
        /// <returns>返回字符串</returns>
		static	std::string ws2s(const std::wstring& ws);
        /// <summary>字符串->宽字符串(非线程安全)</summary>
        /// <param name="s">待转换的字符串</param>
        /// <returns>返回宽字符串</returns>
		static std::wstring s2ws(const std::string& s);
        /// <summary>构造一个文本</summary>
        /// <param name="text">文本内容</param>
        /// <param name="config">文本配置</param>
		Text(Node* parent, std::wstring text = L"", TextConfig config = TextConfig());
        /// <summary>设置文本内容（不建议短时间反复调用此方法，会影响效率）</summary>
        /// <param name="text">文本内容</param>
		void setText(std::wstring text);
        /// <summary>设置文本内容（不建议短时间反复调用此方法，会影响效率）</summary>
        /// <param name="text">文本内容</param>
        /// <param name="config">文本配置</param>
		void setText(std::wstring text, TextConfig config);
        /// <summary>设置文本配置（不建议短时间反复调用此方法，会影响效率）</summary>
        /// <param name="config">文本配置</param>
		void setTextConfig(TextConfig config);
        /// <summary>文本内容</summary>
		std::wstring getText();
        /// <summary>获取文本占据的大小</summary>
        glm::vec2 getSize();
	protected:
        /// <summary>字符list</summary>
		std::list<TTFCharacter*> characters;
        /// <summary>宽字符文本</summary>
		std::wstring text;
        /// <summary>文本配置</summary>
		TextConfig config;
        /// <summary>更新字符（在重设文本内容或者配置后会调用此方法）</summary>
		void updateCharacters();
        /// <summary>文本占据的大小</summary>
        glm::vec2 containSize;
	};
}