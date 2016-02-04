#pragma once

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"
#include "ofxSyphon.h"
#include "panel.hpp"
#include <algorithm>
#include <random>

class ofApp : public ofBaseApp{

	public:
    
        struct Student {
            int grade;
            char major;
            string name;
        };
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void windowResized(int w, int h);
        void drawLot();

        vector<Student> students;
        Student lucky_student;

        PanelSingle *grade;
        PanelSingle *major;

        bool isStoppedG;
        bool isStoppedM;
        bool isSpeedup;
        bool isSlowing;
        bool isImgSent;
    
        ofxTrueTypeFontUC font;
        ofxTrueTypeFontUC font_s;
        ofFbo frame_top;
        ofFbo frame_bottom;
    
    	ofxSyphonServer mainOutputSyphonServer;

};
