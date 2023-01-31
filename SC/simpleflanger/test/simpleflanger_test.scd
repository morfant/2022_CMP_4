Platform.userExtensionDir

{SimpleGain.ar(WhiteNoise.ar(1.0), 0.1)}.play


( //flanger
~path = "/Users/giy/Projects/sc-example-code/effector/sample/peaceful-simple-piano.wav";
// ~path = "/Users/giy/Downloads/pseudo-classical-piano-melody-2.wav";
b = Buffer.read(s, ~path);

f = {
    arg time = 0.0035, feedback = 0.4, amp = 0.1, rate = 0.55, depth = 1, dry = 0.5, wet = 0.5;
    var bypass, in, eff, lfo, out, numCh = 2;
    in = bypass = PlayBuf.ar(numCh, b, BufRateScale.kr(b), loop: 1);
	SimpleFlanger.ar(in, rate, depth, amp);
}.play;
);

(
d = 0.1;
w = 1.0 - d;
f.set(\dry, d, \wet, w, \time, 0.002, \rate, 0.8, \depth, 0.3, \feedback, 0.85);
)

BufWr
