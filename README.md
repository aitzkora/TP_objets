Introduction à la Programmation Orienté Objet (POO)
===================================================
Le C++ comporte plusieurs paradigmes de programmation : *imperatif* , *orienté objet*, *générique* et même
*fonctionel *(depuis c++11)
Aujourd'hui nous allons nous intéresser à l'aspect orienté objet. La POO est fondé sur 3 principes de base :  
 - l'*encapsulation*, 
 - l'*héritage*, 
 - le *polymorphisme*.

Encapsulation
----------------
Dans un contexte de programmation impérative, on implémente des procédures qui agissent «par effet de bords» 
sur des structures de données, par exemple
    
```c++
    void computeSum(vector<int> &x, int & sum)
    {
       sum = 0; 
       for (auto & s : x )
          {
             sum += s;
          }
    }
    //....
    vector<int> z = { 1, 2, 3};
    int s;
    computeSum(z, s);
    assert(s == 6);
```

Un problème de l'utilisation de ce genre de fonction est que l'on doit associer manuellement les structures de données et 
les algorithmes qui agissent dessus. L'*encapsulation* est là pour résoudre ce genre de problème : on va regrouper 
au sein d'une même **classe** les structures de données (les *attributs* ou *membres* ) et les algorithmes (**méthodes**). 
Ainsi imaginons la classe suivante

```c++
    class monTableau {
        vector<int> data;
        public:
        monTableau(const vector<int> & x) : data(x) {}
        int computeSum() { int s = 0; for (auto & x : data ) { s+= x; } return s; }
        ~monTableau() {}
    };
    //....
    monTableau z({1, 2, 3});
    assert( z.computeSum() == 6);
```

On voit apparaître plusieurs choses bizarres :
 - une fonction  - en realité une **méthode** - porte le même nom que la classe. Elle permet de construire une _instance_ 
 de la classe `monTableau`. On l'appelle le **constructeur**
 - une autre méthode porte le nom de la classe précédé d'un ~, c'est le **destructeur**. Cette méthode est responsable
 de libérer la mémoire quand on détruit l'objet. Elle est appelé a chaque fin de vie d'un objet.
 - il y a un mot-clef «public» . C'est un qualificateur d'accés, pour savoir si un membre ou une méthode est public (`public:`)
 privée (`private:`) ou protégée (`protected:`). Tout ce qui suit le qualificateur jusqu'au suivant à cette propriété

On voit au sein de cet exemple que l'usager n'a pas à connaître la structure de données interne (`data`) pour calculer 
la somme. L'encapsulation permet de créer une _interface_ que l'utilisateur de la classe va utiliser sans intervenir directement
sur les structures de données internes. Ceci renforce la _modularité_ du code ainsi obtenu : on peut changer l'interieur d'une 
classe sans en changer l'interface (par exemple, pour optimiser les algorithmes internes), le code qui en dépend n'aura pas à etre modifié 

### Exercice (pour la maison)
Ecrire une classe `chaine` qui prend un `const char *` pour le constructeur et le stocke dans un `vector<char>`. On écrira 
une méthode concat qui prend la chaine une autre chaine en argument et qui renvoie la chaine concaténé avec la chaine courante

Héritage 
--------
L'héritage est un concept de la POO qui permet de partager du code et des attributs entre des classes differentes, sous la 
contrainte que l'une de ces classes est une spécialisation de l'autre (on parle alors de _classe fille_ ou _sous classe_) ou 
que l'autre est une généralisation de la première (on parle alors de _classe mère_ ou _classe de base_ ou encore _super-classe_)
du point de vue de ce que l'on souhaite modèliser dans le langage
Prenons un exemple simple. On veut simuler des véhicules : par exemple des voitures, des camions et des tanks.
On peut imaginer faire une classe de base comme ceci

```c++     
     class Vehicule {
      Moteur _m  
      array<Roue, 4> _roues;
      public:
          Vehicule(const Moteur & m, const Roue & r) : _m(m), _roues({r,r,r,r}) {}
          ~Vehicule(){}
          void demarrer()  {...}
          void arreter() {...}
     }
```

On peut factoriser dans cette classe les attributs et les méthodes que doivent partager les voitures, les camions et les tanks.
Ainsi la classe camion pour correspondre  à 
    
```c++
    class Camion : public Vehicule {
    Benne _benne;
    public:
        camion(const Moteur &m, const Roue & r, const Benne & b): Vehicule(m,r), _benne(b) {}
        ~camion() {}
        void dechargerLaBenne() {...}
   }
```

On pourra lorsque qu'on crée un camion, appeler les méthode suivantes
```c++
     Moteur m(12);
     Roue r("bibendum");
     Benne b("à ordures");
     Camion monCamion(m,r,b);
     monCamion.demarrer() // OK
     monCamion.dechargerLaBenne(); // OK
     monCamion.arreter() //OK
```
par contre un objet `Vehicule` ne pourrait pas appeler `dechargerLaBenne` puisque qu'elle est définie seulement dans la classe
fille
```c++
     Moteur m(42);
     Roue r("bibendum");
     Vehicule monVehicule(m,r);
     monVehicule.demarrer() // OK
     monVehicule.arreter() //OK
     monVehicule.dechargerLaBenne(); // Erreur
```
Polymorphisme
-------------
Le polymorphisme est le troisième principe de base de la POO. Il permet a une même méthode d'avoir une implémentation différente dans des classes 
différente toute en gardant la même signature. Notons que ce comportement ne peut avoir lieu que sur des objets dynamiques (references ou pointeurs).
Imaginons que l'on veuille rajouter une méthode `Tourner` dans la classe `Vehicule`. Il est clair que pour un tank ou une voiture, l'implémentation
doit être différente. Ainsi on va déclarer une méthode virtuelle `Tourner` dans `Vehicule`

```c++


enum class Direction { Gauche , Droite };

class Vehicule {
    ....
public:
    Vehicule(const Moteur & m, const Roue & r) : _m(m), _roues({r,r,r,r}) {}
    ~Vehicule(){}
    //...
    virtual void tourner (const Direction & x = Direction::Gauche) { 
      cout << "vehicule tourne" << endl; }
};

```
que l'on rédéfinit dans la _classe-fille_

```c++
class Tank : public Vehicule {
public:
      Tank(const Moteur & m, const Roue & r): Vehicule(m,r) {}

      virtual void tourner (const Direction & x = Direction::Gauche) {
      cout << "tank tourne" << endl;
      }
};

```
### Question
Que va afficher le code suivant
```c++
class Moteur {};
class Roue {};
Moteur m;
Roue chenilles;
Tank t(m,chenilles);
Vehicule * v  = & t;
t->tourner();
```
«tank tourne» ou «vehicule tourne » ?

Conclusion
----------

La maitrise de l'héritage et du polymorphisme est nécessaire pour écrire des codes complexes et modulaires 
faisant intervernir un nombre important de classes. Dans un premier temps, il est important de 
bien saisir la notion d'encapsulation afin de pouvoir écrire ses premières classes. Afin d'illustrer ce premier
concept nous allons écrire un code d'équation de la chaleur en différences finies (https://github.com/aitzkora/TP_objets/blob/master/chaleur/chaleur.org)

Pour aller plus loin 
==================== 
- Introduction aux objets (http://www.bruno-garcia.net/www/Cours/) par B.L. Garcia (†)
