__author__ = 'chaomai'

import unittest
import csv
import LogisticRegression as lr


class LogisticRegressionTestCase(unittest.TestCase):
    def getData(self):
        samples = []
        labels = []
        with open('data.txt', mode='r') as dataFile:
            reader = csv.reader(dataFile, delimiter=',', lineterminator='\n')
            for r in reader:
                labels.append(r.pop(len(r) - 1))
                samples.append(r)

        return samples, labels

    def testTrain(self):
        samples, labels = self.getData()
        l = lr.LogisticRegression()
        l.train(samples, labels)

    def testPredict(self):
        samples, labels = self.getData()
        l = lr.LogisticRegression()
        l.train(samples, labels)
        p = l.predict(samples)
        print(p)



if __name__ == '__main__':
    unittest.main()
