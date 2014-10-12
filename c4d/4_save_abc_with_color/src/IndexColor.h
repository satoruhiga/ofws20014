#pragma once

#include "ofMain.h"

class IndexColor
{
public:
	
	inline static ofVec2f colorToTexCoord(const ofColor &c)
	{
		unsigned int n = colorToIndex(c);
		float u = (float)(n % getSize()) / getSize();
		float v = (float)(n / getSize()) / getSize();
		return ofVec2f(u, v);
	}
	
	inline static ofColor texCoordToColor(const ofVec2f& tc)
	{
		float u = tc.x * getSize();
		float v = tc.y * getSize() * getSize();
		unsigned int idx = u + v;
		return indexToColor(idx);
	}
	
	inline static unsigned int colorToIndex(const ofColor &c)
	{
		return (c.b << 16) | (c.g << 8) | c.r;
	}
	
	inline static ofColor indexToColor(unsigned int idx)
	{
		ofColor c;
		c.r = idx & 0xFF;
		c.g = (idx >> 8) & 0xFF;
		c.b = (idx >> 16) & 0xFF;
		return c;
	}

	//
	
	inline static void convertColorToTexCoord(ofMesh& mesh)
	{
		vector<ofFloatColor> &colors = mesh.getColors();
		vector<ofVec2f>& TCs = mesh.getTexCoords();
		
		TCs.resize(colors.size());
		
		for (int i = 0; i < colors.size(); i++)
		{
			TCs[i] = colorToTexCoord(colors[i]);
		}
	}

	inline static void convertTexCoordToColor(ofMesh& mesh)
	{
		vector<ofFloatColor> &colors = mesh.getColors();
		vector<ofVec2f>& TCs = mesh.getTexCoords();
		
		colors.resize(TCs.size());
		
		for (int i = 0; i < colors.size(); i++)
		{
			colors[i] = texCoordToColor(TCs[i]);
		}
	}

	//

	static void exportIndexTexture(const string& path)
	{
		ofPixels pix;
		
		pix.allocate(getSize(), getSize(), 3);
		pix.set(0);
		
		for (int b = 0; b < 256; b++)
		{
			for (int g = 0; g < 256; g++)
			{
				for (int r = 0; r < 256; r++)
				{
					ofColor c(r, g, b);
					unsigned int idx = colorToIndex(c);
					
					int x = idx % getSize();
					int y = idx / getSize();
					
					pix.setColor(x, y, c);
				}
			}
		}
		
		pix.mirror(true, false);

		ofSaveImage(pix, path);
	}
	
	inline static unsigned int getSize() { return 4096; }
};