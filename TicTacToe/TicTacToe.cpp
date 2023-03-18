//
//  TicTacToe.cpp
//  starterProject
//
//  Created by Apple Macbook on 16/03/2023.
//

#include "TicTacToe.hpp"


int main() {
    cout << "Round One: Begin! \n Robot == 0\n You == X" << endl;
    
    char layout[3][3] = {   defaultMark, defaultMark, defaultMark,
                            defaultMark, defaultMark, defaultMark,
                            defaultMark, defaultMark, defaultMark };
    int initPos = 0;
    int row, col;
    pair<int, int>  ind;
    pair<int, pair<int, int>> newPos;
    

    while (!isOver(layout)) {
        renderGrid(layout);

        cout << "Enter row no:\n";
        while (!(cin >> row)) {
            cout << "Enter row no \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        row = row - 1;

        cout << "Enter col no \n";
        while (!(cin >> col)) {
            cout << "Enter col no \n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        col = col - 1;

        ind = make_pair(row, col);
        if (isAvailable(layout, ind)) {
            layout[row][col] = PlayerMark;
        }else {
            cout << "Fatal error index out of range \n";
            continue;
        }

        newPos = minimaxAlgo(layout, AIMark, initPos, alphaX, betaX);
        layout[newPos.second.first][newPos.second.second] = AIMark;
    }

    cout << "KO!!\n";
    renderGrid(layout);
    printRes(currStatus(layout, PlayerMark));
    return 0;
}
