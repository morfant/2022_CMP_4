SimpleFlanger : UGen {
	*ar { |in, maxDt = 0.02, rate = 0.5, depth = 1.0, fdbamt = 0.5, debug = 0, mul = 1.0, add = 0.0|
		^this.multiNew('audio', in, maxDt, rate, depth, fdbamt, debug).madd(mul, add);
	}
	*kr { |in, maxDt = 0.02, rate = 0.5, depth = 1.0, fdbamt = 0.5, debug = 0, mul = 1.0, add = 0.0|
		^this.multiNew('control', in, maxDt, rate, depth, fdbamt, debug).madd(mul, add);
	}
	checkInputs {
		^this.checkSameRateAsFirstInput;
	}
}
