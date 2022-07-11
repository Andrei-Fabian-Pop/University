class History:
    def __init__(self, _id, student, operation, step_of_undo):
        """
        :param _id: unique int
        :param student: student class
        :param operation: "add" or "del" - depending on the operation that'll be done when the undo is called
        :param step_of_undo: non-unique int
        """
        self.__id = _id
        self.__student = student
        self.__operation = operation
        self.__step_of_undo = step_of_undo

    @property
    def id(self):
        return self.__id

    @property
    def student(self):
        return self.__student

    @property
    def operation(self):
        return self.__operation

    @property
    def step(self):
        return self.__step_of_undo


def test_history():
    history_test = History(456, {"id": 456, "name": "al", "group": 916}, "del", 2)
    assert history_test.id == 456
    assert history_test.operation == "del"
    assert history_test.step == 2


test_history()
