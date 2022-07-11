import pickle
from src.domain.Student import Student
from src.domain.Discipline import Discipline
from src.domain.Grade import Grade


class RepositoryException(Exception):
    pass


class Repository:
    def __init__(self):
        self._data = dict()

    def __getitem__(self, item):
        if item in self._data:
            return self._data[item]
        else:
            raise RepositoryException("Error. This ID does not exist.")

    def __len__(self):
        return len(self._data)

    def add(self, entity):
        if entity.id in self._data:
            raise RepositoryException("Error. This id is already taken " + str(entity.id))
        self._data[entity.id] = entity

    def delete(self, entity_id):
        print(entity_id)
        print(self._data.keys(), self._data.values())
        if entity_id not in self._data.keys():
            raise RepositoryException("Error. This id does not exist")
        self._data.pop(entity_id)

    def update(self, entity_id, new_entity):
        if entity_id not in self._data.keys():
            raise RepositoryException("Error. This id does not exist")
        if new_entity.id != entity_id:
            raise RepositoryException("Error. The id\'s are not the same")
        self.delete(entity_id)
        self.add(new_entity)

    def get_all(self):
        return [entity for entity in self._data.values()]


class textFileRepository(Repository):
    def __init__(self, save_file, domain):
        super().__init__()
        self.__text_file_name = save_file
        self.__domain_name = domain
        self._load_file()

    def interpret_and_add(self, domain, _id, args):
        self.add(eval(domain + "(int(" + _id + "),*" + str(str(args[:-1]).split(",")) + ")"))

    def _load_file(self):
        try:
            file = open(self.__text_file_name, "rt")
            for line in file.readlines():
                domain, _id, args = line.split(maxsplit=2, sep=",")
                self.interpret_and_add(domain, _id, args)
            file.close()
        except FileNotFoundError:
            print(f"File not found. Input = {self.__text_file_name}")

    def _save_file(self):
        file = open(self.__text_file_name, "w")

        for item in self._data.values():
            file.write(self.__domain_name + "," + ",".join(str(part) for part in vars(item).values()) + "\n")

        file.close()

    def add(self, entity):
        super(textFileRepository, self).add(entity)
        self._save_file()

    def delete(self, entity_id):
        super(textFileRepository, self).delete(entity_id)
        self._save_file()

    def update(self, entity_id, new_entity):
        super(textFileRepository, self).update(entity_id, new_entity)
        self._save_file()


class binFileRepository(Repository):
    def __init__(self, save_file, domain):
        super().__init__()
        self.__bin_file_name = save_file
        self.__domain_name = domain
        self._load_file()

    def _load_file(self):
        try:
            file = open(self.__bin_file_name, "rb")
            self._data = pickle.load(file)
            self._data = {int(key): value for key, value in self._data.items()}
            file.close()
        except EOFError:
            print("File empty.")

    def _save_file(self):
        file = open(self.__bin_file_name, "wb")
        pickle.dump(self._data, file)
        file.close()

    def add(self, entity):
        super(binFileRepository, self).add(entity)
        self._save_file()

    def delete(self, entity_id):
        super(binFileRepository, self).delete(entity_id)
        self._save_file()

    def update(self, entity_id, new_entity):
        super(binFileRepository, self).update(entity_id, new_entity)
        self._save_file()
