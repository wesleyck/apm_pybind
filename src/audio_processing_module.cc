#include <iostream>
#include <string>
#include "pybind11/pybind11.h"
#include "audio_processing_module.h"

namespace py = pybind11;

AudioProcessingModule::AudioProcessingModule(int enabled_ns, int enable_aec, int enable_agc, bool enable_vad)
{
    
    apm = webrtc::AudioProcessingBuilder().Create();
    config = new webrtc::AudioProcessing::Config();

    if(enabled_ns)
    {
        config->noise_suppression.enabled = true;
        //config->noise_suppression.level = config->noise_suppression.kVeryHigh;
    }

    if (enable_aec){
        config->echo_canceller.enabled = true;
        if(enable_aec == 2)
        {
            config->echo_canceller.mobile_mode = true;
        }
    }

    if (enable_agc)
    {
        config->gain_controller1.enabled = true;
        config->gain_controller1.mode = config->gain_controller1.kFixedDigital;
        config->gain_controller1.analog_level_minimum = 0;
        config->gain_controller1.analog_level_maximum = 255;
        //config.gain_controller2.enabled = true;
    }

    

    //config.high_pass_filter.enabled = true;

    //config.voice_detection.enabled = true;

    apm->ApplyConfig(config);

    //apm->noise_reduction()->set_level(kHighSuppression);
    //apm->noise_reduction()->Enable(true);

    near_end_config = new webrtc::StreamConfig(default_rate, default_channel, false);
    far_end_config = new webrtc::StreamConfig(default_rate, default_channel, false);

    int num_frames = near_end_config->num_frames();
    near_end_buf = new float[num_frames * default_channel];
    far_end_buf = new float[num_frames * default_channel];
    near_end_cbuf = new webrtc::ChannelBuffer<float>(num_frames, default_channel);
    far_end_cbuf = new webrtc::ChannelBuffer<float>(num_frames, default_channel);
    

}

AudioProcessingModule::set_ns_level(int ns_level)
{

}

AudioProcessingModule::set_aec_type(bool enable_mobile_mode)
{

}

AudioProcessingModule::set_agc_type(bool aec_type)
{

}

AudioProcessingModule::process_reverse_stream()
{
    apm->ProcessReverseStream(render_frame);
}

AudioProcessingModule::set_system_delay(int delay)
{
    system_delay = delay;
}

AudioProcessingModule::process_stream(const std::string& buf)
{
    const int16_t* temp_buf = (const int16_t*)(buf.data());

    // apm->set_stream_delay_ms(system_delay);
    //apm->set_stream_analog_level();

    int frames = near_end_config->num_frames;
    int channels = near_end_config->num_channels;
    float* des_buf = new float[frames*channels];

    webrtc::S16ToFloat(temp_buf, frames*channels, near_end_buf_f);
    webrtc::Deinterleave(near_end_buf_f, frames, channels, near_end_cbuf->channels());
    
    apm->ProcessStream(near_end_cbuf->channels(), *near_end_config, *near_end_config, near_end_cbuf->channels());

    Interleave(near_end_cbuf->channels(), frames, channels, near_end_buf_f);
    FloatToS16(near_end_buf_f, frames * channels, near_end_buf);

    return string((const char *)near_end_buf);
}

AudioProcessingModule::~AudioProcessingModule()
{
    delete config;
    delete near_end_config;
    delete far_end_config;
    delete near_end_cbuf;
    delete far_end_cbuf;
    delete near_end_buf;
    delete far_end_buf;

    delete apm;
}






PYBIND11_MODULE(audio_processing_module, m){  //这里写的名称和编译的目标名称需要对应
    m.doc() = "This is for pythonic webrtc audio_processing_module!";
    py::class_<AudioProcessingModule>(m, "AudioProcessingModule")
        .def(py::init<int, int, int, bool>())
        .def("process_stream", &AudioProcessingModule::process_stream);
} 

