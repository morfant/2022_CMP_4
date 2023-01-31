// PluginSimplePV.cpp
// giy (giy.hands@gmail.com)

#include "SimplePV.hpp"

//static InterfaceTable* ft;

namespace SimplePV {

SimplePV::SimplePV() {
    mCalcFunc = make_calc_function<SimplePV, &SimplePV::next>();
    next(1);
}

void SimplePV::next(int nSamples) {
//    const float gain = in0(1);
//    Unit* unit = (Unit*)this;
//    PV_GET_BUF
//
//    SCPolarBuf* p = ToPolarApx(buf);
//
//    p->dc = p->dc * gain;
//    p->nyq = p->nyq * gain;
//    for (int i = 0; i < numbins; ++i) {
//        float mag = p->bin[i].mag;
//        p->bin[i].mag = mag * gain;
//    }
//
//
    Unit* unit = (Unit*)this;
    
    PV_GET_BUF
    
//    MAKE_TEMP_BUF
//    if (!this->m_tempbuf) {
//        this->m_tempbuf = (float*)RTAlloc(this->mWorld, buf->samples * sizeof(float));
//        this->m_numbins = numbins;
//    } else if (numbins != this->m_numbins)
//        return;
//
//
//    SCPolarBuf * p = ToPolarApx(buf);
//
//    double rslt[512];
//
//    for (int i = 0; i < 512; i++) {
//        rslt[i] = perlin2D(0, i, mOctave, mPersistence);
//    }
    
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }

}

} // namespace SimplePV

PluginLoad(SimplePVUGens) {
    // Plugin magic
    InterfaceTable* ft = inTable;
    registerUnit<SimplePV::SimplePV>(ft, "SimplePV", false);
}
