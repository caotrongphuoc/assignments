# Build unit_test
unit_test: unit_test.c
	make unit_test

#run
run: unit_test
	./unit_test

#clean
clean:
	make clean
