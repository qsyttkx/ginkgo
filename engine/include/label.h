#pragma once

#include <sprite.h>

class CharacterTTF : public Sprite
{
public:
  CharacterTTF(wchar_t charcode, float fontSize, glm::vec4 color, std::string font);
  virtual ~CharacterTTF();
  int getXoff();
  int getYoff();
  int getWidth();
  int getHeight();
private:
  wchar_t code;
  int xoff, yoff;
};

class Label : public Node
{
public:
  Label(std::string text = "", FontStyle style = FontStyle());
  virtual ~Label();

  // 设置文本
  void setText(std::string text);
  void setText(std::string text, FontStyle style);
  void setFontStyle(FontStyle style);
  // 获取文本
  std::string getText();
  // 获取文本框的尺寸
  glm::vec2 getContainSize();
  //字符串->宽字符串
  static std::wstring s2ws(const std::string &s);
protected:
  std::string text;
  FontStyle style;
  glm::vec2 containSize;
  //更新字符（在重设文本内容或者配置后会调用此方法）
  void updateCharacters();
};