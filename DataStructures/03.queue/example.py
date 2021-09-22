from queue import Queue
from queue import LifoQueue # Lifo는 Stack과 유사하며, collections.dequeue와도 비슷하다.
from queue import PriorityQueue
from MyQueue import MyQueue

my_queue = Queue()
my_queue.put(123)
my_queue.put("appple")

print(my_queue.get())
print(my_queue.get())

lfqueue = LifoQueue()
lfqueue.put(1234)
lfqueue.put(5678)
print(lfqueue.qsize())
print(lfqueue.get())
print(lfqueue.get())
print(lfqueue.qsize())
#마지막에 넣은 것이 먼저 나온다!

pqueue = PriorityQueue()
pqueue.put((10, "app"))
pqueue.put((2, "ball"))
pqueue.put((7,"dog"))

print(pqueue.get())
print(pqueue.get())
print(pqueue.get())

myq = MyQueue()
myq.enqueue(1)
myq.enqueue(2)
myq.enqueue(3)
print(myq.dequeue())
print(myq.dequeue())
print(myq.dequeue())
