#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();

    void showCredits();
    void deviceChanged(int & newDeviceId);

		void keyPressed(int key);
		void keyReleased(int key);


    ofSoundPlayer bgm;
    ofSoundPlayer testSound;
    ofxFFTLive fftLive;

    vector<float> fftSmoothed;
    int nBandsToGet;
    int waveMax = 140;
    bool isPlaying = false;


    ofTrueTypeFont futura;
    ofTrueTypeFont futuraMid;
    ofTrueTypeFont futuraSmall;
    ofTrueTypeFont optima;
    ofTrueTypeFont makerOptima;
    ofTrueTypeFont makerOptimaSmall;
    ofTrueTypeFont pageFont;

    /*
    //string HMD_NAMES[8] = {"Vuzix Z100", "Meta Quest 3", "Vuzix M4000", "Xreal Air 2",
      //"Apple Vision Pro", "MOVERIO BT-40S", "HoloLens 2", "Monocle"};
    //string HMD_MAKERS[8] = {"Vuzix", "Meta", "Vuzix", "Xreal",
      //"Apple", "Epson", "Microsoft", "Brilliant Labs"};
    */
    string HMD_NAMES[8] = {
      "Vuzix M4000",
      "MOVERIO BT-40S",
      "Xreal Air 2",
      "HoloLens 2",
      "Apple Vision Pro",
      "Meta Quest 3",
      "Vuzix Z100",
      "Frame"
    };
    string HMD_MAKERS[8] = {
      "Vuzix",
      "Epson",
      "Xreal",
      "Microsoft",
      "Apple",
      "Meta",
      "Vuzix",
      "Brilliant Labs"
    };
    int hmdNum = 0;
    int pageNum = 0;

    ofRectangle makerTextBB;
    ofRectangle makerSmallTextBB;
    ofRectangle nameTextBB;

    ofImage HMD_IMAGES[8];
    ofColor white = ofColor(255, 255, 255);

    ofColor scarlet = ofColor(187, 11, 11);
    ofxFloatSlider volume;
    ofxIntSlider brightness;
    ofxIntSlider deviceId;
    ofxPanel gui;

    ofSoundStream soundStream;
    vector<ofSoundDevice> devices;

    bool debug = false;
};
