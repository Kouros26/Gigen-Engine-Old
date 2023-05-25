#include "AudioSource.h"
#include <irrKlang.h>
#include "Camera.h"

using namespace irrklang;

AudioSource::AudioSource(GameObject* gameObject) : Component(gameObject)
{
    if (!engine)
    {
        engine = createIrrKlangDevice();
    }
}

AudioSource::~AudioSource()
{
    if (sound)
    {
        sound->stop();
        sound->drop();
    }
}

void AudioSource::Start()
{
    if (playOnStart)
    {
        Play();
    }
}

void AudioSource::Update(float pDeltaTime)
{
    if (sound)
    {
        if (!is2D)
        {
            lm::FVec3 pos = gameObject->GetTransform().GetWorldPosition();
            sound->setPosition({ pos.x, pos.y, pos.z });
        }

        if (sound->isFinished())
            isPlaying = false;
    }
}

Component* AudioSource::Clone(GameObject* newGameObject)
{
    const auto newAudio = new AudioSource(newGameObject);
    newAudio->SetAudio(audioPath);
    newAudio->SetIs2D(is2D);
    newAudio->SetIsLooping(loop);
    newAudio->SetMinDistance(minDistance);
    newAudio->SetPlayOnStart(playOnStart);
    newAudio->SetVolume(volume);
    return newAudio;
}

std::string AudioSource::GetType()
{
    const std::string type(typeid(this).name());
    return type.substr(6, type.size() - 16);
}

void AudioSource::UpdateAudioEngine(Camera* cam)
{
    if (engine)
    {
        lm::FVec3 pos = cam->GetTransform().GetWorldPosition();
        lm::FVec3 dir = -cam->GetFront();
        engine->setListenerPosition(
            { pos.x, pos.y, pos.z },
            { dir.x, dir.y, dir.z }
        );
    }
}

void AudioSource::Clear()
{
    if (engine)
        engine->drop();
}

void AudioSource::Play()
{
    isPlaying = true;
    if (is2D)
    {
        sound = engine->play2D(audioPath.c_str(), loop, false, true);
        if (sound)
            sound->setVolume(volume);
    }
    else
    {
        lm::FVec3 pos = gameObject->GetTransform().GetWorldPosition();
        sound = engine->play3D(audioPath.c_str(), { pos.x, pos.y, pos.z }, loop, false, true);
        if (sound)
        {
            sound->setVolume(volume);
            sound->setMinDistance(minDistance);
        }
    }
}

void AudioSource::Pause()
{
    isPlaying = false;
    if (sound)
        sound->setIsPaused(true);
}

void AudioSource::UnPause()
{
    isPlaying = true;
    if (sound)
        sound->setIsPaused(false);
}

void AudioSource::Stop()
{
    isPlaying = false;
    if (sound)
        sound->stop();
}

void AudioSource::SetAudio(const std::string& path)
{
    audioPath = path;
}

void AudioSource::SetAudioWithLuaPath(const std::string& path)
{
    audioPath = "../../../Resources/Editor/" + path;
}

std::string AudioSource::GetAudio()
{
    return audioPath;
}

bool AudioSource::GetPlayOnStart() const
{
    return playOnStart;
}

void AudioSource::SetPlayOnStart(bool b)
{
    playOnStart = b;
}

bool AudioSource::GetIsLooping() const
{
    return loop;
}

void AudioSource::SetIsLooping(bool b)
{
    loop = b;
    if (sound)
        sound->setIsLooped(loop);
}

bool AudioSource::GetIsPlaying() const
{
    return isPlaying;
}

float AudioSource::GetVolume() const
{
    return volume;
}

void AudioSource::SetVolume(float f)
{
    volume = f;
    if (sound)
        sound->setVolume(volume);
}

float AudioSource::GetMinDistance() const
{
    return minDistance;
}

void AudioSource::SetMinDistance(float f)
{
    minDistance = f;
    if (sound && !is2D)
        sound->setMinDistance(minDistance);
}

bool AudioSource::GetIs2D() const
{
    return is2D;
}

void AudioSource::SetIs2D(bool b)
{
    is2D = b;
}

void AudioSource::Set3D(bool b)
{
    is2D = !b;
}