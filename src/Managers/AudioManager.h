#pragma once
#include <psp2/audioout.h>
#include <psp2/io/fcntl.h>
#include <string>
#include <map>
#include <vector>
#include <psp2/kernel/threadmgr.h> 
#include <psp2/kernel/clib.h>    

struct WavFile
{
    int sampleRate;
    int numChannels;
    int bitsPerSample;
    std::vector<char> data;
};

class AudioManager;

struct ThreadArgs
{
  AudioManager* instance;
  std::string id;

  ThreadArgs(AudioManager* pInstance, std::string pId)
  {
    instance = pInstance;
    id = pId;
  }
};

class AudioManager
{
    static AudioManager *mInstance;
    std::map<std::string, WavFile> mAudioFiles;
    int mAudioPort;                                      
    static int PlaybackThread(SceSize size, void *data); 
    AudioManager();
    ~AudioManager();

public:
    static AudioManager &GetInstance();
    bool LoadWav(const std::string &id, const std::string &filepath);
    void PlayAudio(const std::string &id);
};