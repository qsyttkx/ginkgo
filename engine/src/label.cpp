#include <label.h>
#include <cstring>
#include <imgui.h>
#include <imgui_internal.h>

using namespace glm;
using namespace std;

CharacterTTF::CharacterTTF(wchar_t charcode, float fontSize, vec4 color, string font) : Sprite()
{
    // 一般出现标签的地方字都很多，就不输出释放的信息了
    showReleaseInfo = false;
    // **取得这个字符的纹理

    // 获取这个字体
    code = charcode;
    auto manager = ResourceManager::getInstance();
    stbtt_fontinfo fontinfo = manager->getFontTTF(font);
    // 获取字形的缓冲
    unsigned char *bitmap =
        stbtt_GetCodepointBitmap(&fontinfo,
                                 0,
                                 stbtt_ScaleForPixelHeight(&fontinfo, fontSize),
                                 charcode,
                                 &(texture.width),
                                 &(texture.height),
                                 &xoff,
                                 &yoff);
    // 生成贴图内容（长x宽x4(RGBA)）,对了OpenGL要反转y轴
    unsigned char *data = (unsigned char *)malloc(texture.width * texture.height * 4);
    int i, j;
    for (j = 0; j < texture.height; ++j)
    {
        for (i = 0; i < texture.width; ++i)
        {
            data[(j * texture.width + i) * 4 + 0] = (unsigned char)(255 * color.r);
            data[(j * texture.width + i) * 4 + 1] = (unsigned char)(255 * color.g);
            data[(j * texture.width + i) * 4 + 2] = (unsigned char)(255 * color.b);
            data[(j * texture.width + i) * 4 + 3] = (unsigned char)(bitmap[(texture.height - j - 1) * texture.width + i] * color.a);
        }
    }
    // 如果获取到的width是0，那么可能是遇到了非等宽字体的空格
    if (texture.width != 0)
    {
        glGenTextures(1, &(texture.id));
        glBindTexture(GL_TEXTURE_2D, texture.id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D); //生成mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        // 设空格空位字号的一半
        texture.width = (int)(fontSize / 2.0f);
    }

    free(data);

    // 调整锚点
    setAnchor(0.0f, 1.0f);
    // 根据字符大小调整模型矩阵
    updateModelMatrix();
}

CharacterTTF::~CharacterTTF()
{
    // 字符生成的贴图没有记录在textures中，所以在这里释放资源
    if (texture.id)
    {
        glDeleteTextures(1, &(texture.id));
    }
}

int CharacterTTF::getXoff()
{
    return xoff;
}

int CharacterTTF::getYoff()
{
    return yoff;
}

int CharacterTTF::getWidth()
{
    return texture.width;
}

int CharacterTTF::getHeight()
{
    return texture.height;
}

Label::Label(string text, FontStyle style)
{
    setText(text, style);
}

Label::~Label()
{
}

void Label::setText(string text)
{
    this->text = text;
    updateCharacters();
}

void Label::setText(string text, FontStyle style)
{
    this->text = text;
    this->style = style;
    updateCharacters();
}

string Label::getText()
{
    return text;
}

void Label::setFontStyle(FontStyle style)
{
    this->style = style;
    updateCharacters();
}

void Label::updateCharacters()
{
    // 清除所有文字
    removeAllChildren(true);
    // 将字符串改为宽字符串（这样汉字也对应一个宽字符，才能获取到Unicode编码）
    wstring wtext = s2ws(text);
    // 逐个获取字符并排列
    float x = 0, y = 0;
    for (unsigned int i = 0; i < wtext.length(); i++)
    {
        CharacterTTF *c = new CharacterTTF(wtext[i], float(style.size), style.color, style.font);
        addChild(c);
        c->setPosition(x, y - float(c->getYoff()) - style.size/4);
        // 向右移动下一个字
        x = x + c->getWidth() + 0.5f * float(c->getXoff()) + style.colSpacing;
        // 换行
        if (style.lineWidth > 0 && style.lineWidth < x)
        {
            x = 0.0f;
            y = y - style.size - style.rowSpacing;
        }
    }
    containSize = vec2(x, style.size - y);
}

vec2 Label::getContainSize()
{
    return containSize;
}

wstring Label::s2ws(const string &s)
{
    const char *utf8_chars = s.c_str();
    const int wchars_buf_len = s.size() + 1;
    wchar_t *wchars = new wchar_t[wchars_buf_len];
    // ImGui中将char*转换为wchar型unicode编码的函数
    ImTextStrFromUtf8((ImWchar*)wchars, wchars_buf_len, utf8_chars, NULL, NULL);
    wstring result = wstring(wchars);
    delete[] wchars;
    return result;
}
