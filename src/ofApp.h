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

    ofTrueTypeFont myFont;
    //string array of names
    string HMD_NAMES[10] = {"Apple Vision Pro", "Meta Quest 3", "Xreal light", "Xreal Air 2 Ultra",
                        "Vive Pro", "Hololens 2", "Moverio BT40S", "Vuzix M4000", "Vuzix z100",
                        "Monocle"};
    int scene = 0;

};
