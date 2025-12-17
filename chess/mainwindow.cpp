#include "mainwindow.hh"
#include <QLayout>
#include <QPushButton>
#include <QFile>
#include <QDebug>

/*
 * COMP.CS.155 : 9.5 Shakki : mainwindow.cpp
 * Author: Patrik Reitkivi
 * st.num: 151106280
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
    , game_(Chess())
    , board_widget_(nullptr)
    , squares_grid_(nullptr)
    , selected_square_(nullptr)
    , is_flipped_(false)
    , info_label_(nullptr)
    , color_schemes_({})
{
    // Setting central widget and it's layout
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QHBoxLayout* main_hbox = new QHBoxLayout(central);

    // Initializing the chessboard and inserting it into the main layout
    board_widget_ = new BoardWidget(central);
    squares_grid_ = new QGridLayout(board_widget_);

    // Configuring grid. Grid is filled with ChessSquareWidgets to match the chess game.
    squares_grid_->setSpacing(0);
    squares_grid_->setContentsMargins(32,32,32,32);
    squares_grid_->setOriginCorner(Qt::BottomLeftCorner);

    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){

            // Configuring each ChessSquareWidget
            ChessColor square_col = (ChessColor) ((i+j)%2 == 0);
            Coord square_coord = {i, j};
            ChessSquareWidget* new_square = new ChessSquareWidget(board_widget_, square_col, square_coord);

            connect(new_square, &ChessSquareWidget::clicked_on, this, &MainWindow::on_square_clicked_on);
            connect(this, &MainWindow::some_square_clicked_on, new_square, &ChessSquareWidget::deselect);
            connect(this, &MainWindow::legal_moves_announcement, new_square, &ChessSquareWidget::on_legals_announced);

            squares_grid_->addWidget(new_square, i, j);
        }
    }
    main_hbox->addWidget(board_widget_, 1);

    // Initializing the rest of the UI elements into a frame with a vbox
    QFrame* ui_frame = new QFrame(central);
    QVBoxLayout* ui_box = new QVBoxLayout(ui_frame);
    ui_box->addStretch(1);

    QLabel* title_label = new QLabel(ui_frame);
    title_label->setAlignment(Qt::AlignCenter);
    title_label->setText("PIXEL CHESS");
    ui_box->addWidget(title_label);
    ui_box->addSpacing(32);

    info_label_ = new QLabel(ui_frame);
    info_label_->setAlignment(Qt::AlignCenter);
    ui_box->addWidget(info_label_);

    QLabel* colors_label = new QLabel(ui_frame);
    colors_label->setText("Theme:");

    QComboBox* color_options_box = new QComboBox(ui_frame);
    init_color_schemes_from_file(":/pieces/color_schemes.txt");
    for(int i = 0; i < color_schemes_.size(); i++){
        color_options_box->addItem(color_schemes_[i].name);
    }
    connect(color_options_box, SIGNAL(currentIndexChanged(int)), this, SLOT(combobox_index_changed(int)));

    QHBoxLayout* colors_hbox = new QHBoxLayout();
    colors_hbox->addWidget(colors_label, 1);
    colors_hbox->addWidget(color_options_box, 3);
    ui_box->addLayout(colors_hbox);

    QPushButton* flip_button = new QPushButton(ui_frame);
    flip_button->setText("Flip board");
    connect(flip_button, &QPushButton::clicked, this, &MainWindow::flip_board);
    ui_box->addWidget(flip_button);

    QPushButton* restart_button = new QPushButton(ui_frame);
    restart_button->setText("Restart");
    connect(restart_button, &QPushButton::clicked, this, &MainWindow::restart_game);
    ui_box->addWidget(restart_button);

    QPushButton* quit_button = new QPushButton(ui_frame);
    quit_button->setText("Quit");
    connect(quit_button, &QPushButton::clicked, this, &QMainWindow::close);
    ui_box->addWidget(quit_button);

    ui_box->addStretch(1);
    main_hbox->addWidget(ui_frame);

    restart_game();
    set_color_scheme(ChessColorScheme{"default"});
    resize(1200,900);
}

void MainWindow::flip_board()
{
    // QGridlayout has a very convenient attribute, originCorner.
    // Just changing that is enough to flip the order of the ChessSquareWidgets around.
    is_flipped_?
        squares_grid_->setOriginCorner(Qt::BottomLeftCorner) :
        squares_grid_->setOriginCorner(Qt::TopRightCorner);
    is_flipped_ = !is_flipped_;

    board_widget_->flip_image();
    squares_grid_->update();
}

void MainWindow::restart_game()
{
    // tmp variables are initialized here beceause they really dont need to be
    // re-initialized on every step in the loop
    QLayoutItem* tmp_layout = nullptr;
    ChessSquareWidget* square = nullptr;

    // restarting the game logic, and then setting the
    // ChessSquareWidgets in the squares_grid_ to contain the correct chess piece pointers.
    game_.start_game();
    for(int i = 0; i < BOARD_SIZE; i++){
        for(int j = 0; j < BOARD_SIZE; j++){
            // get layout item at i,j
            tmp_layout = squares_grid_->itemAtPosition(i,j);

            // get the widget in that layout item
            square = static_cast<ChessSquareWidget*>(tmp_layout->widget());

            // setting the correct piece ptr
            square->set_piece(game_.get_board().get_piece_at(square->coord()));
        }
    }
    // un-disabling the board, in case the game was over before
    board_widget_->setDisabled(false);
    update_info_label();
}

void MainWindow::combobox_index_changed(int inx)
{
    // combobox indeces are initialized to match the size of color_schemes_.
    // this check is basically redundant.
    if(inx < 0 || inx >= color_schemes_.size()){
        qDebug() << "Somehow too big index in combobox";
        return;
    }

    set_color_scheme(color_schemes_[inx]);
    update();
}

void MainWindow::set_color_scheme(const ChessColorScheme &palette)
{
    // Call the static methods in PieceImage and ChessSquareWidget to
    // change the colors in all instances.
    PieceImage::set_white_colors(palette.w_piece_base, palette.w_piece_shade);
    PieceImage::set_black_colors(palette.b_piece_base, palette.b_piece_shade);
    ChessSquareWidget::set_white_colors(palette.w_square_base, palette.w_square_hover);
    ChessSquareWidget::set_black_colors(palette.b_square_base, palette.b_square_hover);
}

void MainWindow::on_square_clicked_on(ChessSquareWidget *source)
{
    // If a ChessSquareWidget is moveable, that means it has been highlighted
    // as such; a possible destination for a chess move.
    // If a moveable square is clicked, a move to that spot should be attempted.
    if(source->is_moveable()){
        try_moving(source);
        emit some_square_clicked_on(source);
        return;
    }

    // This is emitted only after the moveable-check, because otherwise, all moveable squares
    // would be set to non-moveable too early.
    // Other than that, all non-clicked squares should be deselected (aka deselect previous selection)
    // in any case, regardless of if current square is selectable.
    emit some_square_clicked_on(source);

    Coord sq_coord = source->coord();
    std::shared_ptr<ChessPiece> piece_ptr = game_.get_board().get_piece_at(sq_coord);

    // If the clicked square has no piece, or if its piece is of the wrong color, it should not be selected.
    if(piece_ptr == nullptr){
        source->deselect();
        return;
    }
    ChessColor piece_color = piece_ptr->get_color();
    if(piece_color != game_.get_current_turn()){
        source->deselect();
        return;
    }

    source->select();
    selected_square_ = source;
    // if a new square is selected, find the legal move destinations of its contained piece.
    std::set<Coord> legal_moves = piece_ptr->get_allowed_moves(game_.get_board());
    // Notify all ChessSquareWidgets to highlight if they ae legal destinations.
    emit legal_moves_announcement(legal_moves);
}

void MainWindow::try_moving(ChessSquareWidget* destination_square)
{
    // The following checks are basically redundant.
    // The logic leading up to try_moving should ensure
    // that a move is valid.
    if(selected_square_ == nullptr){
        qDebug() << "Error: move has no start square";
        return;
    }

    std::shared_ptr<ChessPiece> selected_piece = selected_square_->piece();
    if(selected_piece == nullptr){
        qDebug() << "Error: trying to move no piece";
        return;
    }

    // actually making the chess move in the chess engine.
    bool did_move = game_.make_move(selected_piece, destination_square->coord());
    if(did_move){
        // Moving the pointers in the ChessSquareWidgets as well.
        destination_square->set_piece(selected_piece);
        selected_square_->set_piece(nullptr);
    }

    // If the game is over after a move, disable board widget to disallow further
    // activity on the board.
    if(game_.get_game_state() != IN_PROGRESS){
        board_widget_->setDisabled(true);
    }

    // Finally, deselect (and update) the squares that were moved between.
    selected_square_->deselect();
    selected_square_ = nullptr;
    destination_square->deselect();

    update_info_label();
}

void MainWindow::update_info_label()
{
    GameState game_state = game_.get_game_state();
    ChessColor current_turn = game_.get_current_turn();

    QString text = "";

    if(game_state == IN_PROGRESS){
        (current_turn == WHITE)? text = W_TURN : text = B_TURN;
    }
    else{
        (game_state == WHITE_WIN)? text = W_WIN : text = B_WIN;
    }

    info_label_->setText(text);
}

void MainWindow::init_color_schemes_from_file(const QString &filename)
{
    // Figuring out how to use QFiles to read resource text files was a hassle.

    // making a new input QFile from input filename.
    // if it doesnt open, just... shrug and return. Color schemes aren't so important, and default colors exist.
    QFile input_file(filename);
    if(!input_file.open(QIODevice::ReadOnly | QIODevice::Text)){
        qDebug() << "Error: color scheme file open failed";
        return;
    }
    color_schemes_.clear();

    QString line = "";
    QStringList line_parts = {};
    // Count lines for possible debug messages.
    unsigned int line_n = 0;

    // Read input file line by line.
    while(!input_file.atEnd()){
        line = input_file.readLine();
        // Empty and commented (#) lines are ignored.
        if(line.front() == '#' || line.front() == '\n' || line.isEmpty()){
            line_n++;
            continue;
        }
        // Separate line into the 9 parts; name, and 8 color codes.
        line_parts = line.split(';', Qt::SkipEmptyParts);
        if(line_parts.size() < 9){
            qDebug() << "Line" << line_n << "too few elements\n" << line;
            line_n++;
            continue;
        }

        QString scheme_name = line_parts[0];
        bool conversion_ok = true;
        QVector<QRgb> argb_values = {};

        // try to convert "color codes" into color codes.
        // If that fails, notify and move on to the next line.
        for(int i = 1; i < 9; i++){
            QRgb argb = (QRgb) line_parts[i].toUInt(&conversion_ok, 16); // Color codes are stored as hex numbers
            if(!conversion_ok){
                qDebug() << "Line" << line_n << "invalid color code\n" << line_parts[i];
                break;
            }
            argb_values.append(argb);
        }
        if(!conversion_ok){
            line_n++;
            continue;
        }

        // Finally, initialize and store a new color scheme with the line data.

        ChessColorScheme new_scheme{scheme_name};

        new_scheme.w_piece_base = argb_values[0];
        new_scheme.w_piece_shade = argb_values[1];
        new_scheme.w_square_base = argb_values[2];
        new_scheme.w_square_hover = argb_values[3];

        new_scheme.b_piece_base = argb_values[4];
        new_scheme.b_piece_shade = argb_values[5];
        new_scheme.b_square_base = argb_values[6];
        new_scheme.b_square_hover = argb_values[7];
        line_n++;

        color_schemes_.append(new_scheme);
    }
}

