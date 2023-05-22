import pytest
import math

def sq(num):
	return math.sqrt(num)

def test_sq():
	sqr = math.sqrt(4)
	assert sqr ==  2

