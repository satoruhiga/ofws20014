#include "ofMain.h"

#include "ofxPDF.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxPDF pdf;
	
	void setup()
	{
		pdf.load("test.pdf");
	}
	
	void draw()
	{
		pdf.draw();
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
