#include <GL/glut.h>
#include <math.h>
#include <time.h>
#include "texture_loader.h"


// Class for a Planet object that contains the required simulation properties.
class Planet {
private:
    // Constant values.
    const float pi = 3.1415926f;

	// The planet's distance from the Sun.
	float distance;

	// The planet's radius.
	float radius;

	// The current rotation speed and angle of the planet, with respect to it's axis.
	float rotationSpeed;
	float rotationAngle;

	// The current revolution speed and angle of the planet with respect to the sun.
	float revolutionSpeed;
	float revolutionAngle;

    // The angle in degrees at which a planets orbit around the Sun is tilted relative to the ecliptic plane.
    // The ecliptic plane is defined as the plane containing the Earth's orbit, so the Earth's inclination is 0.
    float inclination;

    // The angle in degrees the axis of a planet (the imaginary line running through the center of the planet from the
    // north to south poles) is tilted relative to a line perpendicular to the planet's orbit around the Sun.
    float obliquity;


	// A speed multiplier, if it exists.
	float speedMult;

	// The planet's texture ID, for texturing purposes.
	GLuint textureID;

public:
    Planet();

    // The initializer for planet with required properties for simulation.
	Planet(float distance, float radius, float rotSpeed, float revSpeed, float speedMult,
           float inclinationDegree, float obliquityDegree);

	// Sets the texture of the planet to the file with the given file name.
	void setTexture(const char* name);

	// Sets the key parameters of the planet's motion.
	void setParams(float distance, float radius, float rotSpeed, float revSpeed,
                   float inclinationDegree, float obliquityDegree);

	// Changes the speed multiplier to a given value.
	void changeSpeed(float ds);

	// Draws the planet and its orbital path.
	void draw(bool sun);
	void drawOrbitPath();
};