#ifndef ANIMATIONPART_H
#define ANIMATIONPART_H

#include <QVector3D>

class AnimationPart
{
public:

    int start;
    int end;
    QVector3D delta;

    AnimationPart();
    AnimationPart(QVector3D delta, int start, int end);
};

#endif // ANIMATIONPART_H
