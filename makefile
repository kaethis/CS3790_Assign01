simpletron:
	g++ ./machine_simulator/prog.cpp -o simpletron
clean:
	rm simpletron
archive:
	tar cvf ../CS3790_4374851_Assign01.tar .
