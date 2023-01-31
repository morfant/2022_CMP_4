// PluginSimpleNoise.cpp
// giy (giy.hands@gmail.com)

#include <iostream>
#include "SC_PlugIn.hpp"
#include "SimpleNoise.hpp"


static InterfaceTable* ft;

namespace SimpleNoise {

SimpleNoise::SimpleNoise() {
    mCalcFunc = make_calc_function<SimpleNoise, &SimpleNoise::next>();
    next(1);
}

void SimpleNoise::next(int nSamples) {
    float* outbuf = out(0);

    float z = mLevel;

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        z += mRgen.frand8();

        if (z > 1.0) z = 2.0 - z;
        else if (z < -1.0) z = -2.0 - z;

        outbuf[i] = z; 
    }

    mLevel = z;

    // if (std::abs(outbuf[0]) > 0.5) {
    //     DoneAction(in0(0), this);
    //     std::cout << "Good bye" << std::endl;
    // }

}

} // namespace SimpleNoise

PluginLoad(SimpleNoiseUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimpleNoise::SimpleNoise>(ft, "SimpleNoise", false);
}
