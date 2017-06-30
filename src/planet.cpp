#include "planet.h"


Planet::Planet() {
    distance = 10;
    radius = 1;
    rotationSpeed = 1;
    rotationAngle = 0;
    revolutionSpeed = 1;
    revolutionAngle = 0;
    speedMult = 1;
}


Planet::Planet(float distance, float radius, float rotSpeed, float revSpeed, float speedMult,
               float inclinationDegree, float obliquityDegree) {
	setParams(distance, radius, rotSpeed, revSpeed, inclinationDegree, obliquityDegree);
    changeSpeed(speedMult);
}


void Planet::changeSpeed(float n) {
    if (n == 0) speedMult = 0;
	else speedMult = float(pow(1.6, n - 1));
}


void Planet::setTexture(const char* name) {
	textureID = loadTexture(loadBMP(name));
}


void Planet::setParams(float distance, float radius, float rotSpeed, float revSpeed,
                       float inclinationDegree, float obliquityDegree) {
	this->distance = distance;
	this->radius = radius;

	this->rotationSpeed = rotSpeed;
    this->rotationAngle = 0;

	this->revolutionSpeed = revSpeed;
    this->revolutionAngle = 0;

    this->inclination = - inclinationDegree * 3;
    this->obliquity = obliquityDegree * pi / 180;
}


void Planet::draw(bool sun) {
	float angle = 2.0f * pi;
	glPushMatrix();

		glColor3f(1, 1, 1);

		// enable texture mapping for the planet
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        // rotate to the current orbit with a degree relative to Earth orbit
        glRotatef(inclination, 0.0, 0.0, 1.0);

		// rotate to the current revolution angle
		glRotatef(revolutionAngle, 0.0, 1.0, 0.0);

		// Translate out to the orbital radius
		glTranslatef(distance * cosf(angle), 0, distance * sinf(angle));

		// rotate to the current rotation angle
		glRotatef(rotationAngle, sinf(obliquity), cosf(obliquity), 0.0);

		// Prepare and draw the sphere itself
		GLUquadric* quad = gluNewQuadric();
		gluQuadricOrientation(quad, (sun? GLU_INSIDE: GLU_OUTSIDE));
		gluQuadricTexture(quad, GLU_TRUE);
		gluSphere(quad, radius, 100, 100);

		glDisable(GL_TEXTURE_2D);

	glPopMatrix();

	// Update the revolution and rotation angles for the next call
	revolutionAngle += revolutionSpeed * speedMult;
	if (revolutionAngle >= 360.0f) {
		revolutionAngle -= 360.0f;
	}
	rotationAngle += rotationSpeed * speedMult;
	if (rotationAngle >= 360.0f) {
		rotationAngle -= 360.0f;
	}
}

void Planet::drawOrbitPath() {
	int segments = 60;
	glPushMatrix();
		glColor3f(1, 1, 1); // circles will be gray-ish
        glRotatef(inclination, 0.0, 0.0, 1.0); // rotate to the current orbit with a degree relative to Earth orbit
		glBegin(GL_LINE_LOOP);
		for(int i = 0; i < segments; i++) {
			float angle = 2.0f * pi * float(i) / float(segments); // get the current angle
			float x = distance * cosf(angle); // calculate the x component
			float z = distance * sinf(angle); // calculate the z component
			glVertex3f(x, 0, z); // output vertices
		}
		glEnd();
	glPopMatrix();
}