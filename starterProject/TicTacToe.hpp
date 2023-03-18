//
//  TicTacToe.hpp
//  starterProject
//
//  Created by Apple Macbook on 16/03/2023.
//

#ifndef TicTacToe_hpp

#include <iostream>
#include <vector>
#include <stdio.h>
#include <limits>

#define TicTacToe_hpp

#define AIMark 'O'
#define PlayerMark 'X'
#define defaultMark '*'

#define Multiplier 1000
#define draw 0
#define betaX numeric_limits<int>::max()
#define alphaX numeric_limits<int>::min()

using namespace std;

const vector<vector<pair<int, int>>> winningPairs = {
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}},
    
    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}},
    
    {{0, 0}, {1, 1}, {2, 2}},
    {{2, 0}, {1, 1}, {0, 2}}
};

void printRes(int state) {
    switch (state) {
        case betaX:
            cout << "Player Won" << endl;
            break;
        case alphaX:
            cout << "Player lost" << endl;
            break;
        case draw:
            cout << "Its a draw" << endl;
            break;
    }
}

void renderGrid(const char (&layout)[3][3]) {
    cout << "\n" <<layout[0][0] << "\t" << layout[0][1] << "\t" << layout[0][2] << "\n\n";
    cout << layout[1][0] << "\t" << layout[1][1] << "\t" << layout[1][2] << "\n\n";
    cout << layout[2][0] << "\t" << layout[2][1] << "\t" << layout[2][2] << "\n\n";
}

vector<pair<int, int>> getAvailPos(const char layout[3][3]) {
    vector<pair<int, int>> availPairs;
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (layout[row][col] != AIMark && layout[row][col] != PlayerMark) {
                availPairs.emplace_back(row, col);
            }
        }
    }
    return availPairs;
}

bool isAvailable(const char (&layout)[3][3], pair<int, int> pos) {
    vector<pair<int, int>> availPos = getAvailPos(layout);
    return find(availPos.begin(), availPos.end(), pos) != availPos.end();
}

bool winningStatus(vector<pair<int, int>> occupied_positions) {
    int num_win_states = winningPairs.size();
    for (int i = 0; i < num_win_states; ++i) {
        const auto& win_state = winningPairs[i];
        if (all_of(win_state.begin(), win_state.end(), [&](auto& pos) {
            return find(begin(occupied_positions), end(occupied_positions), pos) != end(occupied_positions);
        })) {
            return true;
        }
    }
    return false;
}

vector<pair<int, int>> isMarked(const char layout[3][3], char marker) {
    vector<pair<int, int>> markedPairs;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (layout[i][j] == marker) {
                markedPairs.emplace_back(i, j);
            }
        }
    }
    return markedPairs;
}

char get_opponent_marker(char marker) {
    return marker == PlayerMark ? AIMark : PlayerMark;
}


bool isFull(char layout[3][3]) {
    return getAvailPos(layout).size() == 0;
}

int currStatus(char layout[3][3], char marker) {
    const vector<pair<int, int>> occupied_positions = isMarked(layout, marker);
    
    if (winningStatus(occupied_positions))
        return betaX;
    
    const char opponent_marker = get_opponent_marker(marker);
    const vector<pair<int, int>> opponent_occupied_positions = isMarked(layout, opponent_marker);
    
    if (winningStatus(opponent_occupied_positions))
        return alphaX;
    
    if (isFull(layout))
        return draw;
    
    return draw;
}

bool isOver(char layout[3][3]) {
    if (isFull(layout) || (draw != currStatus(layout, AIMark))) {
        return true;
    }
    
    return false;
}

pair<int, pair<int, int>> minimaxAlgo(char layout[3][3], char type,
                                      int step, int alpha, int beta) {
    
    pair<int, int> updatedPos = make_pair(-1, -1);
    int updateScore = (type == AIMark) ? alphaX : betaX;
    
    if (isFull(layout) || currStatus(layout, AIMark) != draw ) {
        updateScore = currStatus(layout, AIMark);
        return make_pair(updateScore, updatedPos);
    }
    
    vector<pair<int, int>> possiblePoses = getAvailPos(layout);
    
    for (int i = 0; i < possiblePoses.size(); i++) {
        
        pair<int, int> currPos = possiblePoses[i];
        layout[currPos.first][currPos.second] = type;
        
        if (type == AIMark) {
            int currScore = minimaxAlgo(layout, PlayerMark, step + 1, alpha, beta).first;
            if (currScore > updateScore) {
                updateScore = currScore - step * Multiplier;
                updatedPos = currPos;
                alpha = max(alpha, updateScore);
                layout[currPos.first][currPos.second] = defaultMark;
                if (alpha >= beta) break;
            }
            
        } else {
            int currScore = minimaxAlgo(layout, AIMark, step + 1, alpha, beta).first;
            if (updateScore > currScore) {
                updateScore = currScore + step * Multiplier;
                updatedPos = currPos;
                beta = min(beta, updateScore);
                layout[currPos.first][currPos.second] = defaultMark;
                if (alpha >= beta) break;
            }
            
        }
        layout[currPos.first][currPos.second] = defaultMark;
    }
    
    return make_pair(updateScore, updatedPos);
}
#endif /* TicTacToe_hpp */
