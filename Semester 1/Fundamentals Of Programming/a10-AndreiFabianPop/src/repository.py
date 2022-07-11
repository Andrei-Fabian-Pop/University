class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self._data = dict()
        self.__index = iter(self._data.values())

    def __setitem__(self, key, value):
        self._data[key] = value

    def __getitem__(self, item):
        if item not in self._data:
            raise RepositoryException("No such item in the repository.")
        return self._data[item]

    def __delitem__(self, key):
        if key not in self._data:
            raise RepositoryException("No such key in the repository.")
        self._data.pop(key)

    def __next__(self):
        return next(iter(self.__index))

    def __iter__(self):
        self.__index = iter(self._data.values())
        return self

    def get_all(self):
        return [{key, entity} for key, entity in self._data.items()]

    @staticmethod
    def gnome_sort(array, comp_func):
        index = 0
        while index < len(array):
            if index == 0:
                index += 1
            elif not comp_func(array[index], array[index - 1]):
                array[index], array[index - 1] = array[index - 1], array[index]
                index -= 1
            else:
                index += 1
        return array

    @staticmethod
    def filter(array, filter_function):
        fin = list()
        for item in array:
            if filter_function(item):
                fin.append(item)
        return fin
