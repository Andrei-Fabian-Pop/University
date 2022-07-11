from src.repository.Repository import Repository
from src.domain.Discipline import Discipline
import re


class DisciplineService:
    def __init__(self, repo):
        self.__discipline_repo = repo

    def add_discipline(self, _id, name, history_service):
        """
        Adds a new discipline to the repository, it gives an id, either a new one or one that was used before,
        stored in self.__id_dump
        :param _id:
        :param history_service:
        :param name: string
        :return: None
        """
        try:
            for item in self.__discipline_repo.get_all():
                if int(_id) == int(item.id):
                    raise ValueError
            self.__discipline_repo.add(Discipline(int(_id), name))
            history_service.add_expression("add", "discipline", [_id, name])
        except ValueError:
            print("This ID already exists.")

    def delete_discipline(self, disc_id):
        """
        Deletes an instance in Repository by its id
        :param disc_id: int
        :return:None
        """
        self.__discipline_repo.delete(disc_id)

    def update_discipline(self, disc_id, new_name):
        """
        Updates a discipline from discipline Repository
        :param disc_id: id of discipline
        :param new_name: name to be updated
        :return: None
        """
        disc_id = int(disc_id)
        self.__discipline_repo.update(disc_id, Discipline(disc_id, new_name))

    def list_disciplines(self):
        """
        Generates a list containing a list of discipline id and discipline name
        :return: list containing a list of discipline id and discipline name
        """
        return [[discipline.id, discipline.name] for discipline in self.__discipline_repo.get_all()]

    def search_discipline_by_id(self, _id):
        """
        Searches the id given is in the discipline repository
        :param _id: int
        :return: returns the name of the discipline or False, if not found
        """
        discipline_list = self.__discipline_repo.get_all()
        for discipline in discipline_list:
            if discipline.id == _id:
                return discipline
        return False

    def search_discipline_by_string(self, disc_string):
        """
        Searches if the given string is a discipline, using partial string matching
        :param disc_string: string
        :return: False or a list of matches
        """
        discipline_list = self.__discipline_repo.get_all()
        result_list = []
        for discipline in discipline_list:
            if self.check_partial_string(discipline.name, disc_string):
                result_list.append(discipline)
        return False if result_list == [] else result_list

    @staticmethod
    def check_partial_string(discipline1, discipline2):
        """
        Performs a series of checks regarding the partial string matching
        :param discipline1: string
        :param discipline2: string
        :return: True of False, depending on weather it is a match
        """
        discipline1 = discipline1.lower()
        discipline2 = discipline2.lower()

        if (discipline1 in discipline2) or (discipline2 in discipline1):
            return True

        discipline1_reg = ".?".join(discipline1[i] for i in range(len(discipline1)))
        discipline2_reg = ".?".join(discipline2[i] for i in range(len(discipline2)))
        if re.search(discipline1_reg, discipline2) or re.search(discipline2_reg, discipline1):
            return True
        return False
