/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 */
#include "config.h"
#if CONFIG_USE_AUDIO==1

#ifndef _AUDIO_FILTER_H
#define _AUDIO_FILTER_H

#include "audio_status.h"
#include "audio_common.h"

class FilterResponse {
public:
    FilterResponse(bool success, const sample_data_t data)
        : success_(success), data_(data)
    {
    }

    bool IsSuccess() { return success_; }
    sample_data_t data() { return data_; }

private:
    bool success_;
    sample_data_t data_;
};

/**
 * 音频过滤基类
 * 
 * 用于音频数据处理、音频数据混合、音频数据特效等需要数据转换的场景
 * 即实现 音频数据A -> 音频数据B 的变换目标
 * 
 * 待实现
 */
class AudioFilter {
public:
    virtual FilterResponse* DoFilter(const sample_data_t data) = 0;
    
};

#endif // _AUDIO_FILTER_H

#endif //CONFIG_USE_AUDIO