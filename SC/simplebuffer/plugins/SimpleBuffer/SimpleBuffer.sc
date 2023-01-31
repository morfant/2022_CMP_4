SimpleBuffer : UGen {
	*ar { |bufnum, rate = 1.0|
		/* TODO */
		^this.multiNew('audio', bufnum, rate);
	}
	checkInputs {
		/* TODO */
		^this.checkValidInputs;
	}
}
