__author__ = 'chaomai'

import sys
import numpy as np
from optparse import OptionParser
from sklearn.feature_extraction.text import HashingVectorizer
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.feature_extraction.text import TfidfTransformer
from sklearn.pipeline import make_pipeline
from sklearn.decomposition import TruncatedSVD
from sklearn.decomposition import PCA
from sklearn.preprocessing import Normalizer
from sklearn.cluster import KMeans
from sklearn.cluster import FeatureAgglomeration
from nltk.corpus import stopwords
from nltk.stem.snowball import SnowballStemmer
from nltk.tokenize import word_tokenize
from re import search
from time import time

op = OptionParser()
op.add_option("--use-lsa", action="store_true", dest="use_lsa", default=False,
              help="Preprocess features with LSA.")
op.add_option("--use-pca", action="store_true", dest="use_pca", default=False,
              help="Preprocess features with PCA.")
op.add_option("--use-feature-agglomeration", action="store_true",
              dest="use_feature_agglomeration", default=False,
              help="Preprocess documents with Feature Agglomeration.")
op.add_option("--components", dest="n_components", type="int", default=200,
              help="Amount of features after dimensionality reduction")
op.add_option("--n-features", dest="n_features", type=int, default=5000,
              help="Maximum number of features (dimensions).")
op.add_option("--no-idf",
              action="store_false", dest="use_idf", default=True,
              help="Disable Inverse Document Frequency feature weighting.")
op.add_option("--use-hashing",
              action="store_false", dest="use_hashing", default=True,
              help="Use a hashing feature vectorizer")

(opts, args) = op.parse_args()
if len(args) > 0:
    op.error("this script takes no arguments.")
    op.print_help()
    sys.exit(1)

if opts.use_lsa:
    pass
elif opts.use_pca:
    pass
elif opts.use_feature_agglomeration:
    pass
else:
    print("Method of dimensionality reduction is not set!")
    exit(1)

file_name = '/home/chaomai/Documents/IdeaProjects/feature_location/data/AllDatajEdit4.3/Corpus-jEdit4.3/Corpus-jEdit4.3CorpusTransformedStemmed.OUT'

java_keywords_file_name = '/home/chaomai/Documents/IdeaProjects/feature_location/data/java_keywords.txt'

with open(file_name, 'r') as file:
    dataset = file.readlines()

with open(java_keywords_file_name, 'r') as java_keywords_file:
    keywords = java_keywords_file.readlines()
    java_keywords = []
    for k in keywords:
        java_keywords.append(word_tokenize(k)[0])


def tokenize_stop_stem(text):
    tokens = word_tokenize(text)
    filtered_tokens = []
    stop_words = stopwords.words('english')
    for token in tokens:
        if search('[a-zA-Z]', token) and len(token) > 2 \
                and not token in stop_words \
                and not token in java_keywords:
            filtered_tokens.append(token)

    stemmer = SnowballStemmer("english")
    stems = [stemmer.stem(t) for t in filtered_tokens]
    return stems


print("Extracting features from the data")
t0 = time()
if opts.use_hashing:
    if opts.use_idf:
        hasher = HashingVectorizer(n_features=opts.n_features,
                                   non_negative=True,
                                   norm=None, binary=False,
                                   tokenizer=tokenize_stop_stem)

        vectorizer = make_pipeline(hasher, TfidfTransformer())

    else:
        vectorizer = HashingVectorizer(n_features=opts.n_features,
                                       non_negative=False,
                                       norm='l2', binary=False,
                                       tokenizer=tokenize_stop_stem)
else:
    vectorizer = TfidfVectorizer(max_df=0.5, max_features=opts.n_features,
                                 min_df=2, use_idf=opts.use_idf,
                                 tokenizer=tokenize_stop_stem)

X = vectorizer.fit_transform(dataset)
print("done in %fs" % (time() - t0))
print("n_samples: %d, n_features: %d" % X.shape)

if opts.use_lsa:
    print("Performing dimensionality reduction using LSA")
    t0 = time()

    svd = TruncatedSVD(n_components=opts.n_components)
    lsa_pipe = make_pipeline(svd, Normalizer(copy=False))
    X = lsa_pipe.fit_transform(X)

    print("done in %fs" % (time() - t0))
elif opts.use_pca:
    print("Performing dimensionality reduction using PCA")
    t0 = time()

    pca = PCA(n_components=opts.n_components)
    pca_pipe = make_pipeline(pca, Normalizer(copy=False))
    X = pca_pipe.fit_transform(X)

    print("done in %fs" % (time() - t0))
elif opts.use_feature_agglomeration:
    print("Performing dimensionality reduction using Feature Agglomeration")
    t0 = time()

    fa = FeatureAgglomeration(n_clusters=opts.n_components)
    fa_pipe = make_pipeline(fa, Normalizer(copy=False))
    X = fa_pipe.fit(X)

    print("done in %fs" % (time() - t0))

km = KMeans(n_clusters=10, init='k-means++', max_iter=500, n_init=1,
            verbose=False, n_jobs=-1)
print("Clustering sparse data with %s" % km)
t0 = time()
km.fit(X)
print("done in %fs" % (time() - t0))

labels = km.labels_
for i in np.unique(labels):
    print((labels == i).sum())
