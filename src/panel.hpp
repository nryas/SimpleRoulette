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
        PanelSingle(string imgPath, int x, int y, float width, float height);
        void update();
        void draw();

        void speedup();
        void slowdown();
        float getVelocity();
        ofVec2f getPosition();
        float getWidth();
        float getHeight();
        void setCropPosition(ofVec4f pos);
        ofVec4f getCropPosition();
        void start();
        void stop();
    
        ofImage img;
    
    private:
        ofVec2f position;
        ofVec4f cropPosition;
        float width;
        float height;
        float velocity;
};

class PanelName {
    public:
        PanelName(int x, int y, float width, float height);
        void update();
        void draw();
    
        void open();
        string getName();
        ofVec2f getPosition();
    
        ofImage img;
    
    private:
        ofVec2f position;
        string name;
};