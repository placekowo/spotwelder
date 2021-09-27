# spotwelder
 Arduino-based spot welder timing circuit.
 
 Pulses a high current transformer with the set millisecond value. Intended for spot welding batteries, but it can be adapted for other things too. 
 
 A TM1637 4-digit display module is used to show the set value, to save on GPIO pins. A rotary encoder is used to set the millisecond value. A 25A solid state relay is    used to control the mains input of the modified microwave transformer. A foot pedal from a tattoo machine is used as a trigger for the code.
 
 The [Grove 4-digit display library] (https://github.com/Seeed-Studio/Grove_4Digital_Display) is used for interfacing with the TM1637 module. This can be found in the Library Manager in the Arduino IDE.

 A microwave transformer was modified by cutting out the secondary winding, and replacing it with 3 turns of jump lead wire. The output is around 2.5V.

 Inspired by Under Dunn: https://www.youtube.com/watch?v=6w9dFNRtqlg
