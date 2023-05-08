// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

(BEGIN)
	// Set address for keyboard intput
	@24576
	D=A
	@keyboard
	M=D

(CHECK)
	// Set Current to last pix 
	@24575
	D=A
	@current
	M=D
	// When key pressed, fill screen
	@keyboard
	A=M
	D=M
	@fillvalue
	M=-1
	@DRAW
	D;JNE
	// Else, clear screen
	@fillvalue
	M=0

(DRAW)
	// Fill or clear current pix
	@fillvalue
	D=M
	@current
	A=M
	M=D
	// If pix are full, jump back to keyboard check
	@current
	D=M
	@16384
	D=D-A
	@CHECK
	D;JLE
	// Decrease current pix by 1
	@current
	M=M-1
	//Draw next pix
	@DRAW
	0;JMP