#pragma once
#include "Component.h"

class Camera;

namespace irrklang
{
    class ISoundEngine;
    class ISound;
}

class AudioSource : public Component
{
public:
    AudioSource(GameObject* gameObject);
    ~AudioSource() override;

    virtual void Start() override;
    virtual void Update(float pDeltaTime) override;
    virtual Component* Clone(GameObject* newGameObject) override;

    virtual std::string GetType() override;

    static void UpdateAudioEngine(Camera* cam);
    static void Clear();

    void Play();
    void Pause();
    void UnPause();
    void Stop();

    void SetAudio(const std::string& path);
    void SetAudioWithLuaPath(const std::string& path);
    std::string GetAudio();

    [[nodiscard]] bool GetPlayOnStart() const;
    void SetPlayOnStart(bool b);

    [[nodiscard]] bool GetIsLooping() const;
    void SetIsLooping(bool b);

    [[nodiscard]] bool GetIsPlaying() const;

    [[nodiscard]] float GetVolume() const;
    void SetVolume(float f);

    [[nodiscard]] float GetMinDistance() const;
    void SetMinDistance(float f);

    [[nodiscard]] bool GetIs2D() const;
    void SetIs2D(bool b);

    void Set3D(bool b);
private:
    std::string audioPath;

    bool is2D = false;
    bool playOnStart = true;
    bool loop = true;
    bool isPlaying = false;
    float volume = 1;
    float minDistance = 5.0f;

    irrklang::ISound* sound = nullptr;
    inline static irrklang::ISoundEngine* engine;
};