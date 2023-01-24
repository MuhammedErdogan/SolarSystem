#include <GL/freeglut.h>

#include "planet.h"
#include "utils.h"

#define WINDOW_WIDTH 900
#define WINDOW_HEIGHT 900

#define PLANET_SCALE 0.175
float angle = 0.0f;
char *filenameArray[9] = {
        (char *) "D:/OpenGL Projects/Solar System/textures/mercury.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/venus.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/earth.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/mars.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/jupiter.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/saturn.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/uranus.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/neptune.bmp",
        (char *) "D:/OpenGL Projects/Solar System/textures/sun.bmp"
};

Planet mercury(planet,0, 1.5, 0, 0, 0.08, 1.475, 2.0, 1.0, nullptr);
Planet venus(planet,1, 2.0, 0, 0, 0.1, 2.0, 0.9, 1.0, nullptr);
Planet moon(satellite,1, 0.5, 0, 0, 0.3, 0.0, 2.0, 1.0, nullptr);
Planet earth(planet,2, 2.5, 0, 0, 0.23, 2.5, 0.7, 1.0, &moon);
Planet mars(planet,3, -3.0, 0, 0, 0.17, 3.0, 0.05, 1.0, nullptr);
Planet jupiterSatellite(satellite,-2, 0.0, 0.0, 0.6, 0.33, 0.0, 2.0, 1.0, nullptr);
Planet jupiter(planet,4, -4.0, 0, 0, 0.5, 4.0, 0.2, 1.0, &jupiterSatellite);
Planet saturn(planet,5, -5.0, 0.0, 0.0, 0.4, 5.0, 0.1, 1.0, nullptr);
Planet neptune(planet,6, -5.7, 0, 0, 0.2, 5.25, 0.02, 1.0, nullptr);
Planet uranus(planet,7, 5.2, 0, 0, 0.23, 5.65, 0.05, 1.0, nullptr);

Planet *planets[8] = {&mercury, &venus, &earth, &mars, &jupiter, &saturn, &neptune, &uranus};

GLfloat ambientParams[] = {0.0, 0.0, 0.0, 1.0};
GLfloat diffuseParams[] = {1.0, 1.0, 1.0, 1.0};
GLfloat specularParams[] = {0.0, 0.0, 0.0, 1.0};

void lightning() {
    GLfloat yellow[] = {0.7f, 0.2f, 0.0f, 1.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, yellow);
    glMaterialfv(GL_FRONT, GL_SPECULAR, yellow);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, yellow);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT7);

    glLightfv(GL_LIGHT7, GL_AMBIENT, ambientParams);
    glLightfv(GL_LIGHT7, GL_DIFFUSE, diffuseParams);
    glLightfv(GL_LIGHT7, GL_SPECULAR, specularParams);
}

void displayInit() {
    glEnable(GL_TEXTURE_2D);
    glGenTextures(9, textureNames);
    for (int i = 0; i < 9; i++) {
        glBindTexture(GL_TEXTURE_2D, textureNames[i]);
        loadTextureFromFile(filenameArray[i]);
    }

    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricTexture(sphere, GL_TRUE);
    gluQuadricNormals(sphere, GLU_FLAT);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(2.0);
    glLineWidth(4.0);
}

void draw_planets() {
    glScalef(PLANET_SCALE, PLANET_SCALE, PLANET_SCALE);
    for (auto &planet: planets) {
        planet->drawPlanet();
    }
}

void draw_orbits() {
    glColor3f(1, 1, 1);
    for (auto &planet: planets) {
        planet->drawOrbit(PLANET_SCALE);
    }
}

void draw_sun() {
    glPushMatrix();
    angle += .2;
    glRotatef(angle, 0.0, 1.0, -1.0);
    glScalef(0.1, 0.1, 0.1);
    GLfloat qPos[] = {0, 0, 0, 1};
    glLightfv(GL_LIGHT7, GL_POSITION, qPos);
    GLfloat yellow[] = {0.7f, 0.2f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, yellow);
    glBindTexture(GL_TEXTURE_2D, textureNames[8]);
    gluSphere(sphere, 1, 100, 100);
    GLfloat black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, black);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    draw_orbits();

    glLoadIdentity();
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    draw_sun();
    draw_planets();

    glPopMatrix();

    glFlush();
}


void idle([[maybe_unused]] int value) {
    for (auto &planet: planets) {
        planet->movePlanet();
    }
    for (auto &planet: planets) {
        planet->rotatePlanet();
    }

    glutPostRedisplay();
    glutTimerFunc(30, idle, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '1':
            ambientParams[0] = 0.0;
            ambientParams[1] = 0.0;
            ambientParams[2] = 0.0;
            diffuseParams[0] = 0.0;
            diffuseParams[1] = 0.0;
            diffuseParams[2] = 0.0;
            specularParams[0] = 1.0;
            specularParams[1] = 1.0;
            specularParams[2] = 1.0;
            break;
        case '2':
            ambientParams[0] = 0.0;
            ambientParams[1] = 0.0;
            ambientParams[2] = 0.0;
            diffuseParams[0] = 1.0;
            diffuseParams[1] = 1.0;
            diffuseParams[2] = 1.0;
            specularParams[0] = 0.0;
            specularParams[1] = 0.0;
            specularParams[2] = 0.0;
            break;
        case '3':
            ambientParams[0] = 1.0;
            ambientParams[1] = 1.0;
            ambientParams[2] = 1.0;
            diffuseParams[0] = 0.0;
            diffuseParams[1] = 0.0;
            diffuseParams[2] = 0.0;
            specularParams[0] = 0.0;
            specularParams[1] = 0.0;
            specularParams[2] = 0.0;
            break;
        case 'q':
            exit(0);
        default:
            break;
    }
    lightning();
    glutPostRedisplay();
}


int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(400, 100);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("The Solar System");
    lightning();
    displayInit();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, idle, 0);
    glutMainLoop();
    return 0;
}
