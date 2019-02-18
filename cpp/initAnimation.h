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
            InitAnimation(int frameRate, int totalTime);

            // Returns the time each frame lasts, in ms
            int getFrameTime();

            // Returns the current frame
            void getFrameInfo(int &currentFrame, int &totalNumOfFrames);

            // Increments frame. Returns false if initialization is done.
            bool incrementFrame();

        private:
            int frameRate; // frames per second
            int totalTime; // ms
            
            int totalNumOfFrames; // Total number of frames during the animation
            int currentFrame; // Current frame
            int frameTime; // Number of ms per frame
    };
}

#endif