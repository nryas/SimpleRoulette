//
//  panel.cpp
//  SimpleRoulette
//
//  Created by Noriyasu Obushi on 2016/01/22.
//
//

#include "panel.hpp"

//--------------------------------------------------------------
PanelSingle::PanelSingle(string imgPath, int x, int y, float width, float height) {
    this->img.load(imgPath);
    this->position = ofVec2f(x, y);
    this->cropPosition = ofVec4f(position.x, position.y, position.x+width, position.y+height);
    this->width = width;
    this->height = height;
    velocity = 0.1f;
}

void PanelSingle::update() {
    
}

void PanelSingle::draw() {
    img.draw(position, width, height);
}

void PanelSingle::speedup() {
    velocity += 0.1;
}

void PanelSingle::slowdown() {
    if (velocity > 0.1) {
        velocity -= 0.1;
    } else {
        velocity = 0;
    }
}

float PanelSingle::getVelocity() {
    return velocity;
}

ofVec2f PanelSingle::getPosition() {
    return position;
}

float PanelSingle::getWidth() {
    return width;
}

float PanelSingle::getHeight() {
    return height;
}

void PanelSingle::setCropPosition(ofVec4f pos) {
    cropPosition = pos;
}

ofVec4f PanelSingle::getCropPosition() {
    return cropPosition;
}

//--------------------------------------------------------------
PanelName::PanelName(int x, int y, float width, float height) {
    this->position = ofVec2f(x, y);
}

void PanelName::update() {
    
}

void PanelName::draw() {
    
}

void PanelName::open() {
    
}

string PanelName::getName() {
    return name;
}

ofVec2f PanelName::getPosition() {
    return position;
}