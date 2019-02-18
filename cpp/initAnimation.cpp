#include "initAnimation.h"

namespace DramaMask
{
    InitAnimation::InitAnimation(int frameRate, int TotalTime)
    {
        this->frameRate = frameRate;
        this->totalTime = totalTime;

        this->frameTime = 1000 / this->frameRate;
        this->totalNumOfFrames = ((double)totalTime / 1000) * frameRate;
        this->currentFrame = 0;
    }

    int InitAnimation::getFrameTime()
    {
        return this->frameTime;
    }

    // Returns true if the animation should keep going.
    // Returns false if the animation is done.
    bool InitAnimation::incrementFrame()
    {
        this->currentFrame++;

        if (this->currentFrame > this->totalNumOfFrames)
        {
            return false;
        }

        return true;
    }
}