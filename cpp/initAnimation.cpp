#include "initAnimation.h"

#include <math.h>

namespace DramaMask
{
    InitAnimation::InitAnimation(int frameRate, int totalTime,int initialWaitTime)
    {
        this->frameRate = frameRate;
        this->totalTime = totalTime;
        this->initialWaitTime = initialWaitTime;

        this->frameTime = 1000 / this->frameRate;
        this->totalNumOfFrames = ((double)totalTime / 1000) * (double)frameRate;
        this->currentFrame = 0;
        this->currentWaitTime = 0;
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
    bool InitAnimation::onTimer()
    {
        // Handle the initial wait time       
        if (this->currentWaitTime < this->initialWaitTime) {
            this->currentWaitTime += this->frameTime;
            return true;
        }

        // Increment the current frame, and check if we're done
        this->currentFrame++;

        if (this->currentFrame > this->totalNumOfFrames)
        {
            return false;
        }

        return true;
    }
}