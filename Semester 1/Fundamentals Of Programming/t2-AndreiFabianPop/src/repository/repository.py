class Repository:
    def __init__(self):
        self.__data = dict()

    def __getitem__(self, item):
        if item in self.__data:
            return self.__data[item]
        else:
            return None

    def add(self, entity):
        if entity.id not in self.__data:
            self.__data[entity.id] = entity

    def get_all(self):
        return [entity for entity in self.__data.values()]
