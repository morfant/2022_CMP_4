// 마우스 포인터가 0점을 지날 때 자동으로 zero/pole이 만들어 지는 원인 파악하기 ==> pole/zero의 개수가 많아지면 Array index 에러가 발생
// 2 pole, 2 zero 이상에 대해서도 대응되도록 할 것인가?
// GUI가 만들어 지는 위치가 zplane와 freqscopeview가 맞춰져 정렬되도록 하기
// 파라메터 결정하는 텍스트 GUI 추가
// freqScopeview에 주파수 표시선 넣기

(
~occupiedBus = s.options.numAudioBusChannels - 11; // 사용하지 않을 것 같은 임의의 채널
SynthDef(\filtergraph_pipe, {
	Out.ar(\outBus.ar(~occupiedBus),
		SOS.ar(WhiteNoise.ar(1), \coef_a0.ar(0), \coef_a1.ar(0), \coef_a2.ar(0), \coef_b1.ar(0), \coef_b2.ar(0))
	);
}).add;

~syn = Synth.head(RootNode(s), \filtergraph_pipe);

~window = Window("My Analyzer", Rect(0, 0, 511, 300));
~freqScope = FreqScopeView(~window, ~window.view.bounds);
~freqScope.inBus_(~occupiedBus);
~freqScope.freqMode_(1); // 0 = linear, 1 = logarithmic
~freqScope.dbRange_(80);
~window.front;
~window.onClose_({~freqScope.kill});

~zp = ZPlane([Polar(0.8, 0.25)], [Polar(-0.8, 0.25)],
	{|z| // 마우스 드래그 시 실행되는 함수

		var coefs = Array.fill(6, {0});
		var poles = z.poles, zeros = z.zeros;
		if (~freqScope.active == false, {~freqScope.active_(true)});
		("poles: " + poles).postln;
		("zeros: " + zeros).postln;
		~coefPoly = FilterCoef.calc(poles, zeros);
		// ("coef: " + ~coefPoly).postln;
		~coefPoly[0].do{|item, i| coefs.put(i, item)}; // a
		~coefPoly[1].do{|item, i| coefs.put(i + 3, item.neg)}; // b
		("coefs: " + coefs).postln;
		~syn.set(\outbus, ~occupiedBus, \coef_a0, coefs[0], \coef_a1, coefs[1], \coef_a2, coefs[2], \coef_b1, coefs[4], \coef_b2, coefs[5]);


});
~zp.gui;
~zp.zplane.mouseUpAction_({arg me, x, y, mod;
	me.refresh;
	~freqScope.active_(false);
});


CmdPeriod.doOnce{
	~syn.free;
	~zp.close;
	~freqScope.kill;
	~window.close;
};

)


	