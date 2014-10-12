#include "ofMain.h"

#include "ofxPDF.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxPDF pdf;
	
	vector<ofVec3f> points;
	
	void setup()
	{
		ofBackground(255);
		
		pdf.load("test.pdf");
		
		ofPath& path = pdf.getPathAt(0);
		ofPolyline poly = path.getOutline()[0];
		
		points = poly.getVertices();
	}
	
	void draw()
	{
		float app_time = ofGetElapsedTimef();
		float animation_time = fmodf(app_time, 2) / 2.;
		
		cout << "app_time: = " << app_time << ", animation_time: " << animation_time << endl;
		
		ofSetColor(0);
		
		for (int i = 0; i < points.size(); i += 2)
		{
			ofVec3f v0 = points[i];
			ofVec3f v1 = points[i + 1];
			
			ofLine(v0, v0.getInterpolated(v1, animation_time));
		}
		
		
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
