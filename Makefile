.PHONY:	all test clean

IN_FILENAME=main.cpp Calculator.cpp
OUT_FILENAME=Calculator.out
IN_TEST=test.cpp Calculator.cpp
OUT_TEST=test.out
COMPILER_NAME=g++
COMPILATION_OPT=-Wall -g

all:	$(OUT_FILENAME)

$(OUT_FILENAME):   $(IN_FILENAME)
	$(COMPILER_NAME) $(COMPILATION_OPT) -o $(OUT_FILENAME) $(IN_FILENAME) 
	
test:	$(OUT_TEST)
	
$(OUT_TEST):   $(IN_TEST)
	$(COMPILER_NAME) $(COMPILATION_OPT) -o $(OUT_TEST) $(IN_TEST)

clean:
	rm -f $(OUT_FILENAME) $(OUT_TEST) 
