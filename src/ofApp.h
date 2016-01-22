#pragma once

#include "ofMain.h"
#include "ofxSvg.h"
#include "panel.hpp"
#include <algorithm>
#include <random>

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		void windowResized(int w, int h);
        void drawLot();
    
        struct Student {
            int grade;
            char major;
            string name;
        };

        vector<Student> students;

        PanelSingle *grade;
        PanelSingle *major;
        PanelName   *name;

        bool isStopped;
        bool isSpeedup;

};
