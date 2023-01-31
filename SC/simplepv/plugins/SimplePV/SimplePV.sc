SimplePV : UGen {
	*new { |buffer, gain|
		^this.multiNew('control', buffer, gain);
	}
}
