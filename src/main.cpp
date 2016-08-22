#include <fstream>

#include "ofApp.h"


int main(int argc, char** argv){
	if(argc != 2){
		ofSetupOpenGL(1024, 768, OF_WINDOW);

		ofRunApp(new ofApp());
	}else{
		std::ifstream ifs(argv[1]);

		int ctrl_length_rate;
		ifs >> ctrl_length_rate;

		std::vector<ofPoint> points;
		while(true){
			int x, y;
			ifs >> x >> y;
			if(ifs.eof()){
				break;
			}
			points.push_back(ofPoint(x + 100, y + 100));
		}

		ofSetupOpenGL(1024, 768, OF_WINDOW);

		ofRunApp(new ofApp(ctrl_length_rate, points));
	}
}
