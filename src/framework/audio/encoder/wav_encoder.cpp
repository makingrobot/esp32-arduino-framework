/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_AUDIO_CODER_WAV==1

#include <Arduino.h>
#include "wav_encoder.h"
#include "wav_header.h"

WavEncoder::WavEncoder()
{

}

WavEncoder::~WavEncoder()
{

}

bool WavEncoder::Init()
{
    return true;
}

sample_data_t WavEncoder::Encode(const sample_data_t data)
{
    return data;
}

void WavEncoder::GetHeaderData(uint8_t *header, uint32_t data_len, audio_config_t config) const
{
    const pcm_wav_header_t wav_header = PCM_WAV_HEADER_DEFAULT(data_len, 
        (uint8_t)config.output_bits, (uint32_t)config.output_rate, (uint8_t)config.output_channels);

    memcpy(header, &wav_header, PCM_WAV_HEADER_SIZE);
}

#endif