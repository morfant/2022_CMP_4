// PluginSimpleFlanger.hpp
// giy (giy@site.com)

#pragma once

#include "SC_PlugIn.hpp"
#include <iostream>

namespace SimpleFlanger {

class SimpleFlanger : public SCUnit {
public:
    SimpleFlanger();
    
    // Destructor
    ~SimpleFlanger();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
    float mDelaysize;
    float * mDelayline;
    float mMaxDt = 0.02;
    float mRate, mDepth, mFdbAmt;
    float mFwdhop;
    float mRp;
    int mWp;
};

} // namespace SimpleFlanger
