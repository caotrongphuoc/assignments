#Build unit_test <br>
unit_test: unit_test.c <br>
	=> make unit_test <br>

#run <br>
run: unit_test <br>
	=> ./unit_test <br>

#clean <br>
clean: <br>
	=> make clean <br>
