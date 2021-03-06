#pragma once

#include "ofMain.h"
#include "ofxSodaLib.h"
#include "Orbit.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
        // audio callbacks
        void audioReceived(float * input, int bufferSize, int nChannels);
        void audioRequested(float * output, int bufferSize, int nChannels);
    
        ofxSodaLib soda;
        float getAngleFromPoint2D(ofVec2f center, ofVec2f soundLocation);
    
        vector< Orbit > orbits;
        const string notes[7] = {"C", "D", "Eb", "F", "G", "Ab", "A"};
    
        int index = 0;
};
