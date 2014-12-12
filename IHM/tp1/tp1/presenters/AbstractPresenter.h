#pragma once
// Le "#pragma once" est une directive preprocesseur servant à avertir le compilateur
// que ce fichier ne doit être inclus qu'une seule fois.

// Il remplace les "gardiens":

//     #ifndef MACLASSE_H
//     #define MACLASSE_H
//     class MaClasse
//     {
//         ...
//     };
//     #endif

// que vous avez peut-être vu par ailleurs. (c'est juste moins long à écrire)


#include <QObject>
// La classe 'AbstractPresenter' herite de QObject, le compilateur doit donc
// "Savoir" ce qu'est un QObject pour cela on inclut le header de QObject.

class MainWindow;
class AbstractModel;
class AbstractParametersWidget;
// La classe 'AbstractPresenter' prend dans son constructeur un pointeur vers
// MainWindow, AbstractModel et AbstractParametersWidget le compilateur a donc besoin de
// savoir que ces classes existent. On pourrait les inclure comme on l'a fait pour la classe QObject.

// Cependant il existe un risque que la classe AbstractModel (par exemple) ait elle aussi
// besoin de conaitre AbstractPresenter. Ceci entrainerait un problème d'inclusion cyclique.

// Pour résoudre ce problème on utilise des "déclarations anticipées".
// De cette manière, au lieu d'inclure les classes, on avertit simplement le compilateur qu'elles existent.
// Cela fonctionne car on manipule des pointeurs (ou des references).
// Si l'on voulait manipuler directement des instance alors, le compilateur devrait connaitre tous les détails de
// la classe en question et nous devrions inclure son header, comme pour QObject ici.
// Noter que lorsqu' on utilisera ces classe pour de bon (ie, dans le .cpp) il faudra les inclure.

// De manière générale on essaie d'utilser au MAXIMUM les déclarations anticipées dans les header.

class AbstractPresenter: public  QObject
{
    Q_OBJECT
//     Ceci est une macro dont Qt a besoin afin de savoir
//     que la classe sera capable d'envoyer des signaux ou bien
//     qu'elle possède des slots. Pour utiliser cette macro dans une classe,
//     il faut que celle-ci hérite de QObject.

public:
//     La porté public permet d'utiliser les méthodes et membres qui suivent depuis n'importe ou.
//     Cela constitue "l'interface" de la classe avec le monde exterieur.

    AbstractPresenter(MainWindow *parent, AbstractModel *model, AbstractParametersWidget* parametersWidget);
    virtual ~AbstractPresenter();
//     Le mot clé virtual sert à rendre une méthode (ou un destructeur) virtuel.
//     Une méthode virtuelle sert à profiter du polymorphisme dynamique. Derrière ces deux mots
//     bien compliqué se cache en fait quelque chose de simple.
//     Exemple:
//          Imaginons une classe Etudiant et une classe EtudiantEsir2.
//          'Etudiant' à une méthode sePrésenter qui retourne: 'Je suis étudiant.'.

//          'EtudiantEsir2'  surcharge la méthode sePrésenter et retourne:
//          'Je suis étudiant à l'esir en 2ème année.'.

//          j'ai un pointeur de type 'Etudiant' pointant sur une instance de type 'EtudiantEsir2',
//          cela est possible car un étudiant à l'ESIR en 2eme année EST un étudiant:

//          Etudiant *etudiant = new EtudiantESIR2;

//          Dans le cas "normal" etudiant->sePresenter() retourne 'Je suis étudiant.'.
//          Mais si la métode sePresenter à été déclarer virtuelle dans la classe Etudiant,
//          alors, etudiant->sePresenter() retourne 'Je suis étudiant à l'esir en 2ème année.'

//          C'est ça que l'on appel le polymorphisme, c'est ce qui vous a permis d'implementer
//          le zoom dans votre méthode GraphicsImageView::wheelEvent(QWheelEvent *e);

//     De manière générale, on déclare toujours les destructeurs virtuels ainsi on est sûr
//     que le bon destructeur est toujours appelé.



protected:
//     La porté protected permet d'utiliser les méthodes et membres qui suivent
//     uniquement depuis cette classe (AbstractPresenter),
//     ou depuis une classe heritant de AbstractPresenter.


    AbstractModel * model;
    AbstractParametersWidget * parametersWidget;


private:
//     La porté private permet d'utiliser les méthodes et membres qui suivent
//     uniquement depuis l'interieur de cette classe.

private slots: //  noter que comme toutes les autre méthodes les slots ont une portée, public, protected ou private.
    /**
     * @brief runModel
     * This slot is used to run the model associate to the presenter.
     */
    virtual void runModel() = 0;
    /**
     * @brief presentModelResults
     * This slot is used to present the result of the model to the view associate to the presenter
     */
    virtual void presentModelResults() = 0;
//     Ces deux méthodes sont "virtuelles pures" c'est à dire qu'elle n'ont pas d'implementaion dans AbstractParameter.
//     Cela fait d'AbstractParameter une classe Abstraite.
//     On ne peut pas creer une instance de classe abstraite, logique certaines de ses méthodes ne sont pas implémentées,
//     on ne saurait quoi faire avec.

//     Dans la pratique on fait des méthode virtuelle pure quand on ne sait pas donner d'implmentation à une méthode,
//     Mais que l'on veux que cette classe déclare cette méthode.

//     Ici nous savons que toutes les classes héritants d'AbstractPresenter doivent savoir lancer un model et présenter ses résultats,
//     (c'est notre "concept" de presenter qui veux ça) mais nous ne savons pas "encore" comment.
//     A vous d'implementer ces méthodes dans votre classe ResizeParameter qui héritera d'AbstractPresenter.

//     L'utilisation des classes abstraite deviens puisssante grâce au polymorphisme (voir plus haut), si à un moment donner je manipule
//     un pointeur 'AbstractPresenter *abstractPresenter', je pourrait ecrire par exemple:
//
//        connect(trucObjet, SIGNAL(signalChose()), abstractPresenter, SLOT(runModel()));
//
//      sans avoir à connaître forcement une implementaion d'AbstractPresenter.
//      Et cela est possible car la méthode runModel() à bien été déclarer dans le header de AbstractPresenter.
};

