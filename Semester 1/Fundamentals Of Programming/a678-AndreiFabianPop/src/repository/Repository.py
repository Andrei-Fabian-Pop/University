class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self.__data = dict()

    def __getitem__(self, item):
        if item in self.__data:
            return self.__data[item]
        else:
            raise RepositoryException("Error. This ID does not exist.")

    def __len__(self):
        return len(self.__data)

    def add(self, entity):
        if entity.id in self.__data:
            raise RepositoryException("Error. This id is already taken " + str(entity.id))
        self.__data[entity.id] = entity

    def delete(self, entity_id):
        if entity_id not in self.__data:
            raise RepositoryException("Error. This id does not exist")
        self.__data.pop(entity_id)

    def update(self, entity_id, new_entity):
        if entity_id not in self.__data.keys():
            raise RepositoryException("Error. This id does not exist")
        if new_entity.id != entity_id:
            raise RepositoryException("Error. The id\'s are not the same")
        self.delete(entity_id)
        self.add(new_entity)

    def get_all(self):
        return [entity for entity in self.__data.values()]
