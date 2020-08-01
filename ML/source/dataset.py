import collections
import os
import itertools
import random
from collections import namedtuple

BuiltinDataset = namedtuple('BuiltinDataset', ['path', 'sep'])

BUILTIN_DATASETS = {
    'ml-100k':
        BuiltinDataset(path='data\\ml-100k\\u.data', sep='\t'),
    'ml-1m'  :
        BuiltinDataset(path='data\\ml-1m\\ratings.dat', sep='::')
}

# 修改seed可影响数据集的划分
random.seed(0)

class DataSet:
    """
    加载,解析,分割数据集的方法类,不需要实例化DataSet对象,直接调用方法
    """
    def __init__(self):
        pass

    @classmethod
    def load_dataset(cls, name='ml-100k'):
        try:
            dataset = BUILTIN_DATASETS[name]
        except KeyError:
            raise ValueError('unknown dataset ' + name + '. Accepted values are ' +
                             ', '.join(BUILTIN_DATASETS.keys()) + '.')
        if not os.path.isfile(dataset.path):
            raise OSError("Dataset data\\" + name + " could not be found in this project.\n")
        with open(dataset.path) as f:
            ratings = [cls.parse_line(line, dataset.sep) for line in itertools.islice(f, 0, None)]
        print("Load " + name + " dataset success.")
        return ratings

    @classmethod
    def parse_line(cls, line: str, sep: str):
        user, movie, rate = line.strip('\r\n').split(sep)[:3]
        return user, movie, rate

    @classmethod
    def train_test_split(cls, ratings, test_size=0.1):
        train, test = collections.defaultdict(dict), collections.defaultdict(dict)
        trainset_len = 0
        testset_len = 0
        for user, movie, rate in ratings:
            if random.random() <= test_size:
                test[user][movie] = int(rate)
                testset_len += 1
            else:
                train[user][movie] = int(rate)
                trainset_len += 1
        print('split data to training set and test set success.')
        print('train set size = %s' % trainset_len)
        print('test set size = %s\n' % testset_len)
        return train, test
