#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

/*
 * COMP.CS.155 : 9.5 Shakki : mainwindow.hh
 * Author: Patrik Reitkivi
 * st.num: 151106280
 *
 * Main application window for the chess game. Oversees and controls relevant
 * UI elements and chess logic.
 */

#include "chess.hh"
#include "chesssquarewidget.hh"
#include "boardwidget.hh"
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <vector>

// Struct to nicely bundle the color scheme of the chess board.
struct ChessColorScheme{
    QString name;

    QRgb w_piece_base = 0xffffffff;
    QRgb w_piece_shade = 0xffe0e0e0;
    QRgb w_square_base = 0xffc2c2c2;
    QRgb w_square_hover = 0xffa1a1a1;

    QRgb b_piece_base = 0xff525252;
    QRgb b_piece_shade = 0xff2e2e2e;
    QRgb b_square_base = 0xff707070;
    QRgb b_square_hover = 0xffa1a1a1;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    // Connects with ChessSquareWidget::clicked_on.
    // Control selection of squares and when to do a chess move.
    void on_square_clicked_on(ChessSquareWidget* source);

    // Rotate board_widget_ and squares_grid_ 180 degrees.
    void flip_board();

    // restarting game entails calling Chess::start_game and resetting the
    // ChessSquareWidgets
    void restart_game();

    // connects to the color scheme combo box. When combo box index changes,
    // change the color scheme to the corresponding color scheme in color_schemes_.
    void combobox_index_changed(int inx);

signals:
    // Signals to notify chess square widgets about current events
    void some_square_clicked_on(ChessSquareWidget* source);
    void legal_moves_announcement(const std::set<Coord>& legals);

private:
    const QString W_TURN = "White's turn";
    const QString B_TURN = "Black's turn";
    const QString W_WIN = "White wins";
    const QString B_WIN = "Black wins";

    // try_moving should really only "try" moves that are certainly legal.
    // basically, makes a chess move and updates the UI accordingly.
    void try_moving(ChessSquareWidget* destination_square);
    void update_info_label();

    void set_color_scheme(const ChessColorScheme& scheme);

    // Initialize color scheme options from an input file. Called in constructor.
    void init_color_schemes_from_file(const QString& filename);

    // chess game engine for chess game logic
    Chess game_;

    // UI element that contains and squares ChessSquareWidgets (and looks like a chess board)
    BoardWidget* board_widget_;

    // Gridlayout that lays out ChessSquareWidgets in a grid-like layout.
    // Set to be the layout of the board_widget_ in constructor.
    QGridLayout* squares_grid_;

    // Selected square is used to store which square is the origin of
    // an attempted chess move.
    ChessSquareWidget* selected_square_;

    bool is_flipped_;

    // info_label_ displays the status of the game.
    QLabel* info_label_;

    // QVector of available color schemes.
    QVector<ChessColorScheme> color_schemes_;
};

#endif // MAINWINDOW_HH
