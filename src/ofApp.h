#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		//void dragEvent(ofDragInfo dragInfo);
		//void gotMessage(ofMessage msg);

    ofTrueTypeFont futura;
    ofTrueTypeFont optima;
    ofTrueTypeFont pageFont;
    //string array of names
    string HMD_NAMES[8] = {"Vuzix z100", "Meta Quest 3", "Vuzix M4000", "Xreal Air 2",
      "Apple Vision Pro", "Moverio BT-40S", "Hololens 2", "Monocle"};
    string HMD_MAKERS[8] = {"Vuzix", "Meta", "Vuzix", "Xreal",
      "Apple", "Epson", "Microsoft", "Brilliant Labs"};
    int scene = 0;
    int hmdNum = 0;

    ofRectangle makerTextBB;
    ofRectangle nameTextBB;

    ofImage HMD_IMAGES[8];
    ofImage logo;

    ofColor scarlet = ofColor(187, 11, 11);

};
