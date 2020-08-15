#include "Recorder.h"

Recorder::Recorder(const Settings &settings)
    : fileName(settings.recorderParams.fileName)
{
    frames.reserve(static_cast<unsigned int>(settings.recorderParams.framesPerSecond * settings.recorderParams.totalSeconds) );
}

void Recorder::captureFrame(const QImage &frame)
{
    //frame.save(QString(QStringLiteral("/Users/jakubstawarczyk/renders/test_%1.jpg").arg(static_cast<int>(frames.size()) ) ));
    frames.push_back(frame);
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
