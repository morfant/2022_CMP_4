// PluginSimpleFlanger.cpp
// giy (giy@site.com)

#include "SimpleFlanger.hpp"

static InterfaceTable* ft;

namespace SimpleFlanger {

SimpleFlanger::SimpleFlanger() {
    
    mMaxDt = in0(1); // 1 번 input 데이터들, control rate
    
    // 초기화
    mDelaysize = sampleRate() * mMaxDt;
    
    mRate = 0.f;
    mDepth = 0.f;
    mFdbAmt = 0.f;
    mFwdhop = ((mDelaysize * mRate) / sampleRate()) + 1.0;
    mRp = 0.f;
    mWp = 0;

    mDelayline = (float*)RTAlloc(mWorld, mDelaysize * sizeof(float));
    memset(mDelayline, 0, mDelaysize * sizeof(float));
    
    std::cout << "SimpleFlanger is created with "<< mDelaysize << " samples delayline." << std::endl;
    

    // 이 UGen을 위한 calculation function 지정
    mCalcFunc = make_calc_function<SimpleFlanger, &SimpleFlanger::next>();

    // 1 sample의 계산을 수행
    next(1);
}

SimpleFlanger::~SimpleFlanger() {
    std::cout << "SimpleFlanger is destroyed!" << std::endl;
    RTFree(mWorld, mDelayline);
}

void SimpleFlanger::next(int nSamples) {
    const float * input = in(0);
    const float rate = in0(2);
    const float depth = in0(3); // wet
    const float fdb = in0(4);
    const float debug = in0(5);
    
    float* output = out(0); // 0 번 output 데이터들

    // member 변수에서 값 가져오기
    float rp = mRp;
    int wp = mWp;
    
    // 임시 지역 변수
    float in, delayed;
    
    if (rate != mRate) {
        mRate = rate;
        mFwdhop = ((mDelaysize * mRate) / sampleRate()) + 1.0;
    }
    
    
    for (int i = 0; i < nSamples; ++i) {
        in = input[i];
        
        int rpi = (int)rp;
        // index가 소수인 경우를 대비한 선형 보간
        float frac = rp - rpi;
        float next = (rpi != mDelaysize - 1 ? mDelayline[rpi + 1] : mDelayline[0]);
        delayed = mDelayline[rpi] + frac * (next - mDelayline[rpi]);
        
        rp += mFwdhop;
        if ((int)rp >= mDelaysize) {rp -= mDelaysize;};
        if ((int)rp < 0) {rp += mDelaysize;};
        
        output[i] = (1.0 - depth) * in + depth * (delayed);
        
        if (debug && wp == 0) {
          std::cout << "!At wp is zero! rpi(" << rpi << ")" << \
          " | delay time: " << (mDelaysize - rpi) / sampleRate() << std::endl;
        }
        
        // output을 포함해서 버퍼에 저장 (피드백)
        mDelayline[wp++] = in + output[i] * fdb;

        if (wp == mDelaysize) {
            wp = 0;
        }
    }
    
    // member 변수에 값 저장하기 - 다음 반복에서 사용하기 위해서
    mRp = rp;
    mWp = wp;
}

} // namespace SimpleFlanger

PluginLoad(SimpleFlangerUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<SimpleFlanger::SimpleFlanger>(ft, "SimpleFlanger", false);
    // 
}
