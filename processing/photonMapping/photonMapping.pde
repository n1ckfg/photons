//Ray Tracing & Photon Mapping
//Grant Schindler, 2007
// https://www.cc.gatech.edu/~phlosoft/photon/

// ----- Scene Description -----
int szImg = 512;                  //Image Size
int nrTypes = 2;                  //2 Object Types (Sphere = 0, Plane = 1)
int[] nrObjects = {2,5};          //2 Spheres, 5 Planes
float gAmbient = 0.1;             //Ambient Lighting
float[] gOrigin = {0.0,0.0,0.0};  //World Origin for Convenient Re-Use Below (Constant)
float[] Light = {0.0,1.2,3.75};   //Point Light-Source Position
float[][] spheres = {{1.0,0.0,4.0,0.5},{-0.6,-1.0,4.5,0.5}};         //Sphere Center & Radius
float[][] planes  = {{0, 1.5},{1, -1.5},{0, -1.5},{1, 1.5},{2,5.0}}; //Plane Axis & Distance-to-Origin

// ----- Photon Mapping -----
int nrPhotons = 1000;             //Number of Photons Emitted
int nrBounces = 3;                //Number of Times Each Photon Bounces
boolean lightPhotons = true;      //Enable Photon Lighting?
float sqRadius = 0.7;             //Photon Integration Area (Squared for Efficiency)
float exposure = 50.0;            //Number of Photons Integrated at Brightest Pixel
int[][] numPhotons = {{0,0},{0,0,0,0,0}};              //Photon Count for Each Scene Object
float[][][][][] photons = new float[2][5][5000][3][3]; //Allocated Memory for Per-Object Photon Info

// ----- Raytracing Globals -----
boolean gIntersect = false;       //For Latest Raytracing Call... Was Anything Intersected by the Ray?
int gType;                        //... Type of the Intersected Object (Sphere or Plane)
int gIndex;                       //... Index of the Intersected Object (Which Sphere/Plane Was It?)
float gSqDist, gDist = -1.0;      //... Distance from Ray Origin to Intersection
float[] gPoint = {0.0, 0.0, 0.0}; //... Point At Which the Ray Intersected the Object

//---------------------------------------------------------------------------------------
// User Interaction and Display ---------------------------------------------------------
//---------------------------------------------------------------------------------------
boolean empty = true, view3D = false; //Stop Drawing, Switch Views
PFont font; PImage img1, img2, img3;  //Fonts, Images
int pRow, pCol, pIteration, pMax;     //Pixel Rendering Order
boolean odd(int x) {return x % 2 != 0;}

void setup() {
  size(50, 50, FX2D);
  surface.setSize(szImg, szImg + 48);
  frameRate(9999);
  font = loadFont("Helvetica-Bold-12.vlw");
  emitPhotons();
  resetRender(); 
  setupInterface(); //drawInterface();
}

void draw() {  
  if (view3D) {
    if (empty) {
      stroke(0); fill(0); rect(0,0,szImg-1,szImg-1); //Black Out Drawing Area
      emitPhotons(); empty = false; frameRate(10);
    }
  } else { //Emit & Draw Photons
    if (empty) {
      render(); 
    } else {
      frameRate(10);
    }
  } //Only Draw if Image Not Fully Rendered
  drawInterface();
}

void setupInterface() {
  img1=loadImage("1_32.png"); 
  img2=loadImage("2_32.png"); 
  img3=loadImage("3_32.png"); //Load Images
}

void drawInterface() {
  stroke(221,221,204); 
  fill(221,221,204); 
  rect(0,szImg,szImg,48); //Fill Background with Page Color 
  //img1=loadImage("1_32.png"); 
  //img2=loadImage("2_32.png"); 
  //img3=loadImage("3_32.png"); //Load Images
  
  textFont(font); //Display Text
  if (!view3D) {
    fill(0); 
    img3.filter(GRAY);
  } else {
    fill(160);
  }
  text("Ray Tracing", 64, szImg + 28);
  if (lightPhotons || view3D) {
    fill(0); 
    img1.filter(GRAY);
  } else {
    fill(160);
  }
  text("Photon Mapping", 368, szImg + 28);
  if (!lightPhotons || view3D) img2.filter(GRAY);
  
  stroke(0); fill(255);  //Draw Buttons with Icons
  rect(198,519,33,33); image(img1,199,520);
  rect(240,519,33,33); image(img2,241,520);
  rect(282,519,33,33); image(img3,283,520);
}

void render() { //Render Several Lines of Pixels at Once Before Drawing
  int x,y,iterations = 0;
  float[] rgb = { 0.0,0.0,0.0 };
  
  while (iterations < (mouseDragging ? 1024 : max(pMax, 256))) {
    //Render Pixels Out of Order With Increasing Resolution: 2x2, 4x4, 16x16... 512x512
    if (pCol >= pMax) {
      pRow++; pCol = 0; 
      if (pRow >= pMax) {
        pIteration++; pRow = 0; pMax = int(pow(2,pIteration));
      }
    }
    boolean pNeedsDrawing = (pIteration == 1 || odd(pRow) || (!odd(pRow) && odd(pCol)));
    x = pCol * (szImg/pMax); y = pRow * (szImg/pMax);
    pCol++;
    
    if (pNeedsDrawing) {
      iterations++;
      rgb = mul3c( computePixelColor(x,y), 255.0);               //All the Magic Happens in Here!
      stroke(rgb[0],rgb[1],rgb[2]); fill(rgb[0],rgb[1],rgb[2]);  //Stroke & Fill
      rect(x,y,(szImg/pMax)-1,(szImg/pMax)-1); //Draw the Possibly Enlarged Pixel
    }                 
  }
  if (pRow == szImg-1) {
    empty = false;
  }
}

void resetRender() { //Reset Rendering Variables
  pRow=0; 
  pCol=0; 
  pIteration=1; 
  pMax=2; 
  frameRate(9999);
  empty=true; 
  if (lightPhotons && !view3D) emitPhotons();
}

void drawPhoton(float[] rgb, float[] p) {           //Photon Visualization
  if (view3D && p[2] > 0.0) {                       //Only Draw if In Front of Camera
    int x = (szImg/2) + (int)(szImg *  p[0]/p[2]); //Project 3D Points into Scene
    int y = (szImg/2) + (int)(szImg * -p[1]/p[2]); //Don't Draw Outside Image
    if (y <= szImg) {
      stroke(255.0*rgb[0],255.0*rgb[1],255.0*rgb[2]); 
      point(x,y);
    }
  }
}
