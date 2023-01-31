// PluginSimpleGain.cpp
// giy (giy.hands@gmail.com)

#include "SC_PlugIn.hpp"
#include "SimpleGain.hpp"
#include <iostream>

static InterfaceTable* ft;

namespace SimpleGain {

SimpleGain::SimpleGain() {
    std::cout << "SimpleGain()" << std::endl;
    mCalcFunc = make_calc_function<SimpleGain, &SimpleGain::next_a>();
    next_a(1);
}

void SimpleGain::next_a(int nSamples) {
    // std::cout << "SimpleGain::next_a()" << std::endl;

    float gain = 0.f;
    const float * gain_ptr;

    if (inRate(Gain) == calc_FullRate) gain_ptr = in(Gain);
    else gain = in0(Gain);
    
    const float* input = in(Source);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        if (inRate(Gain) == calc_FullRate) { 
            outbuf[i] = input[i] * gain_ptr[i];
        } else {
            outbuf[i] = input[i] * gain;
        }
    }
}

} // namespace SimpleGain

PluginLoad(SimpleGainUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimpleGain::SimpleGain>(ft, "SimpleGain", false);
}
