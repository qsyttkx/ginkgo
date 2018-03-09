#pragma once

#include <sprite.h>
#include <label.h>
#include <functional>

class Button : public Sprite
{
public:
  // 构建一个按钮，参数分别为正常、按下、悬停时显示的纹理索引
  Button(std::string normal, std::string pressed = "", std::string hover = "");
  ~Button();
  MouseEventCallback onClick;
  
  // 设置文本
  void setText(std::string text);
  void setText(std::string text, FontStyle style);
  void setFontStyle(FontStyle style);
  // 获取文本
  std::string getText();

private:
  // 三种状态时的纹理
  Texture texNormal, texPressed, texHover;
  MouseEventListener *listener;
  // 判断是否鼠标落在了按钮内
  bool checkMousePosition(glm::vec2 pos);
  bool isPressed;
  Label* label;
};