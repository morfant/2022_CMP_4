// PluginSimplePV.hpp
// giy (giy.hands@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "FFT_UGens.h"

namespace SimplePV {

class SimplePV : public SCUnit {
public:
    SimplePV();

    // Destructor
    // ~SimplePV();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace SimplePV
