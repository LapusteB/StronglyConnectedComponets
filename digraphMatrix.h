#ifndef __DIGRAPH_MATRIX_H
#define __DIGRAPH_MATRIX_H

#include <string>
#include <stack>
#include <unordered_map>
#include <vector>
using namespace std;

enum mark_t { UNDISCOVERED, DISCOVERED, EXPLORED };

class DigraphMatrix
{
private:
  int e, v;
  vector<vector<bool>> a; 
  stack<int> s;
  vector<vector<bool>> z; 
  unordered_map<int,int> ID;

public:
  //Reads in digraph from given file
  //Stores graph as an adjacency matrix
  DigraphMatrix(const string&);
  void DFS (const int& start, unordered_map<int, mark_t>& marks);
  void recDFS (int& start);
  void SecondDFS(const int& start, unordered_map<int, mark_t>& marks, int count, vector<int> &r);
  void recSecondDFS( int& start);
  vector<int> GetOutNeighbors (const int& v1);
  vector<int> GetOutNeighbors2 (const int& v1);
  void ReverseEdges();
  //Returns number of vertices
  int getOrder() const { return v; }
  vector<vector<bool>> getMatrix() const {return a;}
  stack<int> getStack() const {return s;}
  //Returns vector containing component ID for each vertex
  vector<int> stronglyConnectedComponents();
};

#endif