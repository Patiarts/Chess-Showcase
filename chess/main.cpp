#include "mainwindow.hh"
#include <QApplication>

/*
 * COMP.CS.155 : 9.5 Shakki : main.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * CHESS GUI PROJECT
 *
 * This is a simplified chess game program.
 * It contains an interactive Chess board and some simple controls.
 * The user(s) can move chess pieces on the chess board
 * in accordance with the (simplified) rules of Chess.
 * They may flip the board, and they may change the color scheme of the board.
 * There are also buttons to restart the game and to quit the application.
 *
 * CHESS RULES:
 * The goal of Chess is to capture the opponent's king.
 * Two players have a set of pieces; one is white, one is black.
 * The chess board is an 8x8 grid of squares in alternating colors.
 *
 * Each set of pieces contains
 * Pawns (P),
 * Knights (K),
 * Bishops (B)
 * Rooks (R),
 * Queens (Q), and
 * Kings (K).
 * The starting configuration of the board is the following:
 *
 * (black)  R K B Q K B K R
 *          P P P P P P P P
 *          . . . . . . . .
 *          . . . . . . . .
 *          . . . . . . . .
 *          . . . . . . . .
 * (white)  P P P P P P P P
 *          R K B Q K B K R
 *
 * White and black take turns moving their pieces according to piece-specific rules:
 * I don't have time to comment this properly. I wonder if the chess rules were required here.
 *
 * GUI EXPLANATION:
 * The chessboard squares can be clicked to choose pieces.
 * When a piece is chosen, legal moves are highlighted in red.
 * Clicking a legal move performs it, and the chess turn is passed to the opponent.
 * When the game is over (a king is captured), the board becomes locked until a new game is started.
 *
 * The "theme" or color scheme can be changed with the "theme" combo box.
 * The board can be flipped with the "Flip board" button.
 * A new chess game is started with the "Restart" button.
 * The "Quit" button closes the application.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
