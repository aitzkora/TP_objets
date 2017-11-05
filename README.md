Introduction à la Programmation Orienté Objet (POO)
===================================================
Le C++ comporte plusieurs paradigmes de programmation : *imperatif* , *orienté objet*, *générique* et même
*fonctionel*(depuis c++11)
Aujourd'hui nous allons nous intéresser à l'aspect orienté objet. La POO est fondé sur 3 principes de base :  
 - l'*encapsulation*, 
 - l' *héritage*, 
 - het le *polymorphisme*.

Encapsulation
----------------
Dans un contexte de programmation impérative, on implémente des procédures qui agissent «par effet de bords» 
sur des structures de données, par exemple
    

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


Un problème de l'utilisation de ce genre de fonction est que l'on doit associer manuellement les structures de données et 
les algorithmes qui agissent dessus. L'*encapsulation* est là pour résoudre ce genre de problème : on va regrouper 
au sein d'une même **classe** les structures de données (les *attributs* ou *membres* ) et les algorithmes (**méthodes**). 
Ainsi imaginons la classe suivante


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
## Exercice 
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

     
     class Vehicule {
      Moteur _m  
      array<Roue, 4> _roues;
      public:
          Vehicule(const Moteur & m, const Roue & r) : _m(m), _roues({r,r,r,r}) {}
          ~Vehicule(){}
          void demarrer()  {...}
          void arreter() {...}
     }

On peut factoriser dans cette classe les attributs et les méthodes que doivent partager les voitures, les camions et les tanks.
Ainsi la classe camion pour correspondre  à 
    

    class Camion : public Vehicule {
    Benne _benne;
    public:
        camion(const Moteur &m, const Roue & r, const Benne & b): Vehicule(m,r), _benne(b) {}
        ~camion() {}
        void dechargerLaBenne() {...}
   }

On pourra lorsque qu'on crée un camion, appeler les méthode suivantes

     Moteur m(12);
     Roue r("bibendum");
     Benne b("à ordures");
     Camion monCamion(m,r,b);
     monCamion.demarrer() // OK
     monCamion.dechargerLaBenne(); // OK
     monCamion.arreter() //OK

par contre un objet `Vehicule` ne pourrait pas appeler `dechargerLaBenne` puisque qu'elle est définie seulement dans la classe
fille

     Moteur m(42);
     Roue r("bibendum");
     Vehicule monVehicule(m,r);
     monVehicule.demarrer() // OK
     monVehicule.arreter() //OK
     monVehicule.dechargerLaBenne(); // Erreur

Polymorphisme
-------------


