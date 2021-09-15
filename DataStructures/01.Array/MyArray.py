class MyArray:  
    def __init__(self, *values):
        self.__length = len(values)
        self.__innerList = list(values)
        #고정된 크기 할당
        #맨 처음에 해당 길이만큼 크기를 할당한다.
        #이 과정이 없으면 존재하지 않는 값을 접근할 수 있다

    def __checkInvalidIdx(self, idx: int): # 인덱스가 잘못된 값일 때 에러 발생
        if idx < 0 or idx >= self.__length :
            raise IndexError('cannot access the wrong index')

    def __getitem__(self, idx: int): # 인덱스를 통해 접근할 때
        self.__checkInvalidIdx(idx)
        return self.__innerList[idx]

    def __setitem__(self, idx: int, value): # 인덱스를 통해 값을 설정할 때
        self.__checkInvalidIdx(idx)
        self.__innerList[idx] = value
    
    def __delitem__(self, idx: int): # 인덱스를 통해 값을 제거할 때
        #instead delete 
        self.__innerList[idx] = None

    def __str__(self) -> str: # 문자열로 제공. C언어에는 사실 없음.
        return self.__innerList