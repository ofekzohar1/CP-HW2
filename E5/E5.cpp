#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

using VI = std::vector<int>;
using VVI = std::vector<VI>;

typedef pair<int, int> pi;
typedef tuple<int, int, int> triple;

#define Y first
#define X second
#define PB push_back
#define REP(i, start, stop) for (int i = (start); i <= (stop); i++)
#define arrin(a, n) for(int INPUT=0;INPUT<n;INPUT++)cin>>a[INPUT]

/******* constants ******/

#define WALL 'W'
#define TARGET 'X'
#define MAX_H_W 10
#define EMPTY '.'
#define MAX_ROBOTS 4
char board[MAX_H_W + 1][MAX_H_W + 1]; // Board game array
// Array contain the 4 optional moves
pi one_move[4] = {{-1, 0},  // Move up
                  {1,  0},  // Move down
                  {0,  1}, // Move right
                  {0,  -1}}; // Move left

/***** CONFIG type ******/

struct config { // Structure for defining the board's configuration
    pi pos[MAX_ROBOTS + 1]; // Contain all robot's position

    // Define '<' operator for CONFIG type so we can use set<CONFIG>
    // Using pair '<' operator and compare by first robot to the last robot
    bool operator<(const struct config &other) const {
        REP(i, 1, MAX_ROBOTS-1) {
            if (pos[i] == other.pos[i]) continue; // If equal position, move to next robot
            return this->pos[i] < other.pos[i];
        }
        return this->pos[MAX_ROBOTS] < other.pos[MAX_ROBOTS];
    }
} typedef CONFIG;

typedef vector<CONFIG> VCONFIG; // Array of CONFIG type

// Build new board configuration according to r's new position
CONFIG new_config(CONFIG curr, int r, pi next_pos) {
    CONFIG next = curr;
    next.pos[r] = next_pos;
    return next;
}

/***** pair operator overloads - Simpler +/- operations on pairs ******/

template<typename T, typename U>
pair<T, U> operator+(const pair<T, U> &l, const pair<T, U> &r) {
    return {l.first + r.first, l.second + r.second};
}

template<typename T, typename U>
pair<T, U> operator-(const pair<T, U> &l, const pair<T, U> &r) {
    return {l.first - r.first, l.second - r.second};
}

/** Read board grid.
 * Build starting configuration (in &robots) and define target position (in &target).
 *
 * @param n # of robots
 * @param w board's width
 * @param h board's height
 * @param target target position
 * @param robots starting robots configuration
 */
void read_board(int n, int w, int h, pi &target, CONFIG &robots) {
    char cell;
    REP (i, 1, h) REP(j, 1, w) {
            cin >> cell;
            if (cell == TARGET) {
                target = {i, j}; // Define target cell
                cell = EMPTY;
            }

            int cell_int = cell - '0'; // Convert char number to int
            REP (r, 1, n) {
                if (cell_int == r) { // If cell is robot number r
                    robots.pos[r] = {i, j}; // Set r's position in the starting configuration
                    cell = EMPTY;
                }
            }
            board[i][j] = cell; // Build board skeleton (W/O robot numbers or target cell)
        }
}

/********* BFS *********/

set<CONFIG> visible; // Maintain the visited configurations

/** The ricochet robots solver - using bfs principle and dynamic graph building.
 *
 * @param n # of robots
 * @param w board's width
 * @param h board's height
 * @param l Maximum moves allowed
 * @param start starting configuration
 * @param target target cell position
 * @return min # of moves from starting config to target, if not reachable -1
 */
int bfs_board_config(int n, int w, int h, int l, CONFIG &start, const pi &target) {
    visible.insert(start);
    VCONFIG cur_level = {start};
    int moves = 0; // min # of moves to get to current configuration

    while (moves <= l && !cur_level.empty()) { // At most l moves allowed
        VCONFIG next_level;
        for (CONFIG curr_config: cur_level) {
            if (curr_config.pos[1] == target) return moves;
            if (moves == l) continue; // Maximum moves reached, only check for accepting config
            REP(r, 1, n) { // For any robot on board
                pi curr_pos = curr_config.pos[r]; // r's position
                for (auto move: one_move) { // For any optional move (up,down,right,left)
                    pi next_pos = curr_pos;
                    do { // Keep moving in move direction until get to Wall, board edge or other robot
                        next_pos = next_pos + move;
                        bool coll = false; // True if collide with another robot
                        REP(other_r, 1, n) {
                            if (other_r == r) continue; // Same robot
                            if (next_pos == curr_config.pos[other_r]) {coll = true; break;} // Collision
                        }
                        if (coll) break; // If collision occur, stop moving
                    } while (next_pos.X > 0 && next_pos.X <= w && next_pos.Y > 0 &&
                             next_pos.Y <= h && board[next_pos.Y][next_pos.X] != WALL);
                    next_pos = next_pos - move;
                    if (next_pos == curr_pos) continue; // Not moved at all
                    CONFIG next_config = new_config(curr_config, r, next_pos);
                    if (visible.count(next_config)) continue; // Skip next_config if it was visited
                    next_level.PB(next_config);
                    visible.insert(next_config);
                }
            }
        }
        cur_level = next_level;
        moves++;
    }

    return -1; // Target isn't reachable within l moves
}

/**
 * Key observation - the board's configuration determine by all robots position.
 * Start from starting configuration and move all possible directions.
 * Remember the visited configuration.
 * Stop if reached target or moves limit exceeded
 */
void sol() {
    int n, w, h, l;
    pi target; // Target position
    CONFIG start; // start configuration
    cin >> n >> w >> h >> l;

    read_board(n, w, h, target, start);
    int moves = bfs_board_config(n, w, h, l, start, target); // Solve ricochet robots
    cout << (moves != -1 ? to_string(moves) : "NO SOLUTION");
}

int main() {
    ios_base::sync_with_stdio(false);
#ifndef ONLINE_JUDGE

    // For getting input from input.txt file
    freopen("input.txt", "r", stdin);

    // Printing the Output to output.txt file
    freopen("output.txt", "w", stdout);

#endif

    sol();
    return 0;
}
