#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetColor(255, 80, 10);
  futura.load("Futura.ttc", 84);
  optima.load("Optima.ttc", 84);
  for (int i = 0; i < 8; i++) {
    HMD_IMAGES[i].load("img/" + ofToString(i) + ".jpeg");
  }
  logo.load("img/logo.png");

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  int frameCount = ofGetFrameNum();
  float fontRed = abs(sin(frameCount * 0.01)) * 255;
  if (scene == 0) {
    float titleY = ofGetWidth()/2-120;
    float yPad = 120;
    ofSetColor(255, 0, 0);
    //logo.draw(ofGetWidth()/2+100, 80, 580, 580);
    ofSetColor(fontRed, 0, 0);
    optima.drawString("HMD SHOW", 0, titleY);
    optima.drawString("BY", 0, titleY+yPad);
    optima.drawString("TSUKAMOTO TERADA LAB.", 0, titleY+2*yPad);
  } else if (scene == 1) {
    ofSetColor(255, 0, 0);
    float makerX = ofGetWidth();
    float makerY = 120;
    nameTextBB = futura.getStringBoundingBox(HMD_NAMES[hmdNum], makerX, makerY);
    float nameX = ofGetWidth()/2;
    float nameY = ofGetHeight()/2+300;
    makerTextBB = futura.getStringBoundingBox(HMD_MAKERS[hmdNum], nameX, nameY);


    optima.drawString(HMD_MAKERS[hmdNum], makerX-makerTextBB.width-20, makerY);
    //ofDrawRectangle(makerX, makerY-makerTextBB.height, makerTextBB.width, makerTextBB.height);

    ofNoFill();
    ofSetLineWidth(4);
    ofDrawRectangle(ofGetWidth()/2-340, 220, 800, 580);
    ofSetColor(255);
    HMD_IMAGES[hmdNum].draw(ofGetWidth()/2-400, 160, 780, 560);
    ofSetColor(240, 0, 0);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2, nameY);
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
  switch (key) {
    case '0':
      scene = 0;
      break;
    case '1':
      scene = 1;
      break;
    case OF_KEY_LEFT:
      hmdNum = (hmdNum - 1) % 8;
      ofLog() << makerTextBB;
      break;
    case OF_KEY_RIGHT:
      hmdNum = (hmdNum + 1) % 8;
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

