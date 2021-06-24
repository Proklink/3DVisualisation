#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "scene.h"

class Controller
{
public:
    Controller(Scene *scene);
    Scene *scene;

    void startAnimation(int xS, int xE, int yS, int yE, int zS, int zE, float dS);
    void startStepAnimation(int xS, int xE, int yS, int yE, int zS, int zE, float dS);
    void stopAnimation();

};

#endif // CONTROLLER_H
