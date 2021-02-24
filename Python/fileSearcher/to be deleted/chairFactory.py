from abc import ABCMeta, abstractmethod, abstractstaticmethod


class Ichair(metaclass=ABCMeta):
    @abstractstaticmethod
    def get_dimentions():
        """chair interface"""


class BigChair(Ichair):
    def __init__(self):
        self.height = 80
        self.width = 80
        self.depth = 80

    def get_dimentions(self):
        # return a dictionary with his dimentions
        return {"height": self.height, "width": self.width,
                    "depth": self.depth}


class MediumChair(Ichair):
    def __init__(self):
        self.height = 60
        self.width = 60
        self.depth = 60

    def get_dimentions(self):
        # return a dictionary with his dimentions
        return {"height": self.height, "width": self.width,
                    "depth": self.depth}


class SmallChair(Ichair):
    def __init__(self):
        self.height = 40
        self.width = 40
        self.depth = 40

    def get_dimentions(self):
        # return a dictionary with his dimentions
        return {"height": self.height, "width": self.width,
                    "depth": self.depth}


class ChairFactory():
    @staticmethod
    def get_chair(chairtype):
        try:
            if chairtype == "BigChair":
                return BigChair()
            if chairtype == "MediumChair":
                return MediumChair()
            if chairtype == "SmallChair":
                return SmallChair()
            raise AssertionError("Chair not found")
        except AssertionError as _e:
            print(_e)


if __name__ == "__main__":
    CHAIR = ChairFactory.get_chair("BigChair")
    print(f"{CHAIR.__class__} {CHAIR.get_dimentions()}")

    CHAIR = ChairFactory.get_chair("SmallChair")
    print(f"{CHAIR.__class__} {CHAIR.get_dimentions()}")

    CHAIR = ChairFactory.get_chair("MediumChair")
    print(f"{CHAIR.__class__} {CHAIR.get_dimentions()}")