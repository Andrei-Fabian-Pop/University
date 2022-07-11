import unittest

from src.domain.flight import Flight


class RepositoryText:
    def __init__(self, file_name, test_flag=False):
        self.__file_name = file_name
        self.__test_flag = test_flag
        self.__data = {}

        # read input if not in test mode
        if not test_flag:
            file = open(self.__file_name, "rt")
            for line in file:
                arr_line = line.split(",")
                self.__data[arr_line[0]] = Flight(*arr_line)
            file.close()

    def __save_to_file(self):
        """
        saves the self.__data dictionary in the self.__file_name file if the repository is not in testing
        :return:
        """
        if not self.__test_flag:
            file = open(self.__file_name, "wt")
            for item in self.__data.values():
                file.write(",".join([item.id, item.dep_city, item.dep_time, item.arr_city, item.arr_time]))
            file.write("\n")
            file.close()

    def add(self, _id, item):
        """
        adds to the self.__data dictionary the _id:item entry
        :param _id: id
        :param item: item
        :return: none
        """
        if _id in self.__data:
            raise IndexError("ID is already taken.")
        self.__data[_id] = item
        self.__save_to_file()

    def delete(self, _id):
        """
        deletes from the self.__data dictionary the entry with the id _id
        :param _id: id
        :return: none
        """
        if _id not in self.__data:
            raise IndexError
        del self.__data[_id]
        self.__save_to_file()

    def get_all(self):
        """
        constructs a list of all the values of the self.__data dictionary
        :return: list
        """
        res = []
        for item in self.__data.values():
            res.append(item)
        return res


class RepositoryTest(unittest.TestCase):
    def setUp(self) -> None:
        pass

    def tearDown(self) -> None:
        pass

    def test_add(self):
        repo = RepositoryText("", test_flag=True)
        repo.add(1, "flight1")
        self.assertEqual(repo.get_all(), ["flight1"])

    def test_add_same_id(self):
        repo = RepositoryText("", test_flag=True)
        repo.add(1, "flight1")
        with self.assertRaises(IndexError) as err:
            repo.add(1, "flight2")
        self.assertEqual(str(err.exception), "ID is already taken.")

    def test_del(self):
        repo = RepositoryText("", test_flag=True)
        repo.add(1, "flight1")
        repo.delete(1)
        self.assertEqual(repo.get_all(), [])
