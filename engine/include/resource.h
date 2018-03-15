#pragma once

#include <string>
#include <iostream>
#include <glm/glm.hpp>
#include <stb/stb_image.h>
#include <stb/stb_truetype.h>
#include <glad/glad.h>
#include <map>

struct Texture
{
  //贴图在OpenGL中的ID
  GLuint id;
  /*//贴图类型（漫反射啊镜面反射啊啥的）
  std::string type;
  //贴图文件路径（可以用来对比是不是重复加载了贴图）
  std::string path;*/
  //尺寸
  int width, height;
  //格式
  GLenum format;
};

struct FontStyle
{
  // 字号
  unsigned int size;
  // 字体颜色
  glm::vec4 color;
  // 字体(key)
  std::string font;
  // 最大行宽（用来换行），如果为0则不限制
  float lineWidth;
  // 行距
  float rowSpacing;
  // 列距
  float colSpacing;
  FontStyle(unsigned int size = 18, glm::vec4 color = glm::vec4(0, 0, 0, 1),
            std::string font = "", float lineWidth = 0, float rowSpacing = 1.0f,
            float colSpacing = 0.0f)
  {
    this->size = size;
    this->color = color;
    this->font = font;
    this->lineWidth = lineWidth;
    this->rowSpacing = rowSpacing;
    this->colSpacing = colSpacing;
  }
};

class ResourceManager
{
public:
  ResourceManager();
  virtual ~ResourceManager();
  static ResourceManager *getInstance();
  // 将一张纹理载入内(显)存中
  int loadTexture(std::string key, std::string filepath, bool linearOrNearest = true);
  // 释放所有纹理
  void releaseAllTextures();
  // 释放一张纹理
  void releaseTexture(std::string key);
  // 获得一张纹理
  Texture getTexture(std::string key);
  // 将一个TTF字体载入内存中
  int loadFontTTF(std::string key, std::string filepath);
  // 释放所有TTF字体
  void releaseAllFontsTTF();
  // 释放一个TTF字体
  void releaseFontTTF(std::string key);
  // 获得一个TTF字体
  stbtt_fontinfo getFontTTF(std::string key);
private:
  // 载入的纹理记录
  std::map<std::string, Texture> textures;
  // 载入的TTF字体记录
  std::map<std::string, stbtt_fontinfo> fontsTTF;

  static ResourceManager *_instance;
};
