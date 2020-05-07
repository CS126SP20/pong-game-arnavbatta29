// Copyright (c) 2020 CS126SP20. All rights reserved.

#ifndef FINALPROJECT_APPS_MYAPP_H_
#define FINALPROJECT_APPS_MYAPP_H_

#include <cinder/app/App.h>
#include <Box2D/Box2D.h>

namespace myapp {

class MyApp : public cinder::app::App {
 public:
  MyApp();
  void setup() override;
  void update() override;
  void draw() override;
  void keyDown(cinder::app::KeyEvent) override;
  void DrawFirstPaddle();
  void DrawSecondPaddle();
  void DrawBall();

  void PrintPosition();
  void EndGame();
  void DrawWalls();
  void PrintScore();
  void PrintText(const std::string& text, const cinder::ivec2& size,
                 const cinder::vec2& loc);
  bool IsBallTouchingPaddle1();
  bool IsBallTouchingPaddle2();

};

}  // namespace myapp

#endif  // FINALPROJECT_APPS_MYAPP_H_
