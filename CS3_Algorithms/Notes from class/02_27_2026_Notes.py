import random
from typing import List, Dict, Tuple

def merge(numList: [List], start: int, mid: int, end: int):

    leftArray = numList[start : mid+1]# We have to specify start when splicing, because 0 doesn't necessarily mean start.

    rightArray = numList[mid+1 : end+1]

    combinedArray = []

    leftArraySize = len(leftArray)
    rightArraySize = len(rightArray)

    leftidx = 0
    rightidx = 0
    
    while leftidx < leftArraySize and rightidx < rightArraySize:
        if leftArray[leftidx] > rightArray[rightidx]:
            combinedArray.append(rightArray[rightidx])
            rightidx += 1
        else:
            combinedArray.append(leftArray[leftidx])
            leftidx += 1

    for i in range(leftidx, leftArraySize):
        combinedArray.append[leftArray[i]]

    
    for i in range(leftidx, rightArraySize):
        combinedArray.append[rightArray[i]]



    #for i in range(min(leftArraySize, rightArraySize)):

def mergeSort(numList: [list], start: int, end: int) -> None:#Doesn't return anything and takes in a list.
    start, end = 0, len(numList) - 1
    mid = (start + end) // 2
    
    if end < start: return
    mergeSort(numList, start, mid -1)
    mergeSort(numList, mid, end)
    merge(numList, start, mid, end)

def main(numList: [list]) -> None:

    numList = []
    for i in range(1000):
        numList.append(random.randint(1, 1000000))

    mergeSort(numList)



if __name__ == '__main__':
    main()