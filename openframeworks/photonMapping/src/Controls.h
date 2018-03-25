#pragma once

//---------------------------------------------------------------------------------------
//Mouse and Keyboard Interaction --------------------------------------------------------
//---------------------------------------------------------------------------------------
int prevMouseX = -9999, prevMouseY = -9999, sphereIndex = -1;
float s = 130.0; //Arbitary Constant Through Experimentation
boolean mouseDragging = false;

void mouseReleased() {
	prevMouseX = -9999;
	prevMouseY = -9999;
	mouseDragging = false;
}

void keyPressed() {
	switchToMode(key, 9999);
}

void mousePressed() {
	sphereIndex = 2; //Click Spheres
	float[] mouse3 = { (mouseX - szImg / 2) / s, -(mouseY - szImg / 2) / s, 0.5*(spheres[0][2] + spheres[1][2]) };
	if (gatedSqDist3(mouse3, spheres[0], spheres[0][3])) {
		sphereIndex = 0;
	}
	else if (gatedSqDist3(mouse3, spheres[1], spheres[1][3])) {
		sphereIndex = 1;
	}
	if (mouseY > szImg) switchToMode('0', mouseX); //Click Buttons
}

void mouseDragged() {
	if (prevMouseX > -9999 && sphereIndex > -1) {
		if (sphereIndex < nrObjects[0]) { //Drag Sphere
			spheres[sphereIndex][0] += (mouseX - prevMouseX) / s;
			spheres[sphereIndex][1] -= (mouseY - prevMouseY) / s;
		}
		else { //Drag Light
			Light[0] += (mouseX - prevMouseX) / s; Light[0] = constrain(Light[0], -1.4, 1.4);
			Light[1] -= (mouseY - prevMouseY) / s; Light[1] = constrain(Light[1], -0.4, 1.2);
		}
		resetRender();
	}
	prevMouseX = mouseX; prevMouseY = mouseY; mouseDragging = true;
}

void switchToMode(char i, int x) { // Switch Between Raytracing, Photon Mapping Views
	if (i == '1' || x<230) {
		view3D = false; lightPhotons = false; resetRender(); drawInterface();
	}
	else if (i == '2' || x<283) {
		view3D = false; lightPhotons = true;  resetRender(); drawInterface();
	}
	else if (i == '3' || x<513) {
		view3D = true; resetRender(); drawInterface();
	}
}