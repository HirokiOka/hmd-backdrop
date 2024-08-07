#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetColor(255, 80, 10);
  futura.load("Futura.ttc", 84);
  optima.load("Optima.ttc", 84);
  makerOptima.load("Optima.ttc", 64);
  makerOptimaSmall.load("Optima.ttc", 48);
  pageFont.load("Optima.ttc", 24);
  for (int i = 0; i < 8; i++) {
    HMD_IMAGES[i].load("img/" + ofToString(i) + ".jpeg");
  }

  bgm.load("hmd_bgm_3.wav");
  bgm.setLoop(true);
  bgm.play();

  fftLive.setup();
  nBandsToGet = 64;
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSoundUpdate();
  fftLive.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  int frameCount = ofGetFrameNum();
  if (pageNum == 0) {
    float titleY = ofGetWidth()/2-280;
    int yPad = 140;
    ofSetColor(scarlet);
    ofSetLineWidth(3);

    ofNoFill();
    ofDrawTriangle(
        ofGetWidth()/4, 40,
        ofGetWidth()*4/5, 40,
        ofGetWidth(), ofGetHeight()*2/3);

    ofFill();
    ofSetLineWidth(8);
    ofDrawTriangle(
        ofGetWidth()*2/4, 40,
        ofGetWidth()*4/5, 40,
        ofGetWidth()*2/4+20, ofGetHeight()*1/3-62);
    //ofSetColor(255);
    ofDrawTriangle(
        ofGetWidth()*4/5, 40,
        ofGetWidth()*4/5+20, ofGetHeight()/2+12,
        ofGetWidth()*4/5+134, ofGetHeight()*1/3);

    //TITLE TEXTS
    float t1Red = abs(sin(frameCount * 0.004 + 20)) * 200;
    float t1Col = ofMap(t1Red, 0, 200, 1, 255);
    ofSetColor(t1Col, 0, 0);
    optima.drawString("HMD SHOW", 0, titleY);

    float t2Red = abs(sin(frameCount * 0.004 + 10)) * 200;
    float t2Col = ofMap(t2Red, 0, 200, 1, 255);
    ofSetColor(t2Col, 0, 0);
    optima.drawString("BY", 80, titleY+yPad);

    float t3Red = abs(sin(frameCount * 0.004)) * 200;
    float t3Col = ofMap(t3Red, 0, 200, 1, 255);
    ofSetColor(t3Col, 0, 0);
    optima.drawString("TSUKAMOTO TERADA LAB.", 0, titleY+2*yPad);

    //Visualling the sound
    ofSetColor(scarlet);
    float width = (float)(ofGetWidth()) / nBandsToGet;
    const std::vector<float>& fftData = fftLive.getFftNormData();
    for (int i = 0; i < nBandsToGet; i++) {
        float value = fftData[i] * waveMax;
        ofDrawRectangle(i * width, ofGetHeight(), width, -value);
    }

  } else if (pageNum != 0)  {
    hmdNum = pageNum - 1;
    ofSetColor(scarlet);

    int trapW = 1000;
    int trapH = 1200;

    float x1 = ofGetWidth()/2-trapW/2, y1 = ofGetHeight()/2-trapH/4-40;
    float x2 = ofGetWidth()/2+trapW/2, y2 = y1;
    float x3 = x2-trapW/6, y3 = y1+trapH/2-40;
    float x4 = x1+trapW/6, y4 = y3;

    ofPath trapezoid;
    trapezoid.moveTo(x1, y1);
    trapezoid.lineTo(x2, y2);
    trapezoid.lineTo(x3, y3);
    trapezoid.lineTo(x4, y4);
    trapezoid.close();

    trapezoid.setFillColor(ofColor(0));
    trapezoid.setStrokeColor(ofColor(255, 0, 0));
    trapezoid.setStrokeWidth(4);
    trapezoid.draw();

    float makerX = 20;
    float makerY = ofGetHeight()-140;
    makerTextBB = makerOptima.getStringBoundingBox(HMD_MAKERS[hmdNum], makerX, makerY);
    makerSmallTextBB = makerOptimaSmall.getStringBoundingBox(HMD_MAKERS[hmdNum], makerX, makerY);

    float nameX = ofGetWidth()/2;
    float nameY = 48;
    nameTextBB = futura.getStringBoundingBox(HMD_NAMES[hmdNum], nameX, nameY);


    ofSetLineWidth(2);
    ofSetColor(scarlet);
    if (hmdNum == 6 || hmdNum == 7) {
      makerOptimaSmall.drawString(HMD_MAKERS[hmdNum], makerX, makerY-makerSmallTextBB.height-20);
      ofNoFill();
      ofSetColor(255);
      ofDrawLine(makerX, makerY-makerSmallTextBB.height-10, makerX+makerSmallTextBB.width, makerY-makerSmallTextBB.height-10);
    } else {
      makerOptima.drawString(HMD_MAKERS[hmdNum], makerX+10, makerY-makerTextBB.height-20);
      ofNoFill();
      ofSetColor(255);
      ofDrawLine(makerX+20, makerY-makerTextBB.height-8, makerX+makerTextBB.width, makerY-makerTextBB.height-8);
    }

    ofNoFill();
    ofSetLineWidth(4);
    ofSetColor(scarlet);

    ofSetColor(255);
    int imgW = 640;
    int imgH = 480;
    HMD_IMAGES[hmdNum].draw(ofGetWidth()/2-imgW/2, ofGetHeight()/2-imgH/2-60, imgW, imgH);


    ofSetColor(scarlet);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2, nameY+64);
    ofSetColor(255);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2+4, nameY+64+4);

    //Visualling the sound
    ofFill();
    ofSetColor(scarlet);
    float width = (float)(ofGetWidth()) / nBandsToGet;
    const std::vector<float>& fftData = fftLive.getFftNormData();
    for (int i = 0; i < nBandsToGet; i++) {
        float value = fftData[i] * waveMax;
        ofDrawRectangle(i * width, ofGetHeight(), width, -value);
    }

    ofSetColor(255);
    pageFont.drawString(ofToString(pageNum), ofGetWidth()-48, makerY-64);

  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch (key) {
    case '0':
      pageNum = 0;
      break;
    case '1':
      pageNum = 1;
      break;
    case '2':
      pageNum = 2;
      break;
    case '3':
      pageNum = 3;
      break;
    case '4':
      pageNum = 4;
      break;
    case '5':
      pageNum = 5;
      break;
    case '6':
      pageNum = 6;
      break;
    case '7':
      pageNum = 7;
      break;
    case '8':
      pageNum = 8;
      break;
    case OF_KEY_LEFT:
      pageNum = (pageNum + 8) % 9;
      break;
    case OF_KEY_RIGHT:
      pageNum = (pageNum + 1) % 9;
      break;
    default:
      break;
  }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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

