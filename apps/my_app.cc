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

std::unique_ptr<b2World> world;
const float tile_size_ = 25;
int p1PaddlePosition = 20;
int p2PaddlePosition = 20;



MyApp::MyApp() { }

void MyApp::setup() {




}

void MyApp::update() {
    DrawFirstPaddle();
    DrawSecondPaddle();
}

void MyApp::draw() {
    cinder::gl::clear({0, 0, 0});

    b2Vec2 gravity(0.01f, -9.8);
    b2World world(gravity);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(100, 100);
    b2Body* body = world.CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10, 10);
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10;
    fixtureDef.friction = 0;
    body->CreateFixture(&fixtureDef);

    DrawFirstPaddle();
    DrawSecondPaddle();

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); //position, relative to body position
    circleShape.m_radius = 5; //radius


    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
}

void MyApp::DrawFirstPaddle() {
    float r = 0;
    float g = 0;
    float b = 1;
    cinder::gl::color(0,0,1);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p1PaddlePosition - 4),
                                    tile_size_ * 1,
                                    tile_size_ * p1PaddlePosition + tile_size_,
                                    tile_size_ * 1 + tile_size_));

    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p2PaddlePosition - 4),
                                    tile_size_ * 30,
                                    tile_size_ * p2PaddlePosition + tile_size_,
                                    tile_size_ * 30 + tile_size_));
}

void MyApp::DrawSecondPaddle() {
    float r = 0;
    float g = 0;
    float b = 1;
    cinder::gl::color(0,0,1);
    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p1PaddlePosition - 4),
                                    tile_size_ * 1,
                                    tile_size_ * p1PaddlePosition + tile_size_,
                                    tile_size_ * 1 + tile_size_));

    cinder::gl::drawSolidRect(Rectf(tile_size_ * (p2PaddlePosition - 4),
                                    tile_size_ * 30,
                                    tile_size_ * p2PaddlePosition + tile_size_,
                                    tile_size_ * 30 + tile_size_));
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
