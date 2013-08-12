<CsoundSynthesizer>
<CsOptions>
; Select audio/midi flags here according to platform
; Audio out   Audio in    No messages
-odac           -iadc     -d     ;;;RT audio I/O
;-+rtaudio=alsa -odac -d -m0 
; For Non-realtime ouput leave only the line below:
; -o oscils.wav -W ;;; for file output any platform
</CsOptions>
<CsInstruments>

; Initialize the global variables.
sr = 44100
kr = 4410
ksmps = 10
nchnls = 1

kval init 440;

; Instrument #1 - a fast sine oscillator.
instr 1

  iphs = 0
  kval chnget "pitch"
  kamp chnget "volume"
  iws chnget "waveshape"
  
  a1 oscil kamp,kval,p4, iphs
  out a1
endin


</CsInstruments>
<CsScore>
f0 36000 
; Play Instrument #1 for 2 seconds.
f1 0 16384 10 1                                          ; Sine
f2 0 16384 10 1 0.5 0.3 0.25 0.2 0.167 0.14 0.125 .111   ; Sawtooth
f3 0 16384 10 1 0   0.3 0    0.2 0     0.14 0     .111   ; Square
f4 0 16384 10 1 1   1   1    0.7 0.5   0.3  0.1          ; Pulse
f5 0 65536 19 .5 1 0 0 					 ; Theremin

i 1 0 -1 5
;i 1 1 10 1
;i 1 10 10 2
;i 1 20 10 3
;i 1 30 10 4
;i 1 40 -1 5
e
</CsScore>
</CsoundSynthesizer>
