#ifndef EVENT_H
#define EVENT_H

#include "log.h"
#include "window.h"
#include <iostream>
#include <memory>

namespace LZ {
enum EventType { None = 0, Key, MouseMove, MouseButton };
class Event {
public:
  virtual bool handle() {
    LZ::Log::printInfo("Default Handle Event");
    return false;
  }

  virtual int getEventType() {
    return 0;
  }
    

  Window *window;

  bool handled = false;
  int eventType = 0;
protected:
};

class KeyEvent : public Event {
public:
  KeyEvent(Window *window, int key, int action) : keyCode(key), action(action) {
    eventType = Key;
  }
  ~KeyEvent() {
  }
  bool handle() override {
    std::cout << keyCode << std::endl;
    return false;
  }
  virtual int getEventType() override {
    return eventType;
  }

  int getKeyCode() {
    return keyCode;
  }

  inline int getAction() {
    return action;
  }
private:

  int keyCode;
  int action;
};

class MouseMoveEvent : public Event {
public:
  MouseMoveEvent(Window *window, int x, int y) : x(x), y(y){
    eventType = MouseMove;
  }
  ~MouseMoveEvent() {
  }
  bool handle() override {
    std::cout << "X: " << x << "Y: " << y << std::endl;
    return false;
  }
  virtual int getEventType() override {
    return eventType;
  }

  inline int getXpos(){
    return x;
  }

  inline int getYpos() {
    return y;
  }

private:
  int x, y;
  int action;
};

class MouseButtonEvent : public Event {
public:
  MouseButtonEvent(Window *window, int button, int action) : button(button), action(action) {
    eventType = MouseButton;
  }

  ~MouseButtonEvent() {
  }

  bool handle() override {
    std::cout << action << std::endl;
    return false;
  }

  virtual int getEventType() override {
    return eventType;
  }

  int getButton() {
    return button;
  }

  inline int getAction() {
    return action;
  }
private:

  int button;
  int action;
};
void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                 int mods);

void cursorPosCallback(GLFWwindow *window, double xpos, double ypos);

void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

void windowSizeCallback(GLFWwindow *window, int width, int height);
} // namespace LZ

#endif
