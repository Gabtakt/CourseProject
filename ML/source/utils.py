import time
import pickle

import os
import shutil

class LogTime:
    """
    count_time()可以在循环中计数.
    finish()停止计数并打印总的计数和花费时间
    """
    def __init__(self, print_step=20000, words=''):
        self.proccess_count = 0
        self.PRINT_STEP = print_step
        self.start_time = time.time()
        self.words = words
        self.total_time = 0.0

    def count_time(self):
        if self.proccess_count % self.PRINT_STEP == 0:
            curr_time = time.time()
            print(self.words + ' steps(%d), %.2f seconds have spent..' % (
                self.proccess_count, curr_time - self.start_time))
        self.proccess_count += 1

    def finish(self):
        print('total %s step number is %d' % (self.words, self.get_curr_step()))
        print('total %.2f seconds have spent\n' % self.get_total_time())

    def get_curr_step(self):
        return self.proccess_count

    def get_total_time(self):
        return time.time() - self.start_time


class ModelManager:
    """
    用于加载和保存训练的model
    """
    path_name = ''

    @classmethod
    def __init__(cls, dataset_name=None, test_size=0.1):
        if not cls.path_name:
            cls.path_name = "model/" + dataset_name + '-testsize' + str(test_size)

    def save_model(self, model, save_name: str):
        if 'pkl' not in save_name:
            save_name += '.pkl'
        if not os.path.exists('model'):
            os.mkdir('model')
        pickle.dump(model, open(self.path_name + "-%s" % save_name, "wb"))

    def load_model(self, model_name: str):
        if 'pkl' not in model_name:
            model_name += '.pkl'
        if not os.path.exists(self.path_name + "-%s" % model_name):
            raise OSError('There is no model named %s in model/ dir' % model_name)
        return pickle.load(open(self.path_name + "-%s" % model_name, "rb"))

    @staticmethod
    def clean_workspace(clean=False):
        if clean and os.path.exists('model'):
            shutil.rmtree('model')
