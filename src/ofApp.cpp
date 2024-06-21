#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetColor(255);

}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
  if (scene == 0) {
    ofDrawBitmapString("HMD SHOW BY TSUKAMOTO TERADA LAB", ofGetHeight()/2, ofGetWidth()/2);
  } else if (scene == 1) {
    for (int i = 0; i < 10; i++) {
      ofDrawBitmapString(HMD_NAMES[i], 10, 10 + i * 20);
    }
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

