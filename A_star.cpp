#include <iostream>
#include <queue>
#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <algorithm>
using namespace std;


struct nodes {
    int data[3][3];
    int g;          // cost from source (number of moves so far)
    int h;          // heuristic (Manhattan distance to the goal)
    int f;          // g + h
    int x, y;       // coordinates of the blank tile (0)
    nodes *parent;  // used to reconstruct the solution path
};


struct CompareF {
    bool operator()(nodes* a, nodes* b) {
        return a->f > b->f;
    }
};


string serialize(nodes* n) {
    string s;
    s.reserve(18);
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            s += to_string(n->data[i][j]);
            s += ',';
        }
    return s;
}

class A_star {
public:
    
    int goalRow[9], goalCol[9];
    nodes goalState;

    void readBoard(nodes *node, const string &label) {
        cout << "Enter the " << label << " state of the puzzle (3x3 matrix, use 0 for the blank):" << endl;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cin >> node->data[i][j];
                if (node->data[i][j] == 0) {
                    node->x = i;
                    node->y = j;
                }
            }
        }
    }

    void setGoal() {
        readBoard(&goalState, "goal");
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = goalState.data[i][j];
                goalRow[val] = i;
                goalCol[val] = j;
            }
        }
    }

    void manhattan(nodes* currentnode) {
        int distance = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int val = currentnode->data[i][j];
                if (val != 0) {
                    distance += abs(i - goalRow[val]) + abs(j - goalCol[val]);
                }
            }
        }
        currentnode->h = distance;
    }

    bool isGoal(nodes* n) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (n->data[i][j] != goalState.data[i][j]) return false;
        return true;
    }


    bool isSolvable(nodes* n) {
        int rank[9];
        int order = 0;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (goalState.data[i][j] != 0)
                    rank[goalState.data[i][j]] = order++;

        vector<int> arr;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (n->data[i][j] != 0) arr.push_back(rank[n->data[i][j]]);

        int inversions = 0;
        for (size_t i = 0; i < arr.size(); i++)
            for (size_t j = i + 1; j < arr.size(); j++)
                if (arr[i] > arr[j]) inversions++;

        return inversions % 2 == 0;
    }

    void moveBlank(nodes* cur, int newX, int newY, nodes* child) {
        *child = *cur;
        swap(child->data[cur->x][cur->y], child->data[newX][newY]);
        child->x = newX;
        child->y = newY;
    }

    void generateChildren(nodes* currentnode, vector<nodes*>& children) {
        static const int dx[] = {-1, 1, 0, 0}; // up, down, left, right
        static const int dy[] = {0, 0, -1, 1};

        for (int dir = 0; dir < 4; dir++) {
            int newX = currentnode->x + dx[dir];
            int newY = currentnode->y + dy[dir];
            if (newX >= 0 && newX < 3 && newY >= 0 && newY < 3) {
                nodes* child = new nodes();
                moveBlank(currentnode, newX, newY, child);
                child->g = currentnode->g + 1;
                manhattan(child);
                child->f = child->g + child->h;
                child->parent = currentnode;
                children.push_back(child);
            }
        }
    }

    void printState(nodes* n) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++)
                cout << n->data[i][j] << " ";
            cout << endl;
        }
        cout << endl;
    }

    void printPath(nodes* n) {
        vector<nodes*> path;
        while (n != nullptr) {
            path.push_back(n);
            n = n->parent;
        }
        reverse(path.begin(), path.end());

        cout << "Solution found in " << path.size() - 1 << " moves:\n\n";
        int step = 0;
        for (nodes* p : path) {
            cout << "Step " << step++ << ":" << endl;
            printState(p);
        }
    }

    void solve(nodes* initialNode) {
        manhattan(initialNode);
        initialNode->g = 0;
        initialNode->f = initialNode->h;
        initialNode->parent = nullptr;

        if (!isSolvable(initialNode)) {
            cout << "This puzzle configuration cannot reach the given goal state." << endl;
            return;
        }

        priority_queue<nodes*, vector<nodes*>, CompareF> openList;
        map<string, int> bestG; 

        openList.push(initialNode);
        bestG[serialize(initialNode)] = 0;

        int expanded = 0;
        while (!openList.empty()) {
            nodes* current = openList.top();
            openList.pop();

            string key = serialize(current);
            
            if (bestG.count(key) && bestG[key] < current->g) continue;

            expanded++;

            if (isGoal(current)) {
                printPath(current);
                cout << "Nodes expanded: " << expanded << endl;
                return;
            }

            vector<nodes*> children;
            generateChildren(current, children);
            for (nodes* child : children) {
                string ckey = serialize(child);
                if (!bestG.count(ckey) || child->g < bestG[ckey]) {
                    bestG[ckey] = child->g;
                    openList.push(child);
                } else {
                    delete child; // no improvement over a known path, discard
                }
            }
        }

        cout << "No solution found." << endl;
    }
};

int main() {
    A_star eightPuzzle;
    nodes* initialNode = new nodes();

    eightPuzzle.setGoal();                              // goal state entered first
    eightPuzzle.readBoard(initialNode, "initial");       // then the starting board
    eightPuzzle.solve(initialNode);

    return 0;
}