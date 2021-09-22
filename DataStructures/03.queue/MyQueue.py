class MyQueue:
    def __init__(self):
        self.__queue = []

    def enqueue(self, value):
        self.__queue.append(value)

    def dequeue(self):
        retVal = self.__queue.pop(0)
        return retVal