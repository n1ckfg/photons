#pragma once

//---------------------------------------------------------------------------------------
// Raytracing ---------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void raytrace(float[] ray, float[] origin) {
	gIntersect = false; //No Intersections Along This Ray Yet
	gDist = 999999.9;   //Maximum Distance to Any Object

	for (int t = 0; t < nrTypes; t++) {
		for (int i = 0; i < nrObjects[t]; i++) {
			rayObject(t, i, ray, origin);
		}
	}
}

float[] computePixelColor(float x, float y) {
	float[] rgb = { 0.0,0.0,0.0 };
	float[] ray = { x / szImg - 0.5 ,       //Convert Pixels to Image Plane Coordinates
		-(y / szImg - 0.5), 1.0 }; //Focal Length = 1.0
	raytrace(ray, gOrigin);                //Raytrace!!! - Intersected Objects are Stored in Global State

	if (gIntersect) {                       //Intersection                    
		gPoint = mul3c(ray, gDist);           //3D Point of Intersection

		if (gType == 0 && gIndex == 1) {      //Mirror Surface on This Specific Object
			ray = reflect(ray, gOrigin);        //Reflect Ray Off the Surface
			raytrace(ray, gPoint);             //Follow the Reflected Ray
			if (gIntersect) {
				gPoint = add3(mul3c(ray, gDist), gPoint);
			}
		} //3D Point of Intersection

		if (lightPhotons) {                   //Lighting via Photon Mapping
			rgb = gatherPhotons(gPoint, gType, gIndex);
		}
		else {                                //Lighting via Standard Illumination Model (Diffuse + Ambient)
			int tType = gType, tIndex = gIndex;//Remember Intersected Object
			float i = gAmbient;                //If in Shadow, Use Ambient Color of Original Object
			raytrace(sub3(gPoint, Light), Light);  //Raytrace from Light to Object
			if (tType == gType && tIndex == gIndex) //Ray from Light->Object Hits Object First?
				i = lightObject(gType, gIndex, gPoint, gAmbient); //Not In Shadow - Compute Lighting
			rgb[0] = i; rgb[1] = i; rgb[2] = i;
			rgb = getColor(rgb, tType, tIndex);
		}
	}
	return rgb;
}

float[] reflect(float[] ray, float[] fromPoint) {                //Reflect Ray
	float[] N = surfaceNormal(gType, gIndex, gPoint, fromPoint);  //Surface Normal
	return normalize3(sub3(ray, mul3c(N, (2 * dot3(ray, N)))));     //Approximation to Reflection
}