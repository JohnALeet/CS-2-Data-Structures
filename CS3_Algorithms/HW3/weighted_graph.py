class Graph:
    def __init__(self):
    
        self.adjacency_list = {
        "Cardassian Union"  :[("Bajoran", 14),("Romulan Empire", 42) ],
        "Bajoran"  :[("Cardassian Union", 14), ("United Federation of Planets", 22),("Tholian Assembly", 80)],
        "United Federation of Planets" : [("Bajoran", 22),("Romulan Empire", 53),("Klingon Empire", 87)],
        "Romulan Empire" : [("Cardassian Union", 42),("Borg",33), ("United Federation of Planets", 53)],
        "Borg" : [("Tholian Assembly", 10),("Romulan Empire", 33),("Klingon Empire", 41)],
        "Tholian Assembly" : [("Borg",10),("Bajoran",80)],
        "Klingon Empire" : [ ("Borg",41),("United Federation of Planets", 87)]
        }
    
    def depthFirstSearch(self, nodeStart):
        visited = []
        result = []
        stack = []

        if nodeStart not in self.adjacency_list:
            return result
        
        stack.append(nodeStart)
        while stack:
            current = stack.pop()

            if current not in visited:
                visited.append(current)
                result.append(current)
            
                for neighbor, weight in self.adjacency_list[current]:
                    if neighbor not in visited:
                        stack.append(neighbor)
        return result

    
    def breadthFirstSearch(self, nodeStart):
        visited = []
        result = []
        stack = []

        if nodeStart not in self.adjacency_list:
            return result
        
        visited.append(nodeStart)
        stack.append(nodeStart)

        while stack:
            current = stack.pop(0)
            result.append(current)

            for neighbor, weight in self.adjacency_list[current]:
                if neighbor not in visited:
                    visited.append(neighbor)
                    stack.append(neighbor)
        
        return result 



def main():
    graph = Graph()

    print("Greetings, Captain.\n")
    print("Available star systems: ")

    for vertex in graph.adjacency_list:
        print("-", vertex)

    print()
    choice = input("Would you like to run DFS or BFS? ").strip().lower()
    start = input("Enter starting system: \n").strip()

    if start not in graph.adjacency_list:
        print("YOU BROKE IT!!")
        return
    
    if choice == "dfs":
        result = graph.depthFirstSearch(start)
        print("\nEngage DFS Traversal: \n",result)

    elif choice == "bfs":
        result = graph.breadthFirstSearch(start)
        print("\nEngage BFS Traversal: \n", result)

    else: print("Please enter either bfs or dfs.")

if __name__ == "__main__":
    main()