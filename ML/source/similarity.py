import collections

import math

from collections import defaultdict

from utils import LogTime


def calculate_user_similarity(trainset, use_iif_similarity=False):
    """
    计算用户相似度矩阵，建立用户-电影的二维矩阵,只计算存在对同一电影进行评分的用户间的相似度

    :param use_iif_similarity:  是否基于CF IIF计算，若电影欢迎度很高则会降低用户相似度
    :param trainset: 测试数据集
    :return: 用户相似度矩阵
    """
    # 建立电影-用户倒排索引, key=movieID, value=list of userIDs
    print('building movie-users inverse table...')
    movie2users = collections.defaultdict(set)
    movie_popular = defaultdict(int)
    for user, movies in trainset.items():
        for movie in movies:
            movie2users[movie].add(user)
            movie_popular[movie] += 1
    print('building movie-users inverse table success.')

    # 记录用于用户相似度评估的电影数量
    movie_count = len(movie2users)
    print('total movie number = %d' % movie_count)

    # 对用户共同评分的进行计数
    print('generate user co-rated movies similarity matrix...')
    usersim_mat = {}
    movie2users_time = LogTime(print_step=1000)
    for movie, users in movie2users.items():
        for user1 in users:
            # 初始化为0
            usersim_mat.setdefault(user1, defaultdict(int))
            for user2 in users:
                if user1 == user2:
                    continue
                if use_iif_similarity:
                    # 降低欢迎度高的电影的用户间的相似度
                    usersim_mat[user1][user2] += 1 / math.log(1 + len(users))
                else:
                    usersim_mat[user1][user2] += 1
        movie2users_time.count_time()
    print('generate user co-rated movies similarity matrix success.')
    movie2users_time.finish()

    # 计算用户相似度矩阵
    print('calculate user-user similarity matrix...')
    usersim_mat_time = LogTime(print_step=1000)
    for user1, related_users in usersim_mat.items():
        len_user1 = len(trainset[user1])
        for user2, count in related_users.items():
            len_user2 = len(trainset[user2])
            # 用户1和用户2的相似度 = 共同评价电影数 / sqrt(用户1评价电影数 * 用户2评价电影数)
            usersim_mat[user1][user2] = count / math.sqrt(len_user1 * len_user2)
        usersim_mat_time.count_time()

    print('calculate user-user similarity matrix success.')
    usersim_mat_time.finish()
    return usersim_mat, movie_popular, movie_count


def calculate_item_similarity(trainset, use_iuf_similarity=False):
    """
    计算物品相似度矩阵

    :param use_iuf_similarity:  基于Item IUF的相似度计算
                                如果一个用户评价了大量的电影，那么这些电影间的相似度会降低
    :param trainset: 训练数据集
    :return: 物品相似度矩阵
    """
    movie_popular, movie_count = calculate_movie_popular(trainset)

    # 对同一用户评价的电影进行计数
    print('generate items co-rated similarity matrix...')
    movie_sim_mat = {}
    movie2users_time = LogTime(print_step=1000)
    for user, movies in trainset.items():
        for movie1 in movies:
            # 初始化为0
            movie_sim_mat.setdefault(movie1, defaultdict(int))
            for movie2 in movies:
                if movie1 == movie2:
                    continue
                if use_iuf_similarity:
                    # 如果一个用户评价了大量电影，那么这些电影间的相似度会降低
                    movie_sim_mat[movie1][movie2] += 1 / math.log(1 + len(movies))
                else:
                    movie_sim_mat[movie1][movie2] += 1
        movie2users_time.count_time()
    print('generate items co-rated similarity matrix success.')
    movie2users_time.finish()

    # 计算物品相似度矩阵
    print('calculate item-item similarity matrix...')
    movie_sim_mat_time = LogTime(print_step=1000)
    for movie1, related_items in movie_sim_mat.items():
        len_movie1 = movie_popular[movie1]
        for movie2, count in related_items.items():
            len_movie2 = movie_popular[movie2]
            # 物品相似度 = 两电影被同一用户评价数 / sqrt(电影1的评价数 * 电影2的评价数)
            movie_sim_mat[movie1][movie2] = count / math.sqrt(len_movie1 * len_movie2)
        movie_sim_mat_time.count_time()

    print('calculate item-item similarity matrix success.')
    movie_sim_mat_time.finish()
    return movie_sim_mat, movie_popular, movie_count


def calculate_movie_popular(trainset):
    movie_popular = defaultdict(int)
    print('counting movies number and popularity...')

    for user, movies in trainset.items():
        for movie in movies:
            # 对电影受欢迎度进行统计
            movie_popular[movie] += 1
    print('counting movies number and popularity success.')

    movie_count = len(movie_popular)
    print('total movie number = %d' % movie_count)
    return movie_popular, movie_count
