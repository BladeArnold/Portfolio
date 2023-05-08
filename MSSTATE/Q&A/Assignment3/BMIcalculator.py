import math
import sys

def heightcal(ft, inches): # calculates the height into inches 
    heighttotal = (ft * 12) + inches
    return heighttotal

def bmical(weight, height): # gets the bmi 
    bmi = weight / (height)
    return bmi

if __name__ == "__main__":
    height_ft = float(sys.argv[1])
    height_in = float(sys.argv[2])
    weight_pounds = float(sys.argv[3])
    
    height = (heightcal(height_ft, height_in) * 0.025)**2 # does the conversion to meters 
    weight = weight_pounds * 0.45 # does the coversion to metric system 
    BMI = bmical(weight, height) # calls the bmi cal

    print("Your BMI is: ")
    print(round(BMI)) # makes bmi a whole number 

    if(BMI>0): # compares bmi to all of these to find the correct one
        if(BMI<=18.5):
            print("You are underweight.")
        elif(BMI<=25):
            print("You are the normal weight.")
        elif(BMI<=30):
            print("You are overweight.")
        else: 
            print("You are obese.")

