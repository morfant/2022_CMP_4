// PluginSimpleBuffer.hpp
// giy (giy@site.com)

#pragma once

//#include "SC_PlugIn.hpp"

namespace SimpleBuffer {

struct BufRd {
    float m_fbufnum = 0.0;
    float m_failedBufNum;
    SndBuf* m_buf;
};

class SimpleBuffer : public SCUnit, public BufRd {
public:
    SimpleBuffer();

    // Destructor
    // ~SimpleBuffer();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
    size_t index = 0;
    
};

} // namespace SimpleBuffer
