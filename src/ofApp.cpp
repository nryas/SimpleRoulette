#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    isStopped = false;
    
    grade = new PanelSingle("grade_panel.png", 0, ofGetHeight()/2-1020, 240, 2040);
    grade->c_panel = 1;
    
    
//    major = new PanelSingle("major_panel.png", 240, 0, 240, 408);
//    name  = new PanelName(480, 0, 720, 408);
    
    for (int i = 0; i < 2; i++) {
        grade->fbo[i].allocate(240, 2040);
//        major->fbo[i].allocate(240, 2040);
        
        grade->fbo[i].begin();
        grade->img.draw(ofVec2f(0, 0), grade->width, grade->height);
        grade->fbo[i].end();
    }
    
    // csv file must be encoded by utf8 without bom
    ofBuffer buff = ofBufferFromFile("student_names.csv");
    for (auto line: buff.getLines()) {
        cout << line << endl;
        
        Student s;
        s.grade = ofToInt(ofSplitString(line, ",")[0]);
        s.major = ofToChar(ofSplitString(line, ",")[1]);
        s.name  = ofSplitString(line, ",")[2];
        
        students.push_back(s);
    }
    
    std::shuffle(students.begin(), students.end(), std::mt19937());
    
    ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
    // calculate size of panels
    if (isStopped) {
        
    } else {
        if (isSpeedup) {
            grade->speedup();
        } else {
            grade->slowdown();
        }
    }
    
    grade->update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    grade->draw();
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
    if (isSpeedup) {
        // 止める
    } else {
        // 動かす
        std::shuffle(students.begin(), students.end(), std::mt19937());
        auto s = students.back();
        students.pop_back();
    }
    
    isSpeedup = !isSpeedup;
    
//    cout << "------------------------" << endl;
//    cout << s.name << endl;
//    cout << students.size() << endl;
//    cout << "------------------------" << endl;
}
