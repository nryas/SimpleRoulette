//
//  panel.cpp
//  SimpleRoulette
//
//  Created by Noriyasu Obushi on 2016/01/22.
//
//

#include "panel.hpp"

//--------------------------------------------------------------
PanelSingle::PanelSingle(string _imgPath, int _x, int _y, float _width, float _height) {
    
    img.load(_imgPath);
    position = ofVec2f(_x, _y);
    
    width  = _width;
    height = _height;
    velocity = 0.4f;
}

void PanelSingle::update() {
    position.y += velocity;
}

void PanelSingle::draw() {
    auto n_panel = c_panel > 0 ? 1 : 0;
    if (position.y < ofGetHeight()) {
        fbo[c_panel].draw(position.x, position.y);
        fbo[n_panel].draw(position.x, position.y - height);
    } else {
        auto buff = c_panel;
        c_panel = n_panel;
        n_panel = buff;
        position.y -= height;
        fbo[c_panel].draw(position.x, position.y - height);
        fbo[n_panel].draw(position.x, position.y);
    }
}

void PanelSingle::speedup() {
    velocity += 0.4;
}

void PanelSingle::slowdown() {
    if (velocity > 0.4) {
        velocity -= 0.4;
    } else {
        velocity = 0;
    }
}

void PanelSingle::start() {
    
}

void PanelSingle::stop() {
    
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