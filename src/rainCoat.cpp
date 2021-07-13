#include "rainCoat.h"

//--------------------------------------------------------------
void rainCoat::setup(ofxFFApp &app) {

    box2d.init();
    box2d.setFPS(24);
    
    box2d.setGravity(0, 0);
    box2d.registerGrabbing();
    box2d.createBounds(app.frame);

    particles.setup(box2d.getWorld(), 100000);
    particles.setParticleLifetime(180);
    particles.setPhysics(.5, 2, 10000);
    particles.setColor(ofColor(255));
    particles.setBodyType(b2_dynamicBody);
    
    /*for (int i = 0; i < 5000; i++) {
        ofVec2f position = ofVec2f(ofRandom(100),
                                   ofRandom(ofGetHeight()));
        ofVec2f velocity = ofVec2f(0, 0);
        particles.createParticle(position, velocity);
    }*/
    
    image.load("/Users/tskokmt/Downloads/madeon2.png");
    
    sound01.load("/Users/tskokmt/Downloads/FRAME FREE/SOUND/X1.mp3");
    sound01.setLoop(false);
    sound01.setMultiPlay(true);
    sound01.play();
    lastPlayedTime01 = ofGetElapsedTimef();
    
    sound02.load("/Users/tskokmt/Downloads/FRAME FREE/SOUND/A0.mp3");
    sound02.setLoop(false);
    sound02.setMultiPlay(true);
    
    sound03.load("/Users/tskokmt/Downloads/FRAME FREE/SOUND/F1.mp3");
    sound03.setLoop(false);
    sound03.setMultiPlay(true);
}


//--------------------------------------------------------------
void rainCoat::draw(ofxFFApp &app) {
    
    int i = 0;
    while (i < circles.size()) {
        float radius = circles[i]->getRadius() - .05;
        if (radius > 0) {
            circles[i]->setRadius(radius);
            i++;
        } else {
            circles.erase(circles.begin() + i);
        }
    }
    
    //box2d.setGravity(0, ((int)(app.time / 30) % 3 - 1) * 10);
    
    if (particles.getParticleCount() > 10000 && index == -1) index = ofRandom(particles.getParticleCount() - 10000);
    
    force = ofPoint(0, 0);
    if (particles.getParticleCount() > 10000) {
        for (int i = 0; i < app.people.size(); i++) {
            force += ofPoint(app.getPeopleSpeedX()[i] / 3., app.getPeopleSpeedZ()[i] / 3. / 7.);
        }
    }
    if (index >= 0) {
        for (int i = index; i < index + 10000; i++) {
            particles.applyForce(i, force);
        }
    }
    
    edges.clear();
    for (int i = 0; i < app.silhouettes.size(); i++) {
        edges.push_back(ofPtr<ofxBox2dEdge>(new ofxBox2dEdge));
        edges.back()->addVertexes(app.silhouettes[i].polyline);
        edges.back()->setPhysics(0, 1, 1000000);
        edges.back()->create(box2d.getWorld());
    }
    
    if (ofGetMousePressed()) {
        ofPoint p = app.getDisTranslatedPosition(ofPoint(ofGetMouseX(), ofGetMouseY()));
        
        /*float r = ofRandom(4, 20);
        circles.push_back(ofPtr<ofxBox2dCircle>(new ofxBox2dCircle));
        circles.back().get()->setPhysics(0.9, 0.9, 0.1);
        circles.back().get()->setup(box2d.getWorld(), p.x, p.y, r);*/
        
        float radius = 40;
        float x = cos(ofRandom(PI*2.0)) * radius + p.x;
        float y = sin(ofRandom(PI*2.0)) * radius + p.y;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
        particles.createParticle(position, velocity);
    }
    /*for (int i = 0; i < 10; i++) {
        ofPoint p = ofPoint(ofRandom(app.frameC.getLeft(), app.frameC.getRight()), app.frame.height - 40);
        float radius = 40;
        float x = cos(ofRandom(PI*2.0)) * radius + p.x;
        float y = sin(ofRandom(PI*2.0)) * radius + p.y;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
        particles.createParticle(position, velocity);
    }*/
    ofColor color;
    float seed = fmod(app.time / 180. * 256, 256);
    color.setHsb(fmod(seed + ofRandom(8), 256), 255, 255);
    //color = image.getColor(fmod(seed + ofRandom(image.getWidth() / 8.), image.getWidth()), 0);
    for (int i = 0; i < app.silhouettes.size(); i++) {
        //int j = ofRandom(app.silhouettes[i].polyline.getVertices().size());
        for (int j = 0; j < app.silhouettes[i].polyline.getVertices().size(); j += 4) {
            ofPoint p = app.silhouettes[i].polyline.getVertices()[j];
            float radius = 40;
            float x = cos(ofRandom(PI*2.0)) * radius + p.x;
            float y = sin(ofRandom(PI*2.0)) * radius + p.y;
            ofVec2f position = ofVec2f(x, y);
            ofVec2f velocity = p - app.silhouettes[i].polyline.getCentroid2D();
            particles.setColor(color);
            particles.createParticle(position, velocity);
        }
    }
    if (particles.getParticleCount() > 10000) {
        ofxTskokmtMath math;
        ofPoint p = math.randomPointInRectangle(app.frame);
        float radius = 40;
        float x = cos(ofRandom(PI*2.0)) * radius + p.x;
        float y = sin(ofRandom(PI*2.0)) * radius + p.y;
        ofVec2f position = ofVec2f(x, y);
        ofVec2f velocity = ofVec2f(ofRandom(-200, 200), ofRandom(-200, 200));
        particles.setColor(color);
        particles.createParticle(position, velocity);
    }
    
    box2d.update();
    
    ofSetColor(0, 64);
    ofDrawRectangle(app.frame);
    
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofSetColor(255);
    //particles.particleSize = 30;
    particles.draw();
    ofPopMatrix();
    ofDisableBlendMode();
    
    if (particles.getParticleCount() < 3000 && ofGetElapsedTimef() - lastPlayedTime01 > 40) {
        sound01.play();
        lastPlayedTime01 = ofGetElapsedTimef();
    }
    if (particles.getParticleCount() < 3000 && ofGetElapsedTimef() - lastPlayedTime02 > 40) {
        sound03.play();
        lastPlayedTime02 = ofGetElapsedTimef();
    }
    if (particles.getParticleCount() > 60000 && ofGetElapsedTimef() - lastPlayedTime03 > 40) {
        sound03.play();
        lastPlayedTime03 = ofGetElapsedTimef();
    }
}
