from src.domain.students import Student
from src.domain.history import History


class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self.__data = dict()

    def __getitem__(self, item):
        return self.__data[item]

    def __len__(self):
        return len(self.__data)

    def __delete__(self, instance):
        self.__data.pop(instance)

    def is_in_repo(self, entity):
        if str(entity.id) in self.__data:
            return False
        else:
            return True

    def add(self, entity):
        try:
            if entity.id in self.__data:
                raise RepositoryException
            self.__data[entity.id] = entity
        except RepositoryException:
            print("This entity already exists(", str(entity.id), ")")

    def delete(self, entity):
        try:
            if str(entity.id) in self.__data:
                raise RepositoryException
            self.__delete__(entity.id)
        except RepositoryException:
            print("This entity does not exist(", str(entity.id), ")")


def test_repository():
    repo = Repository()
    repo.add(Student(456456, "Mik", 916))
    repo.add(Student(112112, "Al", 917))
    assert repo[456456].name == "Mik"
    assert repo[456456].group == 916
    repo.delete(Student(456456, "Mik", 916))
    assert len(repo) == 1


test_repository()
