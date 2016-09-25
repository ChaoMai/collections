from numpy import *
from math import *


class KNode(object):
    def __init__(self, data=None, label=None, left=None, right=None,
                 axis=None):
        self._data = data
        self._label = label
        self._left = left
        self._right = right
        self._axis = axis

    def __repr__(self):
        return '<%(data)s - %(label)s>' % dict(data=self._data, label=self._label)

    def __hash__(self):
        return id(self)

    def children(self):
        '''
        returns an iterator for the children of the node
        '''
        if self._left:
            yield (self._left, 0)
        if self._right:
            yield (self._right, 1)

    def height(self):
        if self._left is None and self._right is None:
            return 0
        elif not self._left is None and self._right is None:
            return 1 + self._left.height()
        elif self._left is None and not self._right is None:
            return 1 + self._right.height()
        else:
            return 1 + max([self._left.height(), self._right.height()])

    def isBlanced(self):
        '''
        whether all subtrees are balanced
        '''
        left = self._left.height()
        right = self._right.height()

        if abs(left - right) > 1:
            return False

        return True

    def _axisDistance(self, point, axis):
        return pow(self._data[axis] - point[axis], 2)

    def distance(self, point):
        sumDist = 0
        for i in range(0, len(self._data)):
            sumDist += self._axisDistance(point, i)

        return sumDist


class KDTree(object):
    def __init__(self, dimensions=None, selectAxis=None):
        self._root = None
        self._dimensions = dimensions
        self._selectAxis = selectAxis or (lambda prevAxis: (prevAxis + 1) % self._dimensions)

    def isBlanced(self):
        return self._root.isBlanced()

    def add(self, point, label):
        current = self._root

        while True:
            if not current:
                current = KNode(point, label)
                return current

    def _buildKDTree(self, points, labels, axis):
        if len(points) == 0:
            return None

        points = points[points[:, axis].argsort()]
        median = len(points) // 2

        resPoint = points[median]
        resLabel = labels[median]
        left = self._buildKDTree(points[:median],
                                 labels[:median],
                                 self._selectAxis(axis))
        right = self._buildKDTree(points[median + 1:],
                                  labels[median + 1:],
                                  self._selectAxis(axis))

        return KNode(resPoint, resLabel, left, right, axis)

    def build(self, points, labels):
        if len(points) == 0:
            raise ValueError('points must be provided!')

        self._root = self._buildKDTree(points, labels, 0)

    def searchKNN(self, point, k, distance=None):
        '''
        return an ordered list of (node, distance) tuples.
        '''
        if distance is None:
            getDistance = lambda n: n.distance(point)
        else:
            getDistance = lambda n: distance(n._data, point)

        current = self._root
        searchPath = []

        while current:
            searchPath.append(current)

            if point[current._axis] < current._data[current._axis]:
                # left
                current = current._left
            else:
                # right
                current = current._right

        # dict of results
        results = {}

        while len(searchPath) != 0:
            backNode = searchPath.pop()
            distance = backNode.distance(point)

            # whether go to another subspace
            if abs(point[backNode._axis] - backNode._data[backNode._axis]) > distance:
                if point[backNode._axis] < backNode._data[backNode._axis]:
                    # point is currently at left subspace, go right
                    current = backNode._right
                else:
                    # go left
                    current = backNode._left

                if current:
                    searchPath.append(current)
            else:
                if not results:
                    bestNode = None
                    bestDistance = float('inf')
                else:
                    bestNode, bestDistance = sorted(results.items(),
                        key=lambda x: x[1],
                        reverse=False)[0]

                if distance < bestDistance:
                    if len(results) == k and bestNode:
                        results.pop(bestNode)
                    results[backNode] = distance
                elif distance == bestDistance:
                    results[bestNode] = bestDistance
                else:
                    if len(results) < k:
                        results[backNode] = distance

        return sorted(results.items(), key=lambda x: x[1])
