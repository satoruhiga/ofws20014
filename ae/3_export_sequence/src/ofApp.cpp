#include "ofMain.h"

#include "ofxExportImageSequence.h"

class ofApp : public ofBaseApp
{
public:
	
	ofxExportImageSequence seq_out;
	
	void setup()
	{
		ofSeedRandom(<#int val#>)
		ofBackground(0);
		
		seq_out.setup(1280, 720, 30, GL_RGBA, 4);
		seq_out.setFrameRange(0, 300);
	}
	
	void update()
	{
		float t;
		
		if (seq_out.isExporting())
		{
			t = seq_out.getElapsedTime();
		}
		else
		{
			t = ofGetElapsedTimef() * 0.5;
		}

		
		seq_out.begin();
		{
			ofClear(0, 0);
			
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			
			float p = sin(fmodf(t * 0.1 , 1)* PI);
			
			ofEnableBlendMode(OF_BLENDMODE_ADD);
			
			for (int i = 0; i < 10; i++)
			{
				float size = ofNoise(t, i) * 300;
				float s = ofNoise(i, t);
				s = sin(s * PI);
				s = s * s * 40;
				
				if ((i % 3) == 0)
					ofNoFill();
				else
					ofFill();
				
				ofSetColor(ofColor::fromHsb(ofMap(i, 0, 10, 0, 255), 255, 255));
				
				int num = i * 4;
				
				for (int n = 0; n < num; n++)
				{
					float r = ofMap(n, 0, num, 0, 1);
					float rr = r * TWO_PI + ofSignedNoise(i, t) * 1;
					float x = sin(rr) * size;
					float y = cos(rr) * size;
					ofCircle(x, y, s);
				}
			}
		}
		
		seq_out.end();
	}
	
	void draw()
	{
		ofSetColor(255);
		seq_out.draw(0, 0);
	}
	
	void keyPressed(int key)
	{
		seq_out.startExport();
	}
};

int main(int argc, const char** argv)
{
	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp);
	return 0;
}
