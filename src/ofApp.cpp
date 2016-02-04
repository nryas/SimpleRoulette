#include "ofApp.h"

#define CHAR_WIDTH  240
#define CHAR_HEIGHT 408
#define IMG_HEIGHT  2040

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    isStoppedG = isStoppedM = false;
    isSpeedup = false;
    isSlowing = false;
    isImgSent = false;
    
    grade = new PanelSingle("grade_panel.png", 0, ofGetHeight()/2-IMG_HEIGHT/2, CHAR_WIDTH, IMG_HEIGHT, 5.0f);
    major = new PanelSingle("major_panel.png", CHAR_WIDTH, ofGetHeight()/2-IMG_HEIGHT/2, CHAR_WIDTH, IMG_HEIGHT, 5.0f);
    
    // FBOの初期化
    grade->fbo.allocate(CHAR_WIDTH, IMG_HEIGHT);
    major->fbo.allocate(CHAR_WIDTH, IMG_HEIGHT);
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
    if (buff.getText() == "") {
    ofSystemAlertDialog("名簿が書かれたCSVファイルが見つからなかったため，抽選を行えません。このアプリケーションと同一ディレクトリ内のdataディレクトリに[<学年>,<学科>,<名前>]のフォーマットで書かれたCSVファイルをstudent_names.csvとして保存し，やり直してください。");
        ofExit();
    }
    
    for (auto line: buff.getLines()) {
        
        Student s;
        if (ofSplitString(line, ",").size() == 3) {
            s.grade = ofToInt(ofSplitString(line, ",")[0]);
            s.major = ofToChar(ofSplitString(line, ",")[1]);
            s.name  = ofSplitString(line, ",")[2];
            
            // 全角・半角スペースを消す
            ofStringReplace(s.name, "　", " ");
            ofStringReplace(s.name, " ", "");
            
            if (s.name != "") {
                students.push_back(s);
            }
        }
    }

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(students.begin(), students.end(), std::mt19937_64(seed));
    
    ofBackground(242);
    
    font.loadFont("font.ttc", 120);
    font_s.loadFont("font.ttc", 90);
    
    mainOutputSyphonServer.setName("Screen Output");
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle("残り" + ofToString(students.size()) + "人");
    
    // 最後の減速
    if (isSlowing)
    {
        grade->velocity = major->velocity = 0;
        float dist = grade->position.y - grade->index_pos[grade->toIndex(lucky_student.grade)];
        if (abs(dist) > 1.0f) {
            grade->position.y += -dist * 0.1f;
            major->position.y += -dist * 0.1f;
        } else {
            grade->stop(lucky_student.grade);
            major->stop(lucky_student.major);
            isStoppedG = isStoppedM = true;
        }
    }
    
    // 通常の加減速
    else {
        if (isSpeedup) {
            grade->velocity = grade->velocity < 100 ? grade->velocity + 5 : 100;
            major->velocity = major->velocity < 100 ? major->velocity + 5 : 100;
        } else {
            grade->velocity = grade->velocity > 5.0f ? grade->velocity - 5 : 0;
            major->velocity = major->velocity > 5.0f ? major->velocity - 5 : 0;
        }
    
        grade->update();
        major->update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    grade->draw();
    major->draw();
    frame_top.draw(0, 0, ofGetWidth(), ofGetHeight() * 0.1);
    frame_bottom.draw(0, ofGetHeight()*0.9+1, ofGetWidth(), ofGetHeight() * 0.1+1);
    
    if (isStoppedG && isStoppedM) {
        
        auto rect   = font.getStringBoundingBox(lucky_student.name, 0, 0);
        auto rect_s = font_s.getStringBoundingBox(lucky_student.name, 0, 0);
        
        // フォントの輪郭の一番外側 (ダークグレー)
        ofPushStyle();
        ofSetColor(69);
        for (int y = -7; y < 7; y++) {
            for (int x = -7; x < 7; x++) {
                if (rect.width < ofGetWidth()-CHAR_WIDTH*2)
                {
                    font.drawString
                    (
                        lucky_student.name,
                        CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect.getWidth()/2 + x,
                        ofGetHeight()/2 + font.getLineHeight()/2 + y
                    );
                }
                
                else
                {
                    font_s.drawString
                    (
                      lucky_student.name,
                      CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect_s.getWidth()/2 + x,
                      ofGetHeight()/2 + font_s.getLineHeight()/2 + y
                    );
                }
            }
        }
        
        // フォントの輪郭の真ん中 (ライトグレー)
        ofPushStyle();
        ofSetColor(242);
        for (int y = -2; y < 3; y++) {
            for (int x = -2; x < 3; x++) {
                if (rect.width < ofGetWidth()-CHAR_WIDTH*2)
                {
                    font.drawString
                    (
                        lucky_student.name,
                        CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect.getWidth()/2 + x,
                        ofGetHeight()/2 + font.getLineHeight()/2 + y
                    );
                }
                
                else
                {
                    font_s.drawString
                    (
                        lucky_student.name,
                        CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect_s.getWidth()/2 + x,
                        ofGetHeight()/2 + font_s.getLineHeight()/2 + y
                    );
                }
            }
        }
        
        // フォントの輪郭の一番内側 (ダークグレー)
        ofPopStyle();
        if (rect.width < ofGetWidth()-CHAR_WIDTH*2)
        {
            font.drawString
            (
                lucky_student.name,
                CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect.getWidth()/2,
                ofGetHeight()/2 + font.getLineHeight()/2
            );
        }
        
        else
        {
            font_s.drawString
            (
                lucky_student.name,
                CHAR_WIDTH*2 + (ofGetWidth() - CHAR_WIDTH*2)/2 - rect_s.getWidth()/2,
                ofGetHeight()/2 + font_s.getLineHeight()/2
            );
        }
        ofPopStyle();
    }
    
    mainOutputSyphonServer.publishScreen();
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
        ofGetHeight()/2 - CHAR_HEIGHT*5/2,
        ofGetHeight()/2 - CHAR_HEIGHT*5/2 + CHAR_HEIGHT,
        ofGetHeight()/2 - CHAR_HEIGHT*5/2 + CHAR_HEIGHT*2,
        ofGetHeight()/2 - CHAR_HEIGHT*5/2 + CHAR_HEIGHT*3,
        ofGetHeight()/2 - CHAR_HEIGHT*5/2 + CHAR_HEIGHT*4
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
        isImgSent = false;
        // 止まっている -> 動かす
        isSlowing = false;
        isStoppedG = isStoppedM = false;
        
        if (students.size() > 0) {
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(students.begin(), students.end(), std::mt19937_64(seed));
            lucky_student = students.back();
            students.pop_back();
        }
    }
    isSpeedup = !isSpeedup;
}
