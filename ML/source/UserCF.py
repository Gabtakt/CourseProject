import collections
from operator import itemgetter

import math

from collections import defaultdict

import similarity
import utils
from utils import LogTime


class UserBasedCF:
    """
    基于用户的协同过滤
    """
    def __init__(self, k_sim_user=40, n_rec_movie=10, use_iif_similarity=False, save_model=True):
        print("UserBasedCF start...\n")
        self.k_sim_user = k_sim_user
        self.n_rec_movie = n_rec_movie
        self.trainset = None
        self.save_model = save_model
        self.use_iif_similarity = use_iif_similarity

    def fit(self, trainset):
        model_manager = utils.ModelManager()
        # 尝试加载model，加载失败则进行训练
        try:
            self.user_sim_mat = model_manager.load_model(
                'user_sim_mat-iif' if self.use_iif_similarity else 'user_sim_mat')
            self.movie_popular = model_manager.load_model('movie_popular')
            self.movie_count = model_manager.load_model('movie_count')
            self.trainset = model_manager.load_model('trainset')
            print('User origin similarity model has saved before.\nLoad model success...\n')
        except OSError:
            print('No model saved before.\nTrain a new model...')
            self.user_sim_mat, self.movie_popular, self.movie_count = \
                similarity.calculate_user_similarity(trainset=trainset,
                                                     use_iif_similarity=self.use_iif_similarity)
            self.trainset = trainset
            print('Train a new model success.')
            if self.save_model:
                model_manager.save_model(self.user_sim_mat,
                                         'user_sim_mat-iif' if self.use_iif_similarity else 'user_sim_mat')
                model_manager.save_model(self.movie_popular, 'movie_popular')
                model_manager.save_model(self.movie_count, 'movie_count')
            print('The new model has saved success.\n')

    def recommend(self, user):
        if not self.user_sim_mat or not self.n_rec_movie or \
                not self.trainset or not self.movie_popular or not self.movie_count:
            raise NotImplementedError('UserCF has not init or fit method has not called yet.')
        K = self.k_sim_user
        N = self.n_rec_movie
        predict_score = collections.defaultdict(int)
        if user not in self.trainset:
            print('The user (%s) not in trainset.' % user)
            return
        watched_movies = self.trainset[user]
        # 选出与用户user评分习惯最相似的K个用户和相似因子
        for similar_user, similarity_factor in sorted(self.user_sim_mat[user].items(),
                                                      key=itemgetter(1), reverse=True)[0:K]:
            for movie, rating in self.trainset[similar_user].items():
                if movie in watched_movies:
                    continue
                # 用户1对该电影的感兴趣程度 += 用户1和用户2的相似因子 * 用户2的评分
                predict_score[movie] += similarity_factor * rating
        # 返回感兴趣程度最高的N部电影作为推荐
        return [movie for movie, _ in sorted(predict_score.items(), key=itemgetter(1), reverse=True)[0:N]]

    def test(self, testset):
        if not self.n_rec_movie or not self.trainset or not self.movie_popular or not self.movie_count:
            raise ValueError('UserCF has not init or fit method has not called yet.')
        self.testset = testset
        print('Test recommendation system start...')
        N = self.n_rec_movie
        hit = 0 # 命中次数
        rec_count = 0 # 推荐数量
        test_count = 0 # 测试数量
        all_rec_movies = set() # 所有推荐电影集合
        popular_sum = 0 # 欢迎度
        
        test_time = LogTime(print_step=1000)
        for i, user in enumerate(self.trainset):
            test_movies = self.testset.get(user, {})
            rec_movies = self.recommend(user)
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
        predict_time = LogTime(print_step=500)
        for i, user in enumerate(testset):
            rec_movies = self.recommend(user)
            movies_recommend[user].append(rec_movies)
            predict_time.count_time()
        print('Predict scores success.')
        predict_time.finish()
        return movies_recommend
