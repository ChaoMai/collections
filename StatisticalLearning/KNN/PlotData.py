from numpy import *
from matplotlib.pyplot import *
from mpl_toolkits.mplot3d import axes3d

# x: n * m
# y: n * 1
def plotData(x, plotRangeCorrection = 3):
    if x.shape[1] > 3:
        print("Dimension is too high! Unable to plot.")
        return False

    elif x.shape[1] == 2:
        plot(x, 'ob')
        show()

    elif x.shape[1] == 3:
        fig = figure()
        ax = fig.gca(projection='3d')
        ax.plot(x, 'ob')
        show()

    return True
