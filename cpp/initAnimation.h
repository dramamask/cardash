#ifndef INITANIMATION_H
#define INITANIMATION_H

namespace DramaMask
{
    class InitAnimation
    {
        public:
            /**
             * frameRate is the number of frames per second during the initialization
             * totalTime is the total time in ms that the initialization will last 
             */
            InitAnimation(int frameRate, int totalTime, int initialWaitTime);

            // Returns the time each frame lasts, in ms
            int getFrameTime();

            // Returns the current frame
            void getFrameInfo(int &currentFrame, int &totalNumOfFrames);

            // Call on timer callback. Returns false if initialization is done.
            bool onTimer();

        private:
            int frameRate; // frames per second
            int totalTime; // Total animation time, after the initial wiat time (ms)
            int initialWaitTime; // Time to wait before starting the animation (ms)
            
            int totalNumOfFrames; // Total number of frames during the animation
            int currentFrame; // Current frame
            int frameTime; // Number of ms per frame

            int currentWaitTime; // Time we have currently been waiting to start animation
    };
}

#endif