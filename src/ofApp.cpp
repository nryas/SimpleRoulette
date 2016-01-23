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
    frame_top.allocate(ofGetWidth(), ofGetHeight() * 0.1f);
    frame_bottom.allocate(ofGetWidth(), ofGetHeight() * 0.1f);
    
    grade->fbo.begin();
    grade->img.draw(ofVec2f(0, 0), grade->width, grade->height);
    grade->fbo.end();
    
    major->fbo.begin();
    major->img.draw(ofVec2f(0, 0), major->width, major->height);
    major->fbo.end();
    
    frame_top.begin();
    for (int y = 0; y < frame_top.getHeight(); y++) {
        ofPushStyle();
        ofSetColor(10, 10, 10, ofMap(y, 0, frame_top.getHeight(), 255, 0));
        ofDrawLine(0, y, ofGetWidth(), y);
        ofPopStyle();
    }
    frame_top.end();
    
    frame_bottom.begin();
    for (int y = 0; y < frame_bottom.getHeight(); y++) {
        ofPushStyle();
        ofSetColor(10, 10, 10, ofMap(y, 0, frame_bottom.getHeight(), 0, 255));
        ofDrawLine(0, y, ofGetWidth(), y);
        ofPopStyle();
    }
    frame_bottom.end();
    
    // CSV ファイルはUTF-8 BOMなしでエンコードされている必要あり
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

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(students.begin(), students.end(), std::mt19937_64(seed));
    
    ofBackground(242);
    
    font.loadFont("hiragino.ttc", 100);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    // 最後の減速
    if (isSlowing)
    {
        grade->velocity = major->velocity = 0;
        float dist = floor(grade->position.y - grade->index_pos[grade->target]);
        if (abs(dist) > 0.8f) {
            cout << abs(dist) << endl;
            grade->position.y += abs(dist) * 0.1f;
            major->position.y += abs(dist) * 0.1f;
        } else {
            grade->stop(lucky_student.grade);
            major->stop(lucky_student.major);
            isStoppedG = isStoppedM = true;
        }
    }
    
    // 通常の加減速
    else {
            if (isSpeedup) {
                if (grade->velocity < 100) {
                    grade->velocity += 5.0;
                } else {
                    grade->velocity = 100;
                }
                
                if (major->velocity < 100) {
                    major->velocity += 5.0;
                } else {
                    major->velocity = 100;
                }
            } else {
                if (grade->velocity > 5.0) {
                    grade->velocity -= 5.0;
                } else {
                    grade->velocity = 0;
                }
                
                if (major->velocity > 5.0) {
                    major->velocity -= 5.0;
                } else {
                    major->velocity = 0;
                }
            }
        
            grade->update();
            major->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    grade->draw();
    major->draw();
    if (isStoppedG && isStoppedM) {
        auto rect = font.getStringBoundingBox(lucky_student.name, 0, 0);
        ofPushStyle();
        ofSetColor(69);
        for (int y = -7; y < 7; y++) {
            for (int x = -7; x < 7; x++) {
                font.drawString(lucky_student.name, 440 + (ofGetWidth() - 440)/2 - rect.getWidth()/2 + x, ofGetHeight()/2 + font.getLineHeight()/2 + y);
            }
        }
        ofPushStyle();
        ofSetColor(242);
        for (int y = -2; y < 4; y++) {
            for (int x = -2; x < 4; x++) {
                font.drawString(lucky_student.name, 440 + (ofGetWidth() - 440)/2 - rect.getWidth()/2 + x, ofGetHeight()/2 + font.getLineHeight()/2 + y);
            }
        }
        ofPopStyle();
        font.drawString(lucky_student.name, 440 + (ofGetWidth() - 440)/2 - rect.getWidth()/2, ofGetHeight()/2 + font.getLineHeight()/2);
        ofPopStyle();

    }
    
    frame_top.draw(0, 0, ofGetWidth(), ofGetHeight() * 0.1);
    frame_bottom.draw(0, ofGetHeight()*0.9+1, ofGetWidth(), ofGetHeight() * 0.1+1);
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
    int buff[5] = {
    ofGetHeight()/2 - 408*5/2,
    ofGetHeight()/2 - 408*5/2 + 408,
    ofGetHeight()/2 - 408*5/2 + 408*2,
    ofGetHeight()/2 - 408*5/2 + 408*3,
    ofGetHeight()/2 - 408*5/2 + 408*4
    };
    std::memcpy(grade->index_pos, buff, sizeof(int)*5);
    std::memcpy(major->index_pos, buff, sizeof(int)*5);
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
            do{
                unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
                std::shuffle(students.begin(), students.end(), std::mt19937_64(seed));
                lucky_student = students.back();
                students.pop_back();
            } while (lucky_student.name == "");
        }
        
    }
    
    isSpeedup = !isSpeedup;
}
