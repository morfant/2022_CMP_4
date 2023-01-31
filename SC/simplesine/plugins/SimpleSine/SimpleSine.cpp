// PluginSimpleSine.cpp
// giy (giy.hands@gmail.com)

#include "SC_PlugIn.hpp"
#include "SimpleSine.hpp"

static InterfaceTable* ft;

namespace SimpleSine {

SimpleSine::SimpleSine() {
    mCalcFunc = make_calc_function<SimpleSine, &SimpleSine::next>();
    next(1);
}

void SimpleSine::next(int nSamples) {
    float* output = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        
        output[i] = rgen.frand2();
        
    }
}

} // namespace SimpleSine

PluginLoad(SimpleSineUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimpleSine::SimpleSine>(ft, "SimpleSine", false);
}
