#include "ofMain.h"

#include "ofxPDF.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxPDF pdf;
	
	void setup()
	{
		ofBackground(255);
		
		pdf.load("test.pdf");
	}
	
	void draw()
	{
		float app_time = ofGetElapsedTimef();
		float animation_time = fmodf(app_time, 2) / 2.;
		
		cout << "app_time: = " << app_time << ", animation_time: " << animation_time << endl;
		
		ofSetColor(0);
		
		for (int i = 0; i < pdf.getNumPath(); i++)
		{
			ofPath& path = pdf.getPathAt(i);
			
			vector<ofPolyline>& polys = path.getOutline();
			for (int k = 0; k < polys.size(); k++)
			{
				ofPolyline poly = polys[k];
				
				poly = poly.getResampledByCount(100);
				
				int target_size = poly.size() * animation_time;
				poly.resize(target_size);
				
				poly.draw();
			}
		}
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
