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

    // Returns the time in ms taken up by one frame
    int InitAnimation::getFrameTime()
    {
        return this->frameTime;
    }

    // Returns info usefull for objects that perform init animations
    void InitAnimation::getFrameInfo(int &currentFrame, int &totalNumOfFrames)
    {
        currentFrame = this->currentFrame;
        totalNumOfFrames = this->totalNumOfFrames;
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