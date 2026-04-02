/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_PIPE_H
#define _AUDIO_PIPE_H

#include <functional>
#include <string>
#include <vector>
#include <freertos/FreeRTOS.h>

#include "audio_input.h"
#include "audio_output.h"
#include "audio_filter.h"
#include "audio_status.h"

enum PipeAction {
    Begin,
    Processing,
    Ended,
    Error = 9,
};

/**
 * 音频管道
 */
class AudioPipe {
public:
    AudioPipe() { }

    virtual void Start(AudioInput *input,  AudioOutput *output);
    virtual void Stop();

    void MetadataCallback(const char *tag, const char *type, const char *text);
    void StatusCallback(const char *tag, int code, const char *text);
    
    const std::string& last_error() const { return last_error_; }

    void SetFilterList(std::vector<AudioFilter*> filter_list)
    {
        filter_list_ = filter_list;
    }

    void SetPipeListener(std::function<void(PipeAction)> listener)
    {
        pipe_listener_ = listener;
    }

    void SetInputDataListener(std::function<void(const sample_data_t)> listener)
    {
        input_data_listener_ = listener;
    }

    void SetOutputDataListener(std::function<void(const sample_data_t)> listener)
    {
        output_data_listener_ = listener;
    }

protected:
    void Execute();
    
private:
    volatile bool running_;

    AudioInput *input_ = nullptr;
    AudioOutput *output_ = nullptr;

    TaskHandle_t task_handle_;
    
    std::string last_error_ = "";

    std::vector<AudioFilter*> filter_list_;
    std::function<void(PipeAction)> pipe_listener_;
    std::function<void(sample_data_t)> input_data_listener_;
    std::function<void(sample_data_t)> output_data_listener_;
};

#endif // _AUDIO_PIPE_H

#endif 