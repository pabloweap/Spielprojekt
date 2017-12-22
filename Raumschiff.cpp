#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <SDL.h>
#include <string>
#include <SDL_image.h>
#include <vector>

using namespace std;

// Funktionen:
SDL_Surface *bild_laden(const char *dateiname){
      SDL_Surface *bild = IMG_Load(dateiname);
    if (bild == NULL) {
        cout << "Laden von " << dateiname << " fehlgeschlagen!" << endl;
    }
    return bild;
}

// Variablen:
bool ende = false;
bool ende1 = false;
bool ende2 = false;
SDL_Event event;

int taste;
int aenderung;

//Klassen:
class Shot {
private:
    int mvm;
public:
    SDL_Rect Rechteck;
    SDL_Surface *bild;
    int y;
    int x;
    Shot(int,int,int,char*);
    void zeichnen(SDL_Surface *);
    void bewegen();
};


Shot::Shot(int startx, int starty, int startmvm, char *filename){
bild = IMG_Load(filename);
x = startx;
y = starty;
mvm = startmvm;
}

void Shot::bewegen(){
 x = x + mvm*10;
 }

void Shot::zeichnen(SDL_Surface *surf){
 Rechteck = {x: x, y: y,1,1};
 SDL_BlitSurface(bild, NULL, surf, &Rechteck);
 }

class Astronaut {
private:
    int geschwindigkeityachse;
public:
    SDL_Rect Rechteck;
    SDL_Surface *bild;
    int positionx;
    int positiony;
    Astronaut(int,int,int, char*);
    void zeichnen(SDL_Surface *);
    void ybewegen();
    void bewegungaendern(int);
    void bounce();

};

Astronaut::Astronaut(int startpositionx, int startpositiony, int startgeschwindigkeityachse, char *filename){
bild = IMG_Load(filename);
positionx = startpositiony;
positiony = startpositionx;
geschwindigkeityachse = startgeschwindigkeityachse;
}

void Astronaut::bounce(){
geschwindigkeityachse = 0- geschwindigkeityachse/2;
}

void Astronaut::ybewegen(){
 positiony = positiony + geschwindigkeityachse;
 if (positiony > 580-bild->h){
    positiony = 580-bild->h;
    bounce();

 } else if (positiony < 0){
    positiony = 0;
    bounce();
 }
 }

void Astronaut::zeichnen(SDL_Surface *surf){
 Rechteck = {x: positionx, y: positiony,1,1};
 SDL_BlitSurface(bild, NULL, surf, &Rechteck);
 }

void Astronaut::bewegungaendern(int veraenderung){
 geschwindigkeityachse = geschwindigkeityachse + veraenderung;
 }

class Sterne {
  private:
      SDL_Surface *bild;
      int geschwindigkeit;
      int position;
      int position2;
  public:
      Sterne(int, int, char*);
      void zeichnen(SDL_Surface *);
      void bewegen();
};

Sterne::Sterne(int startposition, int geschw, char *filename) {
    bild = IMG_Load(filename);
    geschwindigkeit = geschw;
    position = startposition;
    position2 = startposition + 762;
}

void Sterne::zeichnen(SDL_Surface *surf) {
    SDL_Rect sternposition;
    sternposition = {x:position, y:0, w:762, h:580};
    SDL_BlitSurface(bild, NULL, surf, &sternposition);
    sternposition = {x:position2, y:0, w:762, h:580};
    SDL_BlitSurface(bild, NULL, surf, &sternposition);
}

void Sterne::bewegen() {
    position -= geschwindigkeit;
    if (position < -762) {
        position = 768;
    }
    position2 -= geschwindigkeit;
    if (position2 < -762) {
        position2 = 768;
    }
}

bool getroffen(vector<Shot> schuesse, SDL_Rect b){

    for(int i = 0; i < schuesse.size(); i++){
        if (SDL_HasIntersection(&schuesse[i].Rechteck, &b)) {
            return(true);
            }}

    return(false);
     }

int main(int a, char**b) {
    // Fenster aufbauen
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *win = SDL_CreateWindow("Raumschiff", 100, 100, 760, 580,SDL_WINDOW_SHOWN);
    SDL_Surface *surf = SDL_GetWindowSurface(win);

    IMG_Init( IMG_INIT_PNG );
    SDL_Surface *hintergrund = bild_laden("background.png");

    Sterne s1(0, 9, "stars1.png");
    Sterne s2(0, 6, "stars2.png");
    Sterne s3(0, 3, "stars3.png");
    Astronaut klaas(380,10,0,"astronaut3.png");
    Astronaut yoko(380,730,0,"astronaut2.png");
vector<Shot> schuesse;
vector<Shot> schuesse2;
    while (!ende){

        while (SDL_PollEvent ( &event ) !=0 ) {
        if (event.type == SDL_KEYDOWN){
        taste = event.key.keysym.sym;
        switch(taste){
        case SDLK_w:
                    yoko.bewegungaendern(-1);
                    break;
        case SDLK_UP:
                    klaas.bewegungaendern(-1);
                    break;
        case SDLK_s:
                    yoko.bewegungaendern(1);
                    break;
        case SDLK_DOWN:
                    klaas.bewegungaendern(1);
                    break;
        case SDLK_SPACE:
                    schuesse2.push_back(Shot(yoko.positionx,yoko.positiony,-1,"ShotBlue.png"));
                    break;
        case SDLK_p:
                    schuesse.push_back(Shot (klaas.positionx,klaas.positiony,1,"ShotRed.png"));
                    break;
        case SDLK_ESCAPE:
                    ende = true;
                    break;
        }
            }
            else if (event.type == SDL_QUIT){
                ende = true;
            }
    }
    //Bewegen
        s1.bewegen();
        s2.bewegen();
        s3.bewegen();
        for (int i = 0; i < schuesse.size(); i++){
            schuesse[i].bewegen();
        }
        for (int i = 0; i < schuesse2.size(); i++){
            schuesse2[i].bewegen();
        }

//        schuss1.bewegen();
 //       schuss2.bewegen();
        klaas.bewegungaendern(aenderung);
        klaas.ybewegen();
        yoko.bewegungaendern(aenderung);
        yoko.ybewegen();
    //Zeichnen
        SDL_BlitSurface(hintergrund, NULL, surf, NULL);
        s1.zeichnen(surf);
        s2.zeichnen(surf);
        s3.zeichnen(surf);
        klaas.zeichnen(surf);
        yoko.zeichnen(surf);
        for (int i = 0; i < schuesse.size(); i++){
            schuesse[i].zeichnen(surf);
        }
        for (int i = 0; i < schuesse2.size(); i++){
            schuesse2[i].zeichnen(surf);
        }
    //Anzeigen
        SDL_UpdateWindowSurface(win);
        SDL_Delay(10);
    //Spiel vorbei?
        ende1 = (getroffen(schuesse,yoko.Rechteck));
        ende2 = (getroffen(schuesse2,klaas.Rechteck));
        if (ende1 || ende2){ende = true;}

    }
cout << "Ende";

}
