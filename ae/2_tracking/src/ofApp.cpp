#include "ofMain.h"

#include "ofxAfterEffectsKeyframeParser.h"

class ofApp : public ofBaseApp
{
public:
	ofVideoPlayer player;
	ofxAfterEffectsKeyframeParser key;
	
	void setup()
	{
		key.open("tracking.txt");
		key.dumpTrackName();
		
		player.loadMovie("tracking_test.mov");
		player.play();
	}
	
	void update()
	{
		player.update();
	}
	
	void draw()
	{
		player.draw(0, 0);
		
		const ofxAfterEffectsKeyframeParser::Track& track = key.getTrack("Motion Trackers/Tracker #1/Track Point #1/Feature Center");
		
		int F = player.getCurrentFrame();
		float x = track.getParam(F, "X pixels");
		float y = track.getParam(F, "Y pixels");
		
		ofNoFill();
		ofCircle(x, y, 20, 20);
	}
	
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
