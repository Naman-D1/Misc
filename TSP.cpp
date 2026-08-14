//A traveler needs to visit all the cities from a list, where distances between all the cities are known.
//Each city must be visited only once. 
//Find the shortest possible route such that he visits each city and returns to the origin city.
//Use Hill Climb Algorithm.


#include <iostream>
#include <algorithm>
#include <limits>
#include <cstdlib>
#include <ctime>

using namespace std;

class Salesman {
public:
    int map[4][4];
    int path[4];

    void createstatic(int newMap[4][4]) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                map[i][j] = newMap[i][j];
            }
        }
    }

    void createdynamic(int newMap[4][4]){
        cout<<"Enter the distance matrix (4x4):"<<endl;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                cin >> map[i][j];
            }
        }
    }


    int calculateCost(const int currentPath[4]) {
        int cost = 0;
        for (int i = 0; i < 4; i++) {
            cost += map[currentPath[i]][currentPath[(i + 1) % 4]];
        }
        return cost;
    }

    // Solves TSP using Hill Climbing algorithm
    int solve(int bestPath[4]) {
        for (int i = 0; i < 4; i++) {
            bestPath[i] = i;
        }

        int currentCost = calculateCost(bestPath);
        bool improved = true;

        while (improved) {
            improved = false;

            for (int i = 0; i < 4 - 1; i++) {
                for (int j = i + 1; j < 4; j++) {
                    
                    swap(bestPath[i], bestPath[j]);
                    int neighborCost = calculateCost(bestPath);

                    if (neighborCost < currentCost) {
                        currentCost = neighborCost;
                        improved = true; 
                    } else {
                        swap(bestPath[i], bestPath[j]);
                    }
                }
            }
        }

        return currentCost;
    }
};

int main() {
    // Example 4x4 distance matrix
    int distanceMatrix[4][4] = {
        {0, 400, 500, 300},
        {400, 0, 300, 500},
        {500, 300, 0, 200},
        {300, 500, 200, 0}
    };

    //int distanceMatrix[4][4];

    Salesman salesman;
    salesman.createstatic(distanceMatrix);
    //salesman.createdynamic(distanceMatrix);

    int bestPath[4];
    int minCost = salesman.solve(bestPath);

    cout << "Best Route: ";
    for (int i = 0; i < 4; i++) {
        cout << bestPath[i] << (i < 3 ? " -> " : "");
    }
    cout << " -> " << bestPath[0] << endl; // Return to start
    cout << "Minimum Cost: " << minCost << endl;

    return 0;
}