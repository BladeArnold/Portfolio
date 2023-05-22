import pytest
import math

def divide():
	num1 = float(input("Enter a number: "))
	num2 = float(input("Enter another number: "))	
	div = num1/num2
	
	print("Your numbers divided is:", div)
	return div
def inps():

		inputs = ["3", "1.5"]
	
		for item in inputs:
			yield item
		
Quot = inps()


def test_divide(capsys, monkeypatch):

	monkeypatch.setattr('builtins.input', lambda _: next(Quot))
		
		
	assert divide() == 2.0
	
	#divide()
	
	captured_stdout, captured_stderr = capsys.readouterr()
	
	assert captured_stdout.strip() == "Your numbers divided is: 2.0"
