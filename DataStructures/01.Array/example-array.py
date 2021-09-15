from array import array
from MyArray import MyArray

arr = array('i', [1,2,3,4])
print(arr[3])

#make error if you access the wrong index
try:
    print(arr[4])
except IndexError as err:
    print(err)

arr2 = MyArray(1,2,3,4,5,6,7) # set max length

arr2[3] = 10
arr2[4] = 20 # successfully set !
print(arr2[5])
try: 
    arr2[8] = 14 # can not access wrong index
except IndexError as err:
    print(err)