__author__ = 'chaomai'

import numpy as np
import scipy.optimize as op


class LogisticRegression(object):
    def __init__(self):
        '''
        _theta: 1 * (n + 1)
        _featuresAmount: features' amount(include x0).
        '''
        self._theta = None
        self._featuresAmount = None

    def sigmoid(self, z):
        '''
        sigmoid function.
        :param z: matrix
        :return: sigmoid.
        '''
        return 1 / (1 + np.exp(-z))

    def costFunction(self, theta, samples, labels):
        '''
        cost function.
        :param theta: 1 * (n + 1)
        :param samples: m * (n + 1)
        :param labels: m * 1
        :return: cost.
        '''
        m, features = samples.shape
        sigmoids = self.sigmoid(theta * samples.T)
        j = - 1 / m * np.sum(np.multiply(np.log(sigmoids), labels.T)
                             + np.multiply(np.log(1 - sigmoids), (1 - labels).T))
        return j

    def gradient(self, theta, samples, labels):
        '''
        gradient of theta.
        :param theta: 1 * (n + 1)
        :param samples: m * (n + 1)
        :param labels: m * 1
        :return: gradient
        '''
        m, features = samples.shape
        sigmoids = self.sigmoid(theta * samples.T)
        errors = sigmoids - labels.T
        grads = 1 / m * (errors * samples)
        return grads

    def train(self, samples, labels):
        '''
        train logistic regression model with samples and labels.
        suppose m is samples' amount, n is features' amount.
        :param samples: m * n
        :param labels: m * 1
        '''
        samples = np.matrix(samples, dtype='float')
        labels = np.matrix(labels, dtype='float')

        labels = labels.flatten().T
        lm, ln = labels.shape
        samples = samples.T
        sm, sn = samples.shape
        if not sm == lm:
            samples = samples.flatten('F').reshape((lm, sm * sn / lm))

        m, n = samples.shape
        self._featuresAmount = n + 1
        initialTheta = np.matrix(np.zeros(n + 1))
        X = np.append(np.matrix(np.ones(m)).T, samples, axis=1)

        # res = op.minimize(fun=self.costFunction,
        #                   x0=initialTheta,
        #                   args=(X, labels),
        #                   method='TNC',
        #                   options={'disp': True},
        #                   jac=self.gradient)
        res = op.minimize(fun=self.costFunction,
                          x0=initialTheta,
                          args=(X, labels),
                          method='TNC',
                          jac=self.gradient)
        self._theta = np.matrix(res.x)

    def predict(self, samples):
        '''
        predict the label of inputting sample.
        :param sample: 1 * n
        :return: possibility
        '''
        samples = np.matrix(samples, dtype='float')
        sm, sn = samples.shape
        if not sn == self._featuresAmount - 1:
            samples = samples.flatten('F').reshape((sm * sn / (self._featuresAmount - 1), self._featuresAmount - 1))
        m, n = samples.shape
        sample = np.append(np.matrix(np.ones(m)).T, samples, axis=1)
        return self.sigmoid(self._theta * sample.T) >= 0.5
