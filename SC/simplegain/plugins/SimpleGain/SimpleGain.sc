SimpleGain : UGen {
	*ar { |input, gain|
		/* TODO */
		^this.multiNew('audio', input, gain);
	}
	checkInputs {
	/* TODO */
		if (inputs.at(0).rate != \audio, {
			"Input source must be audio rate signal.".error;
		}, {
			^this.checkValidInputs;
		});
	}
}
