#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetColor(255, 80, 10);
  futura.load("Futura.ttc", 84);
  optima.load("Optima.ttc", 84);
  pageFont.load("Optima.ttc", 24);
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
  int p = 140;
  float fontRed = abs(sin(frameCount * 0.004)) * 200;
  if (scene == 0) {
    float titleY = ofGetWidth()/2-120;
    int yPad = 120;

    //ofSetColor(200 - fontRed, 0, 0);
    //logo.draw(ofGetWidth()/2+100, 80, 500, 500);
    //ofSetColor(fontRed, 0, 0);
    ofSetColor(scarlet);
    ofSetLineWidth(3);
    //ofDrawLine(p, 0, p, ofGetHeight());

    ofNoFill();
    ofDrawTriangle(ofGetWidth()/4, 40, ofGetWidth()*4/5, 40, ofGetWidth(), ofGetHeight()*2/3);

    ofFill();
    ofSetLineWidth(8);
    ofDrawTriangle(ofGetWidth()*2/4, 40,
        ofGetWidth()*4/5, 40,
        ofGetWidth()*2/4+20, ofGetHeight()*1/3-62);
    //ofSetColor(255);
    ofDrawTriangle(ofGetWidth()*4/5, 40,
        ofGetWidth()*4/5+20, ofGetHeight()/2+12,
        ofGetWidth()*4/5+134, ofGetHeight()*1/3);

    ofSetColor(fontRed+fontRed*4/3, 0, 0);
    //optima.drawString("HMD SHOW", titleXPad, titleY+titleYPad);
    //ofSetColor(255,0,0);
    optima.drawString("HMD SHOW", 0, titleY);

    ofSetColor(fontRed+fontRed*2/3, 0, 0);
    //optima.drawString("BY", titleXPad, titleY+yPad+titleYPad);
    //ofSetColor(255,0,0);
    optima.drawString("BY", 0, titleY+yPad);

    ofSetColor(fontRed, 0, 0);
    //optima.drawString("TSUKAMOTO TERADA LAB.", titleXPad, titleY+2*yPad+titleYPad);
    //ofSetColor(255,0,0);
    optima.drawString("TSUKAMOTO TERADA LAB.", 0, titleY+2*yPad);

  } else if (scene == 1) {
    //ofSetColor(255, 0, 0);
    ofSetColor(scarlet);
    float makerX = ofGetWidth();
    float makerY = 120;
    nameTextBB = futura.getStringBoundingBox(HMD_NAMES[hmdNum], makerX, makerY);
    float nameX = ofGetWidth()/2;
    float nameY = ofGetHeight()/2+300;
    makerTextBB = futura.getStringBoundingBox(HMD_MAKERS[hmdNum], nameX, nameY);


    ofSetLineWidth(2);
    optima.drawString(HMD_MAKERS[hmdNum], makerX-makerTextBB.width-20, makerY);
    ofSetColor(255);
    ofDrawLine(makerX-makerTextBB.width-20, makerY+8, makerX-20, makerY+8);
    //ofDrawRectangle(makerX, makerY-makerTextBB.height, makerTextBB.width, makerTextBB.height);

    ofNoFill();
    ofSetLineWidth(4);
    ofSetColor(scarlet);
    ofDrawRectangle(ofGetWidth()/2-500, ofGetHeight()/2+10-300, 1000, 680);
    ofSetColor(255);
    HMD_IMAGES[hmdNum].draw(ofGetWidth()/2-320, ofGetHeight()/2-240, 640, 480);
    ofSetColor(scarlet);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2, nameY+64);
    ofSetColor(255);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2+4, nameY+64+4);
    pageFont.drawString(ofToString(hmdNum+1), ofGetWidth()-24, ofGetHeight()-24);
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
      hmdNum = 0;
      break;
    case '2':
      scene = 1;
      hmdNum = 1;
      break;
    case '3':
      scene = 1;
      hmdNum = 2;
      break;
    case '4':
      scene = 1;
      hmdNum = 3;
      break;
    case '5':
      scene = 1;
      hmdNum = 4;
      break;
    case '6':
      scene = 1;
      hmdNum = 5;
      break;
    case '7':
      scene = 1;
      hmdNum = 6;
      break;
    case '8':
      scene = 1;
      hmdNum = 7;
      break;
    case OF_KEY_LEFT:
      hmdNum = (hmdNum + 7) % 8;
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

