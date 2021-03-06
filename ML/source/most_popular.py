import random

import math

from collections import defaultdict
from operator import itemgetter

import similarity
import utils


class MostPopular:
    """
    选取欢迎度最高的N个电影进行推荐
    """
    def __init__(self, n_rec_movie=10, save_model=True):
        print("MostPopular start...\n")
        self.n_rec_movie = n_rec_movie
        self.trainset = None
        self.save_model = save_model

    def fit(self, trainset):
        model_manager = utils.ModelManager()
        # 尝试加载model，若加载失败则训练model
        try:
            self.movie_popular = model_manager.load_model('movie_popular')
            self.movie_count = model_manager.load_model('movie_count')
            self.trainset = model_manager.load_model('trainset')
            self.total_movies = model_manager.load_model('total_movies')
            self.movie_popular_sort = model_manager.load_model('movie_popular_sort')
            print('MostPopular model has saved before.\nLoad model success...\n')
        except OSError:
            print('No model saved before.\nTrain a new model...')
            self.trainset = trainset
            self.movie_popular, self.movie_count = similarity.calculate_movie_popular(trainset)
            self.total_movies = list(self.movie_popular.keys())
            self.movie_popular_sort = sorted(self.movie_popular.items(), key=itemgetter(1), reverse=True)
            print('Train a new model success.')
            if self.save_model:
                model_manager.save_model(self.movie_popular, 'movie_popular')
                model_manager.save_model(self.movie_count, 'movie_count')
                model_manager.save_model(self.total_movies, 'total_movies')
                model_manager.save_model(self.movie_popular_sort, 'movie_popular_sort')
                print('The new model has saved success.\n')

    def recommend(self, user):
        if not self.n_rec_movie or not self.trainset or not self.movie_popular \
                or not self.movie_count or not self.movie_popular_sort:
            raise NotImplementedError('MostPopular has not init or fit method has not called yet.')
        N = self.n_rec_movie
        predict_movies = list()
        watched_movies = self.trainset[user]
        for movie, _ in self.movie_popular_sort:
            if len(predict_movies) < N and movie not in watched_movies:
                predict_movies.append(movie)
        return predict_movies

    def test(self, testset):

        if not self.n_rec_movie or not self.trainset or not self.movie_popular \
                or not self.movie_count or not self.movie_popular_sort:
            raise ValueError('UserCF has not init or fit method has not called yet.')
        self.testset = testset
        print('Test recommendation system start...')
        N = self.n_rec_movie
        hit = 0 # 命中次数
        rec_count = 0 # 推荐数量
        test_count = 0 # 测试数量
        all_rec_movies = set() # 所有推荐电影集合
        popular_sum = 0 # 欢迎度

        test_time = utils.LogTime(print_step=1000)
        for i, user in enumerate(self.trainset):
            test_movies = self.testset.get(user, {})
            rec_movies = self.recommend(user)  # type:list
            for movie in rec_movies:
                if movie in test_movies:
                    hit += 1
                all_rec_movies.add(movie)
                popular_sum += math.log(1 + self.movie_popular[movie])
            rec_count += N
            test_count += len(test_movies)
            test_time.count_time()
        precision = hit / (1.0 * rec_count) # 预测精度 = 命中次数 / 推荐数量
        recall = hit / (1.0 * test_count) # 召回率 = 命中次数 / 测试数量
        coverage = len(all_rec_movies) / (1.0 * self.movie_count) # 覆盖率 = 所有推荐电影数 / 总电影数
        popularity = popular_sum / (1.0 * rec_count) # 受欢迎程度 = 欢迎度 / 推荐数量

        print('Test recommendation system success.')
        test_time.finish()

        print('precision=%.4f\trecall=%.4f\tcoverage=%.4f\tpopularity=%.4f\n' %
              (precision, recall, coverage, popularity))

    def predict(self, testset):
        movies_recommend = defaultdict(list)
        print('Predict scores start...')
        predict_time = utils.LogTime(print_step=500)
        for i, user in enumerate(testset):
            rec_movies = self.recommend(user)
            movies_recommend[user].append(rec_movies)
            predict_time.count_time()
        print('Predict scores success.')
        predict_time.finish()
        return movies_recommend
