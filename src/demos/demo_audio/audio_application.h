/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_AUDIO==1

#ifndef _MY_APPLICATION_H
#define _MY_APPLICATION_H

#include "src/framework/app/application.h"
#include "src/framework/app/device_state.h"
#include "src/framework/audio/audio_pipe.h"

#if CONFIG_USE_LVGL==1
#include "lvgl_audio_window.h"
#endif

class AudioApplication : public Application {
public:
    AudioApplication();
    ~AudioApplication();
    
    virtual void SetDeviceState(const DeviceState* state) override;

    const std::string& GetAppName() const override { return "DEMO_AUDIO"; }
    const std::string& GetAppVersion() const override { return "1.0.0"; }

protected:
    virtual void OnInit() override;
    virtual void OnLoop() override;

private:
    AudioPipe *pipe_ = nullptr;

#if CONFIG_USE_LVGL==1
    LvglAudioWindow* window_ = nullptr;
#endif
};

#endif //_AUDIO_APPLICATION_H

#endif 