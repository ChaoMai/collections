__author__ = 'chaomai'


class NaiveBayes(object):
    '''
    use multinomial model and m-estimator to implement Naive Bayes.
    train with a list of docs, [([word, ...], label), ...].
    '''

    def __init__(self):
        '''
        suppose n is total size of training set, m is categories' amount.
        _nonRepeatedWords: all non-repeated words
        _mergedDocs: [([word, ...], label), ...], length is m
        _prioriProbability: [probability, ...], 1 * m
        '''
        self._mergedDocs = []
        self._nonRepeatedWords = []
        self._prioriProbability = []
        self._conditionalProbability = []

    def appendByItem(self, words, wordsToBeAppended):
        '''
        :param words: words list
        :param wordsToBeAppended: words list
        :return: words list
        '''
        for i in range(len(wordsToBeAppended)):
            words.append(wordsToBeAppended[i])

        return words

    def mergeDocs(self, docs):
        docs = sorted(docs, key=lambda k: k[1])

        mergedDocs = []

        # set initial label
        preLabel = docs[0][1]
        d = []
        for i in range(len(docs)):
            if preLabel == docs[i][1]:
                d = self.appendByItem(d, docs[i][0])
            else:
                mergedDocs.append((d, preLabel))
                preLabel = docs[i][1]
                d = []
                d = self.appendByItem(d, docs[i][0])

            if i + 1 >= len(docs):
                mergedDocs.append((d, preLabel))

        return mergedDocs

    def calculatePrioriProbability(self):
        wordsAmount = 0
        for d in self._mergedDocs:
            wordsAmount += len(d[0])

        for d in self._mergedDocs:
            self._prioriProbability.append(len(d[0]) / wordsAmount)

    def getAppearTimesInCurrentCategory(self, word, category):
        times = 0
        for d in self._mergedDocs:
            if d[1] == category:
                times += d[0].count(word)

        return times

    def calculateConditionalProbability(self):
        '''
        use m-estimator
        '''
        wholeDocs = []
        for d in self._mergedDocs:
            self.appendByItem(wholeDocs, d[0])

        self._nonRepeatedWords = list(set(wholeDocs))
        nonRepeatedWordsCount = len(self._nonRepeatedWords)

        # use multinomial model
        categoryConditionalProbability = []
        for c in self._mergedDocs:
            for w in self._nonRepeatedWords:
                conditionalProbability = (self.getAppearTimesInCurrentCategory(w, c[1]) + 1) / (
                    len(c[0]) + nonRepeatedWordsCount)
                categoryConditionalProbability.append(conditionalProbability)
            self._conditionalProbability.append(categoryConditionalProbability)
            categoryConditionalProbability = []

    def train(self, docs):
        '''
        create a model
        :param docs: a list of docs, [([word, ...], label), ...]
        '''
        self._mergedDocs = self.mergeDocs(docs)

        self.calculatePrioriProbability()
        self.calculateConditionalProbability()

    def getConditionalProbability(self, word, categoryIndex):
        '''
        get conditional probability under current category.
        :param word: word
        :param categoryIndex: current category
        '''
        if not word in self._nonRepeatedWords:
            return 1
        else:
            return self._conditionalProbability[categoryIndex][self._nonRepeatedWords.index(word)]

    def predict(self, doc):
        '''
        predict category of document.
        If none of these words in the inputting document,
        the category of the inputting document will be whichever category occurs most often in the training data.

        see more information about this:
        http://stackoverflow.com/questions/13459935/handling-missing-attributes-in-naive-bayes-classifier?rq=1

        :param doc: a list of words
        :return: category
        '''

        probabilities = []
        for i in range(len(self._mergedDocs)):
            probability = self._prioriProbability[i]
            for w in doc:
                probability *= self.getConditionalProbability(w, i)

            probabilities.append(probability)

        index = probabilities.index(max(probabilities))
        return self._mergedDocs[index][1]
