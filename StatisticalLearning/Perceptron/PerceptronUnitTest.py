__author__ = 'chaomai'

import unittest
import PerceptronInitial as pt
from numpy import *
from matplotlib.pyplot import *
# from mpl_toolkits.mplot3d import axes3d


class PerceptronTestCase(unittest.TestCase):
    def plotData(self, x, y, w, b, plotRangeCorrection=3):
        '''
        :param x: n * m
        :param y: 1 * m
        :param w:
        :param b:
        :param plotRangeCorrection:
        :return:
        '''
        if w.shape[1] > 3:
            print("Dimension is too high! Unable to plot.")
            return False

        elif w[0][w.shape[1] - 1] == 0:
            print("Invalid data! Unable to plot.")
            return False

        elif w.shape[1] == 2:
            for i in range(0, y.shape[0]):
                if y[i][0] > 0:
                    plot(x[i][0], x[i][1], 'ob')
                else:
                    plot(x[i][0], x[i][1], 'xr')

            x0s = arange(x.min() - plotRangeCorrection, x.max() + plotRangeCorrection, 0.05)
            x1s = - (w[0][0] * x0s + b) / w[0][1]

            plot(x0s, x1s, 'k')
            show()

        elif w.shape[1] == 3:

            fig = figure()
            ax = fig.gca(projection='3d')

            for i in range(0, y.shape[0]):
                if y[i][0] > 0:
                    ax.plot([x[i][0]], [x[i][1]], [x[i][2]], 'ob')
                else:
                    ax.plot([x[i][0]], [x[i][1]], [x[i][2]], 'xr')

            x0s = arange(x.min() - plotRangeCorrection, x.max() + plotRangeCorrection, 0.5)
            x1s = arange(x.min() - plotRangeCorrection, x.max() + plotRangeCorrection, 0.5)
            x0s, x1s = np.meshgrid(x0s, x1s)
            x2s = - (w[0][0] * x0s + w[0][1] * x1s + b) / w[0][2]

            ax.plot_surface(x0s, x1s, x2s, rstride=1, cstride=1, linewidth=0, antialiased=True)
            show()

        return True

    def testPerceptron(self):
        x = array([[3, 3], [4, 3], [1, 1]])
        y = array([[1], [1], [-1]])
        w = array([[0, 0]])
        b = 0
        eta = 1
        iterates = 50

        # positiveSamples = 5
        # x = append(rand(positiveSamples, 2) + array([3, 3]),
        #            rand(positiveSamples, 2) + array([5, 5]), 0)
        # y = append(ones((positiveSamples, 1), int),
        #            ones((positiveSamples, 1), int) * -1, axis = 0)
        # w = array([[0, 0]])
        # b = 0
        # eta = 0.5
        # iterates = 10000

        # positiveSamples = 10
        # x = append(rand(positiveSamples, 3) + array([10, 10, 10]),
        #            rand(positiveSamples, 3) + array([1, 2, 1]),
        #            axis=0)
        # y = append(ones((positiveSamples, 1), int), ones((positiveSamples, 1), int) * -1, axis = 0)
        # w = array([[0, 0, 0]])
        # b = 0
        # eta = 0.5
        # iterates = 500000

        # print(perceptronInitial(x, y, w, b, eta))
        (w, b) = pt.perceptronInitial(x, y, w, b, eta)
        self.plotData(x, y, w, b)
        # perceptronPlotInitial(x, y, w, b, eta, iterates)


if __name__ == '__main__':
    unittest.main()
