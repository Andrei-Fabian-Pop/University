import unittest

from src.repository import Repository, RepositoryException


class RepositoryUnitTest(unittest.TestCase):
    def setUp(self) -> None:
        self.__repo = Repository()

    def tearDown(self) -> None:
        pass

    def test_setItem(self):
        self.__repo[1] = 5
        self.__repo[2] = 18
        self.assertEqual(self.__repo.get_all(), [{1, 5}, {2, 18}])

    def test_getItem(self):
        self.__repo[1] = 5
        self.assertEqual(self.__repo[1], 5)
        with self.assertRaises(RepositoryException) as err:
            _ = self.__repo[66]
        self.assertEqual(str(err.exception), "No such item in the repository.")

    def test_delItem(self):
        self.__repo[1] = 5
        del self.__repo[1]
        self.assertEqual(self.__repo.get_all(), [])
        with self.assertRaises(RepositoryException) as err:
            del self.__repo[66]
        self.assertEqual(str(err.exception), "No such key in the repository.")

    def test_nextAndIter(self):
        self.__repo[1] = 2
        self.__repo[2] = 4
        self.__repo[3] = 6
        self.__repo[4] = 8
        i = 1
        for item in self.__repo:
            self.assertEqual(item, i * 2)
            i += 1

    def test_gnomeSort(self):
        self.assertEqual(self.__repo.gnome_sort([8, 5, 6, 7, 7], lambda a, b: True if a >= b else False),
                         [5, 6, 7, 7, 8])

    def test_filter(self):
        self.assertEqual(self.__repo.filter([1, 2, 4, 4, 5, 6, 8, 9], lambda a: True if a % 2 == 0 else False),
                         [2, 4, 4, 6, 8])
