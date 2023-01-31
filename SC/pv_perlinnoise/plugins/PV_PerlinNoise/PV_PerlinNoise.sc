PV_PerlinNoise : PV_ChainUGen {
    *new { arg buffer, stepScale = 0.02, octave = 1, persistence = 0.5, seed = 0, magScale = 1.0;
        ^this.multiNew('control', buffer, stepScale, octave, persistence, seed, magScale)
    }
}
