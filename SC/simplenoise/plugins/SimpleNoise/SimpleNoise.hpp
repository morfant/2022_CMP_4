// PluginSimpleNoise.hpp
// giy (giy.hands@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "SC_RGen.h"
#include "SC_InterfaceTable.h"

namespace SimpleNoise {

class SimpleNoise : public SCUnit {
public:
    SimpleNoise();

    // Destructor
    // ~SimpleNoise();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
    struct RGen mRgen;

    float mLevel = 0.f;
};

} // namespace SimpleNoise
