import unittest
import functions

class TestFunctions(unittest.TestCase):
    
    def test_dist(self):
        result = functions.dist(3,4,7,8)
        self.assertEqual(result, 4.47213595499958)

    
    def test_dist(self):
        result = functions.dist(0,0,0,0)
        self.assertEqual(result, 0)

    def test_dist(self):
        result = functions.dist(1,0,0,0)
        self.assertEqual(result, 1)

    def test_dist(self):
        result = functions.dist(1,1,1,1)
        self.assertEqual(result, 0)

    def test_dist(self):
        result = functions.dist(-1,-1,-1,1)
        self.assertEqual(result, 1.4142135623730951)







if __name__ == '__main__':
    unittest.main()


    ###6, 8