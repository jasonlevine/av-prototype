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
    //bilal.loadImage("images/Bilal.png");
    aLoveSurreal.loadImage("images/a-love-surreal.png");
    ladies.loadImage("images/ladies.png");
    coolCircle.loadImage("images/cool-circle.png");
    coolHole.loadImage("images/cool-hole.png");
    haeckel.loadImage("images/haeckel.png");
    haeckelScreen.loadImage("images/haeckel.png");
    lipsPyramid.loadImage("images/BILAL_pyramids-lip1.jpg");
    test.allocate(coolHole.getPixelsRef());
    //graphics
    ofEnableAlphaBlending();
    ofBackground(10);
    //
    
    fftToLightness.load("shaders/vert.glsl", "shaders/frag.glsl");
    mandalaScale = 1.0f;
    
    shaderFbo.allocate(1200, 1200);
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
    
    for (int y = 0; y < haeckel.height; y++) {
        for (int x = 0; x < haeckel.width; x++) {
            ofColor pixelCol = haeckel.getColor(x, y);
            float lightness = pixelCol.getLightness();
            int index = 64 - lightness / 4;
            float alpha = fftSmoothed[index] * 512;
            haeckelScreen.setColor(x, y, ofColor(alpha));
        }
    }
    haeckelScreen.update();
    
    circleDegree+=0.2f;
    if (circleDegree > 360.0f) {
        circleDegree-=360.0f;
    }
    
    mandalaScale-=0.001;

}

//--------------------------------------------------------------
void testApp::draw(){
    // draw the fft resutls:
	//ofSetColor(0);
	/*
	float width = (float)(5*128) / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
		ofRect(600+i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
	}*/
    
    if (mandalaScale < 0.5) {
        ofPushMatrix();
        ofTranslate(300, 300);
        ofScale(mandalaScale, mandalaScale);
        ofTranslate(-8400, -6900);
        ofSetColor(255, 255, 255, 255);
        lipsPyramid.draw(0,0, 18000, 12000);
        ofPopMatrix();
    }
    
    if (mandalaScale > 0.0) {
        ofPushMatrix();
        ofTranslate(300, 300);
        ofScale(mandalaScale, mandalaScale);
        ofTranslate(-600, -600);
        
        
        ofSetColor(255, 255, 255, 255);
        ofPushMatrix();
        ofTranslate(600, 600);
        ofRotateZ(circleDegree);
        ofTranslate(-600, -600);
        coolCircle.draw(0,0, 1200, 1200);
        ofPopMatrix();
        
        ofSetColor(255, 255, 255, 200);
        haeckelScreen.draw(0,0, 1200, 1200);
        
        ofSetColor(255, 255, 255, 200);
        coolHole.draw(0, 0, 1200, 1200);

        /*
        shaderFbo.begin();
        fftToLightness.begin();
        fftToLightness.setUniformTexture("tex", test, 0 );
                glBegin(GL_QUADS);
        glTexCoord2f(0, 0); glVertex3f(0, 0, 0);
        glTexCoord2f(ofGetWidth(), 0); glVertex3f(ofGetWidth(), 0, 0);
        glTexCoord2f(ofGetWidth(), ofGetHeight()); glVertex3f(ofGetWidth(), ofGetHeight(), 0);
        glTexCoord2f(0,ofGetHeight());  glVertex3f(0,ofGetHeight(), 0);
        glEnd();
        fftToLightness.end();
        shaderFbo.end();
        
        shaderFbo.draw(0, 0);
         */
        
        
        ofSetColor(255, 255, 255, 255);
        ofPushMatrix();
        ofRotateZ(-circleDegree);
        ladies.draw(0, 0, 390*0.8, 600*0.8);
        ofPopMatrix();
        
        ofPushMatrix();
        ofTranslate(1200, 1200);
        ofRotateZ(circleDegree);
        ladies.draw(0, 0, 390*0.8, 600*0.8);
        ofPopMatrix();
        
        
        ofPopMatrix();
    }
    
    
    
    ofSetColor(0, 255, 0);
    ofDrawBitmapString("fps: " + ofToString(ofGetFrameRate()), 610, 10);
    
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