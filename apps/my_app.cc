// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"

#include <cinder/app/App.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/gl.h>
using cinder::Rectf;


namespace myapp {

using cinder::app::KeyEvent;

std::unique_ptr<b2World> world;
const float tile_size_ = 25;
MyApp::MyApp() { }

void MyApp::setup() {




}

void MyApp::update() { }

void MyApp::draw() {
    cinder::gl::clear({0, 0, 0});

    b2Vec2 gravity(0.01f, -9.8);
    world = std::make_unique<b2World>(gravity);
    cinder::gl::drawSolidCircle( {50,-50}, 50);

    cinder::gl::color({0.0, 0.0, 1.0});

    cinder::gl::drawSolidRect(Rectf(tile_size_ * 10,
                                    tile_size_ * 1,
                                    tile_size_ * 1 + tile_size_,
                                    tile_size_ * 1 + tile_size_));

    cinder::gl::drawSolidRect(Rectf(tile_size_ * 10,
                                    tile_size_ * 10,
                                    tile_size_ * 1 + tile_size_,
                                    tile_size_ * 10 + tile_size_));

    b2BodyDef myBodyDef;
    myBodyDef.type = b2_dynamicBody; //this will be a dynamic body
    myBodyDef.position.Set(10, 20);

    b2Body* dynamicBody1 = world->CreateBody(&myBodyDef);

    b2CircleShape circleShape;
    circleShape.m_p.Set(0, 0); //position, relative to body position
    circleShape.m_radius = 5; //radius


    b2FixtureDef myFixtureDef;
    myFixtureDef.shape = &circleShape; //this is a pointer to the shape above
    dynamicBody1->CreateFixture(&myFixtureDef); //add a fixture to the body
}


void MyApp::keyDown(KeyEvent event) { }

}  // namespace myapp
