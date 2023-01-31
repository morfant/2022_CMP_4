// PluginSimpleGain.hpp
// giy (giy.hands@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace SimpleGain {

class SimpleGain : public SCUnit {
public:
    SimpleGain();

    // Destructor
    // ~SimpleGain();

private:
    enum Inputs {Source, Gain};

    // Calc function
    void next_a(int nSamples);

    // Member variables

};

} // namespace SimpleGain
