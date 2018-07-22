/*C++ for C Programmers: Assignment 3
* Compute Minimum Spanning Tree
* Brittany Deventer
* References:
*   Prim's Algorithm:
*   http://www.geeksforgeeks.org/greedy-algorithms-set-5-prims-minimum-spanning-tree-mst-2/
*   Input graph from file:
*       http://stackoverflow.com/questions/19441727/taking-input-from-a-file-in-c
*   C++ manual:
*       www.cplusplus.com
*/

#include <iostream>
#include <istream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

typedef vector<float> fvect;
typedef vector<int> ivect;
typedef vector<vector<float> > matrix;
typedef vector<bool> bvect;

//Finds a random number to be used in choosing how many edges each node has
float prob()
{

    static default_random_engine randomGenerator;
    static uniform_real_distribution<float> probability(0.0f, 1.0f);

    float p = probability(randomGenerator);
    return p;
}

//Finds edge value based on distance range (always 1.0 to 10.0)
float getEdgeValue(float dstRng)
{
    static default_random_engine randomGenerator;
    static uniform_real_distribution<float> probability(1.0f, dstRng);

    float e = probability(randomGenerator);
    return e;
}

//used in dijkstra function
int shortestPath(fvect dist, bvect closed, int size)
{
    float min = 999999999;
    int minIndex;

    for (int i = 0; i < size; i++)
    {
        if (!closed[i] && dist[i] <= min)
        {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

//used in Prim function
int minimumCost(ivect dist, bvect open, int size)
{
    int min = 9999999;
    int minIndex;

    for (int i = 0; i < size; i++)
    {
        if (!open[i] && dist[i] < min)
        {
            min = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

/*Graph Class*/
class graph{
public:
    matrix m;
    matrix graphFromFile(int size);
    matrix createGraph(float density, float distanceRange, int size);
    float dijkstra(int source, int size, int destination);
    int prim(int size);
    void print(int size);
};
//Creates a matrix of edge distance values from a text file
matrix graph::graphFromFile(int size)
{
    //input file to stream
    ifstream fin;
    fin.open("practice2.txt", ios::in);
    int node, edge, cost;

    //create matrix
    m.clear();
    m.resize(size);
    for (int i = 0; i < size; i++)
    {
        m[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            m[i][j] = 9999;
        }
    }
    //add costs from stream to matrix
    while (fin >> node >> edge >> cost)
    {
        m[node][edge] = cost;
    }

    return m;
}
//Creates of matrix of edge distance values.  -1 means no edge
matrix graph::createGraph(float density, float distanceRange, int size)
{
    float noEdge = -1;
    float hasEdge = 1;
    m.clear();
    vector<bvect> edgeFound;
    edgeFound.clear();
    edgeFound.resize(size);

    //create matrix of size 'size'
    m.resize(size);
    for (int i = 0; i < size; ++i)
    {
        m[i].resize(size);
        edgeFound[i].resize(size);
        for (int j = 0; j < size; ++j)
        {
            edgeFound[i][j] = false;
        }
    }

    //set random edges and values
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (!edgeFound[i][j])
            {
                if (i == j)
                {
                    m[i][j] = m[j][i] = noEdge;
                    //cout << "i == j" << endl;
                    edgeFound[i][j] = edgeFound[j][i] = true;
                }
                else if (prob() < density)
                {
                    m[i][j] = m[j][i] = hasEdge;
                    //cout << "has edge" << endl;
                }
                else
                {
                    m[i][j] = m[j][i] = noEdge;
                    //cout << "no edge" << endl;
                    edgeFound[i][j] = edgeFound[j][i] = true;
                }

                if (m[i][j] == hasEdge && !edgeFound[i][j])
                {
                    float edgeValue = getEdgeValue(distanceRange);
                    m[i][j] = m[j][i] = edgeValue;
                    //cout << "Edge distance is: " << edgeValue << endl;
                    edgeFound[i][j] = edgeFound[j][i] = true;
                }
            }
        }
    }
    return m;
}
//Dijkstra's Shortest Path Algorithm
float graph::dijkstra(int source, int size, int destination)
{
    float infinity = 999999999;
    bvect closed(size); //closed set
    fvect dist(size); //open set
    for (int i = 0; i < size; ++i)
    {
        dist[i] = infinity;
    }
    dist[source] = 0;
    int u;

    //while closed set doesn't include all vertices
    //find min distance and include in closed
    for (int i = 0; i < size; ++i)
    {
        u = shortestPath(dist, closed, size);
        closed[u] = true;
        //Check if we've reached our destination
        if (closed[destination] == true)
        {
            return dist[u];
        }
        //update dist values of adjacent vertices
        for (int j = 0; j < size; ++j)
        {
            if (!closed[j] && m[u][j] != -1 && dist[u] != infinity)
            {
                if (dist[u] + m[u][j] < dist[j])
                {
                    dist[j] = dist[u] + m[u][j];
                }
            }
        }
    }
    cout << "reached end of function, no solution" << endl;
    return -1;
}
//Prim's Minimum Spanning Tree Algorithm
    //returns the cost of the MST
int graph::prim(int size)
{
    ivect dist(size); //cost values used to minimum weight edge
    ivect mst(size); //stores constructed MST
    bvect open(size); //vertices not yet included in tree
    int infinity = 99999;
    bool unused = false;
    //set all distances to max and all vertices to unused
    for (int i = 0; i < size; i++)
    {
        dist[i] = infinity;
        open[i] = unused;
    }

    //make 0 the root node
    dist[0] = 0; //(dist from 0 to 0 is 0)
    mst[0] = -1; //no edge from 0 to 0

    for (int i = 0; i < size - 1; i++)
    {
        //find minimum cost value from open set
        int u = minimumCost(dist, open, size);

        //take u out of open set
        open[u] = true;

        for (int j = 0; j < size; j++)
        {
            //if j is in open set and theres an edge at u j
            if (!open[j] && m[u][j]!= 9999)
            {
                //and if the edge cost is less than the minimum distance stored
                if (m[u][j] < dist[j])
                {
                    //set the minimum edge cost to u in MST
                    mst[j] = u;
                    //set the minimum edge cost to the
                    dist[j] = m[u][j];
                }
            }
        }
    }

    //Print tree
    cout << "Tree: " << endl;
    for (int i = 1; i < size; i++)
    {
        cout << mst[i] << " --> " << i << endl;
    }
    //Compute cost of MST
    int costMST = 0;
    for (int i = 0; i < size; i++)
    {
        costMST = costMST + dist[i];
    }

    return costMST;
}

//prints graph matrix costs
void graph::print(int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << "(";
        for (int j = 0; j < size; ++j)
        {
            cout << m[i][j] << ", ";
        }
        cout << ") " << endl;
    }
}
int main()
{
    graph f, g;
    int size = 20;
    int cost;
    f.graphFromFile(size);
    //f.print(size);
    cost = f.prim(size);
    cout << "Total Cost: " << cost << endl;

    return 0;
}
