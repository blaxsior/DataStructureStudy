from __future__ import annotations #클래스가 자기 자신을 매개변수로 사용하기 위함. 차후 패치가 진행되면 필요 없음.
from typing import Generic, TypeVar #Generics 변수 생성을 위해 Generic 및 TypeVar 사용.

T = TypeVar('T')

class Node:
    """
    링크드 리스트 내부를 구현하는 노드 클래스.
    data : 입력받은 데이터
    next : 다음 노드의 포인터
    """
    def __init__(self, data, next : Node = None):
        """
        @input data : any
        @input next : next node pointer
        """
        self.data = data #
        self.next = next # 다음 노드를 가리키는 포인터

class MyLinkedList(Generic[T]):
    """
    C언어 스타일의 링크드 리스트.
    노드 클래스를 논리적으로 연결시키는 방식으로 데이터를 추가한다. 
    """

    def __init__(self, data: list[T] = []):
        """
        @input data : list[Any]
            만약 data가 인수로 전달되면, append 메서드를 이용하여 리스트에 추가합니다.

        """
        self.head = Node(None) # 구현의 편의성을 위해 더미 노드를 선언
        self.last = self.head # 데이터의 추가를 편하게 하기 위해 마지막 노드를 가리키는 last를 선언
        self.length = 0

        if len(data) > 0:
            for item in data:
                self.add(item)

    def add(self, data: T):
        newNode = Node(data)
        self.last.next = newNode #마지막 노드의 next에 새로운 노드 연결
        self.last = newNode # 새로운 노드를 last로 지정
        self.length += 1

    def delete(self, data : T): 
        cur = self.head
        before = self.head

        while cur.next != None:
            cur = cur.next
            if cur.data == data:
                before.next = cur.next
                retval = cur.data
                del cur # 삭제할 데이터를 발견했다면, 삭제하고 멈춘다.
                self.length -= 1
                return retval
            before = cur
        return None # 끝까지 발견 못하면 None 반환

    def printAll(self):
        cur = self.head
        while cur.next != None:
            cur = cur.next
            print(cur.data, end=' ')
        print()