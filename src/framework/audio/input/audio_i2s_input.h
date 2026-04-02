/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_I2S_INPUT_H
#define _AUDIO_I2S_INPUT_H

#include "../audio_codec.h"
#include "../audio_input.h"

/**
 * I2s设备输入
 */
class AudioI2sInput : public AudioInput {
public:
    AudioI2sInput(AudioCodec *codec, uint16_t samples_msec) : codec_(codec), samples_msec_(samples_msec) {  }
    virtual ~AudioI2sInput() {  Close(); }

    virtual bool Init() override;
    virtual sample_data_t Handle() override;
    virtual bool Close() override;
    virtual bool isEOF() override;

    uint32_t duration_ms() { return duration_msec_; }
    
    virtual const char* Tag() override { return "I2sInput"; };

private:
    AudioCodec *codec_;
    uint16_t samples_msec_;
    int16_t *samples_buf_;
    uint32_t buff_len_;
    uint32_t duration_msec_ = 0;
};

#endif // _AUDIO_I2S_INPUT_H

#endif //CONFIG_USE_AUDIO