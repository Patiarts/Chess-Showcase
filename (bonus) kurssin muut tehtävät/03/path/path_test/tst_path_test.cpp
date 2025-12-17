/*
COMP.CS.115 : 5.5 Polku : tst_path_test.cpp
Tehtävän tekijä: Patrik Reitkivi
Op.num: 151106280
*/

#include <memory>
#include <QtTest>
#include "../gameboard.hh"

class path_test : public QObject
{
    Q_OBJECT

public:
    path_test();
    ~path_test();

private slots:
    void init();

    // Point-tietueen testejä
    void points_testing();
    void points_testing_data();

    // Itse gameboardin testejä
    void test_initial_fill();
    void test_custom_setup();
    void test_get_at();
    void test_get_at_data();

    void test_are_valid_points();
    void test_are_valid_points_data();

    void test_move1();
    void test_move1_data();

    void test_move2();


private:
    std::shared_ptr<GameBoard> board_;
};

path_test::path_test() {}
path_test::~path_test() {}

void path_test::init()
{
    board_.reset();
    board_ = std::make_shared<GameBoard>(GameBoard());
    board_->initial_fill();
}

void path_test::points_testing()
{
    QFETCH(int, p1x);
    QFETCH(int, p1y);
    QFETCH(int, p2x);
    QFETCH(int, p2y);
    QFETCH(int, rex);
    QFETCH(int, rey);

    Point p1 = {p1x, p1y};
    Point p2 = {p2x, p2y};
    Point result = {rex, rey};

    Point sum = p1 + p2;

    bool eq_test = sum == result;
    bool eq_true = sum.x == result.x && sum.y == result.y;

    QVERIFY2(eq_true, "Point sum or assignment operator fail");
    QVERIFY2(eq_test == eq_true, "Point equality operator fail");
}

void path_test::points_testing_data()
{
    QTest::addColumn<int>("p1x");
    QTest::addColumn<int>("p1y");
    QTest::addColumn<int>("p2x");
    QTest::addColumn<int>("p2y");
    QTest::addColumn<int>("rex");
    QTest::addColumn<int>("rey");

    QTest::newRow("nonzero + zero") << 35 << 76 << 0 << 0 << 35 << 76;
    QTest::newRow("zero + negative nonzero") << 0 << 0 << -999 << 1 << -999 << 1;

    int ran1x = std::rand() % 100 - 50;
    int ran1y = std::rand() % 100 -50;
    int ran2x = std::rand() % 100 - 50;
    int ran2y = std::rand() % 100 -50;
    int ranrex = ran1x + ran2x;
    int ranrey = ran1y + ran2y;

    QTest::newRow("random sum") << ran1x << ran1y << ran2x << ran2y << ranrex << ranrey;
}

void path_test::test_initial_fill()
{
    std::string correct_starting_board = "GGGG"
                                         " o  "
                                         " oo "
                                         " o  "
                                         "RRRR";

    QVERIFY2(board_->get_board() == correct_starting_board, "starting board is incorrect");
}

void path_test::test_custom_setup()
{
    std::string setup = "GooRo  oRooGo   G   ";
    QVERIFY2(board_->custom_setup(setup) == true, "valid setup found invalid");
    QVERIFY2(board_->get_board() == setup, "Valid setup not set");

    setup = " G R o   ";
    QVERIFY2(board_->custom_setup(setup) == false, "wrong size setup found valid");

    setup = "GGGG o   :D  o  RRRR";
    QVERIFY2(board_->custom_setup(setup) == false, ":D found valid");
}

void path_test::test_get_at()
{
    QFETCH(int, px);
    QFETCH(int, py);
    QFETCH(char, result);

    Point p = Point{px,py};

    QVERIFY2(board_->get_at(p) == result, "get at point fail");
    QVERIFY2(board_->get_at(px,py) == result, "get at ints fail");
}

void path_test::test_get_at_data()
{
    QTest::addColumn<int>("px");
    QTest::addColumn<int>("py");
    QTest::addColumn<char>("result");

    QTest::newRow("get green piece G") << 2 << 0 << GREEN_PIECE;
    QTest::newRow("get red piece R") << 3 << 4 << RED_PIECE;
    QTest::newRow("get free space o") << 2 << 2 << FREE_SPACE;
    QTest::newRow("get OOB ' '") << 3 << 3 << OUT_OF_BOUNDS;
}

void path_test::test_are_valid_points()
{
    QFETCH(int, p1x);
    QFETCH(int, p1y);
    QFETCH(int, p2x);
    QFETCH(int, p2y);
    QFETCH(bool, result);

    Point p1 = {p1x, p1y};
    Point p2 = {p2x, p2y};

    QVERIFY2(board_->are_valid_points(p1, p2) == result, "valid points check fail");
}

void path_test::test_are_valid_points_data()
{
    QTest::addColumn<int>("p1x");
    QTest::addColumn<int>("p1y");
    QTest::addColumn<int>("p2x");
    QTest::addColumn<int>("p2y");
    QTest::addColumn<bool>("result");

    QTest::newRow("valid top corner") << 0 << 0 << 1 << 1 << true;
    QTest::newRow("valid bottom corner") << COLUMNS-1 << ROWS-1 << 1 << 1 << true;
    QTest::newRow("invalid OOB 1") << -1 << ROWS << COLUMNS << -1 << false;
    QTest::newRow("invalid OOB 2") << 2 << 2 << 6 << 1 << false;
    QTest::newRow("invalid empty start") << 1 << 1 << 1 << 2 << false;
    QTest::newRow("invalid occupied end") << 1 << 0 << 3 << 0 << false;
    QTest::newRow("invalid point in wall") << 0 << 0 << 2 << 1 << false;
}

void path_test::test_move1()
{
    QFETCH(int, p1x);
    QFETCH(int, p1y);
    QFETCH(int, p2x);
    QFETCH(int, p2y);
    QFETCH(bool, result);

    Point p1 = {p1x, p1y};
    Point p2 = {p2x, p2y};

    QVERIFY2(board_->move(p1, p2) == result, "move return incorrect");
}

void path_test::test_move1_data()
{
    QTest::addColumn<int>("p1x");
    QTest::addColumn<int>("p1y");
    QTest::addColumn<int>("p2x");
    QTest::addColumn<int>("p2y");
    QTest::addColumn<bool>("result");

    QTest::newRow("valid green move one down") << 1 << 0 << 1 << 1 << true;
    QTest::newRow("valid red move to dead end") << 1 << 4 << 2 << 2 << true;
    QTest::newRow("invalid green blocked move") << 3 << 0 << 1 << 0 << false;
    QTest::newRow("invalid red blocked move") << 3 << 4 << 1 << 0 << false;
}

void path_test::test_move2()
{
    std::string premove_board = "oGoo"
                                " o  "
                                " oo "
                                " o  "
                                "oRoo";

    std::string postmove_board ="oooo"
                                " o  "
                                " oo "
                                " G  "
                                "oRoo";

    board_->custom_setup(premove_board);

    // Vihreä siirtyy punaisen yläpuolelle
    bool move_return = board_->move({1,0}, {1,3});
    bool piece_moved_correctly = board_->get_board() == postmove_board;

    QVERIFY2(move_return == true, "move return fail 1");
    QVERIFY2(piece_moved_correctly, "incorrectly moved piece 1");

    premove_board = postmove_board;

    // Punainen yrittää siirtyä vihreän yli
    move_return = board_->move({1,4}, {0,0});
    piece_moved_correctly = board_->get_board() == premove_board;

    QVERIFY2(move_return == false, "move return fail 2");
    QVERIFY2(piece_moved_correctly, "incorrectly moved piece 2");

    postmove_board = "oooo"
                     " o  "
                     " oG "
                     " o  "
                     "oRoo";

    // Vihreä siirtyy taskuun
    move_return = board_->move({1,3}, {2,2});
    piece_moved_correctly = board_->get_board() == postmove_board;

    QVERIFY2(move_return == true, "move return fail 3");
    QVERIFY2(piece_moved_correctly, "incorrectly moved piece 3");

    premove_board = postmove_board;
    postmove_board = "Rooo"
                     " o  "
                     " oG "
                     " o  "
                     "oooo";

    // Punainen siirtyy onnistuneesti
    move_return = board_->move({1,4}, {0,0});
    piece_moved_correctly = board_->get_board() == postmove_board;

    QVERIFY2(move_return == true, "move return fail 4");
    QVERIFY2(piece_moved_correctly, "incorrectly moved piece 4");

    premove_board = postmove_board;
    postmove_board = "Rooo"
                     " o  "
                     " oo "
                     " o  "
                     "oooG";

    // Vihreä siirtyy onnistuneesti
    move_return = board_->move({2,2}, {3,4});
    piece_moved_correctly = board_->get_board() == postmove_board;

    QVERIFY2(move_return == true, "move return fail 5");
    QVERIFY2(piece_moved_correctly, "incorrectly moved piece 5");
}




QTEST_APPLESS_MAIN(path_test)

#include "tst_path_test.moc"
