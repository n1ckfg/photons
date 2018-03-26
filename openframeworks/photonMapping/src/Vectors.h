#pragma once

//---------------------------------------------------------------------------------------
//Vector Operations ---------------------------------------------------------------------
//---------------------------------------------------------------------------------------

float[] normalize3(float v[]) {        //Normalize 3-Vector
	float L = sqrt(dot3(v, v));
	return mul3c(v, 1.0 / L);
}

float[] sub3(float a[], float b[]) {   //Subtract 3-Vectors
	float result[] = { a[0] - b[0], a[1] - b[1], a[2] - b[2] };
	return result;
}

float[] add3(float a[], float b[]) {   //Add 3-Vectors
	float[] result = { a[0] + b[0], a[1] + b[1], a[2] + b[2] };
	return result;
}

float[] mul3c(float a[], float c) {    //Multiply 3-Vector with Scalar
	float result[] = { c*a[0], c*a[1], c*a[2] };
	return result;
}

float dot3(float a[], float b[]) {     //Dot Product 3-Vectors
	return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}

float[] rand3(float s) {               //Random 3-Vector
	float[] rand = { random(-s,s),random(-s,s),random(-s,s) };
	return rand;
}

bool gatedSqDist3(float a[], float b[], float sqradius) { //Gated Squared Distance
	float c = a[0] - b[0];          //Efficient When Determining if Thousands of Points
	float d = c * c;                  //Are Within a Radius of a Point (and Most Are Not!)
	if (d > sqradius) {
		return false; //Gate 1 - If this dimension alone is larger than
	} else {
		c = a[1] - b[1];                //         the search radius, no need to continue
		d += c * c;
		if (d > sqradius) {
			return false; //Gate 2
		} else {
			c = a[2] - b[2];
			d += c * c;
			if (d > sqradius) {
				return false; //Gate 3
			} else {
				gSqDist = d;
				return true; //Store Squared Distance Itself in Global State
			}
		}
	}
}