#include "ofMain.h"

#include "ofxAfterEffectsKeyframeParser.h"

class ofApp : public ofBaseApp
{
public:
	ofxAfterEffectsKeyframeParser key;
	
	void setup()
	{
		key.open("test.txt");
		key.dumpTrackName();
	}
	
	void draw()
	{
		float app_time = ofGetElapsedTimef();
		float animation_time = fmodf(app_time, 3);
		
		const ofxAfterEffectsKeyframeParser::Track& track = key.getTrack("Transform/Position");
		
		int F = animation_time * 30;
		float x = track.getParam(F, "X pixels");
		float y = track.getParam(F, "Y pixels");
		
		ofRect(x, y, 100, 100);
	}
	
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
