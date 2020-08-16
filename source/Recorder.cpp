#include "Recorder.h"

Recorder::Recorder(const Settings &settings)
    : settings(settings),
      fileName(settings.recorderParams.fileName),
      frameNum(0)
{
    frames.reserve(static_cast<unsigned int>(settings.recorderParams.framesPerSecond * settings.recorderParams.totalSeconds) );
}

void Recorder::captureFrame(const QImage &frame)
{
    if(settings.recorderParams.streamOnTheFly)
        frame.save(QString(QStringLiteral("%1_%2.jpg").arg(fileName.c_str(), QString("%1").arg(static_cast<int>(frameNum) ) ) ));

    frames.push_back(frame);
    frameNum++;
}

void Recorder::save() const
{
    // save the frames
    for(unsigned int i = 0 ; i < frames.size() ; i++)
    {
       // QString name(QString(QStringLiteral("%1_%2.jpg").arg(fileName.c_str(), static_cast<int>(i) ) ) );
       // frames[i].save(name);
    }
}

Recorder::~Recorder()
{
    // TODO - make sure all is saved
}
