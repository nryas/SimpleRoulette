//
//  panel.cpp
//  SimpleRoulette
//
//  Created by Noriyasu Obushi on 2016/01/22.
//
//

#include "panel.hpp"

//--------------------------------------------------------------
PanelSingle::PanelSingle(string _imgPath, int _x, int _y, float _width, float _height, float _velocity) {
    
    img.load(_imgPath);
    position = ofVec2f(_x, _y);
    
    width  = _width;
    height = _height;
    velocity = _velocity;
    panel_id = 1;
}

int PanelSingle::index_pos[] = {
    -636,
    -228,
     180,
     588,
     996
};

void PanelSingle::update() {
    position.y += floor(velocity);
}

void PanelSingle::draw() {
    if (position.y < index_pos[4]) {
        // 入れ替え前
        fbo.draw(position.x, position.y);
        fbo.draw(position.x, position.y - height);
    } else {
        // 入れ替え後
        position.y -= height;
        fbo.draw(position.x, position.y - height);
        fbo.draw(position.x, position.y);
    }
}

void PanelSingle::start() {
    
}

void PanelSingle::brake(int index) {
    if (index > 0  && index <= 5) {
        target = index - 1;
        position.y = index_pos[target] - 500;
    } else {
        switch (index) {
            case 'M':
                target = 0;
                break;
            case 'E':
                target = 1;
                break;
            case 'I':
                target = 2;
                break;
            case 'C':
                target = 3;
                break;
            case 'A':
                target = 4;
                break;
            default:
                break;
        }
        position.y = index_pos[target] - 500;
    }
}

void PanelSingle::stop(int index) {
    if (index > 0 && index <= 5) {
        position.y = index_pos[index-1];
        velocity = 0;
    }
}