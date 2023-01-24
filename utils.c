#ifndef CO_OP_BALL_GAME_UTILS_H
#define CO_OP_BALL_GAME_UTILS_H

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#endif

#include "Texture.h"
#include <random>

GLUquadricObj* sphere = nullptr;

std::string intToString(int value) {
    std::string str = std::to_string(value);
    return str;
}

void resetRandomSeedWith() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1000000);
    srand(dis(gen));
}

GLfloat returnRandomFloatBetween(GLfloat min, GLfloat max) {
    resetRandomSeedWith();
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::uniform_real_distribution<GLfloat> uni(min, max);
    return uni(rng);
}

void loadTextureFromFile(char *filename)
{
    glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST);

    Texture theTexMap(filename);

    // Pixel alignment: each row is word aligned.  Word alignment is the default.
    // glPixelStorei(GL_UNPACK_ALIGNMENT, 4);

    // Set the interpolation settings to best quality.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB,
                      (GLsizei)theTexMap.GetNumCols(), (GLsizei)theTexMap.GetNumRows(),
                      GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData() );
}

static GLuint textureNames[9];

#endif //CO_OP_BALL_GAME_UTILS_H

