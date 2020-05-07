// Copyright (c) 2020 Arnav Batta. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>

using cinder::Rectf;
using cinder::Color;
using cinder::ColorA;

namespace myapp {

using cinder::app::KeyEvent;

const float tile_size_ = 25;
int p1PaddlePosition = 20;
int p2PaddlePosition = 20;
double circleXPos = 300;
double circleYPos = 200;
double slopeYOfBallMovement = 4;
double slopeXOfBallMovement = 2;
double wallBounceConstant = 0.95;
b2Vec2 gravity(0.0, 0.0);
b2World world(gravity);
b2Vec2 velocity = {1, 1};
b2BodyDef bodyDef;
b2Body* body;
double bounceConstant = 0.8;
int maxXDim = 650;
int maxYDim = 800;
int minXDim = 150;
int minYDim = 0;
int speedLimit = 15;
double speedReducer = 0.75;
bool practiceMode = false;
double paddle1x1;
double paddle1x2;
double paddle1y1;
double paddle1y2;
double paddle2x1;
double paddle2x2;
double paddle2y1;
double paddle2y2;
int topScore = 0;
int bottomScore = 0;
int positiveXSlopes[] = {2, 3, 4};
int negativeXSlopes[] = {-2, -3, -4};
int sizeOfSlopesArray = 3;
bool isGameOver = false;
int scoreToWin = 10;

MyApp::MyApp() { }

/**
 * Creates the ball dynamic body through Box2D used for tracking position
 */
void MyApp::setup() {
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(circleXPos, circleYPos);
        body = world.CreateBody(&bodyDef);

        b2CircleShape* circle = new b2CircleShape();
        circle->m_radius = 0.8;
        circle->m_radius = 8;

        b2FixtureDef* fixtureDef = new b2FixtureDef();
        fixtureDef->shape = circle;
        fixtureDef->density = 10;
        fixtureDef->friction = 0.1;
        fixtureDef->density = 100;
        fixtureDef->friction = 5;
        fixtureDef->restitution = 0.6f; // Make it bounce a little bit

        body->CreateFixture(fixtureDef);
}

/**
 * Checks if a player has won (score >= 10) and if not, updates box2D ball body position
 */
void MyApp::update() {
    world.Step(10, 10, 10);
    if (isGameOver) {
        EndGame();
        return;
    }

    if (topScore >= scoreToWin | bottomScore >= scoreToWin) {
        isGameOver = true;
    }
    b2Vec2 ballPos = {(float32) circleXPos, (float32) circleYPos};
    body->SetTransform(ballPos, 0);
}

/**
 * Calls helper functions to draw paddles, walls, ball, and position of the ball
 */
void MyApp::draw() {
    if (isGameOver) {
        return;
    }
    cinder::gl::clear({0, 0, 0});
    DrawFirstPaddle();
    DrawSecondPaddle();
    DrawBall();
    PrintScore();
    DrawWalls();
    PrintPosition();
}

/**
 * Prints position of Box2D ball in window
 */
void MyApp::PrintPosition() {
    std::string newStr = "Pos :     " + std::to_string((int) body->GetPosition().x) +  " , "
            + std::to_string((int) body->GetPosition().y);
    const std::string text = newStr;
    const cinder::ivec2 size = {100, 50};
    const cinder::vec2 loc = {120, 750};

    PrintText(text, size, loc);
}

/**
 * Prints the score of the players during game
 */
void MyApp::PrintScore() {
    cinder::gl::color(1,1,1);
    const std::string text = std::to_string(topScore);
    const cinder::ivec2 size = {50, 50};
    const cinder::vec2 loc = {50, 350};

    const std::string text2 = std::to_string(bottomScore);
    const cinder::ivec2 size2 = {50, 50};
    const cinder::vec2 loc2 = {50, 450};

    PrintText(text, size, loc);
    PrintText(text2, size2, loc2);
}

/**
 * Adapted from https://courses.grainger.illinois.edu/cs126/sp2020/assignments/snake/
 * Helper function to print text in game window
 * @param text - string to be printed
 * @param size - size of text
 * @param loc - location of text
 */
void MyApp::PrintText(const std::string& text, const cinder::ivec2& size,
               const cinder::vec2& loc) {

    auto box = cinder::TextBox()
            .alignment(cinder::TextBox::CENTER)
            .size(size)
            .backgroundColor(ColorA(0, 0, 0, 0))
            .text(text);

    const auto box_size = box.getSize();
    const cinder::vec2 locp = {loc.x - box_size.x / 1, loc.y - box_size.y / 1};
    const auto surface = box.render();
    const auto texture = cinder::gl::Texture::create(surface);
    cinder::gl::draw(texture, locp);
}

/**
 * Draws first paddle and adjusts position based on user's keystrokes and/or practice mode
 */
void MyApp::DrawFirstPaddle() {
    cinder::gl::color(1,0,0);
    if (practiceMode) {
        cinder::gl::color(0,1,0);
        cinder::gl::drawSolidRect(Rectf(circleXPos - 60,
                                        tile_size_ * 0.01,
                                        circleXPos + 60,
                                        tile_size_ * 0.01 + tile_size_));
        paddle1x1 = circleXPos - 25;
        paddle1x2 = circleXPos + 25;
        paddle1y1 = tile_size_ * 0.01;
        paddle1y2 = tile_size_ * 0.01 + tile_size_;
    } else {
        cinder::gl::drawSolidRect(Rectf(tile_size_ * (p1PaddlePosition - 4),
                                        tile_size_ * 0.01,
                                        tile_size_ * p1PaddlePosition + tile_size_,
                                        tile_size_ * 0.01 + tile_size_));
        paddle1x1 = tile_size_ * (p1PaddlePosition - 4);
        paddle1x2 = tile_size_ * p1PaddlePosition + tile_size_;
        paddle1y1 = tile_size_ * 0.01;
        paddle1y2 = tile_size_ * 0.01 + tile_size_;
    }
}

/**
 * Draws walls which represent the bounds of the game
 */
void MyApp::DrawWalls() {
    cinder::gl::drawSolidRect(Rectf(150,0,650, 5));
    cinder::gl::drawSolidRect(Rectf(150,795,650, 800));
    cinder::gl::drawSolidRect(Rectf(635,0,650, 800));
    cinder::gl::drawSolidRect(Rectf(140,0,155, 800));

}

/**
 * Draws second paddle and adjusts position based on user's keystrokes
 */
void MyApp::DrawSecondPaddle() {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p2PaddlePosition - 4),
                                    tile_size_ * 31,
                                    tile_size_ * p2PaddlePosition + tile_size_,
                                    tile_size_ * 31 + (tile_size_ - 4)));
    paddle2x1 = tile_size_ * (p2PaddlePosition - 4);
    paddle2x2 = tile_size_ * p2PaddlePosition + tile_size_;
    paddle2y1 = tile_size_ * 31;
    paddle2y2 = tile_size_ * 31 + (tile_size_-4);
}

/**
 * Draws position of ball based on its position (touching a wall, bouncing off paddle, etc)
 */
void MyApp::DrawBall() {
    if (abs(slopeYOfBallMovement) > speedLimit) {
        slopeYOfBallMovement *= speedReducer;
    }
    cinder::gl::color((float) rand() / (RAND_MAX),(float) rand() / (RAND_MAX),(float) rand() / (RAND_MAX));

    if ((circleXPos >= (maxXDim - 5) && circleYPos >= maxYDim)) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeXOfBallMovement *= negativeXSlopes[rand() % sizeOfSlopesArray];
        slopeYOfBallMovement *= ((float) bounceConstant + (float) rand() / (RAND_MAX)) * -wallBounceConstant;
        velocity = {-1*velocity.x, -1*velocity.y*((float) 0.5 + (float) rand() / (RAND_MAX))};
        topScore++;
    } else if (circleXPos < minXDim && circleYPos < minYDim) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);

        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
        slopeXOfBallMovement *= positiveXSlopes[rand() % sizeOfSlopesArray];
        slopeYOfBallMovement *= ((float) bounceConstant + (float) rand() / (RAND_MAX)) * -wallBounceConstant;
        // velocity = {-1*velocity.x, -1*velocity.y*((float) 0.5 + (float) rand() / (RAND_MAX))};
        bottomScore++;
    } else if (circleXPos >= (maxXDim - 5) || circleXPos <= minXDim) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;

        if (circleXPos >= (maxXDim - 5)) {
            if (slopeXOfBallMovement > 0) {
                slopeXOfBallMovement = negativeXSlopes[rand() % sizeOfSlopesArray];
            } else {
                slopeXOfBallMovement = positiveXSlopes[rand() % sizeOfSlopesArray];
            }
        } else {
            if (slopeXOfBallMovement > 0) {
                slopeXOfBallMovement = negativeXSlopes[rand() % sizeOfSlopesArray];
            } else {
                slopeXOfBallMovement = positiveXSlopes[rand() % sizeOfSlopesArray];
            }
        }
    } else if (circleYPos >= maxYDim || circleYPos <= minYDim) {
        if (circleYPos >= maxXDim) {
            topScore++;
            circleXPos = 400;
            circleYPos = 100;
            cinder::gl::drawSolidCircle({400, 100}, 8);
            slopeYOfBallMovement = 5;
            slopeXOfBallMovement = positiveXSlopes[rand() % sizeOfSlopesArray];
            return;
        } else {
            bottomScore++;
            circleXPos = 400;
            circleYPos = 100;
            cinder::gl::drawSolidCircle({400, 100}, 8);
            slopeYOfBallMovement = 5;
            slopeXOfBallMovement = 1;
            return;
        }
    } else if (IsBallTouchingPaddle1()) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeYOfBallMovement *= ((float) bounceConstant + (float) rand() / (RAND_MAX)) * -wallBounceConstant;
    } else if (IsBallTouchingPaddle2()) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeYOfBallMovement *= ((float) bounceConstant + (float) rand() / (RAND_MAX)) * -wallBounceConstant;
    }
    else {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
    }

}

/**
 * Helper function to detect ball contact with paddle 1
 */
bool MyApp::IsBallTouchingPaddle1() {
    return (circleXPos <= paddle1x2 && circleXPos >= paddle1x1 && circleYPos <= paddle1y2 && circleYPos >= paddle1y1);
}

/**
 * Helper function to detect ball contact with paddle 2
 */
bool MyApp::IsBallTouchingPaddle2() {
    return (circleXPos <= paddle2x2 && circleXPos >= paddle2x1 && circleYPos <= paddle2y2 && circleYPos >= paddle2y1);
}

/**
 * Detects if game is over and prints winner of game
 */
void MyApp::EndGame() {
    const std::string topPlayerText = "T o p    P l a y e r     W i n s !";
    const std::string bottomPlayerText = "B o t t o m    P l a y e r     W i n s !";
    const cinder::ivec2 size = {180, 70};

    if (topScore > bottomScore) {
        PrintText(topPlayerText, size, getWindowCenter());
    } else {
        PrintText(bottomPlayerText, size, getWindowCenter());
    }
}

/**
 * Reads user's keystrokes and acts appropriately
 * @param event - key pressed
 */
void MyApp::keyDown(KeyEvent event) {
        switch (event.getCode()) {
            case KeyEvent::KEY_LEFT: {
                if (paddle1x1 > minXDim) {
                    p1PaddlePosition = p1PaddlePosition - 1;
                }
                break;
            }
            case KeyEvent::KEY_RIGHT: {
                if (paddle1x2 < maxXDim) {
                    p1PaddlePosition = p1PaddlePosition + 1;
                }
                break;
            }

            case KeyEvent::KEY_a: {
                if (paddle2x1 > minXDim) {
                    p2PaddlePosition = p2PaddlePosition - 1;
                }
                break;
            }

            case KeyEvent::KEY_d: {
                if (paddle2x2 < maxXDim) {
                    p2PaddlePosition = p2PaddlePosition + 1;

                }
                break;
            }

            case KeyEvent::KEY_p: {
                practiceMode = !practiceMode;
                break;
            }

            case KeyEvent::KEY_n: {
                isGameOver = false;
                topScore = 0;
                bottomScore = 0;
                break;
            }

            case KeyEvent::KEY_q: {
                exit(2);
            }
        }
    }
}  // namespace myapp
