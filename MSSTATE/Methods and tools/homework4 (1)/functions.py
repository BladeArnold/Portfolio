import math

## opens a file in read mode
## filename received as a parameter
def openFile(filename):
    infile = open(filename, "r")

    print("File opened.")

## takes two numbers and returns
## the result of a division
def numbers(num1, num2):
    #add if statement if zero is num2
    if(num2 == 0):
        print("Can not divide by zero")
    else:
        return num1 / num2

## takes in two points
## finds the distance between the points
def dist(x1, y1, x2, y2):
    dist = ((x2 - x1) ** 2 + (y2 - y1) ** 2)**.5
    dist = math.sqrt(dist)

    return dist

## takes in a string -- reverses it
## then compares the two
def isPalindrome(temp):
    test = temp[::-1]

    if(test == temp):
        return False

    else:
        return True
    #add print temp
    print(temp)
        

## has input to receive two numbers
## divides the two, then outputs the result
def divide():
    num1 = int(input("Enter a number: "))
    num2 = int(input("Enter another number: "))

    div = num1 / num2

    print("Your numbers divided is:", div)

## returns the squareroot of a particular number
def sq(num):
    return math.sqrt(num)

## grabs user's name
## greets them by their entire name
## names should be strings
def greetUser(fullname):
    print("Hello!")
    #Change so we dont have to parse
    print("Welcome to the program, Please enter a fullname", fullname)
    # Grabs all the names and checks 
    if(fullname.isalnum() == False):
        print("Please do not include numbers")
    else:
        print("Glad to have you!")

## takes in a Python list
## attempts to display the item at the index provided
def displayItem(numbers):
    #List of numbers
    num_list = [1,2,3,4]
    #finds index
    for(index, num) in enumerate(num_list):
        if(num == numbers):
            index = num_list.index(num)
        else:
            print("Please input a number in the list")
    #prints output
    print("Your item at", numbers, "index is", index)
