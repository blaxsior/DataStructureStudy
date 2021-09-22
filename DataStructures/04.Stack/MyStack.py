class MyStack:
    def __init__(self):
        self.__innerList = []

    def push(self, item):
        self.__innerList.append(item)

    def pop(self):
        return self.__innerList.pop()