from numpy import *
from KDTree import *


class KNN(object):
    def __init__(self):
        self._kdTree = None

    def __init__(self, points, labels):
        '''
        suppose n is samples' amount, m is features' amount.
        points: array, training data, n * m
        labels: array, n * 1
        '''
        self.build(points, labels)

    def build(self, points, labels):
        '''
        suppose n is samples' amount, m is features' amount.
        points: array, training data, n * m
        labels: array, n * 1
        '''
        dimensions = points.shape[1]
        self._kdTree = KDTree(dimensions=dimensions)

        self._kdTree.build(points, labels)

    def add(self, x, y):
        '''
        add a point
        x: single array
        y: int
        '''
        pass


    def add(self, x, y):
        '''
        suppose n is samples' amount, m is features' amount.
        x: array, training data, n * m
        y: array, n * 1
        '''
        pass

    def getKNN(self, point, k=5):
        '''
        get nearest n points
        '''
        return self._kdTree.searchKNN(point, k)

    def getLabel(self, point, k=5):
        '''
        get label of point
        '''
        nns = self._kdTree.searchKNN(point, k)

        votes = {}

        for item in nns:
            label = item[0]._label[0]

            if label not in votes:
                votes[label] = 1
            else:
                votes[label] += 1

        return sorted(votes.items(), key=lambda x: x[1], reverse=True)[0][0]
