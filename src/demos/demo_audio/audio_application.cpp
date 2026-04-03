/**
 * ESP32-Arduino-Framework
 * Arduino开发环境下适用于ESP32芯片系列开发板的应用开发框架。
 * 
 * Author: Billy Zhang（billy_zh@126.com）
 */
#include "config.h"
#if APP_DEMO_AUDIO==1

#include <Arduino.h>
#include <WiFi.h>
#include <string>
#include "audio_application.h"
#include "audio_state.h"
#include "src/framework/sys/log.h"
#include "src/framework/board/wifi_board.h"
#include "src/framework/audio/audio_codec.h"
#include "src/framework/lang/lang_zh_cn.h"
#include "src/framework/audio/source/audio_httpstream_source.h"
#include "src/framework/audio/input/audio_decode_input.h"
#include "src/framework/audio/output/audio_i2s_output.h"

#define TAG "AudioApplication"

// 开发板
#if BOARD_XPSTEM_S3_LCD_2_80 == 1
#include "src/boards/xpstem-s3-lcd-2.8/board_config.h"
#define I2S_BCLK    AUDIO_I2S_BCLK_PIN
#define I2S_LRC     AUDIO_I2S_WS_PIN
#define I2S_DAT    AUDIO_I2S_DOUT_PIN
#define I2S_MCLK    AUDIO_I2S_MCLK_PIN
#elif BOARD_XPSTEM_S3_ELECTRONIC_SUIT == 1
#include "src/boards/xpstem-s3-electronic-suit/board_config.h"
#define I2S_BCLK    AUDIO_SPK_BCLK_PIN
#define I2S_LRC     AUDIO_SPK_LRC_PIN
#define I2S_DAT    AUDIO_SPK_DAT_PIN   
#elif BOARD_XPSTEM_JC4827W543 == 1
#include "src/boards/xpstem-jc4827w543/board_config.h"
#define I2S_BCLK    SPECK_BCLK_PIN
#define I2S_LRC     SPECK_LRCLK_PIN
#define I2S_DAT    SPECK_DIN_PIN   
#endif

// 图形化库
#if CONFIG_USE_LVGL==1
#include "src/framework/display/lvgl_display.h"
#endif

#if CONFIG_USE_GFX_LIBRARY==1
#if CONFIG_USE_LVGL==1

#else
#include "src/framework/display/gfx_display.h"
#include "src/framework/display/gfx_window.h"
#endif //CONFIG_USE_LVGL
#endif //CONFIG_USE_GFX_LIBRARY

static const std::string kSsid = "ssid";
static const std::string kPassword = "password";

static const std::string mp3_url = "http://music.163.com/song/media/outer/url?id=1980818176.mp3";

void* create_application() {
    return new AudioApplication();
}

AudioApplication::AudioApplication() : Application() { 
#if CONFIG_USE_LVGL==1
    window_ = new LvglAudioWindow();
    LvglDisplay* disp = static_cast<LvglDisplay*>(Board::GetInstance().GetDisplay());
    disp->SetWindow(window_);
#endif
}

AudioApplication::~AudioApplication() {
   

}

void AudioApplication::OnInit() {
    // 连接WiFi
    WiFi.mode(WIFI_STA);
    WifiBoard* wifi_board = static_cast<WifiBoard*>(&Board::GetInstance());    
#if CONFIG_WIFI_CONFIGURE_ENABLE==1
    if (!wifi_board->StartNetwork(30000)) {
#else
    if (!wifi_board->StartNetwork(kSsid, kPassword, 30000)) {
#endif
        Log::Info(TAG, "WiFi连接失败。");
        SetDeviceState(kDeviceStateWarning);
        //ShowMessage("WiFi连接失败。");
        return;
    }


#if CONFIG_USE_LVGL==1
    window_->SetTitle("music player");
#else CONFIG_USE_GFX_LIBRARY==1
    GfxWindow* window = ((GfxDisplay*)board.GetDisplay())->GetWindow();
    window->SetText("music player");
#endif

    Log::Info(TAG, "play %s", mp3_url.c_str());
    
    // input
    AudioHttpStreamSource *http_source = new AudioHttpStreamSource(mp3_url);
    AudioDecodeInput *input = new AudioDecodeInput(http_source, "mp3");

    // output
    Board& board = Board::GetInstance();
    AudioCodec *codec = board.GetAudioCodec();
    codec->EnableOutput(true);
    AudioI2sOutput *output = new AudioI2sOutput(codec);

    pipe_ = new AudioPipe();
    pipe_->Start(input, output);
    
    SetDeviceState(kDeviceStatePlaying);
}

void AudioApplication::SetDeviceState(const DeviceState* state) {
 
    Application::SetDeviceState(state);

    auto& board = Board::GetInstance();
    auto display = board.GetDisplay();

    if (state == kDeviceStatePlaying) {
        display->SetStatus(Lang::Strings::PLAYING);
    }

}

void AudioApplication::OnLoop() {
    
    vTaskDelay(pdMS_TO_TICKS(1));
}

#endif 