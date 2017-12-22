#include <Flieger.h>
using namespace std;

//Klassen:
class Flieger {
private:
        int geschwindigkeit;

public:
    //Variablen:
    int currentxkoord;
    int currentykoord;
    int winkel;
    SDL_Rect Rechteck;
    SDL_Surface *bild;
    //Konstruktor:
    Flieger(int,int,int,char*);
    //Funktionen:

};

// Funktionen:
SDL_Surface *bild_laden(const char *dateiname){
      SDL_Surface *bild = IMG_Load(dateiname);
    if (bild == NULL) {
        cout << "Laden von " << dateiname << " fehlgeschlagen!" << endl;
    }
    return bild;
}
