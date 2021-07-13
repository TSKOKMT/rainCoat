#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    //setup app
    app.setup("rainCoat", 50014, true, true, true);
    
    rainCoat.setup(app);
}

//--------------------------------------------------------------
void ofApp::update(){

    //update app
    app.update();
    
    if (!app.bActive) return;
    
    //draw
    app.begin(false);
    
    rainCoat.draw(app);
    
    app.end();
}

//--------------------------------------------------------------
void ofApp::draw(){

    //draw app
    app.draw();
    
    ofSetColor(255);
    ofDrawBitmapString(ofToString(rainCoat.particles.getParticleCount()), ofGetWidth() - 100, ofGetHeight() - 20);
}

//--------------------------------------------------------------
void ofApp::exit(){
    
    //exit app
    app.exit();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
