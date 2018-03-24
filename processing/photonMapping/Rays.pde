//---------------------------------------------------------------------------------------
//Ray-Geometry Intersections  -----------------------------------------------------------
//---------------------------------------------------------------------------------------

void raySphere(int idx, float[] r, float[] o) { // Ray-Sphere Intersection: r=Ray Direction, o=Ray Origin 
  float[] s = sub3(spheres[idx],o);  // s=Sphere Center Translated into Coordinate Frame of Ray Origin
  float radius = spheres[idx][3];    // radius=Sphere Radius
  
  //Intersection of Sphere and Line     =       Quadratic Function of Distance
  float A = dot3(r,r);                       // Remember This From High School? :
  float B = -2.0 * dot3(s,r);                //    A x^2 +     B x +               C  = 0
  float C = dot3(s,s) - sq(radius);          // (r'r)x^2 - (2s'r)x + (s's - radius^2) = 0
  float D = B*B - 4*A*C;                     // Precompute Discriminant
  
  if (D > 0.0) {                              //Solution Exists only if sqrt(D) is Real (not Imaginary)
    float sign = (C < -0.00001) ? 1 : -1;    //Ray Originates Inside Sphere If C < 0
    float lDist = (-B + sign*sqrt(D))/(2*A); //Solve Quadratic Equation for Distance to Intersection
    checkDistance(lDist,0,idx); //Is This Closest Intersection So Far?
  }            
}

void rayPlane(int idx, float[] r, float[] o) { //Ray-Plane Intersection
  int axis = (int) planes[idx][0];            //Determine Orientation of Axis-Aligned Plane
  if (r[axis] != 0.0) {                        //Parallel Ray -> No Intersection
    float lDist = (planes[idx][1] - o[axis]) / r[axis]; //Solve Linear Equation (rx = p-o)
    checkDistance(lDist,1,idx);
  }
}

void rayObject(int type, int idx, float[] r, float[] o) {
  if (type == 0) {
    raySphere(idx,r,o); 
  } else {
    rayPlane(idx,r,o);
  }
}

void checkDistance(float lDist, int p, int i) {
  if (lDist < gDist && lDist > 0.0) { //Closest Intersection So Far in Forward Direction of Ray?
    gType = p; gIndex = i; gDist = lDist; gIntersect = true; //Save Intersection in Global State
  } 
}
