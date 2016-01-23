#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    isStopped = true;
    isSpeedup = false;
    isSlowing = false;
    
    grade = new PanelSingle("grade_panel.png", 0, ofGetHeight()/2-1020, 240, 2040, 5.0f);
    major = new PanelSingle("major_panel.png", 240, ofGetHeight()/2-1020, 240, 2040, 5.0f);
//    name  = new PanelName(480, 0, 720, 408);
    
    grade->fbo.allocate(240, 2040);
    major->fbo.allocate(240, 2040);
    
    grade->fbo.begin();
    grade->img.draw(ofVec2f(0, 0), grade->width, grade->height);
    grade->fbo.end();
    
    major->fbo.begin();
    major->img.draw(ofVec2f(0, 0), major->width, major->height);
    major->fbo.end();
    
    
    // シャッフル
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
    
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
    
    isStopped = major->velocity == 0 ? true : false;
    
    if (!isSlowing) {
        // calculate size of panels
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
    } else {
        float dist1 = grade->position.y - grade->index_pos[grade->target];
//        cout << "----------------------" << endl;
//        cout << grade->target << endl;
//        cout << grade->position.y << endl;
//        cout << grade->index_pos[grade->target] << endl;
//        cout << dist << endl;
        if (abs(dist1) > 0) {
            grade->position.y += abs(dist1) * 0.1f;
            grade->velocity = 0;
        } else {
            grade->stop(lucky_student.grade);
            isStopped = true;
        }
        
        float dist2 = major->position.y - major->index_pos[major->target];
        //        cout << "----------------------" << endl;
        //        cout << grade->target << endl;
        //        cout << grade->position.y << endl;
        //        cout << grade->index_pos[grade->target] << endl;
        //        cout << dist << endl;
        if (abs(dist2) > 0) {
            major->position.y += abs(dist2) * 0.1f;
            major->velocity = 0;
        } else {
            major->stop(lucky_student.major);
            isStopped = true;
        }
    }
    
    auto y = grade->position.y;
    auto s = "";
    if (y >= -840 && y < -432)
        s = "1";
    else if (y >= -432 && y < -24)
        s = "2";
    else if (y >= -24 && y < 384)
        s = "3";
    else if (y >= 384 && y < 792)
        s = "4";
    else if (y >= 792)
        s = "5";
}

//--------------------------------------------------------------
void ofApp::draw(){
    grade->draw();
    major->draw();
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
        // 動いている -> 止める　場合
        if (!isSlowing) {
            isSlowing = true;
            grade->brake(floor(ofRandom(1, 6)));
            major->brake(floor(ofRandom(1, 6)));
        }
    }
    else
    {
        // 止まっている -> 動かす　場合
        isSlowing = false;
        isStopped = false;
        if (students.size() > 0) {
            std::shuffle(students.begin(), students.end(), std::mt19937());
            lucky_student = students.back();
            students.pop_back();
        }
        
    }
    
    isSpeedup = !isSpeedup;
    
//    cout << "------------------------" << endl;
//    cout << s.name << endl;
//    cout << students.size() << endl;
//    cout << "------------------------" << endl;
}
