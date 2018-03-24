//---------------------------------------------------------------------------------------
// Lighting -----------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

float lightDiffuse(float[] N, float[] P) {  //Diffuse Lighting at Point P with Surface Normal N
  float[] L = normalize3( sub3(Light,P) ); //Light Vector (Point to Light)
  return dot3(N,L);                        //Dot Product = cos (Light-to-Surface-Normal Angle)
}

float[] sphereNormal(int idx, float[] P) {
  return normalize3(sub3(P,spheres[idx])); //Surface Normal (Center to Point)
}

float[] planeNormal(int idx, float[] P, float[] O) {
  int axis = (int) planes[idx][0];
  float [] N = {0.0,0.0,0.0};
  N[axis] = O[axis] - planes[idx][1];      //Vector From Surface to Light
  return normalize3(N);
}

float[] surfaceNormal(int type, int index, float[] P, float[] Inside) {
  if (type == 0) {
    return sphereNormal(index,P);
  } else {
    return planeNormal(index,P,Inside);
  }
}

float lightObject(int type, int idx, float[] P, float lightAmbient) {
  float i = lightDiffuse( surfaceNormal(type, idx, P, Light) , P );
  return min(1.0, max(i, lightAmbient));   //Add in Ambient Light by Constraining Min Value
}
