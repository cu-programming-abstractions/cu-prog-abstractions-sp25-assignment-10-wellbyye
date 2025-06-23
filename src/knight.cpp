#include "knight.h"
#include <algorithm>
#include <cmath>

using namespace std;

/* -------- minKnightMoves -------- */
int minKnightMoves(const Pos& start, const Pos& target) {
    // Edge case: if we’re already at the target, no moves needed
    if (start == target) return 0;

    // All 8 possible knight moves (row, col deltas)
    vector<pair<int, int>> directions = {
        {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1},
        {+1, +2}, {+1, -2}, {-1, +2}, {-1, -2}
    };

    // Queue for BFS: each element is (position, current move count)
    queue<pair<Pos, int>> q;
    q.push({start, 0});

    // Track visited positions using hash set
    unordered_set<Pos, PosHash> visited;
    visited.insert(start);

    while (!q.empty()) {
        auto [current, steps] = q.front();
        q.pop();

        // Try all 8 possible knight moves
        for (const auto& [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};

            // If we reached the target — return steps + 1
            if (next == target) return steps + 1;

            // If not visited yet, add to queue and mark visited
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push({next, steps + 1});
            }
        }
    }

    // Should never reach here on an infinite board
    return -1;
}

/* -------- getKnightPath -------- */
vector<Pos> getKnightPath(const Pos& start, const Pos& target) {
    // Edge case: if already at the target, just return the starting point
    if (start == target) return {start};

    vector<pair<int, int>> directions = {
        {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1},
        {+1, +2}, {+1, -2}, {-1, +2}, {-1, -2}
    };

    // Queue for BFS
    queue<Pos> q;
    q.push(start);

    // Track where we came from: child -> parent
    unordered_map<Pos, Pos, PosHash> parent;

    // Mark visited positions
    unordered_set<Pos, PosHash> visited;
    visited.insert(start);

    while (!q.empty()) {
        Pos current = q.front();
        q.pop();

        for (const auto& [dr, dc] : directions) {
            Pos next = {current.row + dr, current.col + dc};

            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                parent[next] = current;  // Track path
                q.push(next);

                if (next == target) {
                    // Reconstruct the path by following parents
                    vector<Pos> path;
                    Pos step = target;
                    while (step != start) {
                        path.push_back(step);
                        step = parent[step];
                    }
                    path.push_back(start);
                    reverse(path.begin(), path.end());
                    return path;
                }
            }
        }
    }

    // Fallback (should never reach here)
    return {};
}

/* -------- isValidPosition -------- */
bool isValidPosition(const Pos& pos, int boardSize) {
    // Infinite board = always valid
    if (boardSize == -1) {
        return true;
    }

    // For bounded boards, must be within [0, boardSize)
    return pos.row >= 0 && pos.row < boardSize &&
           pos.col >= 0 && pos.col < boardSize;
}
