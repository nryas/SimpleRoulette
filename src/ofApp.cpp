#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    isStopped = false;
    
    grade = new PanelSingle("grade_panel.png", 0, 0, 240, 408);
    major = new PanelSingle("major_panel.png", 240, 0, 240, 408);
    name  = new PanelName(480, 0, 720, 408);
    
    grade->img.resize(240, 2040);
    major->img.resize(240, 2040);
    
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
            major->speedup();
        } else {
            grade->slowdown();
            major->slowdown();
        }
    }
    
    grade->setCropPosition(grade->getCropPosition() + ofVec4f(0, grade->getVelocity(), 0, grade->getVelocity()));
    major->setCropPosition(major->getCropPosition() + ofVec4f(0, major->getVelocity(), 0, major->getVelocity()));
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
    std::shuffle(students.begin(), students.end(), std::mt19937());
    auto s = students.back();
    students.pop_back();
    
//    cout << "------------------------" << endl;
//    cout << s.name << endl;
//    cout << students.size() << endl;
//    cout << "------------------------" << endl;
}
