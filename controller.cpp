#include "controller.h"

Controller::Controller(Scene *scene)
{
    this->scene = scene;
}

void verifyBounds(int *xStart, int *xEnd, int *yStart, int *yEnd, int *zStart, int *zEnd) {
    if (*xStart > *xEnd) {
        int temp = *xEnd;
        *xEnd = *xStart;
        *xStart = temp;
    }
    if (*zStart > *zEnd) {
        int temp = *zEnd;
        *zEnd = *zStart;
        *zStart = temp;
    }
    if (*yStart < *yEnd) {
        int temp = *yEnd;
        *yEnd = *yStart;
        *yStart = temp;
    }
}

void Controller::startAnimation(int xS, int xE, int yS, int yE, int zS, int zE, float dS) {
    if (scene->knife->knifeTransform->translation() != scene->knife->basePosition)
        stopAnimation();
    scene->discretShift = dS;
    verifyBounds(&xS, &xE, &yS, &yE, &zS, &zE);
    scene->setAnimationBounds(xS, xE, yS, yE, zS, zE);
    scene->createAnimationParts();
    scene->startAutoAnimation();
}

void Controller::stopAnimation(){
    scene->tmr->stop();
    scene->knife->knifeTransform->setTranslation(scene->knife->basePosition);
    scene->discretShift = 0;
    scene->elapsedSteps = 0;
    scene->currentPart = 0;
    scene->isStepAnimationNow = false;
    scene->isAutoAnimationNow = false;
    for (int i = 0; i < scene->animationParts.size(); i++) {
        delete scene->animationParts[i];
        scene->animationParts.erase(scene->animationParts.begin());
        i--;
    }

    for (int i = 0; i < scene->billet->billet.size(); i++)
        for (int j = 0; j < scene->billet->billet[i].size(); j++)
            for (int k = 0; k < scene->billet->billet[i][j].size(); k++)
                scene->billet->billet[i][j][k]->setEnabled(true);

}

void Controller::startStepAnimation(int xS, int xE, int yS, int yE, int zS, int zE, float dS) {


    if (scene->isAutoAnimationNow) {
        scene->tmr->stop();
        scene->isStepAnimationNow = true;
        scene->isAutoAnimationNow = false;
    }

    if (!scene->isStepAnimationNow) {
        scene->discretShift = dS;
        verifyBounds(&xS, &xE, &yS, &yE, &zS, &zE);
        scene->setAnimationBounds(xS, xE, yS, yE, zS, zE);
        scene->createAnimationParts();
        scene->isStepAnimationNow = true;
    }

    scene->startStepAnimation();
}
