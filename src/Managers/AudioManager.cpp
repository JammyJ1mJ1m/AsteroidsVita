#include "AudioManager.h"
#include <cstring>
#include <iostream>
#include <psp2/kernel/sysmem.h>

AudioManager *AudioManager::mInstance = nullptr;

AudioManager::AudioManager()
{
    mAudioPort = sceAudioOutOpenPort(SCE_AUDIO_OUT_PORT_TYPE_BGM, 256, 44100, SCE_AUDIO_OUT_MODE_STEREO);
    if (mAudioPort < 0)
    {
        std::cerr << "Failed to open audio port: " << mAudioPort << std::endl;
    }
}

AudioManager::~AudioManager()
{
    sceAudioOutReleasePort(mAudioPort);
}

AudioManager &AudioManager::GetInstance()
{
    if (!mInstance)
    {
        mInstance = new AudioManager();
    }
    return *mInstance;
}

bool AudioManager::LoadWav(const std::string &id, const std::string &filepath)
{
    int fd = sceIoOpen(filepath.c_str(), SCE_O_RDONLY, 0777);
    if (fd < 0)
    {
        std::cerr << "Failed to open WAV file: " << filepath << std::endl;
        return false;
    }

    char header[44];
    sceIoRead(fd, header, 44);

    // parses the header
    if (std::memcmp(header, "RIFF", 4) != 0 || std::memcmp(header + 8, "WAVE", 4) != 0)
    {
        std::cerr << "Invalid WAV file: " << filepath << std::endl;
        sceIoClose(fd);
        return false;
    }

    int sampleRate = *reinterpret_cast<int *>(header + 24);
    int numChannels = *reinterpret_cast<short *>(header + 22);
    int bitsPerSample = *reinterpret_cast<short *>(header + 34);
    int dataSize = *reinterpret_cast<int *>(header + 40);

    // reads the audio data
    std::vector<char> data(dataSize);
    sceIoRead(fd, data.data(), dataSize);
    sceIoClose(fd);

    WavFile wavFile = {sampleRate, numChannels, bitsPerSample, std::move(data)};
    mAudioFiles[id] = std::move(wavFile);

    return true;
}

static ThreadArgs args = ThreadArgs(nullptr, "");

void AudioManager::PlayAudio(const std::string &id)
{
    auto it = mAudioFiles.find(id);
    if (it == mAudioFiles.end())
    {
        std::cerr << "Audio ID not found: " << id << std::endl;
        return;
    }

    args = ThreadArgs(&GetInstance(), id);

    SceUID threadID = sceKernelCreateThread(
        "PlaybackThread",
        PlaybackThread, // Use the static method
        0x64,           // Thread priority (default)
        0x1000,         // 64KB stack size
        0,
        0,
        nullptr);

    if (threadID < 0)
    {
        std::cerr << "Failed to create playback thread: " << threadID << std::endl;
        return;
    }

    int result = sceKernelStartThread(threadID, 0, nullptr);
    if (result < 0)
    {
        std::cerr << "Failed to start playback thread: " << result << std::endl;
        sceKernelDeleteThread(threadID);
    }
}

void PrintFreeMemoryInfo()
{
    SceKernelFreeMemorySizeInfo info = {0};
    info.size = sizeof(SceKernelFreeMemorySizeInfo);

    int result = sceKernelGetFreeMemorySize(&info);

    if (result < 0)
    {
        std::cerr << "Failed to get free memory info. Error code: " << result << std::endl;
        return;
    }

    std::cout << "====== MEMORY STATUS =====" << std::endl;
    std::cout << "mem size: " << info.size << std::endl;
    std::cout << "mem cdram: " << info.size_cdram << std::endl;
}

int AudioManager::PlaybackThread(SceSize, void *)
{

    PrintFreeMemoryInfo();

    ThreadArgs args = ::args;

    try
    {
        AudioManager *audioManager = args.instance;
        const std::string &audioID = args.id;

        auto it = audioManager->mAudioFiles.find(audioID);
        if (it == audioManager->mAudioFiles.end())
        {
            std::cerr << "Audio ID not found: " << audioID << std::endl;
            return -1;
        }

        WavFile &wavFile = it->second;

        int samplesPerFrame = 256;
        size_t sampleSize = wavFile.bitsPerSample / 8;
        size_t frameSize = samplesPerFrame * sampleSize * wavFile.numChannels;

        // loops through and plays the audio
        for (size_t i = 0; i < wavFile.data.size(); i += frameSize)
        {
            size_t chunkSize = std::min(frameSize, wavFile.data.size() - i);

            // handle buffer alignment popping sound
            // fill remianing space with empty space
            if (chunkSize < frameSize)
            {

                std::vector<char> paddedFrame(frameSize, 0);
                std::memcpy(paddedFrame.data(), wavFile.data.data() + i, chunkSize);
                sceAudioOutOutput(audioManager->mAudioPort, paddedFrame.data());
            }
            else
            {
                sceAudioOutOutput(audioManager->mAudioPort, wavFile.data.data() + i);
            }
        }

        sceKernelExitDeleteThread(0);
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Exception in thread: " << e.what() << std::endl;

        return -1;
    }

    return 0;
}