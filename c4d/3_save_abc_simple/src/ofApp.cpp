#include "ofMain.h"

#include "ofxAlembic.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Writer abc_out;

	ofMesh mesh;
	
	void setup()
	{
		float export_fps = 30;
		
		ofSetFrameRate(export_fps);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc_out.open("out.abc", export_fps);
	}
	
	void update()
	{
		mesh.clear();
		
		for (int i = 0; i < 90; i++)
		{
			ofVec3f v;
			v.x = ofRandom(-100, 100);
			v.y = ofRandom(-100, 100);
			v.z = ofRandom(-100, 100);
			mesh.addVertex(v);
		}
		
		// export to abc
		abc_out.addPolyMesh("/mesh", mesh);
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
