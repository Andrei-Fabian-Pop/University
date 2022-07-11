# # # import texttable
# # #
# # # tableObj = texttable.Texttable()
# # #
# # # tableObj.set_cols_align(["r", "c", "l"])
# # # tableObj.set_cols_dtype(["t", "i", "t"])
# # #
# # # tableObj.add_rows([
# # #         ["ORGANIZATION", "ESTABLISHED", "CEO"],
# # #         ["Google", 1998, "Sundar Pichai"],
# # #         ["Microsoft", 1975, "Satya Nadella"],
# # #         ["Nokia", 1865, "Rajeev Suri"],
# # #         ["Geeks for Geeks", 2008, "Sandeep Jain"],
# # #         ["HackerRank", 2007, "Vivek Ravisankar"]
# # #         ])
# # #
# # # print(tableObj.draw())
# #
# # """
# # Created on Dec 16, 2016
# #
# # @author: Arthur
# # """
# #
# # '''
# #     1. Example of a class that overloads '==' operator.
# #     This allows using Python's inbuilt 'in' syntax
# # '''
# #
# #
# # class IDObject:
# #     """
# #     Base class that we use to demonstrate overloading '=='
# #     """
# #
# #     def __init__(self, objectId):
# #         self._id = objectId
# #
# #     @property
# #     def id(self):
# #         return self._id
# #
# #     def __eq__(self, o):
# #         return type(o) == type(self) and o.id == self.id
# #
# #
# # '''
# #     2. We have a few derived classes
# # '''
# #
# #
# # class Car(IDObject):
# #     def __init__(self, carId, make, model):
# #         IDObject.__init__(self, carId)
# #         self._make = make
# #         self._model = model
# #
# #     def __str__(self):
# #         return str(self.id) + " " + str(self._make) + " " + str(self._model)
# #
# #     def __repr__(self):
# #         return str(self)
# #
# #
# # class Student(IDObject):
# #     def __init__(self, studentId, name):
# #         IDObject.__init__(self, studentId)
# #         self._name = name
# #
# #     def __str__(self):
# #         return str(self.id) + " " + self._name
# #
# #     def __repr__(self):
# #         return str(self)
# #
# #
# # '''
# #     3. Let's test how the '==' operator works
# # '''
# #
# #
# # def test_equals():
# #     c1 = Car(1, "Dacia", "Sandero")
# #     c2 = Car(1, "Dacia", "Logan")
# #     c3 = Car(2, "Dacia", "Lodgy")
# #
# #     s1 = Student(1, "Anna")
# #     s2 = Student(1, "John")
# #     s3 = Student(2, "Maria")
# #
# #     print(c1 == c1)
# #     print(s1 == s1)
# #
# #     print(c1 == c2)
# #     print(c1 == c3)
# #
# #     print(s1 == s2)
# #     print(s1 == s3)
# #
# #     print(c1 == s1)
# #     print(c1 == s3)
# #
# #
# # '''
# #     4. Let's test how the 'in' operation works
# # '''
# #
# #
# # def test_in():
# #     c1 = Car(1, "Dacia", "Sandero")
# #     c2 = Car(1, "Dacia", "Logan")
# #     c3 = Car(2, "Dacia", "Lodgy")
# #
# #     s1 = Student(1, "Anna")
# #     s2 = Student(1, "John")
# #     s3 = Student(2, "Maria")
# #
# #     cars = [c1, c2, c3, s1]
# #
# #     print(c1 in cars)
# #     print(s2 in cars)
# #     print(s3 in cars)
# #
# #
# # '''
# #     5. An example of an iterable collection that wraps a list
# # '''
# #
# #
# # class MyCollection:
# #     def __init__(self):
# #         self._data = []
# #
# #     def add(self, o):
# #         self._data.append(o)
# #
# #     def __iter__(self):
# #         """
# #         Return an iterator
# #         NB! This works only when a single iterator is requested at any one time
# #         """
# #         self._iterPoz = 0
# #         return self
# #
# #     def __next__(self):
# #         """
# #         Returns the next element of the iteration
# #         """
# #         if self._iterPoz >= len(self._data):
# #             raise StopIteration()
# #         rez = self._data[self._iterPoz]
# #         self._iterPoz = self._iterPoz + 1
# #         return rez
# #
# #
# # def test_in_collection():
# #     c1 = Car(1, "Dacia", "Sandero")
# #     c2 = Car(2, "Dacia", "Logan")
# #     c3 = Car(3, "Dacia", "Lodgy")
# #     c4 = Car(4, "Dacia", "Duster")
# #
# #     collection = MyCollection()
# #     collection.add(c1)
# #     collection.add(c2)
# #     collection.add(c3)
# #     collection.add(c4)
# #
# #     '''
# #     This calls the __next__ method until StopIteration() is raised
# #     '''
# #     for c in collection:
# #         print(c)
# #
# #     print(c3 in collection)
# #     print(c4 in collection)
# #
# #
# # test_in_collection()
#
# """
# Created on Jan 6, 2017
#
# @author: Arthur
# """
#
# '''
#     Calculate the maximum sum of consecutive elements within an array
#
#     e.g. for array [-2, -5, 6, -2, -3, 1, 5, -6] the maximum sum is 7 (6-2-3+1+5, as the numbers must be consecutive)
# '''
# arr = [-2, -5, 6, -2, -3, 1, 5, -6]
#
# '''
# 1. 1st naive implementation. What is the complexity?
# '''
#
#
# def max_subarray_sum_very_slow(arr):
#     maximum = arr[0]
#     for i in range(0, len(arr)):
#         for j in range(i, len(arr)):
#             s = 0
#             for k in range(i, j + 1):
#                 s += arr[k]
#                 if s > maximum:
#                     maximum = s
#     return maximum
#
#
# '''
# 2. 2nd naive implementation. What is the complexity?
# '''
#
#
# def max_subarray_sum_slow(arr):
#     maximum = arr[0]
#     for i in range(0, len(arr)):
#         s = 0
#         for j in range(i, len(arr)):
#             s += arr[j]
#             if s > maximum:
#                 maximum = s
#     return maximum
#
#
# '''
# 3. Divide & conquer implementation
# '''
#
#
# def max_crossing_sum(array, low, middle, high):
#     """
#     Find the maximum possible temp sum in array such that array[middle] is part of it
#
#     input:
#         low, high - Low and high bounds, respectively
#         middle - the midpoint to consider
#
#     output:
#         The value of the maximum crossing temp_sum
#     """
#     # Include elements on left of middle
#     temp_sum = 0
#     i = middle
#     left_sum = -10 ** 10
#     while i >= low:
#         temp_sum = temp_sum + array[i]
#         i -= 1
#         if temp_sum > left_sum:
#             left_sum = temp_sum
#     # Include elements on right of middle
#     temp_sum = 0
#     i = middle + 1
#     right_sum = -10 ** 10
#     while i <= high:
#         temp_sum = temp_sum + array[i]
#         i += 1
#         if temp_sum > right_sum:
#             right_sum = temp_sum
#     return left_sum + right_sum
#
#
# def max_subarray_sum(array, low, high):
#     """
#     Calculate the maximum subarray sum
#
#     input:
#         array - The input array
#         low, high - Low and high bounds, respectively
#
#     output:
#         The resulting sum value
#     """
#     if low == high:
#         return array[low]
#
#     m = (low + high) // 2
#     return max(max_subarray_sum(array, low, m), max_subarray_sum(array, m + 1, high),
#                max_crossing_sum(array, low, m, high))
#
#
# '''
# 4. Dynamic programming implementation.
# '''
#
#
# def max_subarray(X):
#     """
#     We traverse the array once. For each index i  in the array, we calculate the maximum subarray sum ending at that index.
#     If that sum is larger than the one previously recorded, we remember it (in the max_so_far variable)
#     """
#     max_ending_here = max_so_far = X[0]
#     print(X)
#     for x in X[1:]:
#         max_ending_here = max(x, max_ending_here + x)
#         print("MEH:", max_ending_here, end=", ")
#         max_so_far = max(max_so_far, max_ending_here)
#         print("MSF:", max_so_far)
#
#     return max_so_far
#
#
# data = [-2, -5, 6, -2, -3, 1, 5, -6]
# print(max_subarray(data))
#
# 0-1 Knapsack problem
#

W = 10
values_data = [5, 3, 10, 4, 2]
weights_data = [2, 3, 4, 3, 6]


#
# Version 1 - non dynamic programming
#
def knapsack(W, values, weights, index):
    # Basic case - no more room or we've gone through all items
    if W == 0 or index < 0:
        return 0

    # Item we are currently does not fit in knapsack
    if weights[index] > W:
        return knapsack(W, values, weights, index - 1)
    else:
        # Maximum between the decision of including it or not
        return max(values[index] + knapsack(W - weights[index], values, weights, index - 1),
                   knapsack(W, values, weights, index - 1))


#
# Version 2 - dynamic programming
#

# Pretty-print auxiliary table, this should help follow the algorithm's steps


from texttable import Texttable


def pretty_print(v):
    t = Texttable()
    t.header(['X'] + list(range(W + 1)))
    for i in range(len(v)):
        t.add_row([i] + v[i])
    print(t.draw())


def knapsack_dp(W, values, weights):
    V = [[0 for x in range(W + 1)] for x in range(len(values) + 1)]

    # Go over every item
    for i in range(len(values) + 1):
        # Go over every possible weight
        for j in range(W + 1):
            if i == 0 or j == 0:
                V[i][j] = 0
            elif weights[i - 1] > j:
                # Current item does not fit, do not include it
                V[i][j] = V[i - 1][j]
            else:
                # Maximum between skipping the item and including it
                V[i][j] = max(V[i - 1][j], values[i - 1] + V[i - 1][j - weights[i - 1]])
    pretty_print(V)
    return V[len(values)][W]


print(knapsack_dp(W, values_data, weights_data))