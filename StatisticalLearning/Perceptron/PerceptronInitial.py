from numpy import *
from numpy.random import *
import Utilities.PlotData as pl


def isValid(x, y, w, b):
    return (y * (w.dot(x) + b) > 0)[0]

# xi: 1 * n
# yi
# w: 1 * m
# b
# eta
def updateParameter(xi, yi, w, b, eta):
    w = w + eta * xi * yi
    b = b + eta * yi
    return (w, b)

# Suppose n is samples' amount, m is features' amount.
# x: array, training data, n * m
# y: array, n * 1
# w: array, weights, 1 * m
# b: bias
# eta: learning rate
def perceptronInitial(x, y, w, b, eta, maxIteration = 50):
    tryed = 0
    i = 0
    while (i < x.shape[0]):
        tryed += 1

        if isValid(x[i], y[i], w, b) == False:
            # update w and b using eta
            (w, b) = updateParameter(x[i], y[i], w, b, eta)
            i = 0
            continue

        # reach maxium iteration's time or end of x
        if (tryed >= maxIteration) or (i == x.shape[0] - 1):
            return (w, b)

        i += 1

def perceptronPlotInitial(x, y, w, b, eta, maxIteration = 50):
    tryed = 0
    i = 0
    preW = w
    while (i < x.shape[0]):
        if not array_equal(preW, w):
            print("w: %s", w)
            print("b: %s", b)
            pl.plotData(x, y, w, b)
            #if plotData(x, y, w, b) == True:
            #    print("Enter a key to continue:")
            #    input("--> ")
            preW = w
            print("\r")

        tryed += 1

        if isValid(x[i], y[i], w, b) == False:
            # update w and b using eta
            (w, b) = updateParameter(x[i], y[i], w, b, eta)
            i = 0
            continue

         # reach maxium iteration's time or end of x
        if (tryed >= maxIteration) or (i == x.shape[0] - 1):
            return (w, b)

        i += 1
