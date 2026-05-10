class MinHeap:
    def __init__(self):
        self.heap = []
        self.current_size = 0

    def size(self):
        return self.current_size

    def is_empty(self):
        return self.current_size == 0

    def __str__(self):
        return "Heap: " + str(self.heap)

    def insert(self, key):
        self.heap.append(key)
        self.current_size += 1
        self.heapify_up(self.current_size - 1)

    def heapify_up(self, index):
        while index > 0:
            parent_index = (index - 1) // 2

            if self.heap[index] < self.heap[parent_index]:
                temp = self.heap[index]
                self.heap[index] = self.heap[parent_index]
                self.heap[parent_index] = temp

                index = parent_index
            else:
                break

    def peek(self):
        if self.is_empty():
            raise Exception("Heap is empty")

        return self.heap[0]

    def extract_min(self):
        if self.is_empty():
            raise Exception("Heap is empty")

        min_value = self.heap[0]

        last_value = self.heap.pop()
        self.current_size -= 1

        if not self.is_empty():
            self.heap[0] = last_value
            self.heapify_down(0)

        return min_value

    def heapify_down(self, index):
        while True:
            left_child = 2 * index + 1
            right_child = 2 * index + 2
            smallest = index

            if left_child < self.current_size and self.heap[left_child] < self.heap[smallest]:
                smallest = left_child

            if right_child < self.current_size and self.heap[right_child] < self.heap[smallest]:
                smallest = right_child

            if smallest != index:
                temp = self.heap[index]
                self.heap[index] = self.heap[smallest]
                self.heap[smallest] = temp

                index = smallest
            else:
                break

    def build_heap(self, array):
        self.heap = array.copy()
        self.current_size = len(self.heap)

        start_index = self.current_size // 2 - 1

        for i in range(start_index, -1, -1):
            self.heapify_down(i)

    def decrease_key(self, index, new_key):
        if index < 0 or index >= self.current_size:
            raise Exception("Index out of range")

        if new_key > self.heap[index]:
            raise Exception("New key is greater than current key")

        self.heap[index] = new_key
        self.heapify_up(index)

    def delete(self, index):
        if index < 0 or index >= self.current_size:
            raise Exception("Index out of range")

        self.decrease_key(index, float("-inf"))
        self.extract_min()


def heap_sort(array):
    heap = MinHeap()
    heap.build_heap(array)

    sorted_list = []

    while not heap.is_empty():
        sorted_list.append(heap.extract_min())

    return sorted_list


def main():
    print("Test 1 — Insert & Peek")
    heap = MinHeap()

    values = [15, 10, 20, 8, 25, 3]

    for value in values:
        heap.insert(value)
        print("Inserted:", value)
        print(heap)
        print("Peek:", heap.peek())
        print()

    print("Test 2 — Extract-Min")

    for i in range(3):
        extracted = heap.extract_min()
        print("Extracted:", extracted)
        print(heap)
        print()

    print("Test 3 — Build-Heap")

    heap2 = MinHeap()
    heap2.build_heap([42, 18, 7, 35, 12, 50, 3, 27])
    print(heap2)
    print()

    print("Test 4 — Decrease Key & Delete")

    heap2.decrease_key(5, 1)
    print("After decrease_key(5, 1):")
    print(heap2)
    print()

    heap2.delete(2)
    print("After delete(2):")
    print(heap2)
    print()

    print("Test 5 — Heap Sort")

    sorted_result = heap_sort([64, 34, 25, 12, 22, 11, 90])
    print(sorted_result)


if __name__ == "__main__":
    main()