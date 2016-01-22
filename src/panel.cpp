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
    if (cropPosition.z > img.getHeight()) {
        
        // クロップ終了位置が画像の下端を下回った場合，はみ出た部分が上に来るよう画像を加工
        auto pixels = img.getPixels();
        unsigned char new_pixels[sizeof(pixels) / sizeof(unsigned char)];
        int exceedHeight = (int)floor(cropPosition.w) - img.getHeight();
        
        for (int h = exceedHeight; h < img.getHeight(); h++) {
            for (int w = 0; w < img.getWidth(); w++) {
                int index = h*img.getWidth()*3 + w*3;
                new_pixels[index-exceedHeight*w] = pixels[index];
            }
        }
        
        for (int h = 0; h < exceedHeight; h++) {
            for (int w = 0; w < img.getWidth(); w++) {
                int index = h*img.getWidth()*3 + w*3;
                new_pixels[index+exceedHeight*w] = pixels[index];
            }
        }
        
        // クロップ開始位置が画像の下端を下回った場合，デフォルトの位置に移動
        if (cropPosition.w > img.getHeight()) {
            cropPosition = ofVec4f(0, 0, width, height);
        }
        
        ofImage new_img;
        new_img.setFromPixels(new_pixels, img.getWidth(), img.getHeight(), OF_IMAGE_COLOR);
        new_img.draw(position, width, height);
    }
    
    // 問題なくクロップできる場合
    else {
        img.crop(cropPosition.x, cropPosition.y, cropPosition.z, cropPosition.w);
        img.draw(position, width, height);
    }
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