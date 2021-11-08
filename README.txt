Music selection: Flohwalzer

This is my final project 1. I, Laurenz Heidrich, have worked on this project alone.

As an instrument, I have implemented the additive synthesizer. I have implemented the following functions:

10 - Sinusoid playback on demand from the sequencer
20 - Definition of all harmonics
30 - Envelope generation
35 - Polyphony
45 - Vibrato

Regarding the effects, I have implemented chorus, reverbation and flanging and the controllable effects send:

10 - Component passes audio
20 - 1 Effect
30 - 3 Effects
40 - Controllable effects send

I have turned in a website, an audio file of length greater 1 minute and I use all system components as well as all capabilities:

10 - Suitable length audio files and web site turned in.
20 - Audio file is recognizable as music in the opinion of the TA and Instructor.
30 - Audio file utilizes all system components.
40 - Audio file utilizes all capabilities of all system components.

I have uploaded 2 .wav-files and their corresponding .score-files

song.wav/song.score is my final file which uses all components of the additive sythesizer as well as all 3 effects and the effect send

sample_fight.wav/sample_fight.score is the 15 second music file which only demonstrates the additive synthesizer without any effects.

The format of the score-file is the following:

<?xml version="1.0" encoding="utf-8"?>
<score bpm="" beatspermeasure="">
     <instrument instrument="AdditiveSynth">
          <note measure="" beat="" duration="" note="" harmonics="//Define up to 8 harmonic levels" vibrato="//freq //level"/>
	  :
	  :
     </instrument>
         <effect effect="flanging" delay="" wet="" dry="" level=""/>
	 <effect effect="reverbation" rate="" wet="" dry=""/>
	 <effect effect="chorus" delay="" wet="" dry=""/>
</score>
