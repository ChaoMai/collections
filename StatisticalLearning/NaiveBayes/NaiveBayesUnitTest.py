__author__ = 'chaomai'

import unittest
import NaiveBayes as nb


class NaiveBayesTestCase(unittest.TestCase):
    def getTestData(self):
        doc1 = (['Chinese', 'Beijing', 'Chinese'], 'yes')
        doc2 = (['Chinese', 'Chinese', 'Shanghai'], 'yes')
        doc3 = (['Chinese', 'Macao'], 'yes')
        doc4 = (['Tokyo', 'Japan', 'Chinese'], 'no')

        docs = []
        docs.append(doc1)
        docs.append(doc2)
        docs.append(doc3)
        docs.append(doc4)

        return docs

    def testTrain(self):
        docs = self.getTestData()
        n = nb.NaiveBayes()
        n.train(docs)

    def testPredict(self):
        docs = self.getTestData()
        n = nb.NaiveBayes()
        n.train(docs)

        print(n.predict(['Chinese', 'Chinese', 'Chinese', 'Tokyo', 'Japan']))

if __name__ == '__main__':
    unittest.main()
