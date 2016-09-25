import unittest
from numpy import *
from numpy.random import *
from KDTree import *

class Test_KDTreeUnitTest(unittest.TestCase):
    def testAdd(self):
        kd = KDTree(dimensions = 3)
        points = array([[5, 4, 3], [10, 2, 1], [4, 5, 6], [6, 1, 5], [1, 2, 3]])
        labels = array([[1], [1], [1], [-1], [-1]])
        kd.add([5, 4, 3], 1)

    def testBuild(self):
        kd = KDTree(dimensions = 3)
        points = array([[5, 4, 3], [10, 2, 1], [4, 5, 6], [6, 1, 5], [1, 2, 3]])
        labels = array([[1], [1], [1], [-1], [-1]])
        kd.build(points, labels)
        print(kd.searchKNN(([4, 4, 6]), 3)[0][0]._data)
        pass

    def testHeight(self):
        t = array([[0, 1, 2]])
        t = t.T

        samples = 5000
        x1 = rand(samples, 2) + array([3, 3])
        y1 = ones((samples, 1), int) *  t[0][0]
        x2 = rand(samples, 2) + array([6, 6])
        y2 = ones((samples, 1), int) *  t[1][0]
        x3 = rand(samples, 2) + array([7, 2])
        y3 = ones((samples, 1), int) *  t[2][0]

        x = append(append(x1, x2, axis = 0), x3, axis = 0)
        y = append(append(y1, y2, axis = 0), y3, axis = 0)

        testPoint = array([3.2, 3])
        kd = KDTree(dimensions = 2)
        kd.build(x, y)
        print(kd._root.height())

    def testBalanced(self):
        t = array([[0, 1, 2]])
        t = t.T

        samples = 5000
        x1 = rand(samples, 2) + array([3, 3])
        y1 = ones((samples, 1), int) *  t[0][0]
        x2 = rand(samples, 2) + array([6, 6])
        y2 = ones((samples, 1), int) *  t[1][0]
        x3 = rand(samples, 2) + array([7, 2])
        y3 = ones((samples, 1), int) *  t[2][0]

        x = append(append(x1, x2, axis = 0), x3, axis = 0)
        y = append(append(y1, y2, axis = 0), y3, axis = 0)

        testPoint = array([3.2, 3])
        kd = KDTree(dimensions = 2)
        kd.build(x, y)
        print(kd.isBlanced())

if __name__ == '__main__':
    unittest.main()
