#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	width = ofGetWidth();
	height = ofGetHeight();
	
	renderedPixels.allocate(width, height, OF_PIXELS_RGBA);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			renderedPixels.setColor(x, y, ofColor::red);
		}
	}

	rendered = shared_ptr<ofTexture>(new ofTexture);
	rendered->allocate(renderedPixels);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(128, 128, 128);
	ofSetColor(255, 255, 255, 255);

	rendered->draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
