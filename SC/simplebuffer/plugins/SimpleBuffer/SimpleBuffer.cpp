// PluginSimpleBuffer.cpp
// giy (giy@site.com)

#include <iostream>
#include "SC_PlugIn.hpp"
#include "SimpleBuffer.hpp"

static InterfaceTable* ft;

namespace SimpleBuffer {

SimpleBuffer::SimpleBuffer() {
    std::cout << "SimpleBuffer()" << std::endl;
    mCalcFunc = make_calc_function<SimpleBuffer, &SimpleBuffer::next>();
    next(1);
}

void SimpleBuffer::next(int nSamples) {
    auto unit = this;
    float rate = in0(1);
    float * outbufL = out(0);
    GET_BUF_SHARED
    
//    std::cout << "bufFrames: " << bufFrames << std::endl;
    size_t bl = bufFrames * bufChannels;
    
    for (int i = 0; i < nSamples; ++i) {
        float phase = index * rate;
        if ((int)phase > bl) phase -= bl;
        if ((int)phase < 0) phase += bl;
        outbufL[i] = bufData[(int)phase];
        index++;
        if (index > bl) index -= bl;
        if (index < 0) index += bl;
    }
}

} // namespace SimpleBuffer

PluginLoad(SimpleBufferUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimpleBuffer::SimpleBuffer>(ft, "SimpleBuffer", false);
}
