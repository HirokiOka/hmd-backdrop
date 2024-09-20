#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetColor(255, 80, 10);
  futura.load("Futura.ttc", 84);
  futuraMid.load("Futura.ttc", 52);
  futuraSmall.load("Futura.ttc", 32);
  optima.load("Optima.ttc", 84);
  makerOptima.load("Optima.ttc", 64);
  makerOptimaSmall.load("Optima.ttc", 48);
  pageFont.load("Optima.ttc", 24);

  for (int i = 0; i < 8; i++) {
    HMD_IMAGES[i].load("img/" + ofToString(i) + ".jpeg");
  }

  bgm.load("hmd_bgm_v5_re.wav");
  bgm.setLoop(true);
  //bgm.play();
  isPlaying = false;

  ofHideCursor();


  devices = soundStream.getDeviceList();
  for (int i = 0; i < devices.size(); i++) {
    ofLog() << "Device " << i << ": " << devices[i].name;
  }

  gui.setup();
  gui.add(brightness.setup("Brightness", 255, 0, 255));
  gui.add(deviceId.setup("Audio Device", 0, 0, devices.size()-1));
  gui.add(volume.setup("BGM Volume", 0.5, 0.0, 1.0));

  soundStream.setDeviceID(deviceId);
  soundStream.setup(this, 0, 2, 44100, 256, 4);

  deviceId.addListener(this, &ofApp::deviceChanged);

  fftLive.setup();
  soundStream.setInput(fftLive);
  nBandsToGet = 64;
}

//--------------------------------------------------------------
void ofApp::update(){
  ofSoundUpdate();
  bgm.setVolume(volume);
  white.setBrightness(brightness);
  fftLive.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
  ofBackground(0);
  int frameCount = ofGetFrameNum();

  if (pageNum == 0) {
    int yPad = 140;
    int iconLineWidth = 8;

    //Draw HMD ICON
    ofPoint p1 = ofPoint(ofGetWidth()/4, ofGetHeight() / 24);
    ofPoint p2 = ofPoint(ofGetWidth()*4/5, ofGetHeight() / 24);
    ofPoint p3 = ofPoint(ofGetWidth(), ofGetHeight()*2/3);

    ofPoint p1_2 = p1 + (p2 - p1) * (1.0 / 2.0);
    ofPoint p2_3 = p2 + (p3 - p2) * (5.0 / 12.0);
    ofPoint p1_3_1 = p1 + (p3 - p1) * (1.0 / 3.0);
    ofPoint p1_3_2 = p1 + (p3 - p1) * (2.0 / 3.0);

    ofNoFill();
    ofSetColor(scarlet);
    ofDrawTriangle(p1, p2, p3);
    ofFill();
    ofSetLineWidth(iconLineWidth);
    ofDrawTriangle(p1_2, p2, p1_3_1);
    ofDrawTriangle(p2, p2_3, p1_3_2);

    //TITLE TEXTS
    float titleY = ofGetHeight()/2;

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


  } else if (pageNum == 9) {
    showCredits();

  } else if (pageNum != 0)  {
    hmdNum = pageNum - 1;
    ofSetColor(scarlet);

    int trapW = 1000;
    int trapH = 1200;

    float x1 = ofGetWidth()/2-trapW/2, y1 = ofGetHeight()/2-trapH/4-40;
    float x2 = ofGetWidth()/2+trapW/2, y2 = y1;
    float x3 = x2-trapW/6, y3 = y1+trapH/2-40;
    float x4 = x1+trapW/6, y4 = y3;

    ofPath backTrapezoid;
    backTrapezoid.moveTo(x1-70, y1-30);
    backTrapezoid.lineTo(x2+70, y2-30);
    backTrapezoid.lineTo(x3, y3);
    backTrapezoid.lineTo(x4, y4);
    backTrapezoid.close();

    ofPath trapezoid;
    trapezoid.moveTo(x1, y1);
    trapezoid.lineTo(x2, y2);
    trapezoid.lineTo(x3, y3-10);
    trapezoid.lineTo(x4, y4-10);
    trapezoid.close();

    backTrapezoid.setFillColor(ofColor(scarlet));
    backTrapezoid.setStrokeColor(ofColor(scarlet));
    backTrapezoid.setStrokeWidth(4);
    backTrapezoid.draw();

    trapezoid.setFillColor(ofColor(0));
    trapezoid.setStrokeColor(ofColor(scarlet));
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
    //When the maker name is too long, use smaller font
    if (hmdNum == 6 || hmdNum == 7) {
      makerOptimaSmall.drawString(HMD_MAKERS[hmdNum], makerX, makerY-makerSmallTextBB.height-20);
      ofNoFill();
      ofSetColor(white);
      ofDrawLine(makerX, makerY-makerSmallTextBB.height-10, makerX+makerSmallTextBB.width, makerY-makerSmallTextBB.height-10);
    } else {
      makerOptima.drawString(HMD_MAKERS[hmdNum], makerX+10, makerY-makerTextBB.height-20);
      ofNoFill();
      ofSetColor(white);
      ofDrawLine(makerX+20, makerY-makerTextBB.height-8, makerX+makerTextBB.width, makerY-makerTextBB.height-8);
    }

    ofNoFill();
    ofSetLineWidth(4);
    ofSetColor(scarlet);

    ofSetColor(white);
    int imgW = 640;
    int imgH = 480;
    HMD_IMAGES[hmdNum].draw(ofGetWidth()/2-imgW/2, ofGetHeight()/2-imgH/2-60, imgW, imgH);

    ofSetColor(scarlet);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2, nameY+64);
    ofSetColor(white);
    futura.drawString(HMD_NAMES[hmdNum], nameX-nameTextBB.width/2+4, nameY+64+4);

    ofSetColor(white);
    pageFont.drawString(ofToString(pageNum), ofGetWidth()-48, makerY-64);



  }
  //DRAW Setting GUI
  if (debug) {
    gui.draw();
  }

  //Visualize FFT
  ofSetColor(scarlet);
  ofFill();
  float width = (float)(ofGetWidth()) / nBandsToGet;
  const std::vector<float>& fftData = fftLive.getFftNormData();
  for (int i = 0; i < nBandsToGet; i++) {
    float value = fftData[i] * waveMax;
    ofDrawRectangle(i * width + 10, ofGetHeight(), width * 9/10, -value-10);
  }
}

//--------------------------------------------------------------
void ofApp::showCredits(){
  string models[8] = {
    "Takuma Shibata",
    "Yuki Morisaki",
    "Taichi Kyogoku",
    "Marii Mochizuki",
    "Salman Suwandi",
    "Kanata Utsunomiya",
    "Genki Mizutani",
    "Haruki Nagao"
  };

  string staff[4] = {
    "Hiroki Oka",
    "Natsumi Matsui",
    "Taichi Kyogoku",
    "Yusuke Miyajima"
  };

  ofBackground(0);
  //Draw center line
  /*
  ofSetColor(white);
  ofDrawLine(ofGetWidth()/2, 0, ofGetWidth()/2, ofGetHeight());
  */

  /*
  //Draw quarter line
  ofDrawLine(ofGetWidth()/4, 0, ofGetWidth()/4, ofGetHeight());
  ofDrawLine(ofGetWidth()*3/4, 0, ofGetWidth()*3/4, ofGetHeight());
  */

  int offsetY = ofGetHeight()/5;
  int pX = ofGetWidth()/2;
  int pY = 90;
  int titlePaddingY = 10;
  int underlinePaddingY = 10;
  int underlineExt = 4;
  ofRectangle staffBB = makerOptimaSmall.getStringBoundingBox("Staff", 0, 0);
  int subTitleX = ofGetWidth()/2 - staffBB.width/2;

  ofSetColor(white);
  makerOptimaSmall.drawString("Staff", subTitleX, pY);

  //Draw underline
  ofSetColor(scarlet);
  ofSetLineWidth(4);
  ofDrawLine(subTitleX-underlineExt, pY+underlinePaddingY, subTitleX + staffBB.width + underlineExt, pY+underlinePaddingY);

  //Draw staff names

  ofSetColor(white);
  ofNoFill();

  for (int i = 0; i < 4; i++) {
    int row = i / 2;
    int column = i % 2;
    int textX = ofGetWidth()/4 + row * pX;
    int textY = offsetY + titlePaddingY + pY * column;
    ofRectangle bb = futuraSmall.getStringBoundingBox(staff[i], textX, textY);

    ofSetColor(white);
    futuraSmall.drawString(staff[i], bb.x- bb.width/2, textY);
  }

  //SubTitle2 
  ofRectangle modelsBB = makerOptimaSmall.getStringBoundingBox("Models", 0, 0);
  int textY = offsetY + 2*pY + 20 ;
  int subTitleX2 = ofGetWidth()/2 - modelsBB.width/2;
  ofSetColor(white);
  makerOptimaSmall.drawString("Models", subTitleX2, textY);

  //Draw underline
  ofSetColor(scarlet);
  ofDrawLine(subTitleX2 -underlineExt, textY+underlinePaddingY, subTitleX2 + modelsBB.width+underlineExt, textY+underlinePaddingY);

  //Draw model names
  ofSetColor(white);
  int yDist = pY*2 + pY;
  for (int i = 0; i < 8; i++) {
    int row = i / 4;
    int column = i % 4;
    int textX = ofGetWidth()/4 + row * pX;
    int textY = offsetY + titlePaddingY + yDist + pY * column;
    ofRectangle bb = futuraSmall.getStringBoundingBox(models[i], textX, textY);

    ofSetColor(white);
    futuraSmall.drawString(models[i], bb.x - bb.width/2, textY);

  }
}

void ofApp::deviceChanged(int & newDeviceId) {
    ofLog() << "Device changed to " << newDeviceId;
    soundStream.close();
    soundStream.setDeviceID(newDeviceId);
    soundStream.setup(this, 0, 2, 44100, 256, 4);
    soundStream.setInput(fftLive);
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
    case '9':
      pageNum = 9;
      break;
    case OF_KEY_LEFT:
      //pageNum = (pageNum + 8) % 9;
      pageNum = (pageNum + 9) % 10;
      break;
    case OF_KEY_RIGHT:
      //pageNum = (pageNum + 1) % 9;
      pageNum = (pageNum + 1) % 10;
      break;
    case 'd':
      debug = !debug;
      break;
    case ' ':
      if (isPlaying) {
        bgm.stop();
        isPlaying = false;
      } else {
        bgm.play();
        isPlaying = true;
      }
      break;
    default:
      break;
  }

}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

