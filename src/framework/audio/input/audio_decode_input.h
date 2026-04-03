/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_DECODE_INPUT_H
#define _AUDIO_DECODE_INPUT_H

#include <string>
#include "../audio_input.h"
#include "../audio_source.h"
#include "../audio_decoder.h"

/**
 * 音频解码输入
 */
class AudioDecodeInput : public AudioInput {
public:
    AudioDecodeInput(AudioSource *source, const std::string& in_format);
    virtual ~AudioDecodeInput();

    virtual bool Init() override;
    virtual sample_data_t Handle() override;
    virtual bool Close() override;
    virtual bool isEOF() override;

    virtual const char* Tag() override { return "DecoderInput"; };
    
    virtual void SetMetadataCallback(AudioStatus::MetadataCallbackFn fn, void *data) override {
        status.RegisterMetadataCallback(fn, Tag(), data);
        source_->SetMetadataCallback(fn, data);
    }

    virtual void SetStatusCallback(AudioStatus::StatusCallbackFn fn, void *data) override { 
        status.RegisterStatusCallback(fn, Tag(), data);
        source_->SetStatusCallback(fn, data);
    }

private:
    AudioSource *source_;
    AudioDecoder *decoder_;
    const std::string in_format_;

};

#endif // _AUDIO_DECODE_INPUT_H

#endif //CONFIG_USE_AUDIO