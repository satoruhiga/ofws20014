#include "ofMain.h"

#include "ofxAlembic.h"
#include "IndexColor.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Writer abc_out;

	ofMesh mesh;
	
	void setup()
	{
		IndexColor::exportIndexTexture("tex.png");
		
		float export_fps = 30;
		
		ofSetFrameRate(export_fps);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc_out.open("out.abc", export_fps);
	}
	
	void update()
	{
		mesh.clear();
		
		float t = ofGetElapsedTimef() * 0.3;
		float noise_scale = 0.05;
		
		float size = 300;
		float shape_size = 200;
		
		int num = 100;
		for (int i = 0; i < num; i++)
		{
			ofVec3f base(ofSignedNoise(10, 0, 0, i * noise_scale + t),
						 ofSignedNoise(0, 10, 0, i * noise_scale + t),
						 ofSignedNoise(0, 0, 10, i * noise_scale + t));
			
			ofVec3f v0(ofSignedNoise(1, 0, 0, i * noise_scale + t),
					   ofSignedNoise(0, 1, 0, i * noise_scale + t),
					   ofSignedNoise(0, 0, 1, i * noise_scale + t));
			
			ofVec3f v1(ofSignedNoise(2, 0, 0, i * noise_scale + t),
					   ofSignedNoise(0, 2, 0, i * noise_scale + t),
					   ofSignedNoise(0, 0, 2, i * noise_scale + t));

			ofVec3f v2(ofSignedNoise(3, 0, 0, i * noise_scale + t),
					   ofSignedNoise(0, 3, 0, i * noise_scale + t),
					   ofSignedNoise(0, 0, 3, i * noise_scale + t));
			
			float hue = ofMap(i, 0, num, 0, 1);
			ofFloatColor c = ofFloatColor::fromHsb(hue, 1, 1);
			
			float s = fabs(sin(i * 0.1 + t)) + 0.1;
			
			mesh.addColor(c);
			mesh.addColor(c);
			mesh.addColor(c);
			
			mesh.addVertex(base * size + v0 * shape_size * s);
			mesh.addVertex(base * size + v1 * shape_size * s);
			mesh.addVertex(base * size + v2 * shape_size * s);
		}
		
		IndexColor::convertColorToTexCoord(mesh);
		
		// export to abc
		abc_out.addPolyMesh("/mesh", mesh);
	}
	
	ofEasyCam cam;
	void draw()
	{
		ofEnableDepthTest();
		
		cam.begin();
		mesh.draw();
		cam.end();
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
