Introduction à la Programmation Orienté Objet (POO)
===================================================
Le C++ comporte plusieurs paradigmes de programmation : *imperatif* , _orienté objet_, *générique* et même
fonctionel (depuis c++11)
Aujourd'hui nous allons nous intéresser à l'aspect orienté objet.
la POO est fondé sur 3 principes de base :  l'*encapsulation*, l' *héritage* et le *polymorphisme*

l'encapsulation
----------------
Dans un contexte de programmation impérative, on implémente des procédures qui agissent «par effet de bords» 
sur des structures de donnés, par exemple
    

    void computeSum(vector<int> &x, double & sum)
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
les algorithmes qui agissent dessus. L'*encapsulation* est là pour résoudre ce genre de probleme : on va regrouper 
au sein d'une même **classe** les structures de données (les *attributs* ou *membres* ) et les algorithmes (**méthodes**). 
Ainsi imaginons la classe suivante

    class monTableau {
       vector<int> data;
    public: 
       monTableau(vector<int> & x) : data(x) {}
       int computeSum() { int s = 0; for (auto & x : data ) { s+= x; } return s; }
       ~monTableau() {}
    };
    // ... 
    monTableau z({ 1, 2, 3});
    assert( z.computeSum() == 6);

On voit apparaître plusieurs choses bizarres :
 - une fonction  - en realité une **méthode** - porte le même nom que la classe. Elle permet de construire une _instance_ 
 de la classe `monTableau`. On l'appelle le **constructeur**
 - une autre méthode porte le nom de la classe précédé d'un $\tilde$, c'est le **destructeur**. Cette méthode est responsable
 de libérer la mémoire quand on détruit l'objet. Elle est appelé a chaque fin de vie d'un objet.
 - il y a un mot-clef «public:» . C'est un qualificateur d'accés, pour savoir si un membre ou une méthode est public, 
 privée (`private`) ou protégée (`protected:`). Tout ce qui suit le qualificateur jusqu'au suivant à cette propriété

On voit au sein de cet exemple que l'usager n'a pas à connaître la structure de données interne (`data`) pour calculer la somme
