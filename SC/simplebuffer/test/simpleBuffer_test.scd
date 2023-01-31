(
~path = "/Users/giy/Projects/sc-example-code/effector/sample/peaceful-simple-piano.wav";
// ~path = "/Users/giy/Downloads/pseudo-classical-piano-melody-2.wav";
b = Buffer.read(s, ~path);
// b.play

{SimpleBuffer.ar(b, 2.0)}.play;

)
