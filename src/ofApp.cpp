#include "ofApp.h"


void ofApp::setup() {
	ofSetBackgroundColor(ofColor::black);
	ofEnableBlendMode(OF_BLENDMODE_ADD);

	displayLevel = VERBOSE;
}


void ofApp::draw() {
	for(int i=0; i<max(ofGetWidth(), ofGetHeight()); i+=10){
		if(i%100 == 0){
			ofSetColor(ofColor::white, 128);
		}else{
			ofSetColor(ofColor::white, 64);
		}
		ofDrawLine(0, i, ofGetWidth(), i);
		ofDrawLine(i, 0, i, ofGetHeight());
	}

	ofSetColor(ofColor::white);
	for(auto p: points) {
		ofDrawCircle(p, 4);
	}

	if(displayLevel >= PATH_LINE && points.size() >= 2){
		for(unsigned int i=1; i<points.size(); i++){
			ofDrawLine(points[i-1], points[i]);
		}
	}

	if(points.size() >= 3){
		ofPoint oldCtrl;

		for(unsigned int i=1; i<points.size()-1; i++){
			double rad = atan2(points[i-1].x - points[i+1].x, points[i-1].y - points[i+1].y);

			double ctrl_length = points[i-1].distance(points[i+1]) / ctrl_length_rate;

			ofPoint a(points[i].x + sin(rad)*ctrl_length, points[i].y + cos(rad)*ctrl_length);
			ofPoint b(points[i].x - sin(rad)*ctrl_length, points[i].y - cos(rad)*ctrl_length);

			if(displayLevel >= VERBOSE){
				ofSetColor(ofColor::red);
				ofDrawCircle(a, 4);
				ofSetColor(ofColor::green);
				ofDrawCircle(b, 4);
				ofSetColor(ofColor::white);
				ofDrawLine(a, b);
			}

			if(i >= 2){
				ofPoint oldPos = points[i-1];
				for(double t=0.0; t<=1.0; t+=0.01){
					ofSetColor(255, 255*t, 255);
					ofPoint p(
						(pow(1.0-t, 3) * oldPos)
						+ (3 * pow(1.0-t, 2) * t * oldCtrl)
						+ (3 * (1.0-t) * pow(t, 2) * a)
						+ (pow(t, 3) * points[i])
					);
					ofDrawLine(oldPos, p);
					oldPos = p;
				}
			}
			oldCtrl = b;
		}
	}
}


void ofApp::keyPressed(int key) {
	switch(key){
	case ' ':
		points.clear();
		break;
	case 'd':
		displayLevel = static_cast<displaylevel_t>(displayLevel + 1);
		if(displayLevel > VERBOSE){
			displayLevel = PATH_ONLY;
		}
		break;
	case 'z':
		ctrl_length_rate++;
		break;
	case 'x':
		if(ctrl_length_rate > 1){
			ctrl_length_rate--;
		}
		break;
	case 's':
		output();
		break;
	}
}


void ofApp::mousePressed(int x, int y, int button) {
	points.push_back(ofPoint(x, y));
}


void ofApp::output() const {
	if(points.size() < 4){
		return;
	}

	std::cout << ctrl_length_rate << std::endl;

	auto base = points[1];
	for(auto p: points) {
		std::cout << p.x - base.x << "\t" << base.y - p.y << std::endl;
	}
}
