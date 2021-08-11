#ifndef __AUDIO_PROCESSING_MODULE__
#define __AUDIO_PROCESSING_MODULE__

#include "include/modules/audio_processing/include/audio_processing.h"
#include "include/common_audio/channel_buffer.h"

namespace std
{
    class AudioProcessing;
    class StreamConfig;
    template <template T> class ChannelBuffer;
    
} // namespace std


class AudioProcessingModule
{
public:
    AudioProcessingModule(int enabled_ns=0, int enable_aec=0, int enable_agc=0, bool enable_vad=false);
    void set_ns_level(int ns_level);
    void set_aec_type(bool enable_mobile_mode=false);
    void set_agc_type(bool aec_type);
    void process_stream(const int stream);
    void process_reverse_stream();
    void set_system_delay(int delay=0);

    ~AudioProcessingModule();
private:
    static const int default_rate = 16000;
    static const int default_channel = 1;
    static const int frame_size_ms = 10;
    int system_delay = 0;

    webrtc::AudioProcessing* apm;
    webrtc::AudioProcessing::Config* config;
    webrtc::StreamConfig* near_end_config;
    webrtc::StreamConfig* far_end_config;
    int16_t* near_end_buf;
    float* near_end_buf_f;
    int16_t* far_end_buf;
    float* far_end_buf_f;
    webrtc::ChannelBuffer<float> *near_end_cbuf;
    webrtc::ChannelBuffer<float> *far_end_cbuf;


};
class StreamConfig;
template <template T> classChannelBuffer;

#endif //__AUDIO_PROCESSING_MODULE_H__