// Copyright (c) 2020 [Your Name]. All rights reserved.

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
double slopeYOfBallMovement = 30;
double slopeXOfBallMovement = 30;
int maxDimension = 800;
double wallBounceConstant = 1.01;
b2Vec2 gravity(0.0, 0.0);
b2World world(gravity);
    b2Vec2 velocity;
b2BodyDef bodyDef;
    b2Body* body;

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



MyApp::MyApp() { }

void MyApp::setup() {
    // MakeBallPhysics();
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(circleXPos, circleYPos);
    body = world.CreateBody(&bodyDef);
    velocity = {30.0, 50.0};
    body->SetLinearVelocity(velocity);
    // body->ApplyLinearImpulse(b2Vec2(0,10), body->GetPosition());
    b2CircleShape* circle = new b2CircleShape();
    circle->m_radius = 0.8;

    b2FixtureDef* fixtureDef = new b2FixtureDef();
    fixtureDef->shape = circle;
    fixtureDef->density = 10;
    fixtureDef->friction = 0.1;
    fixtureDef->restitution = 0.6f; // Make it bounce a little bit

    body->CreateFixture(fixtureDef);

}

void MyApp::update() {
    world.Step(150, 1, 1);
    DrawFirstPaddle();
    DrawSecondPaddle();
    DrawBall();
    // TestDraw();
    MakeBallPhysics();
    std::cout << circleXPos << ", " << circleYPos << ";" << body->GetPosition().x << ", " << body->GetPosition().x << "\n";
}

void MyApp::draw() {
    cinder::gl::clear({0, 0, 0});

    DrawFirstPaddle();
    DrawSecondPaddle();
    MakeBallPhysics();
    DrawBall();
    PrintScore();
    DrawWalls();
}

void MyApp::MakeBallPhysics() {
    body->SetLinearVelocity(velocity);
    circleXPos = body->GetPosition().x;
    circleYPos = body->GetPosition().y;
}

void MyApp::TestDraw() {
    cinder::gl::color(0,0,1);
    cinder::gl::drawSolidCircle({circleXPos, circleYPos}, 8);
}

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


void MyApp::DrawFirstPaddle() {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p1PaddlePosition - 4),
                                    tile_size_ * 0.01,
                                    tile_size_ * p1PaddlePosition + tile_size_,
                                    tile_size_ * 0.01 + tile_size_));
    paddle1x1 = tile_size_ * (p1PaddlePosition - 4);
    paddle1x2 = tile_size_ * p1PaddlePosition + tile_size_;
    paddle1y1 = tile_size_ * 0.01;
    paddle1y2 = tile_size_ * 0.01 + tile_size_;
}

void MyApp::DrawWalls() {
    cinder::gl::color(1, 1, 1);
    cinder::gl::drawSolidRect(Rectf(0,0,800, 10));
    cinder::gl::drawSolidRect(Rectf(0,0,10, 800));
    cinder::gl::drawSolidRect(Rectf(790,0,800, 800));
    cinder::gl::drawSolidRect(Rectf(0,790,800, 800));
}

void MyApp::DrawSecondPaddle() {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p2PaddlePosition - 4),
                                    tile_size_ * 31,
                                    tile_size_ * p2PaddlePosition + tile_size_,
                                    tile_size_ * 31 + tile_size_));
    paddle2x1 = tile_size_ * (p2PaddlePosition - 4);
    paddle2x2 = tile_size_ * p2PaddlePosition + tile_size_;
    paddle2y1 = tile_size_ * 31;
    paddle2y2 = tile_size_ * 31 + tile_size_;
}

void MyApp::DrawBall() {
    cinder::gl::color(0,0,1);
    if ((circleXPos >= maxDimension && circleYPos >= maxDimension)) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeXOfBallMovement *= -wallBounceConstant;
        slopeYOfBallMovement *= -wallBounceConstant;
        velocity = {-1*velocity.x, -1*velocity.y*((float) 0.5 + (float) rand() / (RAND_MAX))};
        topScore++;
    } else if (circleXPos < 0 && circleYPos < 0) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);

        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
        slopeXOfBallMovement *= -wallBounceConstant;
        slopeYOfBallMovement *= -wallBounceConstant;
        velocity = {-1*velocity.x, -1*velocity.y*((float) 0.5 + (float) rand() / (RAND_MAX))};
        bottomScore++;
    } else if (circleXPos >= maxDimension || circleXPos <= 0) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
        slopeXOfBallMovement *= -wallBounceConstant;
        velocity = {-1*velocity.x, velocity.y};
    } else if (circleYPos >= maxDimension || circleYPos <= 0) {
        if (circleYPos >= maxDimension) {
            topScore++;
            circleXPos = 400;
            circleYPos = 400;
            cinder::gl::drawSolidCircle({400, 400}, 8);
            body->SetTransform(b2Vec2(400,400),body->GetAngle());
            velocity = {velocity.x, velocity.y};
            return;
        } else {
            bottomScore++;
            circleXPos = 400;
            circleYPos = 400;
            cinder::gl::drawSolidCircle({400, 400}, 8);
            body->SetTransform(b2Vec2(400,400),body->GetAngle());
            velocity = {velocity.x * ((float) 0.5 + (float) rand() / (RAND_MAX)), velocity.y
                        * ((float) 0.5 * (float) rand() / (RAND_MAX))};
            return;
        }
    } else if (IsBallTouchingPaddle1()) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeYOfBallMovement *= -wallBounceConstant;
        velocity = {velocity.x, -1*velocity.y * ((float) 0.5 + (float) rand() / (RAND_MAX))};
    } else if (IsBallTouchingPaddle2()) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
        slopeYOfBallMovement *= -wallBounceConstant;
        velocity = {velocity.x, -1*velocity.y * ((float) 0.5 + (float) rand() / (RAND_MAX))};
    }
    else {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
    }

}

bool MyApp::IsBallTouchingPaddle1() {
    return (circleXPos <= paddle1x2 && circleXPos >= paddle1x1 && circleYPos <= paddle1y2 && circleYPos >= paddle1y1);
}

bool MyApp::IsBallTouchingPaddle2() {
    return (circleXPos <= paddle2x2 && circleXPos >= paddle2x1 && circleYPos <= paddle2y2 && circleYPos >= paddle2y1);
}

void MyApp::keyDown(KeyEvent event) {
        switch (event.getCode()) {
            case KeyEvent::KEY_LEFT: {
                p1PaddlePosition = p1PaddlePosition - 1;
                break;
            }
            case KeyEvent::KEY_RIGHT: {
                p1PaddlePosition = p1PaddlePosition + 1;
                break;
            }

            case KeyEvent::KEY_a: {
                p2PaddlePosition = p2PaddlePosition - 1;
                break;
            }

            case KeyEvent::KEY_d: {
                p2PaddlePosition = p2PaddlePosition + 1;
                break;
            }
        }
    }
}  // namespace myapp
