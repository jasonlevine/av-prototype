#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //audio
    audio.loadSound("01 Cake & Eat It Too.aif");
    audio.play();
    
    fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 128;
    
    //images
    bilal.loadImage("images/Bilal.png");
    aLoveSurreal.loadImage("images/a-love-surreal.png");
    ladies.loadImage("images/ladies.png");
    coolCircle.loadImage("images/cool-circle.png");
    coolHole.loadImage("images/cool-hole.png");
    blueAura.loadImage("images/blue-aura.png");
    haeckel.loadImage("images/haeckel.png");
    
    //graphics
    ofEnableAlphaBlending();
    
    //
    circleDegree = 0;
}

//--------------------------------------------------------------
void testApp::update(){
    ofSoundUpdate();
    float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed value sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}
    circleDegree+=fftSmoothed[1]/2.0f;
    if (circleDegree > 360.0f) {
        circleDegree-=360.0f;
    }
    
    circleScale = fftSmoothed[50];
}

//--------------------------------------------------------------
void testApp::draw(){
    // draw the fft resutls:
	ofSetColor(0);
	
	float width = (float)(5*128) / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		ofRect(600+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
	}
    //float degrees = fftSmoothed[1] * 45.0f;
    
    ofSetColor(255, 255, 255, 255);
    
    
    ofPushMatrix();
    ofTranslate(300, 300);
    ofRotateZ(circleDegree);
    ofScale(circleScale, circleScale);
    ofTranslate(-300, -300);
    coolCircle.draw(0,0, 600, 600);
    ofPopMatrix();
    
    coolHole.draw(0,0, 600, 600);
}



//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}