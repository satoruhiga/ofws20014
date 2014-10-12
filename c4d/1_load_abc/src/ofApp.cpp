#include "ofMain.h"

#include "ofxAlembic.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Reader abc;
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc.open("sample.abc");
		
		abc.dumpNames();
	}
	
	void update()
	{
		float abc_range = (abc.getMaxTime() - abc.getMinTime());
		float t = fmodf(ofGetElapsedTimef(), abc_range) + abc.getMinTime();
		abc.setTime(t);
	}
	
	ofEasyCam cam;
	void draw()
	{
		cam.begin();
		ofNoFill();
		abc.draw();
		cam.end();
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
