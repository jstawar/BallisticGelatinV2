#ifndef RECORDER_H
#define RECORDER_H

#include "Settings.h"

#include <string>
#include <vector>

// TODO - this should use some external lib to create a AVI (?) file on the fly
// read this: https://stackoverflow.com/questions/34511312/how-to-encode-a-video-from-several-images-generated-in-a-c-program-without-wri
class Recorder
{
private:
    std::string fileName;
public:
    Recorder(const Settings &settings);
    void captureFrame();
};

#endif // RECORDER_H
