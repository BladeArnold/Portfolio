// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

(BEGIN)
	// Set to zero
	@R2
	M=0

(LOOP)
	//IF R1 <= 0, stop
	@R1
	D=M
	@END
	D;JLE
	// Add R0 + R2
	@R0
	D=M
	@R2
	M=M+D
	// Decrease R1 by one
	@R1
	M=M-1
	//Loop function
	@LOOP
	0;JMP

(END)
	//End Program
	@END
	0;JMP