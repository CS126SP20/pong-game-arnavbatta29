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
double slopeYOfBallMovement = 1;
double slopeXOfBallMovement = 1;
int maxDimension = 800;



MyApp::MyApp() { }

void MyApp::setup() {
    // MakeBallPhysics();
}

void MyApp::update() {
    DrawFirstPaddle();
    DrawSecondPaddle();
    DrawBall();
    MakeBallPhysics();
}

void MyApp::draw() {
    cinder::gl::clear({0, 0, 0});

    DrawFirstPaddle();
    DrawSecondPaddle();
    DrawBall();

}

void MyApp::MakeBallPhysics() {
    b2Vec2 gravity(0.01f, -9.8);
    b2World world(gravity);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(circleXPos, circleYPos);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(16, 16);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10;
    fixtureDef.friction = 0.1;
    body->CreateFixture(&fixtureDef);
}


void MyApp::DrawFirstPaddle() {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p1PaddlePosition - 4),
                                    tile_size_ * 1,
                                    tile_size_ * p1PaddlePosition + tile_size_,
                                    tile_size_ * 1 + tile_size_));

}

void MyApp::DrawSecondPaddle() {
    cinder::gl::color(1,0,0);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p2PaddlePosition - 4),
                                    tile_size_ * 30,
                                    tile_size_ * p2PaddlePosition + tile_size_,
                                    tile_size_ * 30 + tile_size_));
}

void MyApp::DrawBall() {
    cinder::gl::color(0,0,1);
    if ((circleXPos >= maxDimension && circleYPos >= maxDimension)) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
    } else if (circleXPos < 0 && circleYPos < 0) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
    } else if (circleXPos >= maxDimension || circleXPos <= 0) {
        cinder::gl::drawSolidCircle({circleXPos - slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos - slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
    } else if (circleYPos >= maxDimension || circleYPos <= 0) {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos - slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos - slopeYOfBallMovement;
    } else {
        cinder::gl::drawSolidCircle({circleXPos + slopeXOfBallMovement,
                                     circleYPos + slopeYOfBallMovement}, 8);
        circleXPos = circleXPos + slopeXOfBallMovement;
        circleYPos = circleYPos + slopeYOfBallMovement;
    }

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
