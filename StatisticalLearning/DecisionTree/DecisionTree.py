__author__ = 'chaomai'
import math


class Node(object):
    def __init__(self, subNodes=None, featureIndex=None, feature=None, label=None):
        '''
        nodes in decision tree.
        :param subNodes: list of sub nodes, [subNode1, subNode2, ...]
        :param featureIndex:
        :return:
        '''
        self.subNodes = subNodes
        self.featureIndex = featureIndex
        self.feature = feature
        self.label = label


class ID3(object):
    '''
    implement decision tree with id3.
    don't use threshold when chose best feature.
    '''

    def __init__(self):
        self._root = Node()

    def getNonRepeatedValues(self, data):
        '''
        get non repeated values in list of data
        :param data: list of data
        :return: list of non repeated values
        '''
        return list(set(data))

    def calculateEntropy(self, labels):
        entropy = 0
        for c in self.getNonRepeatedValues(labels):
            ck = labels.count(c)
            d = len(labels)
            if ck != 0:
                entropy += - (ck / d) * math.log2(ck / d)
        return entropy

    def getNonRepeatedFeatureValues(self, samples, featureIndex):
        '''
        get non repeated values at featureIndex in list of data
        :param samples:
        :param featureIndex:
        :return:
        '''
        index = 0
        for s in zip(*samples):
            if index == featureIndex:
                return self.getNonRepeatedValues(s)
            index += 1

    def getNonRepeatedValuesSubSets(self, samples, labels, featureIndex):
        '''
        split into several sub sets.
        :param samples:
        :param labels:
        :param featureIndex:
        :return:
        '''
        nonRepeatedValues = self.getNonRepeatedFeatureValues(samples, featureIndex)

        subSamplesSetDict = {}
        subLabelsSetDict = {}

        for i in range(len(samples)):
            for nrv in nonRepeatedValues:
                if nrv == samples[i][featureIndex]:
                    # add label to corresponding set
                    if not nrv in subSamplesSetDict:
                        subSamplesSetDict[nrv] = []
                    subSamplesSetDict[nrv].append(samples[i])

                    if not nrv in subLabelsSetDict:
                        subLabelsSetDict[nrv] = []
                    subLabelsSetDict[nrv].append(labels[i])
        return subSamplesSetDict, subLabelsSetDict

    def calculateConditionalEntropy(self, samples, labels, featureIndex):
        subSamplesSetDict, subLabelsSetDict = self.getNonRepeatedValuesSubSets(samples, labels, featureIndex)

        # calculate conditional entropy.
        conditionalEntropy = 0
        for k in subLabelsSetDict.keys():
            di = len(subLabelsSetDict[k])
            d = len(labels)
            conditionalEntropy += (di / d) * self.calculateEntropy(subLabelsSetDict[k])
        return conditionalEntropy

    def calculateEntropyGain(self, samples, labels, featureIndex):
        return self.calculateEntropy(labels) - self.calculateConditionalEntropy(samples, labels, featureIndex)

    def findBestFeatureIndex(self, samples, labels, NoUsedFeaturesIndexs):
        entropyGains = []
        for nufi in NoUsedFeaturesIndexs:
            entropyGains.append(self.calculateEntropyGain(samples, labels, nufi))
        return entropyGains.index(max(entropyGains))

    def buildTree(self, samples, labels, NoUsedFeaturesIndexs):
        '''
        build sub trees
        :param samples:
        :param labels:
        :param NoUsedFeaturesIndexs:
        :return: sub nodes
        '''
        # if all features are used or labels are same, then there won't be necessary to create sub nodes.
        if len(NoUsedFeaturesIndexs) == 0 or len(set(labels)) == 1:
            return [Node(None, None, None, max(set(labels), key=labels.count))]

        subNodes = []
        bestFeatureIndex = self.findBestFeatureIndex(samples, labels, NoUsedFeaturesIndexs)
        NoUsedFeaturesIndexs.remove(bestFeatureIndex)
        subSamplesSetDict, subLabelsSetDict = self.getNonRepeatedValuesSubSets(samples, labels, bestFeatureIndex)
        for nrfv in self.getNonRepeatedFeatureValues(samples, bestFeatureIndex):
            subNodes.append(Node(self.buildTree(subSamplesSetDict[nrfv],
                                                subLabelsSetDict[nrfv],
                                                NoUsedFeaturesIndexs),
                                 bestFeatureIndex,
                                 nrfv))
        return subNodes

    def train(self, samples, labels):
        '''
        create a ID3 model.
        :param samples: list of samples, [[f1, f2, ...], ...]
        :param labels: list of labels, [label1, ...]
        '''

        self._root.subNodes = self.buildTree(samples, labels, list(range(len(samples[0]))))

    def traverseTree(self, node, sample):
        if node.subNodes is None:
            return node.label
        else:
            for sn in node.subNodes:
                if sn.feature is not None:
                    if sn.feature == sample[sn.featureIndex]:
                        return self.traverseTree(sn, sample)
                else:
                    return self.traverseTree(sn, sample)
            return 'cannot decide category'

    def predict(self, sample):
        '''
        predict category of inputting sample
        :param sample:
        :return:
        '''
        return self.traverseTree(self._root, sample)


class C4_5(ID3):
    '''
    implement decision tree with C4.5.
    don't use threshold when chose best feature.
    '''

    def getFeatureValues(self, samples, featureIndex):
        '''
        get values at featureIndex in list of data
        :param samples:
        :param featureIndex:
        :return:
        '''
        index = 0
        for s in zip(*samples):
            if index == featureIndex:
                return s
            index += 1

    def calculateFeatureEntropy(self, samples, featureIndex):
        return self.calculateEntropy(self.getFeatureValues(samples, featureIndex))

    def calculateEntropyGainRatio(self, samples, labels, featureIndex):
        a = self.calculateFeatureEntropy(samples,
                                         featureIndex)
        return self.calculateEntropyGain(samples, labels, featureIndex) / self.calculateFeatureEntropy(samples,
                                                                                                       featureIndex)

    def findBestFeatureIndex(self, samples, labels, NoUsedFeaturesIndexs):
        entropyGainRatios = []
        for nufi in NoUsedFeaturesIndexs:
            entropyGainRatios.append(self.calculateEntropyGainRatio(samples, labels, nufi))
        return entropyGainRatios.index(max(entropyGainRatios))


class CART(object):
    pass

# class C4_5(object):
#     '''
#     implement decision tree with C4.5.
#     don't use threshold when chose best feature.
#     '''
#
#     def __init__(self):
#         self._root = Node()
#
#     def getNonRepeatedValues(self, data):
#         '''
#         get non repeated values in list of data
#         :param data: list of data
#         :return: list of non repeated values
#         '''
#         return list(set(data))
#
#     def calculateEntropy(self, labels):
#         entropy = 0
#         for c in self.getNonRepeatedValues(labels):
#             ck = labels.count(c)
#             d = len(labels)
#             if ck != 0:
#                 entropy += - (ck / d) * math.log2(ck / d)
#         return entropy
#
#     def getNonRepeatedFeatureValues(self, samples, featureIndex):
#         '''
#         get non repeated values at featureIndex in list of data
#         :param samples:
#         :param featureIndex:
#         :return:
#         '''
#         index = 0
#         for s in zip(*samples):
#             if index == featureIndex:
#                 return self.getNonRepeatedValues(s)
#             index += 1
#
#     def getNonRepeatedValuesSubSets(self, samples, labels, featureIndex):
#         '''
#         split into several sub sets.
#         :param samples:
#         :param labels:
#         :param featureIndex:
#         :return:
#         '''
#         nonRepeatedValues = self.getNonRepeatedFeatureValues(samples, featureIndex)
#
#         subSamplesSetDict = {}
#         subLabelsSetDict = {}
#
#         for i in range(len(samples)):
#             for nrv in nonRepeatedValues:
#                 if nrv == samples[i][featureIndex]:
#                     # add label to corresponding set
#                     if not nrv in subSamplesSetDict:
#                         subSamplesSetDict[nrv] = []
#                     subSamplesSetDict[nrv].append(samples[i])
#
#                     if not nrv in subLabelsSetDict:
#                         subLabelsSetDict[nrv] = []
#                     subLabelsSetDict[nrv].append(labels[i])
#         return subSamplesSetDict, subLabelsSetDict
#
#     def calculateConditionalEntropy(self, samples, labels, featureIndex):
#         subSamplesSetDict, subLabelsSetDict = self.getNonRepeatedValuesSubSets(samples, labels, featureIndex)
#
#         # calculate conditional entropy.
#         conditionalEntropy = 0
#         for k in subLabelsSetDict.keys():
#             di = len(subLabelsSetDict[k])
#             d = len(labels)
#             conditionalEntropy += (di / d) * self.calculateEntropy(subLabelsSetDict[k])
#         return conditionalEntropy
#
#     def calculateEntropyGain(self, samples, labels, featureIndex):
#         return self.calculateEntropy(labels) - self.calculateConditionalEntropy(samples, labels, featureIndex)
#
#     def getFeatureValues(self, samples, featureIndex):
#         '''
#         get values at featureIndex in list of data
#         :param samples:
#         :param featureIndex:
#         :return:
#         '''
#         index = 0
#         for s in zip(*samples):
#             if index == featureIndex:
#                 return s
#             index += 1
#
#     def calculateFeatureEntropy(self, samples, featureIndex):
#         return self.calculateEntropy(self.getFeatureValues(samples, featureIndex))
#
#     def calculateEntropyGainRatio(self, samples, labels, featureIndex):
#         a = self.calculateFeatureEntropy(samples,
#                                          featureIndex)
#         return self.calculateEntropyGain(samples, labels, featureIndex) / self.calculateFeatureEntropy(samples,
#                                                                                                        featureIndex)
#
#     def findBestFeatureIndex(self, samples, labels, NoUsedFeaturesIndexs):
#         entropyGainRatios = []
#         for nufi in NoUsedFeaturesIndexs:
#             entropyGainRatios.append(self.calculateEntropyGainRatio(samples, labels, nufi))
#         return entropyGainRatios.index(max(entropyGainRatios))
#
#     def buildTree(self, samples, labels, NoUsedFeaturesIndexs):
#         '''
#         build sub trees
#         :param samples:
#         :param labels:
#         :param NoUsedFeaturesIndexs:
#         :return: sub nodes
#         '''
#         # if all features are used or labels are same, then there won't be necessary to create sub nodes.
#         if len(NoUsedFeaturesIndexs) == 0 or len(set(labels)) == 1:
#             return [Node(None, None, None, max(set(labels), key = labels.count))]
#
#         subNodes = []
#         bestFeatureIndex = self.findBestFeatureIndex(samples, labels, NoUsedFeaturesIndexs)
#         NoUsedFeaturesIndexs.remove(bestFeatureIndex)
#         subSamplesSetDict, subLabelsSetDict = self.getNonRepeatedValuesSubSets(samples, labels, bestFeatureIndex)
#         for nrfv in self.getNonRepeatedFeatureValues(samples, bestFeatureIndex):
#             subNodes.append(Node(self.buildTree(subSamplesSetDict[nrfv],
#                                                 subLabelsSetDict[nrfv],
#                                                 NoUsedFeaturesIndexs),
#                                  bestFeatureIndex,
#                                  nrfv))
#         return subNodes
#
#     def train(self, samples, labels):
#         '''
#         create a C4.5 model.
#         :param samples: list of samples, [[f1, f2, ...], ...]
#         :param labels: list of labels, [label1, ...]
#         '''
#
#         self._root.subNodes = self.buildTree(samples, labels, list(range(len(samples[0]))))
#
#     def traverseTree(self, node, sample):
#         if node.subNodes is None:
#             return node.label
#         else:
#             for sn in node.subNodes:
#                 if sn.feature is not None:
#                     if sn.feature == sample[sn.featureIndex]:
#                         return self.traverseTree(sn, sample)
#                 else:
#                     return self.traverseTree(sn, sample)
#             return 'cannot decide category'
#
#     def predict(self, sample):
#         '''
#         predict category of inputting sample
#         :param sample:
#         :return:
#         '''
#         return self.traverseTree(self._root, sample)
