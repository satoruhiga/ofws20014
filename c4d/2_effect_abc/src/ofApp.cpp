#include "ofMain.h"

#include "ofxAlembic.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxAlembic::Reader abc;
	ofMesh mesh;
	
	ofLight light0;
	ofLight light1;
	
	void setup()
	{
		ofSetFrameRate(60);
		ofSetVerticalSync(true);
		ofBackground(0);
		
		abc.open("sample.abc");
		
		abc.dumpNames();
		
		light0.setup();
		light0.setDiffuseColor(ofFloatColor(0.4, 0.4, 0.8));
		light1.setup();
		light1.setDiffuseColor(ofFloatColor(0.4, 0.8, 0.4));
	}
	
	void update()
	{
		float abc_range = (abc.getMaxTime() - abc.getMinTime());
		float t = fmodf(ofGetElapsedTimef(), abc_range) + abc.getMinTime();
		abc.setTime(t);
		
		abc.get("ClonerShape", mesh);
		
		updateMesh(mesh);
		
		light0.orbit(ofGetElapsedTimef() * 10, 0, 2000);
		light1.orbit(ofGetElapsedTimef() * -20, 60, 2000);
	}
	
	ofEasyCam cam;
	void draw()
	{
		ofEnableDepthTest();
		
		cam.begin();
		light0.enable();
		light1.enable();

		ofScale(0.3, 0.3, 0.3);
		mesh.draw();
		cam.end();
	}
	
	void updateMesh(ofMesh& mesh)
	{
		float t = ofGetElapsedTimef();
		
		ofVec3f axis;
		axis.x = ofSignedNoise(1, 0, 0, t);
		axis.y = ofSignedNoise(0, 1, 0, t);
		axis.z = ofSignedNoise(0, 0, 1, t);
		axis.normalize();
		
		vector<ofVec3f>& verts = mesh.getVertices();
		vector<ofVec3f>& norms = mesh.getNormals();
		for (int i = 0; i < verts.size(); i++)
		{
			ofVec3f& v = verts[i];
			ofVec3f& n = norms[i];
			ofVec3f vv = v;
			
			float r = vv.y * fmodf(t, 10) * 0.1;
			
			vv.rotate(r, axis);
			n.rotate(r, axis);
			
			v = vv;
		}
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
