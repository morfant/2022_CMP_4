(// Test synthdef : Non Sustained Env - has to be .free
SynthDef.new(\mtest, {
	var sig = SinOsc.ar(\freq.ar(440), mul: 0.1);
	Out.ar(0, sig * EnvGen.kr(Env.perc(), \gate.kr(1), doneAction: 0));
}).add;
)

a = Synth(\mtest);

(// Test synthdef: Sustained Env - has to be .release
SynthDef.new(\mtest2, {
	var sig = VarSaw.ar(\freq.ar(440), mul: 0.1);
	Out.ar(0, sig * EnvGen.kr(Env.adsr(), \gate.kr(1), doneAction: 2));
}).add;
)
a.free

b = Synth(\mtest2)
b.free;

---------------------------------------------

* KeyDownAction has 6 keys pressed limit at the same time.
** release 모드와 free 모드를 선택할 수 있게 해야 함.
*** octaveOffset 표시?
**** Synthdef 이름 표시?

// ex) MidiKey.new(\synthdefName, freeMode: false);

(
~window = Window("MidiKey", bounds: Rect(0, 0, 300, 100)).front;
~window.view.background = Color.new255(153, 255, 102);
~text = StaticText(~window, Rect(110, 20, 160, 60));
~text.align = \center;
~text.font = Font("Andale Mono", 20);
~text.string = "NOTE";
~enableKeyToMidi = False;
~button = Button(~window, Rect(20, 20, 100, 60)).states_([
	["OFF", Color.white, Color.black], // text color, bg color
	["ON", Color.black, Color.cyan],
])
.action_({ |but|
	if (but.value == 1, {~enableKeyToMidi = True}, {~enableKeyToMidi = False});
	~enableKeyToMidi.value.postln;
})
.onClose_({

});

~octaveOffset = 0;
~noteName = "";
~noteOnList = ();
~synthName = \mtest2;
~nodes = ();
~isOn = (
	'a':False,
	'w':False,
	's':False,
	'e':False,
	'd':False,
	'f':False,
	't':False,
	'g':False,
	'y':False,
	'h':False,
	'u':False,
	'j':False,
	'k':False,
	'o':False,
	'l':False
);

~window.view.keyDownAction = {|v, char, mod, uni, keycode, key|
	var note = 60 + (12 * ~octaveOffset);
	var nextIdx = 0;
	var sym = char.asSymbol;
	~noteName = "";
	// [v, char, mod, uni, keycode, key].postln;


	switch(sym,
		'a', {note = note + 0},
		'w', {note = note + 1},
		's', {note = note + 2},
		'e', {note = note + 3},
		'd', {note = note + 4},
		'f', {note = note + 5},
		't', {note = note + 6},
		'g', {note = note + 7},
		'y', {note = note + 8},
		'h', {note = note + 9},
		'u', {note = note + 10},
		'j', {note = note + 11},
		'k', {note = note + 12},
		'o', {note = note + 13},
		'l', {note = note + 14},
		'z', {~octaveOffset = ~octaveOffset - 1; ~octaveOffset = max(~octaveOffset, -5)},
		'x', {~octaveOffset = ~octaveOffset + 1; ~octaveOffset = min(~octaveOffset, 4)}
	);
	// ("down:" + sym).postln;
	// note.postln;
	if (~enableKeyToMidi == True, {
		if (~isOn[sym] == False, {
			var sorted;
			~nodes[sym] = Synth(~synthName, [\freq, note.midicps]);
			~noteOnList[sym] = note.asString;
			sorted = ~noteOnList.values.sort({ |a, b| a < b });
			sorted.do{|i| ~noteName = ~noteName + i.asString;};
			~text.string = ~noteName.asString;
			~isOn[sym] = True;
		})
	});
};

~window.view.keyUpAction = {|v, char, mod, uni, keycode, key|
	var sym = char.asSymbol;
	~noteName = "";
	// [v, char, mod, uni, keycode, key].postln;
	// ("up:" + sym).postln;
	if (~enableKeyToMidi == True, {
		if (~nodes[sym].notNil, {
			var sorted;
			// ~nodes[sym].free;
			~nodes[sym].release();
			~isOn[sym] = False;
			~noteOnList[sym] = nil;
			sorted = ~noteOnList.values.sort({ |a, b| a < b });
			sorted.do{|i| ~noteName = ~noteName + i.asString;};
			~text.string = ~noteName.asString;
		});
	});
};

CmdPeriod.doOnce{~window.close};
)// End of Class
