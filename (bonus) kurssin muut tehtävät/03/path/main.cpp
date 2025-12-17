/*
COMP.CS.115 : 5.5 Polku : main.cpp
Tehtävän tekijä: Patrik Reitkivi
Op.num: 151106280

Polkupeli-ohjelma.

SÄÄNNÖT:
'Polku' on yksinpelattava pulmapeli, jota pelataan seuraavanlaisella laudalla (alkuasetelma):

            ===============
            |   | 1 2 3 4 |
            ---------------
            | 1 | G G G G |
            | 2 |   o     |
            | 3 |   o o   |
            | 4 |   o     |
            | 5 | R R R R |
            ===============

Laudan yläreunassa on vihreitä nappuloita (G), ja alareunassa punaisia (R).
Pelin tavoite on siirtää nappuloita tyhjiä ruutuja (o) pitkin niin, että vihreät
ja punaiset nappulat ovat vaihtaneet paikkaa; siis vihreät ovat kaikki alhaalla,
ja punaiset kaikki ylhäällä.

    Nappulaa saa siirtää kahden kentän välillä vain silloin, kun lähtökentästä
on olemassa avoin polku kohdekenttään tyhjiä ruutuja (o) pitkin. Polun varrella ei saa olla muita nappuloita,
eikä polku saa hypätä seinien (' ') yli. Polku ei voi kulkea vinottain, vaan sen askelet saavat
olla ainoastaan oikea-vasen-ylös-alas-suuntaisia.

    Nappuloita saa siirtää vain yksi kerrallaan. Yhden nappulan siirto ruudusta toiseen
lasketaan yhdeksi siirroksi, siirtopolun pituudesta riippumatta. Minimimäärä siirtoja
pelin voittamiseksi on 30.


OHJELMAN KÄYTTÖ:
Ohjelma ottaa syötteenä 4 kokonaislukua, jotka merkitsevät siirron alku-ja loppukenttiä.
Syötepisteiden laillisuus tarkistetaan;
- niiden on oltava laudan sisällä,
- alkupisteessä on oltava nappula,
- loppupisteessä on oltava vapaa kenttä         (siirto alkaa ja loppuu sopivista pisteistä),
- ja kenttien välillä on olemassa vapaa polku   (siirto noudattaa pelin sääntöjä).
Jos näistä ehdoista jokin ei toteudu, siirtoa ei tehdä, ja tulostetaan sopiva virheilmoitus.
Jos ehdot toteutuvat, pyydetty siirto tehdään ja pelilauta tulostetaan.
Syötepisteiden kysymistä jatketaan, kunnes peli on voitettu,
siis kun vihreät (G) ja punaiset (R) ovat vaihtaneet paikkoja.
Ohjelma loppuu, kun peli voitetaan, tai pelaaja poistuu syötteellä (q).
Ohjelman lopuksi tulostetaan tehtyjen siirtojen lukumäärä (vain onnistuneet siirrot lasketaan).


HUOMIOITA TOTEUTUKSESTA:
Älykkäiden osoittimien käyttötarkoitusta piti miettiä.
Tehtävänannosta sain käsityksen, että tarkoitus oli toteuttaa koko pelilauta
taulukkona älykkäitä osoittimia, jotka osoittavat erillisiin pelinappula- ja peliruutu-
olioihin. Koska tämä ei kuitenkaan ollut vaatimus, toteutin tässä pelilaudan yksinkertaisesti
merkkijonona, ja sen sijaan polun löytäminen tapahtuu rekursiivisesti pinona Path_elem-tietueita.

    osatehtävänä oli toteuttaa yksikkötestejä ohjelman luokille. Tekemistäni testeissä pari on
kömpelöhköjä, koska en viitsinyt selvittää, miten monimutkaisemmat tietorakenteet kuten std::string
ja Point-tietue saataisiin ilmoitettua tieto-ohjattujen testien käyttöön (joku QMetaType juttu).

    Kun aloin tekemään tätä tehtävää, tehtävänannossa ei ollut erikseen selitetty, minkälaisia
committeja pitäisi tehdä. Hieman ennen kuin olin jo valmis, tehtävänantoon lisättiin erityisvaatimuksia
eli en voinut commiteille, joita en voinut noudattaa. Tässä selitetty suurin piirtein, mitkä tekemistäni
commiteista vastaavat nykyisen tehtävänannon pyytämiä committeja.

"toteutettu gameboard annetut metodit testeineen":
    - Ohjelma tulostaa pelin alkutilanteen
    - Ohjelma tarkistaa syötteiden oikeellisuuden
    - yksikkötestit omina committeinaan (melkein kaikki)

"kirjoitettu alustavasti pathfind_fromto, lisätty move-testi" ja
"Korjattu pathfind_fromto vika jossa paluusuunta tarkistettiin väärin":
    - Ohjelma siirtää nappulaa, jos se on mahdollista
    - yksikkötestit omina committeinaan (vielä yksi)

*/

#include "gameboard.hh"
#include <iostream>

using namespace std;

// Vakiotulosteita
const string INPUT_TEXT = "Enter start point (x, y) and destination point (x, y), or q to quit: ";
const string INVALID_POINT = "Invalid start/destination point.";
const string IDENTICAL_POINTS = "Given points are the same.";   // Aktuaalisesti käyttötarkoitukseton
const string CANNOT_MOVE = "There is no path between start point and destination point.";
const string GAME_OVER = "Game over. Congratulations!";
const string MOVES_MADE = " move(s) made.";


// Päästää pelaajan pelaamaan peliä.
// Kunnes peli on ohi, lukee käyttäjän komentoja ja
// siirtää nappuloita jos mahdollista.
// Joka siirron jälkeen, tulostaa pelilaudan jälleen.
// Kun peli loppuu tai käyttäjä antaa quit-komennon,
// tulostaa tehtyjen siirtojen määrän.
void playGame(GameBoard& gb)
{
    Point p1 = {0, 0};
    Point p2 = {0, 0};
    string command = "";
    unsigned int total_moves = 0;
    gb.print();

    while(not gb.is_game_over())
    {
        cout << INPUT_TEXT;
        cin >> command;
        if(command == "q" or command == "Q")
        {
            cout << total_moves << MOVES_MADE << endl;
            return;
        }
        try
        {
            p1.x = stoi(command) - 1;
            cin >> command;
            p1.y = stoi(command) - 1;
            cin >> command;
            p2.x = stoi(command) - 1;
            cin >> command;
            p2.y = stoi(command) - 1;
        }
        catch (invalid_argument const& ex)
        {
            cout << "Invalid argument: " << ex.what() << endl;
            return;
        }

        // Check validity of the points
        if(not gb.are_valid_points(p1, p2))
        {
            cout << INVALID_POINT << endl;
            continue;
        }

        // Try to move
        if(gb.move(p1, p2))
        {
            ++total_moves;
            gb.print();
        }
        else
        {
            cout << CANNOT_MOVE << endl;
        }
    }
    cout << GAME_OVER << endl;
    cout << total_moves << MOVES_MADE << endl;
}


int main()
{
    GameBoard board;
    board.initial_fill();
    playGame(board);
    return 0;
}
