SimpleSine : UGen {
	*ar { |mul = 1.0, add = 0.0|
		/* TODO */
		^this.multiNew('audio').madd(mul, add);
	}
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
