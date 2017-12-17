#define EXPORT
#include <macros.h>
#include <text.h>
#include <locale.h>  
#include <iostream>

using namespace std;
using namespace ginkgo;
using namespace glm;

std::map<std::string, stbtt_fontinfo> TTFCharacter::loadedFonts;

TTFCharacter::TTFCharacter(Node* parent, wchar_t charcode, float fontSize, glm::vec4 color, string font) :Node(parent)
{
    id = 0;
    code = charcode;
    // 获取这个字体
    auto iter = loadedFonts.find(font);
    if (iter == loadedFonts.end())
    {
        // 如果没有缓存这个字体则现在载入一下
        loadFont(font.c_str());
        iter = loadedFonts.find(font);
    }
    stbtt_fontinfo fontinfo = (*iter).second;

    // 获取字形的缓冲
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&fontinfo, 0, stbtt_ScaleForPixelHeight(&fontinfo, fontSize), charcode, &width, &height, &xoff, &yoff);
    // 生成贴图内容（长x宽x4(RGBA)）,对了OpenGL要反转y轴
    unsigned char* data = (unsigned char*)malloc(width*height * 4);
    int i, j;
    for (j = 0; j < height; ++j) {
        for (i = 0; i < width; ++i)
        {
            data[(j*width + i) * 4 + 0] = (unsigned char)(255 * color.r);
            data[(j*width + i) * 4 + 1] = (unsigned char)(255 * color.g);
            data[(j*width + i) * 4 + 2] = (unsigned char)(255 * color.b);
            data[(j*width + i) * 4 + 3] = (unsigned char)(bitmap[(height - j - 1)*width + i] * color.a);
        }
    }

    // 如果获取到的width是0，那么可能是遇到了非等宽字体的空格
    if (width != 0)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);//生成mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        // 空格空位字号的一半
        width = (int)(fontSize / 2.0f);
    }

    free(data);


    float vertices[] =
    {	// 这样设置顶点位置可以使得锚点在字的左上角
        // 顶点位置		      				    纹理坐标
                0.0f,           0.0f,  0.0f,    0.0f, 1.0f,
                0.0f, -(float)height,  0.0f,    0.0f, 0.0f,
        (float)width, -(float)height,  0.0f,    1.0f, 0.0f,

                0.0f,           0.0f,  0.0f,    0.0f, 1.0f,
        (float)width, -(float)height,  0.0f,    1.0f, 0.0f,
        (float)width,           0.0f,  0.0f,    1.0f, 1.0f
    };
    // 生成VAO, VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glBindVertexArray(0);
}

TTFCharacter::~TTFCharacter()
{
    if (id)
    {
        glDeleteTextures(1, &id);
        glDeleteBuffers(1, &VBO);
        glDeleteVertexArrays(1, &VAO);
    }
}

// 加载一个TTF字体文件到内存中
void TTFCharacter::loadFont(const char* filePath)
{
    stbtt_fontinfo font;
    FILE* fp;
    // 先分配个32MB的空间
    unsigned char* buffer = (unsigned char*)malloc(1 << 25);
    // 读取文件
    if (fopen_s(&fp, filePath, "rb"))
    {
        cout << "找不到字体文件[" << filePath << "]";
        return;
    };
    size_t bSize = fread(buffer, 1, 1 << 25, fp);
    fclose(fp);
    // 调整分配的空间为文件大小
    buffer = (unsigned char*)realloc(buffer, bSize);
    // 初始化字体
    stbtt_InitFont(&font, buffer, stbtt_GetFontOffsetForIndex(buffer, 0));
    // 把这个字体添加到缓存中
    loadedFonts.insert(make_pair(string(filePath), font));
}

void TTFCharacter::releaseFont(const char* filePath)
{
    auto iter = loadedFonts.find(filePath);
    if (iter != loadedFonts.end())
    {
        // 释放内存
        free((*iter).second.data);
        loadedFonts.erase(iter);
    }
}


void TTFCharacter::update(float dt)
{
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, id);
    Shader::basicDiffuse.setInt("texture_diffuse1", 0);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

string Text::ws2s(const wstring& ws)
{
    string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";  

    setlocale(LC_ALL, "chs");

    const wchar_t* _Source = ws.c_str();
    size_t _Dsize = 2 * ws.size() + 1;
    char *_Dest = new char[_Dsize];
    memset(_Dest, 0, _Dsize);
    size_t retSize;
    wcstombs_s(&retSize, _Dest, _Dsize, _Source, _Dsize);
    string result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, curLocale.c_str());

    return result;
}

wstring Text::s2ws(const string& s)
{
    setlocale(LC_ALL, "chs");

    const char* _Source = s.c_str();
    size_t _Dsize = s.size() + 1;
    wchar_t *_Dest = new wchar_t[_Dsize];
    wmemset(_Dest, 0, _Dsize);
    size_t retSize;
    mbstowcs_s(&retSize, _Dest, _Dsize, _Source, _Dsize);
    wstring result = _Dest;
    delete[]_Dest;

    setlocale(LC_ALL, "C");

    return result;
}

Text::Text(Node* parent, std::wstring text, TextConfig config) :Node(parent)
{
    setText(text, config);
    // 这个文本肯定是有部分纹理是透明的啦，所以默认他要进行手动排序吧
    this->shouldSort = true;
}

void Text::setText(std::wstring text)
{
    this->text = text;
    updateCharacters();
}

void Text::setText(std::wstring text, TextConfig config)
{
    this->text = text;
    this->config = config;
    updateCharacters();
}

void Text::setTextConfig(TextConfig config)
{
    this->config = config;
    updateCharacters();
}

void Text::updateCharacters()
{
    // 清除所有的文字
    auto iter = characters.begin();
    for (auto i = characters.begin(); i != characters.end();)
    {
        TTFCharacter* child = *i;
        // 安全的删除成员，c++11支持erase方法返回被删除的下一个节点
        i = characters.erase(i);
        child->removedFromParent();//这个操作只会断绝其父子关系而不释放内存
        delete(child);
    }

    // 接口已经直接改为用宽字符
    //// 多字节转为宽字符（才能正确获取到对应的字形）
    //wstring wtext = s2ws(text);
    float x = 0, y = 0;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        TTFCharacter* c = new TTFCharacter(this, text[i], config.size, config.color, config.font);
        c->name = (char*)&text[i];
        c->position.x = x;
        c->position.y = y - (float)(c->yoff);
        characters.push_back(c);
        // 向右移动下一个字
        x = x + c->width + c->xoff + config.colSpacing;
        // 换行
        if (config.lineWidth > 0 && config.lineWidth < x)
        {
            x = 0.0f;
            y = y - config.size - config.rowSpacing;
        }
    }
    containSize = vec2(x, config.size - y);
}

wstring Text::getText()
{
    return text;
}

vec2 Text::getSize()
{
    return containSize;
}
