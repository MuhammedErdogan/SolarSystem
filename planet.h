#include <GL/freeglut.h>
#include <cmath>
#include "utils.h"

#define PI 3.14

enum CelestialBodyType{
    sun = -1,
    planet = 0,
    satellite = 1
};

class Planet {
    CelestialBodyType type;
    GLint id;
    GLfloat planetX;
    GLfloat planetY;
    GLfloat planetZ;
    GLfloat radius;
    GLfloat orbitRadius;
    GLfloat orbitSpeed;
    GLfloat rotationSpeed;
    GLfloat angle;
    GLfloat rotationAngle;
    Planet *child;
public:
    explicit Planet(CelestialBodyType type,GLint id ,GLfloat planetX, GLfloat planetY, GLfloat planetZ, GLfloat radius,
                    GLfloat orbitRadius, GLfloat orbitSpeed,
                    GLfloat rotationSpeed, Planet *child);

    void drawPlanet();

    void drawOrbit(GLfloat multiplier);

    void movePlanet();

    void rotatePlanet();
};

inline Planet::Planet(CelestialBodyType type,GLint id ,GLfloat planetX, GLfloat planetY, GLfloat planetZ, GLfloat radius,
                      GLfloat orbitRadius, GLfloat orbitSpeed,
                      GLfloat rotationSpeed, Planet *child) {
    this->type = type;
    this->id = id;
    this->planetX = planetX;
    this->planetY = planetY;
    this->planetZ = planetZ;
    this->radius = radius;
    this->orbitRadius = orbitRadius;
    this->orbitSpeed = orbitSpeed;
    this->rotationSpeed = rotationSpeed;
    this->child = child;

    this->angle = returnRandomFloatBetween(0, 60);
    this->rotationAngle = returnRandomFloatBetween(0, 60);
}

inline void Planet::drawPlanet() {
    glPushMatrix();

    if (id == 5) {
        glRotatef(angle, 0.0, 1.0, -1.0);
    } else if (type == satellite &&id == 1) {
        glRotatef(angle, 0.0, 0.1, 0.05);
    } else if (type == satellite && id == 2) {
        glRotatef(angle, 1.0, 0.5, 0.0);
    } else {
        glRotatef(angle, 0.0, 1.0, -0.5);
    }

    glTranslatef(planetX, planetY, planetZ);
    glRotatef(rotationAngle, 0.0, 1.0, 0.0);
    glScalef(radius, radius, radius);

    if (type == satellite) {
        glColor3f(0.5, 0.5, 0.5);
        glScalef(radius, radius, radius);
        glutSolidSphere(0.5, 100, 100);
    } else {
        glScalef(1 / radius, 1 / radius, 1 / radius);
        glColor3f(1.0, 1.0, 1.0);
        //glShadeModel(GL_SMOOTH);
        glBindTexture(GL_TEXTURE_2D, textureNames[id]);
        gluSphere(sphere, radius, 100, 100);
    }

    if (child != nullptr) {
        child->drawPlanet();
    }

    glPopMatrix();
}

inline void Planet::drawOrbit(GLfloat multiplier) {
    glPushMatrix();
    if (id == 5) {
        glRotatef(45, 1.0, 0.0, 0.0);
    } else {
        glRotatef(63, 1.0, 0.0, 0.0);
    }
    glScalef(orbitRadius * multiplier, orbitRadius * multiplier, orbitRadius * multiplier);
    glBegin(GL_POINTS);
    double ang1 = 0.0;
    for (int i = 0; i < 500; i++) {
        glVertex2d(cos(ang1), sin(ang1));
        ang1 += 2 * PI / 500;
    }
    glEnd();
    glPopMatrix();
}

inline void Planet::movePlanet() {
    angle += orbitSpeed;
    if (angle > 360) {
        angle -= 360;
    }

    if (child != nullptr) {
        child->movePlanet();
    }
}

inline void Planet::rotatePlanet() {
    rotationAngle += rotationSpeed;
    if (rotationAngle > 360) {
        rotationAngle -= 360;
    }

    if (child != nullptr) {
        child->rotatePlanet();
    }
}


