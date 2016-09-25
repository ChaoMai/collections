__author__ = 'chaomai'

import unittest
import DecisionTree as dt


class DecisionTreeTestCase(unittest.TestCase):
    def getTestData0(self):
        samples = [['no', 'no'],
                   ['no', 'no'],
                   ['yes', 'no'],
                   ['yes', 'yes'],
                   ['no', 'no'],
                   ['no', 'no'],
                   ['no', 'no'],
                   ['yes', 'yes'],
                   ['no', 'yes'],
                   ['no', 'yes'],
                   ['no', 'yes'],
                   ['no', 'yes'],
                   ['yes', 'no'],
                   ['yes', 'no'],
                   ['no', 'no']]

        labels = ['no',
                  'no',
                  'yes',
                  'yes',
                  'no',
                  'no',
                  'no',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'no']

        return samples, labels

    def getTestData1(self):
        samples = [['young', 'no', 'no', 'normal'],
                   ['young', 'no', 'no', 'good'],
                   ['young', 'yes', 'no', 'good'],
                   ['young', 'yes', 'yes', 'normal'],
                   ['young', 'no', 'no', 'normal'],
                   ['middle age', 'no', 'no', 'normal'],
                   ['middle age', 'no', 'no', 'good'],
                   ['middle age', 'yes', 'yes', 'good'],
                   ['middle age', 'no', 'yes', 'very good'],
                   ['middle age', 'no', 'yes', 'very good'],
                   ['old age', 'no', 'yes', 'very good'],
                   ['old age', 'no', 'yes', 'good'],
                   ['old age', 'yes', 'no', 'good'],
                   ['old age', 'yes', 'no', 'very good'],
                   ['old age', 'no', 'no', 'normal']]

        labels = ['no',
                  'no',
                  'yes',
                  'yes',
                  'no',
                  'no',
                  'no',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'no']

        return samples, labels

    def getTestData2(self):
        samples = [['1', 'young', 'no', 'no', 'normal'],
                   ['2', 'young', 'no', 'no', 'good'],
                   ['3', 'young', 'yes', 'no', 'good'],
                   ['4', 'young', 'yes', 'yes', 'normal'],
                   ['5', 'young', 'no', 'no', 'normal'],
                   ['6', 'middle age', 'no', 'no', 'normal'],
                   ['7', 'middle age', 'no', 'no', 'good'],
                   ['8', 'middle age', 'yes', 'yes', 'good'],
                   ['9', 'middle age', 'no', 'yes', 'very good'],
                   ['10', 'middle age', 'no', 'yes', 'very good'],
                   ['11', 'old age', 'no', 'yes', 'very good'],
                   ['12', 'old age', 'no', 'yes', 'good'],
                   ['13', 'old age', 'yes', 'no', 'good'],
                   ['14', 'old age', 'yes', 'no', 'very good'],
                   ['15', 'old age', 'no', 'no', 'normal']]

        labels = ['no',
                  'no',
                  'yes',
                  'yes',
                  'no',
                  'no',
                  'no',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'yes',
                  'no']

        return samples, labels

    # def testID3Predict0(self):
    #     samples, labels = self.getTestData0()
    #     id3 = dt.ID3()
    #     id3.train(samples, labels)
    #     print(id3.predict(['no', 'no']))
    #     print(id3.predict(['yes', 'no']))

    # def testID3Train1(self):
    #     samples, labels = self.getTestData1()
    #     id3 = dt.ID3()
    #     id3.train(samples, labels)

    # def testID3Predict1(self):
    #     samples, labels = self.getTestData1()
    #     id3 = dt.ID3()
    #     id3.train(samples, labels)
    #     print(id3.predict(['young', 'no', 'no', 'normal']))
    #     print(id3.predict(['young', 'yes', 'no', 'good']))

    # def testC4_5Predict0(self):
    #     samples, labels = self.getTestData0()
    #     c4_5 = dt.C4_5()
    #     c4_5.train(samples, labels)
    #     print(c4_5.predict(['no', 'no']))
    #     print(c4_5.predict(['yes', 'no']))

    # def testC4_5Predict1(self):
    #     samples, labels = self.getTestData1()
    #     c4_5 = dt.C4_5()
    #     c4_5.train(samples, labels)
    #     print(c4_5.predict(['young', 'no', 'no', 'normal']))
    #     print(c4_5.predict(['young', 'yes', 'no', 'good']))

    # def testC4_5Train2(self):
    #     samples, labels = self.getTestData2()
    #     c4_5 = dt.C4_5()
    #     c4_5.train(samples, labels)

    def testC4_5Predict2(self):
        samples, labels = self.getTestData2()
        c4_5 = dt.C4_5()
        c4_5.train(samples, labels)
        print(c4_5.predict(['1', 'young', 'no', 'no', 'normal']))
        print(c4_5.predict(['3', 'young', 'yes', 'no', 'good']))
        print(c4_5.predict(['100', 'young', 'yes', 'noo', 'good']))

if __name__ == '__main__':
    unittest.main()
