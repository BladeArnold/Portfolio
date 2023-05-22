import pytest
import math

def sq(num):
	return math.sqrt(num)


def test_sq():
	try: 	
 		sqr = math.sqrt(-36)
	 	assert sqr == -6

	except:
		print("\n Cannot squareroot negatives")

