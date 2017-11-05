#include <iostream>
#include <vector>
#include <array>
#include <functional>

using namespace std;

struct Moteur {};
struct Roue {};


enum class Direction { Gauche , Droite };

class Vehicule {
    Moteur _m;
    array<Roue, 4> _roues;
public:
    Vehicule(const Moteur & m, const Roue & r) : _m(m), _roues({r,r,r,r}) {}
    ~Vehicule(){}
    void demarrer()  { cout << "le véhicule démarre " << endl;  }
    void arreter() { cout << "le véhicule s'arrête" << endl; }
    virtual void tourner (const Direction & x = Direction::Gauche) { 
       if (x == Direction::Gauche)
           cout << "le véhicule tourne à gauche" << endl;
       else if (x == Direction::Droite)
           cout << "le véhicule tourne à droite" << endl;
       else
           cerr << "direction inconnue" << endl;
    }
};

class Tank : public Vehicule {
    public:
      Tank(const Moteur & m, const Roue & r): Vehicule(m,r) {}

virtual void tourner (const Direction & x = Direction::Gauche) { 
       if (x == Direction::Gauche)
           cout << "le tank tourne à gauche" << endl;
       else if (x == Direction::Droite)
           cout << "le tank tourne à droite" << endl;
       else
           cerr << "direction inconnue" << endl;
    }
};


int main(int argc, char * argv[])
{

    Moteur honda;
    Roue michelin;
    Vehicule maCaisse(honda, michelin);
    cout << "c'est ma caisse" << endl;
    maCaisse.demarrer();
    maCaisse.tourner(Direction::Gauche);
    maCaisse.arreter();

    Moteur renault;
    Roue chenilles;
    Tank monCharPatton(renault, chenilles);

    cout << "c'est mon char Patton" << endl;
    monCharPatton.demarrer();
    monCharPatton.tourner(Direction::Droite);
    monCharPatton.arreter();

    cout << "c'est ma deuxieme Caisse" << endl;
    Vehicule * maDeuxiemeCaisse = &monCharPatton;
    maDeuxiemeCaisse->demarrer();
    maDeuxiemeCaisse->tourner();
    maDeuxiemeCaisse->arreter();
 
    return 0;
}
