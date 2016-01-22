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
        void update();      // 速度分だけ座標移動, はみ出し時の処理
        void draw();        // fboの描画

        void speedup();     // update()時
        void slowdown();    // update()時
    
        void start();       // isSpeedupの切り替え
        void stop();        // isSpeedupの切り替え・指定した場所で止める
    
        ofImage img;        // 画像
        ofFbo fbo[2];       // fbo[0]:上, fbo[1]:下
        ofVec2f position;   // fboの左上の座標
    
        float width;        // fboの幅 240
        float height;       // fboの高さ 2040
        float velocity;     // update()時の移動量 0.1f
        int c_panel;       // パネルが上(0)か下(1)か
};

class PanelName {
    public:
        PanelName(int x, int y, float width, float height);
        void update();
        void draw();
    
        void open();

        ofVec2f position;
        string name;
};