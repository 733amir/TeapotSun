/*
 * Solar System Simulation
 * Written by Amir Khazaie (733amir@gmail.com)
 *
 * This project is for Computer Graphics course by Dr. Maziar Palhang,
 * held in Isfahan University of Technology.
 */

// External Libraries
#include <math.h>
#include <iostream>
#include <GL/glut.h>

// My Modules
#include "planet.h"
#include "galaxy.h"

// Constants
const float pi = 3.141592654f;

// values for mouse movement and camera control
float xpos = 0, ypos = 0, zpos = 0, xrot = 25, yrot = 30;

// values for planets
const int num_planets = 8; // number of planets in system

Galaxy galaxy;
Planet sun;
Planet planets[num_planets];

float speedMult; // the movement speed multiplier, affected by keyboard input
float movementSpeed; // low values means faster movement speed

bool* keyStates = new bool[256]; // boolean array to track multiple keypresses


// Initialization
void galaxyInitialization(void) {
    float orbitsScale = 20, orbitsStart = 50;
    float diameterScale = 1;
    float revSpeedMult = 0.1, rotSpeedMult = 1.0;

    // No key press at start, so initialize them to false at start.
	for (int i = 0; i < 256; i++) keyStates[i] = false;

    // Speed of planets orbiting the sun in the galaxy.
    speedMult = 0.0;
    // Speed of camera movement.
    movementSpeed = 1.0;

	// Galaxy
    galaxy = Galaxy(10000.0f);
    galaxy.setTexture("res/galaxy.bmp");

    // Planet parameters are distance, radius, rotSpeed, revSpeed, inclinationDegree, obliquityDegree.

    // Sun
    sun.setParams(0.0f, 25.0f, (1/10.0f) * rotSpeedMult, 0.0f, 0, 0);
    sun.changeSpeed(speedMult);
    sun.setTexture("res/sun.bmp");

    // Mercury
    planets[0].setParams(0.387f * orbitsScale + orbitsStart, 0.383f * diameterScale,
                         (1/58.8f) * rotSpeedMult, 1.59f * revSpeedMult, 7, 0.034);
    planets[0].changeSpeed(speedMult);
    planets[0].setTexture("res/planet_0.bmp");

    // Venus
    planets[1].setParams(0.723f * orbitsScale + orbitsStart, 0.949f * diameterScale,
                         (1/244.0f) * rotSpeedMult, 1.18f * revSpeedMult, 3.4, 177.4);
    planets[1].changeSpeed(speedMult);
    planets[1].setTexture("res/planet_1.bmp");

    // Earth
    planets[2].setParams(1.0f * orbitsScale + orbitsStart, 1.0f * diameterScale,
                         (1/1.0f) * rotSpeedMult, 1.0f * revSpeedMult, 0, 23.4);
    planets[2].changeSpeed(speedMult);
    planets[2].setTexture("res/planet_2.bmp");

    // Mars
    planets[3].setParams(1.52f * orbitsScale + orbitsStart, 0.532f * diameterScale,
                         (1/1.03f) * rotSpeedMult, 0.808f * revSpeedMult, 1.9, 25.2);
    planets[3].changeSpeed(speedMult);
    planets[3].setTexture("res/planet_3.bmp");

    // Jupiter
    planets[4].setParams(5.2f * orbitsScale + orbitsStart, 11.21f * diameterScale,
                         (1/0.415f) * rotSpeedMult, 0.439f * revSpeedMult, 1.3, 3.1);
    planets[4].changeSpeed(speedMult);
    planets[4].setTexture("res/planet_4.bmp");

    // Saturn
    planets[5].setParams(9.58f * orbitsScale + orbitsStart, 9.45f * diameterScale,
                         (1/0.445f) * rotSpeedMult, 0.325f * revSpeedMult, 2.5, 26.7);
    planets[5].changeSpeed(speedMult);
    planets[5].setTexture("res/planet_5.bmp");

    // Uranus
    planets[6].setParams(19.2f * orbitsScale + orbitsStart, 4.01f * diameterScale,
                         (1/0.72f) * rotSpeedMult, 0.228f * revSpeedMult, 0.8, 97.8);
    planets[6].changeSpeed(speedMult);
    planets[6].setTexture("res/planet_6.bmp");

    // Neptune
    planets[7].setParams(30.05f * orbitsScale + orbitsStart, 3.88f * diameterScale,
                         (1/0.673f) * rotSpeedMult, 0.182f * revSpeedMult, 1.8, 28.3);
    planets[7].changeSpeed(speedMult);
    planets[7].setTexture("res/planet_7.bmp");

}


// Capture keyboard
void keyOperations(void) {
	// move forward by holding 'w'
	if (keyStates['w'] && !keyStates['s']) {
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * pi);
		xrotrad = (xrot / 180 * pi);
		xpos += float(sin(yrotrad)) / movementSpeed;
		zpos -= float(cos(yrotrad)) / movementSpeed;
		ypos -= float(sin(xrotrad)) / movementSpeed;
	}

	// move backward by holding 's'
	if (keyStates['s'] && !keyStates['w']) {
		float xrotrad, yrotrad;
		yrotrad = (yrot / 180 * pi);
		xrotrad = (xrot / 180 * pi);
		xpos -= float(sin(yrotrad)) / movementSpeed;
		zpos += float(cos(yrotrad)) / movementSpeed;
		ypos += float(sin(xrotrad)) / movementSpeed;
	}

	// strafe right by holding 'd'
	if (keyStates['d'] && !keyStates['a']) {
		float yrotrad;
		yrotrad = (yrot / 180 * pi);
		xpos += float(cos(yrotrad)) / movementSpeed;
		zpos += float(sin(yrotrad)) / movementSpeed;
	}

	// strafe left by holding 'a'
	if (keyStates['a'] && !keyStates['d']) {
		float yrotrad;
		yrotrad = (yrot / 180 * pi);
		xpos -= float(cos(yrotrad)) / movementSpeed;
		zpos -= float(sin(yrotrad)) / movementSpeed;
	}

    // move camera up by holding 'o'
    if (keyStates['o'] && !keyStates['l']) {
        xrot--;
    }

    // move camera down by holding 'l'
    if (keyStates['l'] && !keyStates['o']) {
        xrot++;
    }

    // move camera left by holding 'k'
    if (keyStates['k'] && !keyStates[';']) {
        yrot--;
    }

    // move camera right by holding ';'
    if (keyStates[';'] && !keyStates['k']) {
        yrot++;
    }

	// hit Esc to quit
	if (keyStates[27]) { exit(0); }
}


// Enable rendering properties of OpenGL.
void initRendering(void) {
    GLfloat light_diffuse[] = { 2, 2, 2, 0 };
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);

    GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    GLfloat light_specular[] = { 0, 0, 0, 0 };
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING); // Enable lighting for light related computations.
	glEnable(GL_LIGHT0); // Enables light zero to be used as sun.
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glShadeModel(GL_SMOOTH); // set the shader to smooth shader
}


// Camera rotation and translation commands for user interaction
void updateCamera(void) {
	glRotatef(xrot, 1.0, 0.0, 0.0);  //rotate our camera on the x-axis (left and right)
	glRotatef(yrot, 0.0, 1.0, 0.0);  //rotate our camera on the y-axis (up and down)
	glTranslated(-xpos, -ypos, -zpos); //translate the screen to the position of our camera
}


// Drawing all scene.
void drawScene(void) {
    // Draw sun, galaxy and each of planets.
	sun.draw(true);
	galaxy.draw();
	for (int i = 0; i < num_planets; i++)
		planets[i].draw(false);

    // Draw galaxy grid and planets orbit.
	if (!keyStates[' ']) {
		// galaxy.drawGrid();
        for (int i = 0; i < num_planets; i++)
            planets[i].drawOrbitPath();
	}
}


// display our solar system
void display (void) {
	keyOperations(); // set the keypress operations
	glClearColor(0.0, 0.0, 0.0, 1.0); // clear the screen to black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the color buffer and the depth buffer

	glLoadIdentity();

	updateCamera(); // set our camera position

	drawScene(); // draw the scene



    GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glFlush();
	glutSwapBuffers(); // swap the buffers
}


// GL reshape function
void reshape (int w, int h) {
	// set the viewport to the current window specifications
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	// set the matrix to projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// set the perspective (angle of sight, width, height, depth)
	gluPerspective(60, (GLfloat) w / (GLfloat) h, 0.1, 10000.0);
	// set the matrix back to model
	glMatrixMode(GL_MODELVIEW);
}


// set a keypressed state to true while key is held down
void keyPressed (unsigned char key, int x, int y) {  
	// Set the state of the current key to pressed
	keyStates[key] = true;
	
	// set speed of system with number keys. exponential increase!
	int speedChange = key - '0';
	if (speedChange >= 0 && speedChange < 10) {
		sun.changeSpeed(speedChange);
		for (int i = 0; i < num_planets; i++) {
			planets[i].changeSpeed(speedChange);
		}
	}

    // Movement speed change with q (faster), e (slower)
    if (keyStates['q'] && !keyStates['e']) {
        movementSpeed--;
        if (movementSpeed < 1)
            movementSpeed = 1;
    }

    if (keyStates['e'] && !keyStates['q']) {
        movementSpeed++;
        if (movementSpeed > 10)
            movementSpeed = 10;
    }


}  


// set a keypressed state to false when key is released
void keyUp (unsigned char key, int x, int y) {  
	keyStates[key] = false; // Set the state of the current key to not pressed  
}


// main function
int main (int argc, char **argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(960, 540); 
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Solar System Simulation by Amir Khazaie (733amir@gmail.com)");

	initRendering();
    galaxyInitialization();

	glutDisplayFunc(display); 
	glutIdleFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyPressed);
	glutKeyboardUpFunc(keyUp);

	glutMainLoop();
	return 0;
}