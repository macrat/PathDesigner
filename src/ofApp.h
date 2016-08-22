#pragma once

#include <vector>

#include "ofMain.h"


enum displaylevel_t {
	PATH_ONLY,
	PATH_LINE,
	VERBOSE
};


class ofApp : public ofBaseApp{
private:
	std::vector<ofPoint> points;
	displaylevel_t displayLevel;
	unsigned int ctrl_length_rate;

public:
	ofApp() : ctrl_length_rate(4) {}
	ofApp(unsigned int ctrl_length_rate, std::vector<ofPoint> points) : points(points), ctrl_length_rate(ctrl_length_rate) {}

	void setup();
	void draw();

	void keyPressed(int key);
	void mousePressed(int x, int y, int button);

	void output() const;
};
