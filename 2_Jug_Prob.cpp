#include <iostream>
using namespace std;

class jugs_prob {
public:
    struct jug {
        int x = 0, y = 0;
        int parent_index = -1;
    };

    int target;
    int cap1, cap2;
    jug jugs[1000];
    int total_states = 0;

    jugs_prob(int c1, int c2, int t) {
        cap1 = c1;
        cap2 = c2;
        target = t;
    }
    
    jug fill1(jug current) {
        current.x = cap1;
        return current;
    }

    jug fill2(jug current) {
        current.y = cap2;
        return current;
    }

    jug flushx(jug current) {
        current.x = 0;
        return current;
    }

    jug flushy(jug current) {
        current.y = 0;
        return current;
    }

    jug transfer1to2(jug current) {
        if ((current.x + current.y) >= cap2) {
            current.x = current.x - (cap2 - current.y);
            current.y = cap2;
        } else {
            current.y = current.x + current.y;
            current.x = 0;
        }
        return current;
    }

    jug transfer2to1(jug current) {
        if ((current.x + current.y) >= cap1) {
            current.y = current.y - (cap1 - current.x);
            current.x = cap1;
        } else {
            current.x = current.x + current.y;
            current.y = 0;
        }
        return current;
    }
    
    bool is_visited(jug next_state) {
        for (int i = 0; i < total_states; i++) {
            if (jugs[i].x == next_state.x && jugs[i].y == next_state.y) {
                return true;
            }
        }
        return false;
    }

    void solve() {
        jugs[0] = {0, 0, -1};
        total_states = 1;

        int current_index = 0;

        while (current_index < total_states) {
            jug current = jugs[current_index];

            if (current.x == target || current.y == target) {
                std::cout << "Target found! Steps taken:\n";
                print_path(current_index);
                return;
            }

            jug moves[6];
            moves[0] = fill1(current);
            moves[1] = fill2(current);
            moves[2] = flushx(current);
            moves[3] = flushy(current);
            moves[4] = transfer1to2(current);
            moves[5] = transfer2to1(current);

            for (int i = 0; i < 6; i++) {
                moves[i].parent_index = current_index;

                if (!is_visited(moves[i]) && total_states < 1000) {
                    jugs[total_states] = moves[i];
                    total_states++;
                }
            }
            current_index++;
        }

        std::cout << "No solution possible for these targets/capacities.\n";
    }

    void print_path(int index) {
        if (index == -1) return;
        print_path(jugs[index].parent_index);
        std::cout << "Jug 1: " << jugs[index].x << "L | Jug 2: " << jugs[index].y << "L\n";
    }
};

int main() {
    int cap1, cap2, target;
    cout << "Please enter the capacities of the two jugs and the target amount:\n";
    cin >> cap1 >> cap2 >> target;
    jugs_prob problem(cap1, cap2, target);
    problem.solve();
    return 0;
}