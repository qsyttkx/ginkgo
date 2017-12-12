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
    //文本配置
	struct DLL TextConfig
	{
        //字号
		float size;
        //字体颜色
		glm::vec4 color;
        //字体文件路径
		std::string font;
        //一行最多能有多宽（用来换行），如果为0则不限制
		float lineWidth;
        //行距
		float rowSpacing;
        //列距
		float colSpacing;
        //构造一个新的文本配置
        //字体大小
        //字体颜色
        //字体文件路径
        //行宽，表示一行最多能有多宽（用来换行），如果为0则不限制
        //行距
        //列距
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

    //TTF字符
	class DLL TTFCharacter :public Node
	{
	public:
        //构造一个TTF字符
        //父节点
        //字形码
        //字体大小
        //颜色
        //字体名
		TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
        //析构时释放GPU资源
		virtual ~TTFCharacter();
        //加载一个字体文件
        //字体文件路径
		static void loadFont(const char* filePath);
        //释放一个字体文件
        //字体文件路径
		static void releaseFont(const char* filePath);
        //渲染
		virtual void update(float dt);
        //宽，高，横偏移量，纵偏移量
        int width, height, xoff, yoff;
	protected:
        //缓存的字体文件
		static std::map<std::string, stbtt_fontinfo> loadedFonts;
        //字符贴图的id
		GLuint id;
        //顶点数组、缓冲对象
		GLuint VAO, VBO;
        //字符码
        wchar_t code;
	};

	class DLL Text :public Node
	{
	public:
        //宽字符串->字符串(非线程安全)
        //待转换的宽字符串
        //返回字符串
		static	std::string ws2s(const std::wstring& ws);
        //字符串->宽字符串(非线程安全)
        //待转换的字符串
        //返回宽字符串
		static std::wstring s2ws(const std::string& s);
        //构造一个文本
        //文本内容
        //文本配置
		Text(Node* parent, std::wstring text = L"", TextConfig config = TextConfig());
        //设置文本内容（不建议短时间反复调用此方法，会影响效率）
        //文本内容
		void setText(std::wstring text);
        //设置文本内容（不建议短时间反复调用此方法，会影响效率）
        //文本内容
        //文本配置
		void setText(std::wstring text, TextConfig config);
        //设置文本配置（不建议短时间反复调用此方法，会影响效率）
        //文本配置
		void setTextConfig(TextConfig config);
        //文本内容
		std::wstring getText();
        //获取文本占据的大小
        glm::vec2 getSize();
	protected:
        //字符list
		std::list<TTFCharacter*> characters;
        //宽字符文本
		std::wstring text;
        //文本配置
		TextConfig config;
        //更新字符（在重设文本内容或者配置后会调用此方法）
		void updateCharacters();
        //文本占据的大小
        glm::vec2 containSize;
	};
}