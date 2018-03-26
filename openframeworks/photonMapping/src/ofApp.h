#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int width;
		int height;
		ofPixels renderedPixels;
		shared_ptr<ofTexture> rendered;

		int szImg;                  //Image Size
		int nrTypes;                  //2 Object Types (Sphere = 0, Plane = 1)
		int nrObjects[];          //2 Spheres, 5 Planes
		float gAmbient;             //Ambient Lighting
		float gOrigin[] = { 0.0,0.0,0.0 };  //World Origin for Convenient Re-Use Below (Constant)
		float Light[] = { 0.0,1.2,3.75 };   //Point Light-Source Position
		float spheres[][] = { { 1.0,0.0,4.0,0.5 },{ -0.6,-1.0,4.5,0.5 } };         //Sphere Center & Radius
		float planes[][] = { { 0, 1.5 },{ 1, -1.5 },{ 0, -1.5 },{ 1, 1.5 },{ 2,5.0 } }; //Plane Axis & Distance-to-Origin

																						// ----- Photon Mapping -----
		int nrPhotons;             //Number of Photons Emitted
		int nrBounces;                //Number of Times Each Photon Bounces
		bool lightPhotons;      //Enable Photon Lighting?
		float sqRadius;             //Photon Integration Area (Squared for Efficiency)
		float exposure;            //Number of Photons Integrated at Brightest Pixel
		int numPhotons[][] = { { 0,0 },{ 0,0,0,0,0 } };              //Photon Count for Each Scene Object
		float photons[][][][][] = new float[2][5][5000][3][3]; //Allocated Memory for Per-Object Photon Info

															   // ----- Raytracing Globals -----
		boolean gIntersect = false;       //For Latest Raytracing Call... Was Anything Intersected by the Ray?
		int gType;                        //... Type of the Intersected Object (Sphere or Plane)
		int gIndex;                       //... Index of the Intersected Object (Which Sphere/Plane Was It?)
		float gSqDist, gDist = -1.0;      //... Distance from Ray Origin to Intersection
		float[] gPoint = { 0.0, 0.0, 0.0 }; //... Point At Which the Ray Intersected the Object
};
