#include "ofApp.h"

void ofApp::setup(){
    int ticksPerBuffer = 8; // 8 * 64 = buffer len of 512
    ofSoundStreamSetup(2, 2, this, 44100, ofxPd::blockSize()*ticksPerBuffer, 3);
    
    // give absolute paths to soundfiles
    string path = "sounds";
    ofDirectory dir(path);
    string absPath = dir.getAbsolutePath();
    
    soda.init();
    soda.createSampler("s0",absPath + "/s0.wav",10);
    soda.createSampler("s1",absPath + "/s1.wav",10);
    soda.createSampler("s2",absPath + "/s2.wav",10);
    
    // populate dataset with random data
    vector<DataObject*> v1;
    for(int i=0; i<50; i++) { v1.push_back(new DataObject(ofVec2f(ofRandom(ofGetWidth()), ofRandom(100)))); }
    dataset.push_back(v1);
    
    vector<DataObject*> v2;
    for(int i=0; i<80; i++) { v2.push_back(new DataObject(ofVec2f(ofRandom(ofGetWidth()), ofRandom(100)))); }
    dataset.push_back(v2);
    
    vector<DataObject*> v3;
    for(int i=0; i<40; i++) { v3.push_back(new DataObject(ofVec2f(ofRandom(ofGetWidth()), ofRandom(100)))); }
    dataset.push_back(v3);
}

void ofApp::update(){}
void ofApp::draw(){
    ofBackground(34);
    
    ofPushMatrix();
    ofTranslate(0,ofGetHeight()/2-200);
    ofColor c1 = ofColor(255,121,115);
    for(auto data : dataset[0]) {
        data->draw(c1);
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0,ofGetHeight()/2-100);
    ofColor c2 = ofColor(200);
    for(auto data : dataset[1]) {
        data->draw(c2);
    }
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0,ofGetHeight()/2);
    ofColor c3 = ofColor(71,206,255);
    for(auto data : dataset[2]) {
        data->draw(c3);
    }
    ofPopMatrix();
    
    ofSetColor(c1);
    ofDrawLine(0,ofGetHeight()/2-100,ofGetWidth(),ofGetHeight()/2-100);
    ofSetColor(c3);
    ofDrawLine(0,ofGetHeight()/2,ofGetWidth(),ofGetHeight()/2);
    
    ofSetColor(240);
    if(mouseY<ofGetHeight()/2-100) {
        ofDrawLine(mouseX,ofGetHeight()/2-200,mouseX,ofGetHeight()/2-100);
    }else if(mouseY>ofGetHeight()/2-100 && mouseY<ofGetHeight()/2) {
        ofDrawLine(mouseX,ofGetHeight()/2-100,mouseX,ofGetHeight()/2);
    } else if(mouseY>ofGetHeight()/2 && mouseY<ofGetHeight()/2+100){
        ofDrawLine(mouseX,ofGetHeight()/2,mouseX,ofGetHeight()/2+100);
    } else {
        ofDrawLine(mouseX,ofGetHeight()/2-200,mouseX,ofGetHeight()/2+100);
    }
}

void ofApp::keyPressed(int key){}
void ofApp::keyReleased(int key){}
void ofApp::mouseMoved(int x, int y ){
    if(mouseY<ofGetHeight()/2-100) {
        playFirstSet();
    }else if(mouseY>ofGetHeight()/2-100 && mouseY<ofGetHeight()/2) {
        playSecondSet();
    } else if(mouseY>ofGetHeight()/2 && mouseY<ofGetHeight()/2+100){
        playThirdSet();
    } else {
        playFirstSet();
        playSecondSet();
        playThirdSet();
    }
}

void ofApp::playFirstSet() {
    for(auto data : dataset[0]) {
        if(data->mPos.distance(ofVec2f(mouseX,data->mPos.y)) < data->mSize) {
            if(data->canPlay) {
                float panValue = data->mPos.x/float(ofGetWidth());
                float shiftValue = ofMap(data->mPos.y,0,100,20,2);
                soda.set("s0")->volume(0.4)->pan(panValue)->shift(shiftValue)->play();
                data->fade = 255;
            }
            data->canPlay = false;
        }else {
            data->canPlay = true;
        }
    }
}

void ofApp::playSecondSet() {
    for(auto data : dataset[1]) {
        if(data->mPos.distance(ofVec2f(mouseX,data->mPos.y)) < data->mSize) {
            if(data->canPlay) {
                float panValue = data->mPos.x/float(ofGetWidth());
                float shiftValue = ofMap(data->mPos.y,0,100,3,0.2);
                soda.set("s1")->volume(0.4)->pan(panValue)->shift(shiftValue)->play();
                data->fade = 255;
            }
            data->canPlay = false;
        }else {
            data->canPlay = true;
        }
    }
}

void ofApp::playThirdSet() {
    for(auto data : dataset[2]) {
        if(data->mPos.distance(ofVec2f(mouseX,data->mPos.y)) < data->mSize) {
            if(data->canPlay) {
                float panValue = data->mPos.x/float(ofGetWidth());
                float shiftValue = ofMap(data->mPos.y,0,100,2,0.1);
                soda.set("s2")->volume(0.2)->pan(panValue)->shift(shiftValue)->play();
                data->fade = 255;
            }
            data->canPlay = false;
        }else {
            data->canPlay = true;
        }
    }
}

void ofApp::mouseDragged(int x, int y, int button){}
void ofApp::mousePressed(int x, int y, int button){}
void ofApp::mouseReleased(int x, int y, int button){}
void ofApp::mouseEntered(int x, int y){}
void ofApp::mouseExited(int x, int y){}
void ofApp::windowResized(int w, int h){}
void ofApp::gotMessage(ofMessage msg){}
void ofApp::dragEvent(ofDragInfo dragInfo){}

void ofApp::audioReceived(float * input, int bufferSize, int nChannels) {
    soda.audioReceived(input, bufferSize, nChannels);
}

void ofApp::audioRequested(float * output, int bufferSize, int nChannels) {
    soda.audioRequested(output, bufferSize, nChannels);
}

