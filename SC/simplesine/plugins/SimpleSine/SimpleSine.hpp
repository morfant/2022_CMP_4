// PluginSimpleSine.hpp
// giy (giy.hands@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include "SC_RGen.h"

namespace SimpleSine {


class SimpleSine : public SCUnit {
public:
    SimpleSine();

    // Destructor
    // ~SimpleSine();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
    struct RGen rgen;
    
};

} // namespace SimpleSine
