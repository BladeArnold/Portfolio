import pytest
import math


##### test with integers
def divide():
	num1 = int(input("Enter a number: "))
	num2 = int(input("Enter another number: "))
	
	div = num1/num2
	
	print("Your numbers divided is:", div)
	
	return div
	

def inps():
	inputs = ["6", "6"]
	
	for item in inputs:
	     yield item
		
Quot = inps()

def test_divide(capsys, monkeypatch):

	
	monkeypatch.setattr('builtins.input', lambda _: next(Quot))
	
	assert divide() == 1.0
	
	
	captured_stdout, captured_stderr = capsys.readouterr()
	
	assert captured_stdout.strip() == "Your numbers divided is: 1.0"


