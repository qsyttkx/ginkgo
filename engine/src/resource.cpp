#include <cstdio>
#include <resource.h>

using namespace std;

ResourceManager *ResourceManager::_instance = nullptr;

ResourceManager::ResourceManager()
{
    if (_instance != nullptr)
        return;

    // 由于OpenGL读取纹理的方向不一样我们需要在加载时反转所有纹理
    stbi_set_flip_vertically_on_load(true);

    _instance = this;
}

ResourceManager::~ResourceManager()
{
    // 清除所有纹理
    releaseAllTextures();
    releaseAllFontsTTF();
}

ResourceManager *ResourceManager::getInstance()
{
    return _instance;
}

int ResourceManager::loadTexture(std::string key, string path, bool linearOrNearest)
{
    // 先检查key是否有重复
    if (textures.find(key) != textures.end())
    {
        cerr << "failed to load texture: " << path << ", the key is conflict!" << endl;
        return 1; // 异常时返回1
    }

    Texture t;
    glGenTextures(1, &(t.id));

    int nrComponents;
    unsigned char *data = stbi_load(path.c_str(), &(t.width), &(t.height), &nrComponents, 0);
    if (data)
    {
        if (nrComponents == 1)
            t.format = GL_RED;
        else if (nrComponents == 3)
            t.format = GL_RGB;
        else if (nrComponents == 4)
            t.format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, t.id);
        glTexImage2D(GL_TEXTURE_2D, 0, t.format, t.width, t.height, 0, t.format, GL_UNSIGNED_BYTE, data);
        //glGenerateMipmap(GL_TEXTURE_2D);//生成mipmap

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        if(linearOrNearest)
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        }
        else
        {
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        }

        // glBindTexture(GL_TEXTURE_2D, 0);

        stbi_image_free(data);

        textures.insert(make_pair(key, t));

        cout << "Texture: " << path << " is loaded." << endl;
        return 0; // 正常时返回0
    }
    else
    {
        cerr << "failed to load texture: " << path << ", can't read data!" << endl;
        return 1; // 异常时返回1
    }
}

void ResourceManager::releaseAllTextures()
{
    for (auto iter = textures.begin(); iter != textures.end(); ++iter)
    {
        Texture t = (*iter).second;
        if (t.id)
        {
            cout << "Texture [" << (*iter).first << "] has been released." << endl;
            glDeleteTextures(1, &(t.id));
        }
    }
    textures.clear();
}

void ResourceManager::releaseTexture(string key)
{
    GLenum id = textures["key"].id;
    if (id)
    {
        cout << "Texture [" << key << "] has been released." << endl;
        glDeleteTextures(1, &id);
    }
}

Texture ResourceManager::getTexture(string key)
{
    auto iter = textures.find(key);
    if (iter == textures.end())
    {
        cerr << "Failed to find texture [" << key << "]!" << endl;
        return Texture();
    }
    else
    {
        return (*iter).second;
    }
}

int ResourceManager::loadFontTTF(string key, string filepath)
{
    stbtt_fontinfo font;
    FILE *fp;
    // 先分配个32MB的空间
    unsigned char *buffer = (unsigned char *)malloc(1 << 25);
    // 读取文件
    if (!(fp = fopen(filepath.c_str(), "rb")))
    {
        cerr << "Can't find font file[" << filepath << "]!" << endl;
        return 1;
    };
    size_t bSize = fread(buffer, 1, 1 << 25, fp);
    fclose(fp);
    // 调整分配的空间为文件大小
    buffer = (unsigned char *)realloc(buffer, bSize);
    // 初始化字体
    stbtt_InitFont(&font, buffer, stbtt_GetFontOffsetForIndex(buffer, 0));
    // 把这个字体添加到缓存中
    fontsTTF.insert(make_pair(key, font));
    return 0;
}

void ResourceManager::releaseAllFontsTTF()
{
    for (auto iter = fontsTTF.begin(); iter != fontsTTF.end(); ++iter)
    {
        cout << "TrueType Font [" << (*iter).first << "] has been released." << endl;
        free((*iter).second.data);
    }
    fontsTTF.clear();
}

void ResourceManager::releaseFontTTF(string key)
{
    auto iter = fontsTTF.find(key);
    if (iter != fontsTTF.end())
    {
        // 释放内存
        free((*iter).second.data);
        fontsTTF.erase(iter);
    }
}

stbtt_fontinfo ResourceManager::getFontTTF(string key)
{
    // 不指定字体则返回首个字体
    if(key.length() == 0 && fontsTTF.size()>0)
    {
        return (*fontsTTF.begin()).second;
    }

    auto iter = fontsTTF.find(key);
    if (iter == fontsTTF.end())
    {
        cerr << "Failed to find font [" << key << "]!" << endl;
        return stbtt_fontinfo();
    }
    else
    {
        return (*iter).second;
    }
}
