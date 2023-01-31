(
{
    var in, chain;
    in = WhiteNoise.ar(0.2);
    chain = FFT(LocalBuf(2048), in);
    chain = SimplePV(chain, 0.1);
    IFFT(chain);
}.play
)