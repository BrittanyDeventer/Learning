/*C++ for C Programmers: Assignment 2
* Dijkstra's Shortest Path Algorithm
* Brittany Deventer
* References:
*   Dijkstra Tutorial:
*       https://www.youtube.com/watch?v=VpLkj53uqE8
*       http://www.geeksforgeeks.org/greedy-algorithms-set-6-dijkstras-shortest-path-algorithm/
*   Random Number Generator Tutorial:
*       https://www.youtube.com/watch?v=JGwSEbnJGR0
*   C++ manual
*       www.cplusplus.com
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

using namespace std;

typedef vector<float> fvect;
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

//Graph Class
class graph{
public:
    matrix m;
    matrix createGraph(float density, float distanceRange, int size);
    float dijkstra(int source, int size, int destination);
    void print(int size);
};

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


int main()
{
    graph f, g;
    float a;
    float sum = 0;
    float found = 0;

    //Find average shortest path of density 20%
    cout << " Calculate average for 20% density " << endl;
    f.createGraph(0.2, 10.0, 50);
    for (int i = 1; i < 50; ++i)
    {

        a = f.dijkstra(0, 50, i);
        found++;
        sum = sum + a;
    }
    float average = sum / found;
    cout << "Average for 20% =  " << average << endl;

    //Find average shortest path of density 40%
    cout << " Calculate average for 40% density " << endl;
    g.createGraph(0.4, 5.0, 50);
    for (int i = 1; i < 50; ++i)
    {
        a = g.dijkstra(0, 50, i);
        if (a != -1)
        {
            sum = sum + a;
            found++;
        }
    }
    average = sum / found;
    cout << "Average for 40% =  " << average << endl;
    return 0;
}
