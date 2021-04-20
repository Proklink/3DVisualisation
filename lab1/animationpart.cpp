#include "animationpart.h"

AnimationPart::AnimationPart()
{

}

AnimationPart::AnimationPart(QVector3D delta, int start, int end) {
    this->delta = delta;
    this->start = start;
    this->end = end;
}
