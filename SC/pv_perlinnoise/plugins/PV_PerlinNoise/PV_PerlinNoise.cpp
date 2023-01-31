// PluginPV_PerlinNoise.cpp
// giy (giy.hands@gmail.com)

#include "SC_PlugIn.hpp"
#include "PV_PerlinNoise.hpp"

InterfaceTable* ft;

namespace PV_PerlinNoise {

PV_PerlinNoise::PV_PerlinNoise() {
    init();
    
    mCalcFunc = make_calc_function<PV_PerlinNoise, &PV_PerlinNoise::next>();
    next(1);
}


void PV_PerlinNoise::init() {
    for (size_t i = 0; i < 256; i++) {
        p[i] = p[256 + i] = permutation[i];
    }
}

int PV_PerlinNoise::fastfloor(double n) {
    return n >= 0 ? (int)n : (int)(n - 1);
}

double PV_PerlinNoise::dot(int arr[2], double x, double y) {
    return arr[0] * x + arr[1] * y;
}

double PV_PerlinNoise::easing(double x) {
    return x * x * x * (x * (x * 6 - 15) + 10);
}

double PV_PerlinNoise::lerp(double b, double e, double w) {
    return b + (e - b) * w;
}

int PV_PerlinNoise::getGradientIndex(int x, int y) {
    
    int intX = x & 255;
    int intY = y & 255;
    
    int gradIdx00 = p[intX + p[intY]] & 3;
    int gradIdx01 = p[intX + p[intY + 1]] & 3;
    int gradIdx11 = p[intX + 1 + p[intY + 1]] & 3;
    int gradIdx10 = p[intX + 1 + p[intY]] & 3;
    
    int result = 0;
    result = gradIdx00;
    result = result << 4;
    result += gradIdx01;
    result = result << 4;
    result += gradIdx11;
    result = result << 4;
    result += gradIdx10;
    
    return result;
}

double PV_PerlinNoise::gradient2DNoise(double xx, double yy) {
    
    double x = xx;
    double y = yy;
    int intX = fastfloor(x);
    int intY = fastfloor(y);
    double fracX = x - intX;
    double fracY = y - intY;

    // get gradients
    int idx = getGradientIndex(intX, intY);
    int idx00 = (idx >> 12) & 0xF;
    int idx01 = (idx >> 8) & 0xF;
    int idx11 = (idx >> 4) & 0xF;
    int idx10 = idx & 0xF;
//
    
    // get distvecs
//    dist00 = fracX - 0, fracY - 0
//    dist10 = fracX - 1, fracY - 0
//    dist11 = fracX - 1, fracY - 1
//    dist01 = fracX - 0, fracY - 1
    
    double infu00 = grad(idx00, fracX - 0, fracY - 0);
    double infu01 = grad(idx01, fracX - 0, fracY - 1);
    double infu11 = grad(idx11, fracX - 1, fracY - 1);
    double infu10 = grad(idx10, fracX - 1, fracY - 0);
    
    
    double b = lerp(infu00, infu10, easing(fracX));
    double t = lerp(infu01, infu11, easing(fracX));
    
    return lerp(b, t, easing(fracY));
}

double PV_PerlinNoise::grad(int g, double x, double y) {
    
    switch (g) {
        case 0b00: return x + y; break;
        case 0b01: return x - y; break;
        case 0b10: return -x + y; break;
        case 0b11: return -x - y; break;
        default: break;
    }
}
double PV_PerlinNoise::perlin2DNoise(double x, double y, int octave, double persistence) {
    
    double total = 0;
    double maxValue = 0;
    double amplitude = 1.0;
    int frequency = 1;
    
    for (size_t i = 0; i < octave; i++) {
        total += gradient2DNoise(x * frequency, y * frequency) * amplitude;
        maxValue += amplitude;
        frequency *= 2;
        amplitude *= persistence;
    }
    
    return total / maxValue;
    
}




void PV_PerlinNoise::next(int nSamples) {
    
    Unit* unit = (Unit*)this;
    PV_GET_BUF
    
    mStepScale = in0(1);
    mOctave = in0(2);
    mPersistence = in0(3);
    mSeed = in0(4);
    mMagScale = in0(5);
    
    
    SCPolarBuf * p = ToPolarApx(buf);
//    SCComplex * q = ToComplexApx(buf);
    
    
//    float rslt[numbins];
//    for (int i = 0; i < numbins; ++i) {
//        rslt[i] = abs(perlin2DNoise(i * mStepScale, mCounter * mStepScale, mOctave, mPersistence));
//    }
//
    
    p->dc = 0.f;
    p->nyq = 0.f;
    
    
    for (int i = 0; i < numbins; ++i) {
//        p->bin[i].mag = rslt[i] * mMagScale;
        p->bin[i].mag = abs(perlin2DNoise(i * mStepScale, mCounter * mStepScale, mOctave, mPersistence)) * mMagScale;
        
//        p->bin[i].phase = 0.f;
    }
    
    mCounter++;
//    mCounter = mCounter % 1024;
    mCounter = mCounter & ((1 << 11) - 1);
//    mCounter = mCounter % 2147483647;
    
}

} // namespace PV_PerlinNoise

PluginLoad(PV_PerlinNoiseUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<PV_PerlinNoise::PV_PerlinNoise>(ft, "PV_PerlinNoise", false);
}
