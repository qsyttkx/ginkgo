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
    // ��ȡ�������
    auto iter = loadedFonts.find(font);
    if (iter == loadedFonts.end())
    {
        // ���û�л��������������������һ��
        loadFont(font.c_str());
        iter = loadedFonts.find(font);
    }
    stbtt_fontinfo fontinfo = (*iter).second;

    // ��ȡ���εĻ���
    unsigned char* bitmap = stbtt_GetCodepointBitmap(&fontinfo, 0, stbtt_ScaleForPixelHeight(&fontinfo, fontSize), charcode, &width, &height, &xoff, &yoff);
    // ������ͼ���ݣ���x��x4(RGBA)��,����OpenGLҪ��תy��
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

    // �����ȡ����width��0����ô�����������˷ǵȿ�����Ŀո�
    if (width != 0)
    {
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_2D, id);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);//����mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    else
    {
        // �ո��λ�ֺŵ�һ��
        width = (int)(fontSize / 2.0f);
    }

    free(data);


    float vertices[] =
    {	// �������ö���λ�ÿ���ʹ��ê�����ֵ����Ͻ�
        // ����λ��		      				    ��������
                0.0f,           0.0f,  0.0f,    0.0f, 1.0f,
                0.0f, -(float)height,  0.0f,    0.0f, 0.0f,
        (float)width, -(float)height,  0.0f,    1.0f, 0.0f,

                0.0f,           0.0f,  0.0f,    0.0f, 1.0f,
        (float)width, -(float)height,  0.0f,    1.0f, 0.0f,
        (float)width,           0.0f,  0.0f,    1.0f, 1.0f
    };
    // ����VAO, VBO
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
    }

    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

// ����һ��TTF�����ļ����ڴ���
void TTFCharacter::loadFont(const char* filePath)
{
    stbtt_fontinfo font;
    FILE* fp;
    // �ȷ����32MB�Ŀռ�
    unsigned char* buffer = (unsigned char*)malloc(1 << 25);
    // ��ȡ�ļ�
    if (fopen_s(&fp, filePath, "rb"))
    {
        cout << "�Ҳ��������ļ�[" << filePath << "]";
#ifdef WIN32
        cout << "�����滻Ϊarialbd.ttf"<< endl;
        fopen_s(&fp, "C:/Windows/Fonts/arialbd.ttf", "rb");
#else
        return;
#endif // WIN32
    };
    size_t bSize = fread(buffer, 1, 1 << 25, fp);
    fclose(fp);
    // ��������Ŀռ�Ϊ�ļ���С
    buffer = (unsigned char*)realloc(buffer, bSize);
    // ��ʼ������
    stbtt_InitFont(&font, buffer, stbtt_GetFontOffsetForIndex(buffer, 0));
    // �����������ӵ�������
    loadedFonts.insert(make_pair(string(filePath), font));
}

void TTFCharacter::releaseFont(const char* filePath)
{
    auto iter = loadedFonts.find(filePath);
    if (iter != loadedFonts.end())
    {
        // �ͷ��ڴ�
        free((*iter).second.data);
        loadedFonts.erase(iter);
    }
}


void TTFCharacter::render()
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
    // ����ı��϶����в���������͸������������Ĭ����Ҫ�����ֶ������
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
    // ������е�����
    auto iter = characters.begin();
    for (auto i = characters.begin(); i != characters.end();)
    {
        TTFCharacter* child = *i;
        // ��ȫ��ɾ����Ա��c++11֧��erase�������ر�ɾ������һ���ڵ�
        i = characters.erase(i);
        child->removedFromParent();//�������ֻ��Ͼ��丸�ӹ�ϵ�����ͷ��ڴ�
        delete(child);
    }

    // �ӿ��Ѿ�ֱ�Ӹ�Ϊ�ÿ��ַ�
    //// ���ֽ�תΪ���ַ���������ȷ��ȡ����Ӧ�����Σ�
    //wstring wtext = s2ws(text);
    float x = 0, y = 0;
    for (unsigned int i = 0; i < text.length(); i++)
    {
        TTFCharacter* c = new TTFCharacter(this, text[i], config.size, config.color, config.font);
        c->position.x = x;
        c->position.y = y - (float)(c->yoff);
        characters.push_back(c);
        // �����ƶ���һ����
        x = x + c->width + c->xoff + config.colSpacing;
        // ����
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
