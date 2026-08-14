//Implementation of Solution of Constraint Satisfaction Problem like
//SEND+MORE=MONEY

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class CSP{
    public:
    // Function to check if the current assignment is valid
    bool isValidAssignment(const vector<int>& assignment, const vector<int>& variables) {
        // Check for unique values (no duplicates)
        for (size_t i = 0; i < assignment.size(); ++i) {
            for (size_t j = i + 1; j < assignment.size(); ++j) {
                if (assignment[i] == assignment[j]) {
                    return false; 
                }
            }
        }

        int S = assignment[0];
        int E = assignment[1];
        int N = assignment[2];
        int D = assignment[3];
        int M = assignment[4];
        int O = assignment[5];
        int R = assignment[6];
        int Y = assignment[7];

        // Ensure that S and M are not zero (leading digits)
        if (S == 0 || M == 0) {
            return false;
        }

        // Calculate SEND, MORE, and MONEY
        int SEND = S * 1000 + E * 100 + N * 10 + D;
        int MORE = M * 1000 + O * 100 + R * 10 + E;
        int MONEY = M * 10000 + O * 1000 + N * 100 + E * 10 + Y;

        return (SEND + MORE == MONEY);
    }

   bool backtrack(vector<int>& assignment,
               const vector<int>& variables,
               int index)
{
    if (index == variables.size()) {
        return isValidAssignment(assignment, variables);
    }

    for (int value = 0; value <= 9; value++) {
        assignment[index] = value;

        // Only check duplicate constraint here
        bool ok = true;
        for (int i = 0; i < index; i++) {
            if (assignment[i] == value) {
                ok = false;
                break;
            }
        }

        if (ok && backtrack(assignment, variables, index + 1))
            return true;
    }

    assignment[index] = -1;
    return false;
}

    void solveCSP() {
        vector<int> variables = {0, 1, 2, 3, 4, 5, 6, 7}; // S, E, N, D, M, O, R, Y
        vector<int> assignment(variables.size(), -1); // Initialize assignment with -1

        if (backtrack(assignment, variables, 0)) {
            cout << "Solution found:\n";
            cout << "S=" << assignment[0] << ", E=" << assignment[1] << ", N=" << assignment[2];
            cout << ", D=" << assignment[3] << ", M=" << assignment[4] << ", O=" << assignment[5] << ", R=" << assignment[6] << ", Y=" << assignment[7] << endl;
        } else {
            cout << "No solution found.\n";
        }
    }
};

int main() {
    CSP csp;
    csp.solveCSP();
    return 0;
}