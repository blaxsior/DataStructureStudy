from MyLinkedList import MyLinkedList

linked_list = MyLinkedList[int]([1,2,3,4,5,6,7,8,9,10])
print(linked_list.delete(1))
print(linked_list.delete(3))
print(linked_list.delete(4))
print(linked_list.delete(6))
linked_list.printAll()