#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    isStoppedG = isStoppedM = false;
    isSpeedup = false;
    isSlowing = false;
    
    grade = new PanelSingle("grade_panel.png", 0, ofGetHeight()/2-1020, 240, 2040, 5.0f);
    major = new PanelSingle("major_panel.png", 240, ofGetHeight()/2-1020, 240, 2040, 5.0f);
    
    grade->fbo.allocate(240, 2040);
    major->fbo.allocate(240, 2040);
    
    grade->fbo.begin();
    grade->img.draw(ofVec2f(0, 0), grade->width, grade->height);
    grade->fbo.end();
    
    major->fbo.begin();
    major->img.draw(ofVec2f(0, 0), major->width, major->height);
    major->fbo.end();
    
    // csv file must be encoded by utf8 without bom
    ofBuffer buff = ofBufferFromFile("student_names.csv");
    for (auto line: buff.getLines()) {
        
        Student s;
        if (ofSplitString(line, ",").size() == 3) {
            s.grade = ofToInt(ofSplitString(line, ",")[0]);
            s.major = ofToChar(ofSplitString(line, ",")[1]);
            s.name  = ofSplitString(line, ",")[2];
        }
        
        students.push_back(s);
    }
    std::shuffle(students.begin(), students.end(), std::mt19937());
    
    ofBackground(242);
    
    font.loadFont("hiragino.ttc", 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // 最後の減速
    if (isSlowing)
    {
        float dist1 = grade->position.y - grade->index_pos[grade->target];
        if (abs(dist1) > 2.0f) {
            grade->position.y += abs(dist1) * 0.1f;
            grade->velocity = 0;
        } else {
            grade->stop(lucky_student.grade);
            isStoppedG = true;
        }
        
        float dist2 = major->position.y - major->index_pos[major->target];
        if (abs(dist2) > 2.0f) {
            major->position.y += abs(dist2) * 0.1f;
            major->velocity = 0;
        } else {
            major->stop(lucky_student.major);
            isStoppedM = true;
        }
    }
    
    // 通常の加減速
    else {
            if (isSpeedup) {
                if (grade->velocity < 100) {
                    grade->velocity += 5.0;
                    major->velocity += 5.0;
                } else {
                    grade->velocity = 100;
                    major->velocity = 100;
                }
            } else {
                if (grade->velocity > 5.0) {
                    grade->velocity -= 5.0;
                    major->velocity -= 5.0;
                } else {
                    grade->velocity = 0;
                    major->velocity = 0;
                }
            }
            
            grade->update();
            major->update();
    }
    
//    auto y = grade->position.y;
//    auto s = "";
//    if (y >= -840 && y < -432)
//        s = "1";
//    else if (y >= -432 && y < -24)
//        s = "2";
//    else if (y >= -24 && y < 384)
//        s = "3";
//    else if (y >= 384 && y < 792)
//        s = "4";
//    else if (y >= 792)
//        s = "5";
}

//--------------------------------------------------------------
void ofApp::draw(){
    grade->draw();
    major->draw();
    if (isStoppedG && isStoppedM) {
        ofPushStyle();
        ofSetColor(20);
        font.drawString(lucky_student.name, 500, ofGetHeight()/2 + font.getLineHeight()/2);
        ofPopStyle();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' ') {
        drawLot();
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    drawLot();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::drawLot() {
    if (isSpeedup)
    {
        // 動いている -> 止める
        if (!isSlowing) {
            isSlowing = true;
            grade->brake(lucky_student.grade);
            major->brake(lucky_student.major);
        }
    }
    else
    {
        // 止まっている -> 動かす
        isSlowing = false;
        isStoppedG = isStoppedM = false;
        if (students.size() > 0) {
            std::shuffle(students.begin(), students.end(), std::mt19937());
            lucky_student = students.back();
            students.pop_back();
        }
        
    }
    
    isSpeedup = !isSpeedup;
}
