#pragma once

/*
    Created by Ben McChesney
    @ Helios Interactive

    301 8th Street, STE 250
    San Francisco , CA

    5/3/2013
*/
#include "ofMain.h"
#include "ofxAutomatedInput.h"

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		ofxAutomatedInput autoInput ;

		void automatedInputHandler( AutomatedInputData &args ) ;
};
