import pytest
from functions import *
import functions
import unittest

#test for the display item
@pytest.mark.parametrize("numbers", [1,2,3,4,"a"])
def test_displayItem(numbers):
    assert  displayItem(numbers) == None

#test for the greetuser
@pytest.mark.parametrize("fullname", ["Blade alex arnold", "What is name", "I am god", "1 is lonley"])
def test_greetUser(fullname):
    assert greetUser(fullname) == None






class TestFunctions(unittest.TestCase):
    # test for dist
    def test_dist1(self):
        self.assertEqual(functions.dist(3,3,2,2), 1.189207115002721)
    def test_dist2(self):
        self.assertEqual(functions.dist(4,4,2,2), 1.6817928305074292)
    def test_dist3(self):
        self.assertEqual(functions.dist(5,4,3,2), 1.6817928305074292)
    def test_dist4(self):
        self.assertEqual(functions.dist(6,6,3,2), 0)
    

    #test for the string revesal
    def test_isPalindrome1(self):
        self.assertTrue(functions.isPalindrome("hey"), "yeh")
    def test_isPalindrome2(self):
        self.assertFalse(functions.isPalindrome("hey"), "hey")
    def test_isPalindrome3(self):
        self.assertTrue(functions.isPalindrome("say"), "yas")


    #test for numbers
    def test_numbers1(self):
        self.assertEqual(functions.numbers(10,5), 2)
    def test_numbers2(self):
        self.assertEqual(functions.numbers(1,4), 0.25)
    def test_numbers3(self):
        self.assertEqual(functions.numbers(-1,2), -0.5)
    def test_numbers4(self):
        self.assertEqual(functions.numbers(0,4), 0)
    def test_numbers5(self):
        self.assertEqual(functions.numbers(2,0), None)
    def test_numbers6(self):
        self.assertEqual(functions.numbers(0.5,3), 0.16666666666666666)

    #tests for the openfile
    def test_openFile1(self):
        self.assertIsNone(functions.openFile("testing.txt"))
    def test_openFile2(self):
        self.assertEqual(functions.openFile("testing.txt"), None)
    def test_openFile3(self):
        self.assertIsNone(functions.openFile("files.txt"))



        
        





