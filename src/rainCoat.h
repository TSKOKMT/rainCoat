#pragma once

#include "ofMain.h"

#include "ofxFFApp.h"

#include "ofxLiquidFun.h"

class rainCoat {

public:
    void setup(ofxFFApp &app);
    void draw(ofxFFApp &app);
    
    ofxBox2d box2d;
    vector<ofPtr<ofxBox2dCircle>> circles;
    ofxBox2dParticleSystem particles;
    vector<ofPtr<ofxBox2dEdge>> edges;
    
    int index = -1;
    ofPoint force;
    
    ofImage image;
    
    ofSoundPlayer sound01;
    float lastPlayedTime01;
    ofSoundPlayer sound02;
    float lastPlayedTime02;
    ofSoundPlayer sound03;
    float lastPlayedTime03;
    ofSoundPlayer sound04;
};
