# Calculator
The programm can parse and calculate different mathematical expressions.


## What programm can do?:
- calculate the simplest arithmetic operations: "+", "-", "*", "/", "%", "!", "p" (exponentiation p), "s" (sqrt)
- set and use variable values
- parse expressions with brackets and various mathematical expressions including all possible arithmetic operations and setted variables
- use integer and floating point numbers up to 3 decimal places 

## How to use it?:
- use ";" in the end of the string (!!!)
- to calculate simple mathematical expression just type it
- to use variables you need to set them first
- to set variables you need to type "`let` [variable_name] = [value];"
- [variable_name] can be only one (lowercase or uppercase) letter (but not "p", "s" or "q" as it is already in list of arithmetic operations or used for service)
- to change variable value use "`let` [variable_name] = [value];" again
- to exit the programm type "`q`"

## Some examples of usage:

![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%201.png)
![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%202.png)
![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%203.png)
![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%204.png)
![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%205.png)
![alt text](https://github.com/Viroslav/SFE/blob/master/pictures/programm%20work%206.png)

# Quickstart
 to install in linux from nothing
 enter the following commands:

```
sudo apt update
sudo apt install git build-essential -y
git clone https://github.com/Viroslav/SFE.git
cd SFE
make
./Calculator.out
```

If you work from root just not use sudo.

# Tests

to run tests 
enter the following commands after quikstart:

```
make test
./test.out
```

