class Node:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None


class PriorityQueue:

    def __init__(self):
        self.heap = []
        self.current_size = 0

    def is_empty(self):
        return self.current_size == 0

    def size(self):
        return self.current_size

    def insert(self, node):
        self.heap.append(node)
        self.current_size += 1
        self.heapify_up(self.current_size - 1)

    def extract_min(self):
        if self.is_empty():
            raise Exception("Priority queue is empty")

        min_node = self.heap[0]

        last_node = self.heap.pop()
        self.current_size -= 1

        if not self.is_empty():
            self.heap[0] = last_node
            self.heapify_down(0)

        return min_node

    def heapify_up(self, index):
        while index > 0:
            parent_index = (index - 1) // 2

            if self.heap[index].freq < self.heap[parent_index].freq:
                temp = self.heap[index]
                self.heap[index] = self.heap[parent_index]
                self.heap[parent_index] = temp

                index = parent_index
            else:
                break

    def heapify_down(self, index):
        while True:
            left_child = 2 * index + 1
            right_child = 2 * index + 2
            smallest = index

            if left_child < self.current_size and self.heap[left_child].freq < self.heap[smallest].freq:
                smallest = left_child

            if right_child < self.current_size and self.heap[right_child].freq < self.heap[smallest].freq:
                smallest = right_child

            if smallest != index:
                temp = self.heap[index]
                self.heap[index] = self.heap[smallest]
                self.heap[smallest] = temp

                index = smallest
            else:
                break

def build_frequency_table(text):
    freq = {}

    for char in text:
        if char in freq:
            freq[char] += 1
        else:
            freq[char] = 1

    return freq


def build_huffman_tree(freq):
    pq = PriorityQueue()

    for char in freq:
        node = Node(char, freq[char])
        pq.insert(node)

    if pq.size() == 0:
        return None

    if pq.size() == 1:
        only_node = pq.extract_min()
        parent = Node(None, only_node.freq)
        parent.left = only_node
        return parent

    while pq.size() > 1:
        left = pq.extract_min()
        right = pq.extract_min()

        parent = Node(None, left.freq + right.freq)
        parent.left = left
        parent.right = right

        pq.insert(parent)

    return pq.extract_min()

def generate_codes(root):
    codes = {}

    def walk_tree(node, current_code):
        if node is None:
            return

        if node.char is not None:
            codes[node.char] = current_code
            return

        walk_tree(node.left, current_code + "0")
        walk_tree(node.right, current_code + "1")

    walk_tree(root, "")

    return codes


def encode_text(text, codes):
    encoded = ""

    for char in text:
        encoded += codes[char]

    return encoded


def decode_text(encoded_text, root):
    decoded = ""
    current = root

    for bit in encoded_text:
        if bit == "0":
            current = current.left
        else:
            current = current.right

        if current.char is not None:
            decoded += current.char
            current = root

    return decoded


def print_frequency_table(freq):
    print("Frequency Table:")

    for char in freq:
        if char == " ":
            print("'space':", freq[char])
        elif char == "\n":
            print("'newline':", freq[char])
        else:
            print(char + ":", freq[char])

def print_codes(codes):
    print("Huffman Codes:")

    for char in codes:
        if char == " ":
            print("'space':", codes[char])
        elif char == "\n":
            print("'newline':", codes[char])
        else:
            print(char + ":", codes[char])


def compression_stats(original_text, encoded_text):
    original_size = len(original_text) * 8
    compressed_size = len(encoded_text)

    print("Original size:", original_size, "bits")
    print("Compressed size:", compressed_size, "bits")

    if compressed_size == 0:
        print("Compression ratio: N/A")
    else:
        ratio = original_size / compressed_size
        print("Compression ratio:", round(ratio, 2))


def load_from_file():
    filename = input("Enter file name: ")

    try:
        file = open(filename, "r")
        text = file.read()
        file.close()
        return text
    except:
        print("Could not open file.")
        return ""


def main():
    print("Huffman Coding")
    print("1. Enter a string")
    print("2. Load from file")

    choice = input("Choose an option: ")

    if choice == "1":
        text = input("Enter text: ")
    elif choice == "2":
        text = load_from_file()
    else:
        print("Invalid option.")
        return

    if text == "":
        print("No text entered.")
        return

    freq = build_frequency_table(text)
    root = build_huffman_tree(freq)
    codes = generate_codes(root)
    encoded = encode_text(text, codes)
    decoded = decode_text(encoded, root)

    print()
    print_codes(codes)

    print()
    print("Encoded String:")
    print(encoded)

    print()
    print("Decoded String:")
    print(decoded)

    print()
    print_frequency_table(freq)

    print()
    print("Compression Statistics:")
    compression_stats(text, encoded)


if __name__ == "__main__":
    main()