
def addEdge(u,v, adjMatrix):
    """docstring?"""
    adjMatrix[u][v] = 1
    adjMatrix[v][u] = 1
    # undirected graph, uses 1 to mark if there is an edge at that point
    # having the reverse of the lines makes the graph mirrored
    #  - makes sure that the points can be traversed from either direction

    # use just one adjMatrix[u][v] to do a directed graph
    # use numbers instead of 1 for a weighted graph
    

def checkEdge(u,v, adjMatrix) -> bool:
    return (adjMatrix[u][v] == 1)
    # returns bool of if there is a connection between the two points

def explore(adjMatrix, visited):
    # looks at all edges coming out of a vertex, 
    # uses visited as a flag to mark if a vertex has been explored

    visited[u] = True
    couter = 0
    previsit(u, counter)

    for i in range(len(adjMatrix[u])):
        if adjMatrix[u][i] == 1 and not visited[i]:
            # hasn't been visited and there is an edge connecting to something
            explore(adjMatrix, i, visited)

    postvisit(u)

def genAdjMatrix(graphSize):
    adjMatrix = [[0]*graphSize for _ in range(graphSize)]
    return adjMatrix

def previsit(u, counter):
    counter += 1

def printAdjMatrix(adjMatrix)
    for row in adjMatrix:
        print(row)

def main() -> None:
    graphSize = int(input("How many vertices are in the graph? "))
    adjMatrix = genAdjMatrix(graphSize)
    visited = [False for _ in range(graphSize)]
    addEdge(0,1, adjMatrix)
    addEdge(1,2, adjMatrix)
    addEdge(1,3, adjMatrix)
    addEdge(1,4, adjMatrix)
    addEdge(3,2, adjMatrix)
    printAdjMatrix(adjMatrix)
    explore(adjMatrix, 0, visited)
    print(visited)

if __name__ == "__main__":
    main()