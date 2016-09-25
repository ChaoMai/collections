import unittest
from numpy import *
from numpy.random import *
import KNN as k

class Test_KNNUnitTest(unittest.TestCase):
    def testSearch(self):
        points = array([[5, 4, 3], [10, 2, 1], [4, 5, 6], [6, 1, 5], [1, 2, 3]])
        labels = array([[1], [1], [1], [-1], [-1]])

        testPoint = array([10, 3, 3])

        knn = k.KNN(points, labels)
        print(knn.getLabel(testPoint))

    def testRun(self):
        t = array([[0, 1, 2]])
        t = t.T

        samples = 50
        x1 = rand(samples, 2) + array([5, 5])
        y1 = ones((samples, 1), int) *  t[0][0]
        x2 = rand(samples, 2) + array([6, 6])
        y2 = ones((samples, 1), int) *  t[1][0]
        x3 = rand(samples, 2) + array([7, 2])
        y3 = ones((samples, 1), int) *  t[2][0]

        x = append(append(x1, x2, axis = 0), x3, axis = 0)
        y = append(append(y1, y2, axis = 0), y3, axis = 0)
        testPoint = array([3.2, 3])

        p = 10
        knn = k.KNN(x, y)
        print(knn.getLabel(testPoint, p))
        print(knn.getKNN(testPoint, p))

        #points = array([[5, 4, 3], [10, 2, 1], [4, 5, 6], [6, 1, 5], [1, 2, 3]])
        #labels = array([[1], [1], [1], [-1], [-1]])
        #testPoint = array([10, 3, 3])

        #knn = k.KNN(points, labels)
        #print(knn.getLabel(testPoint))


if __name__ == '__main__':
    unittest.main()
