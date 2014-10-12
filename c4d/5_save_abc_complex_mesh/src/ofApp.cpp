#include "ofMain.h"

#include "ofxAlembic.h"
#include "ofxTrueTypeFontUL2.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Writer abc_out;
	ofxTrueTypeFontUL2 font;
	
	ofMesh mesh;
	
	string text;
	float animation_time;
	
	void setup()
	{
		float export_fps = 30;
		
		ofSetFrameRate(export_fps);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc_out.open("out.abc", export_fps);
		
		font.loadFont("verdana.ttf", 72, false, true, true, 0.5);
		
		animation_time = 0;
	}
	
	void update()
	{
		static int time_t = ofGetElapsedTimef();
		int time = ofGetElapsedTimef();
		
		if (time_t != time)
		{
			time_t = time;
			
			animation_time = 0;
			
			char buf[32];
			sprintf(buf, "%04i:%02i:%02i:%02i:%02i:%02i ",
					ofGetYear(),
					ofGetMonth(),
					ofGetDay(),
					ofGetHours(),
					ofGetMinutes(),
					ofGetSeconds());
			
			text = buf;
			
			cout << text << endl;
		}
		
		// animation time
		animation_time += (1 - animation_time) * 0.03;
		
		// text
		float caret = ofClamp(animation_time * 2, 0, 1);
		string t = text.substr(0, text.size() * caret);
		
		if (ofInRange(caret, 0, 0.95))
		{
			t += (char)ofRandom(32, 126);
		}

		// mesh
		vector<ofPath> paths = font.getStringAsPoints(t, 0, 0);
		
		mesh.clear();
		for (int i = 0; i < paths.size(); i++)
		{
			ofPath& path = paths[i];
			mesh.append(path.getTessellation());
		}
		
		// export to abc
		abc_out.addPolyMesh("/time", mesh);
	}
	
	ofEasyCam cam;
	void draw()
	{
		cam.begin();
		mesh.drawWireframe();
		cam.end();
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
