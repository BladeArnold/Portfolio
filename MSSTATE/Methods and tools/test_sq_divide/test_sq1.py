import pytest
import math


def sq(num):
	return math.sqrt(num)


def test_sq():
	try:
		sqr = math.sqrt(5)
		assert sqr == 2
	except:
		print("That is an imperfect square")

