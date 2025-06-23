/*
 * knight.h
 * --------
 * This header defines the structures and function prototypes for solving
 * the Knight Moves problem using BFS (Breadth-First Search).
 *
 * Author: [Your Name]
 * Course: [Course Info, optional]
 * Description:
 * We’re finding the shortest way a knight can move from one square to another
 * on an infinite chessboard. Knight moves in L-shapes: 8 possibilities per turn.
 *
 * Functions:
 * - minKnightMoves: returns the minimum number of moves from start to target
 * - getKnightPath: returns the full path from start to target
 * - isValidPosition: checks if a position is legal (for infinite or bounded boards)
 */

#pragma once
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>

using namespace std;

/*
 * Struct: Pos
 * -----------
 * Represents a position on the chessboard.
 * Contains row and col values (can be negative for infinite board).
 */
struct Pos {
    int row, col;

    // Comparison operators to check if two positions are the same or not
    bool operator==(const Pos& other) const {
        return row == other.row && col == other.col;
    }

    bool operator!=(const Pos& other) const {
        return !(*this == other);
    }
};

/*
 * Struct: PosHash
 * ---------------
 * This lets us use Pos in hash-based containers like unordered_map or unordered_set.
 * We need it because Pos is a custom struct, and C++ needs help to hash it properly.
 */
struct PosHash {
    size_t operator()(const Pos& p) const {
        // Combines row and col hashes using XOR and shift for uniqueness
        return hash<int>()(p.row) ^ (hash<int>()(p.col) << 1);
    }
};

/*
 * Function: minKnightMoves
 * ------------------------
 * Calculates the minimum number of knight moves from start to target.
 * Uses Breadth-First Search (BFS) for shortest path on an infinite board.
 *
 * Returns:
 * - int: number of moves required to reach the target from the start
 *   (returns 0 if already at the target)
 */
int minKnightMoves(const Pos& start, const Pos& target);

/*
 * Function: getKnightPath
 * -----------------------
 * Calculates the actual path taken by the knight from start to target.
 * Also uses BFS, but keeps track of each move so we can reconstruct the full path.
 *
 * Returns:
 * - vector<Pos>: list of positions (in order) from start to target
 */
vector<Pos> getKnightPath(const Pos& start, const Pos& target);

/*
 * Function: isValidPosition
 * -------------------------
 * Checks if a position is valid on the chessboard.
 * - For infinite boards: always returns true
 * - For bounded boards: returns true if within board size (if boardSize > 0)
 *
 * Parameters:
 * - boardSize: optional size of the board (default is -1 for infinite)
 *
 * Returns:
 * - bool: true if position is valid, false otherwise
 */
bool isValidPosition(const Pos& pos, int boardSize = -1);
