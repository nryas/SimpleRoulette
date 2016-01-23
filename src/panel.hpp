//
//  panel.hpp
//  SimpleRoulette
//
//  Created by Noriyasu Obushi on 2016/01/22.
//
//
#include "ofMain.h"

class PanelSingle {
    public:
        PanelSingle(string imgPath, int x, int y, float width, float height, float velocity);
        void update();
        void draw();
    
        void start();
        void brake(int index);
        void stop(int index);
    
        ofImage img;
        ofFbo fbo;
        ofVec2f position;
    
        float width;
        float height;
        float velocity;
        unsigned int panel_id;
        static int index_pos[];
        int target;
};