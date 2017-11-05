Équation de la chaleur
======================
- Le but de ce TP est d'écrire une classe en C++ qui simulera l'équation de la chaleur sur un carré.
Pour cela on aimerait avoir un programme principal du genre
```c++
#include "Chaleur.hpp"

int main(int argc, char * argv[])
{
    if (argc < 3)
    {
        std::cerr << "usage "  <<argv[0] << " maxIt prec" << std::endl;
    }
    int maxIt = std::atoi(argv[1]);
    double eps = std::atof(argv[2]);
    Chaleur poeleACharbon(1., 1., 100, 100);
    poeleACharbon.initialise(1.0);
    poeleACharbon.resout(maxIt, eps);
    return 0;
}
```

Le classe `Chaleur` aura donc _a minima_ l'interface suivante
```c++
class Chaleur {
    public:
        Chaleur(double deltaX, double deltaY, int dimX, int dim);
        ~Chaleur();
        int resout(int maxIt, double eps);
        void initialise(double valSurLeBord);
};
```
On pourra encoder l'etat de la solution courante de plusieurs façons : 
- soit un double * , qu'il faudra allouer dans le constructeur et liberer dans le destructeur
```c++
Chaleur::Chaleur(...)
{
...
_sol =  new double [_dimX * _dimY];
...
}

Chaleur::~Chaleur()
{
delete [] _sol;
}
```
- soit un vector<double> de la STL
Dans les deux cas, on aura interet a utiliser un stockage plat, car les pointeurs de pointeurs sont lents en mémoire et
les tableaux bidimensionels `double [DIM1][DIM2]` necessitent quand a eux de connaître leur taille à la compilation

On aura d'ailleurs interet a stocker les deux etats succesifs `X_n` et `X_n+1` de la solutions dans 2 tableaux differents
dont on pourra faire une copie simple grâce à la fonction `std::copy_n`

