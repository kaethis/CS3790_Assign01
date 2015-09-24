-----------------------------------------------------------------
      _   ___ ___ ___ ___ _  _ __  __ ___ _  _ _____    __  _ 
     /_\ / __/ __|_ _/ __| \| |  \/  | __| \| |_   _|  /  \/ |
    / _ \\__ \__ \| | (_ | .` | |\/| | _|| .` | | |   | () | |
   /_/ \_\___/___/___\___|_|\_|_|  |_|___|_|\_| |_|    \__/|_|
                                                            
-----------------------------------------------------------------
Author: 	Matt W. Martin, 4374851
		kaethis@tasmantis.net

Project:	CS3790, Assignment 01:
		"SIMPLETRON" Machine Simulator

Date Issued:	09-Sept-2015
Date Archived:	22-Sept-2015

File:		README.txt


Comments:	This assignment consists of one prog:
		simpletron

		- simpletron:	A simulated computer which runs
				programs written in a language 
				called Simple Machine Language
				(or SML).  Its memory consists of
				100 WORDS (4-digit decimals) and
				has three registers: an
				accumulator for testing and
				storing values, a program counter
				and an instruction register.  See
				machine_simulator/prog.cpp for
				more details.

MAKE:		./simpletron	Creates simpletron program.
		./clean		Removes program (if it exists).
		./archive	Creates archive in parent-dir.
		
GIT Repository:	 https://github.com/kaethis/CS3790_Assign01.git

Notes (Optional):

- I've included your SML test programs in a directory called
  sml_progs; each file contains the extension .sml.  If you'd
  like SIMPLETRON to run these progs without having to input
  them manually, execute the program like so:

    $> ./simpletron < sml_progs/prog.sml
    (where "prog" is the name of the SML program)

- A consequence the function I'm using to convert an integer into
  a string means inputing a value that cannot be cast into an int
  (except for "GO") results in that memory location containing
  zero.  It's a minor greivance, but I'll make the assumption the
  user knows what they're doing.

- Exceeding the number of memory locations (from 0 to 99) in the
  input phase will end the input routine and try to execute.
  Just so you know.
