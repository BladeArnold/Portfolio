
from BMIcalculator import heightcal
from BMIcalculator import bmical


def test_heightcal(): #to test the height calulate  
    assert heightcal(0, 0) == 0
    assert heightcal(3, 3) == 39
    assert heightcal(5, 10) == 70
    assert heightcal(4, 0) == 48
    assert heightcal(100, 36) == 1236

def test_calculatebmi(capsys): #to test the bmi calculate  
    assert bmical(0, 1) == 0
    assert bmical(3, 3) == 1
    assert bmical(100, 10) == 10
    assert bmical(125, 5) == 25
    assert bmical(12500, 50) == 250

    

def bmicategory(bmi): #to test the catagories 
    if bmi < 18.5:
        return "Underweight"
    elif bmi < 25.1:
        return "Normal weight"
    elif bmi < 30:
        return "Overweight"
    else:
        return "Obese"

def test_bmicategory(): #to test the catagories 
    assert bmicategory(18.4) == "Underweight"
    assert bmicategory(0) == "Underweight"
    assert bmicategory(18.5) == "Normal weight"
    assert bmicategory(24.9) == "Normal weight"
    assert bmicategory(25) == "Overweight"
    assert bmicategory(29.9) == "Overweight"
    assert bmicategory(30) == "Obese"
    assert bmicategory(1234567890) == "Obese"


