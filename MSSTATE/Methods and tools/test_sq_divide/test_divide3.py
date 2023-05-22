import pytest
import math

def divide():
	try:
		num1 = int(input("Enter a number: "))
		num2 = int(input("Enter another number: "))	
		div = num1/num2
	
		print("Your numbers divided is:", div)
		return div
		
	except ZeroDivisionError:
		print("You can't divided by zero")	
		
def inps():

		inputs = ["3", "0"]
	
		for item in inputs:
			yield item

		
Quot = inps()


def test_divide(monkeypatch):

	monkeypatch.setattr('builtins.input', lambda _: next(Quot))
		
		
	assert divide() == None
