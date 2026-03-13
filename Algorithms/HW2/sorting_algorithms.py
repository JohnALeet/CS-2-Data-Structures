import time, random

def bubble_Sort(nums) -> None:

    n = len(nums)

    for i in range(n):
        for j in range( n - 1):
            if nums[j] > nums[j+1]:
                temp = nums[j]
                nums[j] = nums[j+1]
                nums[j+1] = temp
    
    return nums

def selection_sort(nums):

    n = len(nums)
    for i in range(n):
        smallest = nums[i]
        smallest_index = i

        j = i + 1
        while j < n:
            if nums[j] < smallest:
                smallest = nums[j]
                smallest_index = j
            j += 1

    temp = nums[i]
    nums[i] = nums[smallest_index]
    nums[smallest_index] = temp

    return nums

def insertion_sort(nums):

    #I used GeeksforGeeks.org's code as a jumping off point.
    i = 1
    while i < len(nums):
        current = nums[i]
        j = i - 1

        while j >= 0 and nums[j] > current:
            nums[j+1] = nums[j]
            j -= 1
        
        nums[j+1] = current
        i += 1
    return nums

def quick_sort(nums):
    if len(nums) <=1:
        return nums
    
    split = len(nums) // 2
    value = nums[split]

    left = []
    right = []
    equal = []

    for x in nums:
        if x < value:
            left.append(x)
        elif x > value:
            right.append(x)
        else:
            equal.append(x)

    left_sorted = quick_sort(left)
    right_sorted = quick_sort(right)

    return left_sorted + equal + right_sorted


def merge_Sort(nums):

    split = len(nums) // 2

    left = nums[:split]
    right = nums[split:]
    
    #print(left, right)

    return left, right



def main():

    n = 100000

    data = []
    for i in range(n):
        data.append(random.randint(0, 1000000))

    print("Numer of elements in the set: ", n )

    arr = data[:]
    timerStart = time.perf_counter()
    bubble_Sort(arr)
    timerEnd = time.perf_counter()
    print("Bubble Sort time: ", timerEnd - timerStart)

    arr = data[:]
    timerStart = time.perf_counter()
    selection_sort(arr)
    timerEnd = time.perf_counter()
    print("Selection sort time: ", timerEnd - timerStart)

    arr = data[:]
    timerStart = time.perf_counter()
    insertion_sort(arr)
    timerEnd = time.perf_counter()
    print("Insertion sort time: ", timerEnd - timerStart)

    arr = data[:]
    timerStart = time.perf_counter()
    quick_sort(arr)
    timerEnd = time.perf_counter()
    print("Quick Sort Time: ", timerEnd - timerStart)

    arr = data[:]
    timerStart = time.perf_counter()
    arr.sort()
    timerEnd = time.perf_counter()
    print("Python Sort time: ", timerEnd - timerStart)
    
    arr = data[:]
    timerStart = time.perf_counter()
    merge_Sort(arr)
    timerEnd = time.perf_counter()
    print("Merge sort time: ", timerEnd - timerStart)


if __name__ == "__main__":
    main()