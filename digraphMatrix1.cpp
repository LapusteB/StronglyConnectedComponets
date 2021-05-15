#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <queue>
#include "digraphMatrix.h"
using namespace std;


DigraphMatrix::DigraphMatrix(const string& filename)
{
    int v1, v2;
    string str;
    ifstream in(filename);

    if(in.is_open())
    {
        //read in v vertices and e edges
        in >> v >> e;
        in.ignore();// ignores "\n"

        for(int i = 0; i < v; i++)
        {
            vector<bool> b;
            for(int j = 0; j < v; j++)
            b.push_back(false);
        a.push_back(b);
        z.push_back(b);//revserse matrix
        }

        while(in >> v1 >> v2)
        {
            a[v1][v2] = 1;//normal
            z[v2][v1] = 1;//reverse
        }
    }
   in.close();
}

vector<int> DigraphMatrix::GetOutNeighbors(const int& v1)  
{
    vector<int> r;
    int count = 0;
    for (int i = 0; i < v; i++)
    {        
        if (a[v1][i] != 0)
        {
            r.push_back(i);
        }
    }
    return r;
}

vector<int> DigraphMatrix::GetOutNeighbors2(const int& v1)  
{
    vector<int> r;
    int count = 0;
    for (int i = 0; i < v; i++)
    {        
        if (z[v1][i] != 0)
        {
            r.push_back(i);
        }
    }
    return r;
}

void DigraphMatrix::DFS (const int& start, unordered_map<int, mark_t>& marks)
{
    marks[start] = DISCOVERED;
    vector<int> n = GetOutNeighbors(start);

    for (int i = 0; i < n.size(); i++)
        if (marks[n[i]] == UNDISCOVERED)
        {
            DFS(n[i], marks);
        } 

    marks[start] = EXPLORED;
    
    s.push(start); 
   
}
void DigraphMatrix::recDFS (int& start)
{
    unordered_map<int, mark_t> marks;
    for (int i = 0; i < v; i++)
    {
        marks[i] = UNDISCOVERED;
        
    }
    for(int i = 0; i < v; i++)
    {
        if(marks[i] == UNDISCOVERED)
        DFS(i, marks);
    }
}

void DigraphMatrix::SecondDFS(const int& start, unordered_map<int, mark_t>& marks, int count, vector<int>& r)
{
    marks[start] = DISCOVERED;
    vector<int> n = GetOutNeighbors2(start);
    
    for (int i = 0; i < n.size(); i++)
        if (marks[n[i]] == UNDISCOVERED)
        {
            SecondDFS(n[i], marks, count, r);
        } 

    marks[start] = EXPLORED;
    
    cout << start << " ";
    r[start] = count;

}
void DigraphMatrix::recSecondDFS (int& start)
{

}


vector<int> DigraphMatrix::stronglyConnectedComponents() 
{
    int x = 0;
    vector<int> r(v, 0);
    int count = 0;
    cout << "This is the explored order: ";
    recDFS(x);

    unordered_map<int, mark_t> marks;
    for (int i = 0; i < v; i++)
    {
        marks[i] = UNDISCOVERED;
    }    

   

    while(!s.empty())
    {
       
        if(marks[s.top()] == UNDISCOVERED) 
        {
            SecondDFS(s.top(), marks, count, r);
            count++;
        }
        s.pop();
    }
    
   return r;
}

