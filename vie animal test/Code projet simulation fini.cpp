#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <windows.h>
#include <cmath>
using namespace std;
int compteurDeReaPlante = 0;

class Dinosaure {
protected:
    int sante;
    int jaugeNourriture;
    int compteurAccouplement;
    int D_coordX, D_coordY;
    bool carni = false;
    bool herbi = false;
    int age;

public:

    Dinosaure(int hp, int nourriture, bool regimeC, bool regimeH) :
        sante(hp), jaugeNourriture(nourriture), carni(regimeC), herbi(regimeH), D_coordX(rand() % 60), D_coordY(rand() % 60), age(rand() % 8), compteurAccouplement(0) {}

    virtual void attaquer(Dinosaure& cible) = 0;

    virtual void trouverNourriture() = 0;

    void vieux() {
        age++;
    }

    void avancerTempsEvent() {
        age += 9;
    }

    void resetAge() {
        age = 0;
    }
    virtual void chasse(Dinosaure& D_cible) {

        if (D_coordX < D_cible.donnerCoordX()) {
            if (D_coordX < 60) D_coordX += 2;
        }
        else if (D_coordX > D_cible.donnerCoordX()) {
            if (D_coordX > 0) D_coordX -= 2;
        }

        if (D_coordY < D_cible.donnerCoordY()) {
            if (D_coordY < 60)  D_coordY += 2;
        }
        else if (D_coordY > D_cible.donnerCoordY()) {
            if (D_coordY > 0) D_coordY -= 2;
        }
    }

    virtual void fuite(Dinosaure& D_fuir) {

        if (D_coordX < D_fuir.donnerCoordX()) {
            if (D_coordX > 0) D_coordX--;
        }
        else if (D_coordX > D_fuir.donnerCoordX()) {
            if (D_coordX < 60) D_coordX++;
        }

        if (D_coordY < D_fuir.donnerCoordY()) {
            if (D_coordY > 0) D_coordY--;
        }
        else if (D_coordY > D_fuir.donnerCoordY()) {
            if (D_coordY < 60) D_coordY++;
        }
    }

    void perteDeVie(int degats) {
        sante -= degats;
        if (sante < 0) sante = 0;
    }

    virtual int donnerSante() {
        return sante;
    }
    virtual int DefVie(int V) {
        sante = V;
        return sante;
    }

    double distanceEntreDinos(Dinosaure& autreDino) const { // Pas encore fini
        double dx = D_coordX - autreDino.D_coordX;
        double dy = D_coordY - autreDino.D_coordY;
        return sqrt(dx * dx + dy * dy);
    }

    virtual int donnerCoordX() {
        return D_coordX;
    }
    virtual int donnerCoordY() {
        return D_coordY;
    }
    virtual int donnerNourriture() {
        return jaugeNourriture;
    }
    virtual int giveNourriture(int nourr) {
        jaugeNourriture += nourr;
        return jaugeNourriture;
    }
    virtual int enleverNourriture(int nourr) {
        jaugeNourriture -= nourr;
        return jaugeNourriture;
    }
    virtual int donnerAge() {
        return age;
    }
    virtual bool donnerRegimeC() {
        return carni;
    }

    virtual bool donnerRegimeH() {
        return herbi;
    }

    virtual string donnerEspece() = 0;

    virtual Dinosaure* nouveauEnfant() = 0;

    virtual void verifConditionAccouplement() {
        if (compteurAccouplement > 0) {
            compteurAccouplement--;
        }
    }

    virtual void verifNourriture() {
        if (jaugeNourriture > 0) {
            jaugeNourriture--;
        }
    }

    bool accouplementPossible() {
        return compteurAccouplement == 0;
    }

    bool verifAgeAccouplement() {
        return age > 5;
    }

    void resetAccouplement() {
        compteurAccouplement = 3;
    }

    bool enVie() const {
        return sante > 0;
    }
};

class Carnivore : public Dinosaure {
protected:
    string espece;
    int C_coordX, C_coordY;
public:

    Carnivore(string nomEspece) : espece(nomEspece), C_coordX(rand() % 60), C_coordY(rand() % 60), Dinosaure(sante, 50, true, false) {}

    void attaquer(Dinosaure& cible) override {}

    void trouverNourriture() override {
        if (C_coordX < 60) C_coordX += rand() % 2;
        if (C_coordY < 60) C_coordY += rand() % 2;
        if (C_coordX > 0)  C_coordX -= rand() % 2;
        if (C_coordY > 0)  C_coordY -= rand() % 2;
    }

    void chasse(Dinosaure& D_cible) {

        if (C_coordX < D_cible.donnerCoordX()) {
            if (C_coordX < 60) C_coordX += 2;
        }
        else if (C_coordX > D_cible.donnerCoordX()) {
            if (C_coordX > 0) C_coordX -= 2;
        }

        if (C_coordY < D_cible.donnerCoordY()) {
            if (C_coordY < 60)  C_coordY += 2;
        }
        else if (C_coordY > D_cible.donnerCoordY()) {
            if (C_coordY > 0) C_coordY -= 2;
        }
    }

    int donnerSante() override {
        return sante;
    }

    int donnerNourriture() override {
        return jaugeNourriture;
    }

    int giveNourriture(int nourr) override {
        jaugeNourriture += nourr;
        return jaugeNourriture;
    }

    int enleverNourriture(int nourr) override {
        jaugeNourriture -= nourr;
        return jaugeNourriture;
    }

    int donnerCoordX() override {
        return C_coordX;
    }
    int donnerCoordY() override {
        return C_coordY;
    }

    void verifNourriture() override {
        if (jaugeNourriture > 0) {
            jaugeNourriture--;
        }
    }

    Dinosaure* nouveauEnfant() override {
        Dinosaure* enfant = new Carnivore(espece);
        enfant->resetAccouplement();
        enfant->resetAge();
        enfant->DefVie(sante);
        return enfant;
    }

    string donnerEspece() override {
        return espece;
    }
};

class Herbivore : public Dinosaure {
protected:
    string espece;
    int H_coordX, H_coordY;
public:
    Herbivore(string nomEspece) : espece(nomEspece), H_coordX(rand() % 60), H_coordY(rand() % 60), Dinosaure(sante, 50, false, true) {}

    void trouverNourriture() override {
        if (H_coordX < 60) H_coordX += rand() % 2;
        if (H_coordY < 60) H_coordY += rand() % 2;
        if (H_coordX > 0)  H_coordX -= rand() % 2;
        if (H_coordY > 0)  H_coordY -= rand() % 2;
    }

    void fuite(Dinosaure& D_fuir) {

        if (H_coordX < D_fuir.donnerCoordX()) {
            if (H_coordX > 0) H_coordX--;
        }
        else if (H_coordX > D_fuir.donnerCoordX()) {
            if (H_coordX < 60) H_coordX++;
        }

        if (H_coordY < D_fuir.donnerCoordY()) {
            if (H_coordY > 0)  H_coordY--;
        }
        else if (H_coordY > D_fuir.donnerCoordY()) {
            if (H_coordY < 60) H_coordY++;
        }
    }

    void attaquer(Dinosaure& cible) override {}

    int donnerSante() override {
        return sante;
    }

    int donnerNourriture() override {
        return jaugeNourriture;
    }
    int giveNourriture(int nourr) {
        jaugeNourriture += nourr;
        return jaugeNourriture;
    }
    int enleverNourriture(int nourr) {
        jaugeNourriture -= nourr;
        return jaugeNourriture;
    }
    int donnerCoordX() override {
        return H_coordX;
    }
    int donnerCoordY() override {
        return H_coordY;
    }

    void verifNourriture() override {
        if (jaugeNourriture > 0) {
            jaugeNourriture--;
        }
    }

    string donnerEspece() override {
        return espece;
    }

    Dinosaure* nouveauEnfant() override {
        Dinosaure* enfant = new Herbivore(espece);
        enfant->resetAccouplement();
        enfant->resetAge();
        enfant->DefVie(sante);
        return enfant;
    }
};

class Triceratops : public Herbivore {
public:
    Triceratops() : Herbivore("le Triceratops") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 7;
        cible.perteDeVie(degats);
        cout << espece << " se defend et effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;
    }

};
class Stegosaure : public Herbivore {
public:
    Stegosaure() : Herbivore("le Stegosaure") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 15;
        cible.perteDeVie(degats);
        cout << espece << " se defend et effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;
    }

};
class Brachiosaure : public Herbivore {
public:
    Brachiosaure() : Herbivore("le Brachiosaure") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 20;
        cible.perteDeVie(degats);
        cout << espece << " se defend et effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;
    }

};
class Ankylosaure : public Herbivore {
public:
    Ankylosaure() : Herbivore("l'Ankylosaure") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 15;
        cible.perteDeVie(degats);
        cout << espece << " se defend et effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;
    }

};

class Rex : public Carnivore {
public:
    Rex() : Carnivore("le T-Rex") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 20;
        cible.perteDeVie(degats);
        cout << espece << " effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;
    }

};

class Raptor : public Carnivore {
public:
    Raptor() : Carnivore("le Raptor") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 10;
        cible.perteDeVie(degats);
        cout << espece << " effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;

    }

};
class Allosaure : public Carnivore {
public:
    Allosaure() : Carnivore("l'Allosaure") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 15;
        cible.perteDeVie(degats);
        cout << espece << " effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;

    }

};
class Ceratosaure : public Carnivore {
public:
    Ceratosaure() : Carnivore("le Ceratosaure") {}
    void attaquer(Dinosaure& cible) override {
        int degats = 15;
        cible.perteDeVie(degats);
        cout << espece << " effectue une attaque sur " << cible.donnerEspece() << " en lui infligeant " << degats << " de degats." << endl << endl;

    }

};

class Plante {
protected:
    string nom;
    int reapparition;
    int P_coordX, P_coordY;
    bool typeArbre = false;
    bool typeBuisson = false;

public:
    bool present = true;


    Plante(string n, int r, bool A, bool B) :
        nom(n), reapparition(r), typeArbre(A), typeBuisson(B), P_coordX(rand() % 60), P_coordY(rand() % 60) {}

    virtual string donnerNomPlante() = 0;

    virtual int donnerXPlante() {
        return P_coordX;
    }

    virtual int donnerYPlante() {
        return P_coordY;
    }

    virtual bool presence() {
        return present;
    }

    virtual int rea() {
        return reapparition;
    }

    virtual bool donnerTypeArbre() {
        return typeArbre;
    }

    virtual bool donnerTypeBuisson() {
        return typeBuisson;
    }

    virtual void reaFct() {

        if (present == false) {

            compteurDeReaPlante++;

            if (compteurDeReaPlante >= reapparition)
            {
                present = true;
                compteurDeReaPlante = 0;

            }
        }
    }

};

class Arbre : public Plante {
protected:
    string nomDePlante;
    int A_coordX, A_coordY;

public:
    Arbre(string n) : nomDePlante(n), A_coordX(rand() % 60), A_coordY(rand() % 60), Plante("Arbre", 8, true, false) {}

    string donnerNomPlante() {
        return nomDePlante;
    }

    void reaFct() override {

        if (present == false) {

            compteurDeReaPlante++;

            if (compteurDeReaPlante >= reapparition)
            {
                present = true;
                compteurDeReaPlante = 0;

            }
        }
    }
};

class Baie : public Plante {
protected:
    string nomDePlante;
    int B_coordX, B_coordY;

public:
    Baie(string n) : nomDePlante(n), B_coordX(rand() % 60), B_coordY(rand() % 60), Plante("Buisson", 4, false, true) {}

    string donnerNomPlante() {
        return nomDePlante;
    }

    void reaFct() override {

        if (present == false) {

            compteurDeReaPlante++;

            if (compteurDeReaPlante >= reapparition)
            {
                present = true;
                compteurDeReaPlante = 0;
            }
        }
    }
};

class Chene : public Arbre {
public:
    Chene() : Arbre("un Chene") {}
};
class Bouleau : public Arbre {
public:
    Bouleau() : Arbre("un Bouleau") {}
};
class Accacia : public Arbre {
public:
    Accacia() : Arbre("un Accacia") {}
};
class Azzuberry : public Baie {
public:
    Azzuberry() : Baie("une Azzuberry") {}
};
class Stimberry : public Baie {
public:
    Stimberry() : Baie("une Stimberry") {}
};
class Amarberry : public Baie {
public:
    Amarberry() : Baie("une Amarberry") {}
};
class Tintoberry : public Baie {
public:
    Tintoberry() : Baie("une Tintoberry") {}
};

class Jeu {
private:
    vector<Dinosaure*> dinosaures;
    vector<Plante*> plantes;
    bool chasse = false;

public:
    int combien = 0;

    ~Jeu() {
        for (auto dinosaure : dinosaures)
            delete dinosaure;
        for (auto plante : plantes)
            delete plante;
    }

    void verif() {

        int nombresDinos;

        cout << "Entrez un nombre de dinosaures entre 10 et 30 : ";
        while (!(cin >> nombresDinos)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Erreur, veuillez selectionner un nombre." << endl;
            cout << "Entrez le nombre de dinosaures: ";
        }

        if (nombresDinos < 10 || nombresDinos > 30) {
            cout << "Erreur, veuillez selectionner un nombre de dinosaures correct." << endl;
            verif();
        }
        cin.ignore();
        lancerJeu(nombresDinos);
    }


    void ajouterDinosaure(int nombresDinos) {
        for (int i = 0; i < nombresDinos; i++) {
            int classe = rand() % 8;
            switch (classe) {
            case 0:
                dinosaures.push_back(new Rex());
                break;
            case 1:
                dinosaures.push_back(new Triceratops());
                break;

            case 2:
                dinosaures.push_back(new Raptor());
                break;
            case 3:
                dinosaures.push_back(new Stegosaure());
                break;
            case 4:
                dinosaures.push_back(new Allosaure());
                break;
            case 5:
                dinosaures.push_back(new Brachiosaure());
                break;
            case 6:
                dinosaures.push_back(new Ceratosaure());
                break;
            case 7:
                dinosaures.push_back(new Ankylosaure());
                break;
            }

        }
    }

    void ajouterPlante() {
        srand(time(0));
        for (int i = 0; i < 24; i++)
        {
            int classe = rand() % 7;
            switch (classe) {
            case 0:
                plantes.push_back(new Chene());
                break;
            case 1:
                plantes.push_back(new Bouleau());
                break;
            case 2:
                plantes.push_back(new Accacia());
                break;
            case 3:
                plantes.push_back(new Azzuberry());
                break;
            case 4:
                plantes.push_back(new Tintoberry());
                break;
            case 5:
                plantes.push_back(new Amarberry());
                break;
            case 6:
                plantes.push_back(new Stimberry());
                break;
            }
        }
    }

    void chasses() {
        cout << endl << endl;
        cout << "              IL Y'A TRES TRES TRES TRES TRES TRES TRES LONGTEMPS :" << endl << endl << endl;
        cout << "________________________________________________________________________" << endl << endl;
        cout << "                          LES DINOSAURES CHASSENT " << endl << endl << endl;

        for (auto carnivore : dinosaures) {

            for (auto herbivore : dinosaures) {

                if ((carnivore->donnerRegimeC() == true && carnivore->donnerRegimeH() == false) && (herbivore->donnerRegimeC() == false && herbivore->donnerRegimeH() == true) && herbivore->enVie() && carnivore->enVie() && carnivore->distanceEntreDinos(*herbivore) < 5.0) {
                    carnivore->chasse(*herbivore);
                    chasse = true;
                    cout << carnivore->donnerEspece() << " prends en chasse " << herbivore->donnerEspece() << endl << endl;
                }
            }
        }
        cout << "________________________________________________________________________" << endl << endl;
    }

    void fuites() {
        for (auto carnivore : dinosaures) {

            for (auto herbivore : dinosaures) {

                if ((carnivore->donnerRegimeH() == false && carnivore->donnerRegimeC() == true) && (herbivore->donnerRegimeH() == true && herbivore->donnerRegimeC() == false) && (herbivore->donnerRegimeH() != false && herbivore->donnerRegimeC() != true) && herbivore->enVie() && carnivore->enVie() && herbivore->distanceEntreDinos(*carnivore) < 5.0 && chasse == true) {
                    herbivore->fuite(*carnivore);
                    herbivore->enleverNourriture(2);
                }
            }
        }
    }

    void attaqueDeDino() {
        cout << "                    LES DINOSAURES PASSENT A L'ATTAQUE ! " << endl << endl << endl;

        for (auto carnivore : dinosaures) {

            for (auto herbivore : dinosaures) {

                if ((carnivore->donnerRegimeC() == true && carnivore->donnerRegimeH() == false) && (herbivore->donnerRegimeC() == false && herbivore->donnerRegimeH() == true) &&
                    herbivore->enVie() && carnivore->enVie() && carnivore->distanceEntreDinos(*herbivore) < 5.0 && chasse == true) {

                    carnivore->attaquer(*herbivore);
                    carnivore->enleverNourriture(2);
                }

                if ((carnivore->donnerRegimeH() == false && carnivore->donnerRegimeC() == true) && (herbivore->donnerRegimeH() == true && herbivore->donnerRegimeC() == false) &&
                    (herbivore->donnerRegimeH() != false && herbivore->donnerRegimeC() != true) && herbivore->enVie() && carnivore->enVie() && herbivore->distanceEntreDinos(*carnivore) < 5.0 && chasse == true) {

                    herbivore->attaquer(*carnivore);
                    herbivore->enleverNourriture(3);
                }
            }
        }
        cout << "________________________________________________________________________" << endl << endl;
    }

    void gestionNourriture() {

        cout << "                      LES HERBIVORES SE NOURRISSENT " << endl << endl << endl;

        for (auto plante : plantes) {

            plante->reaFct();

            for (auto dinosaure : dinosaures)
            {
                if (dinosaure->donnerCoordX() && dinosaure->donnerCoordY() == plante->donnerXPlante() && plante->donnerYPlante() && plante->present == true && dinosaure->donnerRegimeH() == true && dinosaure->donnerRegimeC() == false)
                {
                    if (plante->donnerTypeArbre() == true)   dinosaure->giveNourriture(10);
                    else if (plante->donnerTypeBuisson() == true) dinosaure->giveNourriture(5);

                    cout << dinosaure->donnerEspece() << " mange " << plante->donnerNomPlante() << endl << endl;
                    plante->present = false;
                    plante->reaFct();
                }
            }
        }

        for (auto dinosaure : dinosaures)
        {
            dinosaure->verifNourriture();
        }
        cout << "________________________________________________________________________" << endl << endl;
    }

    void gestionAccouplement() {
        vector<Dinosaure*> nouveauxDinosaures;
        cout << "                         GESTION DES NAISSANCES " << endl << endl << endl;

        for (auto dinosaure : dinosaures) {
            dinosaure->verifConditionAccouplement();
            if (!dinosaure->accouplementPossible())  continue;


            for (auto autreDino : dinosaures) {
                if (dinosaure != autreDino && dinosaure->donnerEspece() == autreDino->donnerEspece() &&
                    dinosaure->enVie() && autreDino->enVie() && autreDino->accouplementPossible() && dinosaure->verifAgeAccouplement()
                    && autreDino->verifAgeAccouplement()) {

                    if (dinosaure->donnerCoordX() - autreDino->donnerCoordX() <= 2
                        && dinosaure->donnerCoordY() - autreDino->donnerCoordY() <= 2
                        && dinosaure->donnerCoordX() - autreDino->donnerCoordX() >= -2
                        && dinosaure->donnerCoordY() - autreDino->donnerCoordY() >= -2) {
                        nouveauxDinosaures.push_back(dinosaure->nouveauEnfant());
                        cout << dinosaure->donnerEspece() << " se trouvant en (" << dinosaure->donnerCoordX() << ", " << dinosaure->donnerCoordY() << ")"
                            << " et le dinosaure " << autreDino->donnerEspece() << " se trouvant en (" << autreDino->donnerCoordX() << ", "
                            << autreDino->donnerCoordY() << ") a donne naissance a un autre dino. \n" << endl;
                        dinosaure->enleverNourriture(12);
                        autreDino->enleverNourriture(12);

                        dinosaure->resetAccouplement();
                        autreDino->resetAccouplement();
                        break;
                    }
                }
            }
        }
        cout << "________________________________________________________________________" << endl << endl;
        dinosaures.insert(dinosaures.end(), nouveauxDinosaures.begin(), nouveauxDinosaures.end());
    }

    void deplacement() {
        for (const auto& info_dinosaure : dinosaures) {
            info_dinosaure->trouverNourriture();
        }
    }
    void Viedinos() {
        for (auto dinosaure : dinosaures) {
            if (dinosaure->donnerEspece() == "le T-Rex") {
                dinosaure->DefVie(120);
            }
            else if (dinosaure->donnerEspece() == "le Raptor") {
                dinosaure->DefVie(70);
            }
            else if (dinosaure->donnerEspece() == "le Triceratops") {
                dinosaure->DefVie(80);
            }
            else if (dinosaure->donnerEspece() == "le Brachiosaure") {
                dinosaure->DefVie(120);
            }
            else if (dinosaure->donnerEspece() == "l'Allosaure") {
                dinosaure->DefVie(90);
            }
            else if (dinosaure->donnerEspece() == "l'Ankylosaure") {
                dinosaure->DefVie(70);
            }
            else if (dinosaure->donnerEspece() == "le Ceratosaure") {
                dinosaure->DefVie(90);
            }
            else if (dinosaure->donnerEspece() == "le Stegosaure") {
                dinosaure->DefVie(90);
            }
        }
    }

    void afficherInfos() {
    cout << "                      INFORMATIONS DES DINOSAURES" << endl << endl << endl;
    cout << "Nombre de dinosaures: " << dinosaures.size() << endl << endl;
    cout << "Voulez vous afficher les informations supplementaires ? (Oui : 1 OU Non : 2)" << endl << endl;
    int question;

    while (!(cin >> question) || question <= 0 || question > 2) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "\nErreur, veuillez saisir un nombre correct.\n" << endl;
        cout << "Voulez vous afficher les informations supplementaires ? (Oui : 1 OU Non : 2)" << endl << endl;
    }

    if (question == 1) {
        for (const auto& info_dinosaure : dinosaures) {
            cout << info_dinosaure->donnerEspece() << " a " << info_dinosaure->donnerAge() << " ans avec " << info_dinosaure->donnerSante()
                << " points de vies et " << info_dinosaure->donnerNourriture() << " points de nourriture." << endl;
            cout << info_dinosaure->donnerEspece() << " se trouve en (" << info_dinosaure->donnerCoordX() << " , " << info_dinosaure->donnerCoordY() << ')' << endl << endl;
        }
    }

}

    void Age_dinos() {
        for (auto& dinosaure : dinosaures) {
            dinosaure->vieux();
        }
    }
    void Mort() {
        cout << "                   INFORMATIONS SUR LES DINOSAURES MORT" << endl << endl << endl;
        for (auto CD = dinosaures.begin(); CD != dinosaures.end(); ) {//CD correspond à chaque dinosaure
            auto dinosaure = *CD;
            if (dinosaure->donnerAge() >= 100 || dinosaure->enVie() == false || dinosaure->donnerNourriture() <= 0) {
                cout << dinosaure->donnerEspece() << " (" << dinosaure->donnerCoordX() << ", " << dinosaure->donnerCoordY() << ")" << " est mort a " << dinosaure->donnerAge() << " ans." << endl << endl;
                combien--;
                delete dinosaure;
                CD = dinosaures.erase(CD);
            }
            else {
                ++CD;
            }
        }
        cout << "________________________________________________________________________" << endl << endl;
    }

    int verifCoordonnee(const string& message) {
        int coordonnee;
        cout << message;
        while (!(cin >> coordonnee)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Erreur, veuillez saisir un nombre valide." << endl;
            cout << message;
        }
        return coordonnee;
    }

    void avancerTemps() {
        for (auto& dinosaure : dinosaures) {
            dinosaure->avancerTempsEvent();
            dinosaure->enleverNourriture(9);
        }
    }

    void Cataclysme() {
        cout << endl << endl;
        cout << "               UN CATACLYSME SURVIENT !!!" << endl << endl << endl;
        int randomCata(rand() % 4);
        for (auto dinosaure : dinosaures) {
            if (randomCata == 0) {
                dinosaure->perteDeVie(15);
            }
            else if (randomCata == 1) {
                dinosaure->perteDeVie(20);
                dinosaure->enleverNourriture(15);
            }
            else if (randomCata == 2) {
                dinosaure->perteDeVie(45);
            }
            else if (randomCata == 3) {
                dinosaure->perteDeVie(1000);
            }
        }
        if (randomCata == 0) {
            cout << "Le monde subit un siesme !!!" << endl << endl;
        }
        else if (randomCata == 1) {
            cout << "Le monde entre dans une ere glaciaire !!!" << endl << endl;
        }
        else if (randomCata == 2) {
            cout << "Le monde change, un volcan se forme !!!" << endl << endl;
        }
        else if (randomCata == 3) {
            cout << "Un meteore s'abat sur la planete !!!!!!!!!!!!" << endl << endl;
        }
        Sleep(6000);
    }

    void nourrirDinoUtilisateur() {
        int nourriture = 1 + rand() % 10;
        int x, y;
        x = verifCoordonnee("\nVeuillez rentrer la coordonnee en x du dino : ");
        y = verifCoordonnee("Veuillez rentrer la coordonnee en y du dino : ");

        bool valide = false;
        for (auto dinosaure : dinosaures) {
            if (dinosaure->donnerCoordX() == x && dinosaure->donnerCoordY() == y && dinosaure->enVie()) {
                dinosaure->giveNourriture(nourriture);
                cout << "\nVous avez nourri " << dinosaure->donnerEspece() << " de " << nourriture << "." << endl;
                Sleep(5000);
                valide = true;
                break;
            }
        }
        if (!valide) {
            cout << "\nAucun dino se trouve a ces coordonnees." << endl;
            Sleep(5000);
        }
    }

void favoriserAccouplement() {
    int xPremierDino, yPremierDino, xDeuxiemeDino, yDeuxiemeDino;

    xPremierDino = verifCoordonnee("\nVeuillez rentrer la coordonnee x du premier dinosaure : ");
    yPremierDino = verifCoordonnee("Veuillez rentrer la coordonnee y du premier dinosaure : ");
    xDeuxiemeDino = verifCoordonnee("\nVeuillez rentrer la coordonnee x du deuxieme dinosaure  : ");
    yDeuxiemeDino = verifCoordonnee("Veuillez rentrer la coordonnee y du premier dinosaure : ");

    bool valide = false;
    for (auto dinosaure : dinosaures) {
        for (auto autreDinosaure : dinosaures) {
            if (dinosaure->donnerEspece() == autreDinosaure->donnerEspece() && dinosaure->enVie() && autreDinosaure->enVie() && dinosaure->donnerCoordX() == xPremierDino
                && dinosaure->donnerCoordY() == yPremierDino && autreDinosaure->donnerCoordX() == xDeuxiemeDino && autreDinosaure->donnerCoordY() == yDeuxiemeDino
                && dinosaure->verifAgeAccouplement() && autreDinosaure->verifAgeAccouplement()) {
                dinosaures.push_back(dinosaure->nouveauEnfant());

                cout << dinosaure->donnerEspece() << " est ne!" << endl;
                valide = true;
                Sleep(5000);
            }
        }
    }
    if (!valide) {
        cout << "\nL'accouplement n'a pas ete possible." << endl;
        Sleep(5000);
    }
}

    void chasseUtilisateur() {
        int xPremierDino, yPremierDino, xDeuxiemeDino, yDeuxiemeDino;
        bool valide = false;

        xPremierDino = verifCoordonnee("\nVeuillez rentrer la coordonnee x du premier dinosaure (Carnivore) : ");
        yPremierDino = verifCoordonnee("Veuillez rentrer la coordonnee y du premier dinosaure (Carnivore) : ");
        xDeuxiemeDino = verifCoordonnee("\nVeuillez rentrer la coordonnee x du deuxieme dinosaure (Herbivore) : ");
        yDeuxiemeDino = verifCoordonnee("Veuillez rentrer la coordonnee y du premier dinosaure (Herbivore) : ");

        for (auto dinosaure : dinosaures) {
            for (auto autreDino : dinosaures) {
                if (dinosaure->donnerRegimeC() == true && autreDino->donnerRegimeH() == true && dinosaure != autreDino && dinosaure->donnerEspece() != autreDino->donnerEspece()
                    && dinosaure->enVie() && autreDino->enVie() && dinosaure->donnerCoordX() == xPremierDino
                    && autreDino->donnerCoordX() == xDeuxiemeDino && dinosaure->donnerCoordY() == yPremierDino && autreDino->donnerCoordY() == yDeuxiemeDino) {

                    dinosaure->chasse(*autreDino);

                    chasse = true;
                    valide = true;
                    cout << dinosaure->donnerEspece() << " se trouve en ( " << dinosaure->donnerCoordX() << ", " << dinosaure->donnerCoordY() << " )." << endl;
                    cout << autreDino->donnerEspece() << " se trouve en ( " << autreDino->donnerCoordX() << ", " << autreDino->donnerCoordY() << " )." << endl;
                    cout << dinosaure->donnerEspece() << " prend en chasse " << autreDino->donnerEspece() << endl << endl;
                    Sleep(10000);
                    break;
                }
            }
        }
        if (!valide) {
            cout << "\nLes deux dinosaures ne correspondent pas aux criteres necessaires a la chasse." << endl;
            Sleep(5000);
        }
    }

    void demandeInteraction() {
        cout << "\nVoulez-vous interagir avec le monde ou bien passer au tour suivant? (1/2)" << endl;
        cout << "\nVotre choix: ";
        int choix;
        while (!(cin >> choix)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "\nErreur, veuillez selectionner un nombre." << endl;
            cout << "\nVotre choix: ";
        }
        if (choix == 1) {
            cout << "\n***Interaction***\n" << endl;
            cout << "1. Nourrir un dinosaure." << endl;
            cout << "2. Avancer le temps." << endl;
            cout << "3. Favoriser la chasse. " << endl;
            cout << "4. Favoriser l'accouplement." << endl;
            cout << "5. Evenements. \n" << endl;
            cout << "\nVotre choix: ";
            int choixInteraction;
            while (!(cin >> choixInteraction) || choixInteraction <= 0 || choixInteraction > 5) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "\nErreur, veuillez selectionner un nombre correct." << endl;
                cout << "\nVotre choix: ";
            }
            switch (choixInteraction) {
            case 1: nourrirDinoUtilisateur(); break; //faudra mettre les différentes méthodes ici
            case 2: avancerTemps(); break;
            case 3: chasseUtilisateur(); break;
            case 4: favoriserAccouplement(); break;
            case 5: Cataclysme(); break;
            }

        }
        else if (choix == 2) {
            cout << "\nAppuyez sur Entree pour passer au tour suivant\n";
            cin.ignore();
        }
        else {
            cout << "Erreur, veuillez reessayer." << endl;
            demandeInteraction();
        }
    }
    void preGame() {
        cout << "         " <<
            R"(
          _____ ____  ___ ___  __ __  _       ____  ______  ____  ___   ____       ___    ____  ____    ___  
         / ___/l    j|   T   T|  T  T| T     /    T|      Tl    j/   \ |    \     |   \  l    j|    \  /   \ 
        (   \_  |  T | _   _ ||  |  || |    Y  o  ||      | |  TY     Y|  _  Y    |    \  |  T |  _  YY     Y
         \__  T |  | |  \_/  ||  |  || l___ |     |l_j  l_j |  ||  O  ||  |  |    |  D  Y |  | |  |  ||  O  |
         /  \ | |  | |   |   ||  :  ||     T|  _  |  |  |   |  ||     ||  |  |    |     | |  | |  |  ||     |
         \    | j  l |   |   |l     ||     ||  |  |  |  |   j  ll     !|  |  |    |     | j  l |  |  |l     !
          \___j|____jl___j___j \__,_jl_____jl__j__j  l__j  |____j\___/ l__j__j    l_____j|____jl__j__j \___/)" << endl << endl;

        cout << R"(               
               @@@@@@@@@@ 
             @@@@@@@@@@@@@@@                                                                        
           @@@@@@@@@@  @@@@@@@                                                                      
         @@@@@@@@@@@@@@@@@@@@@@                                                                     
        @@@@@@@@@@@@@@@@@@@@@@@@@                                                                   
       @@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                 
      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                                                 
     @@@@@@@@@@@ @@@@@@@@@@@@@@@@@                                                                  
    @@@@@@@@@@@                                                                                     
   @@@@@@@@@@@                                                                                      
  @@@@@@@@@@@                                                                                       
  @@@@@@@@@@                                                                                        
 @@@@@@@@@@                                                                                         
 @@@@@@@@@@                                                                                         
@@@@@@@@@@@                                                                                         
@@@@@@@@@@@                                                                                         
@@@@@@@@@@@                                                                                         
@@@@@@@@@@@                                                                                         
@@@@@@@@@@@@                                                                                        
@@@@@@@@@@@@@                                                                                       
@@@@@@@@@@@@@@                                                                                      
@@@@@@@@@@@@@@@                                                                                     
@@@@@@@@@@@@@@@@                                                                                    
@@@@@@@@@@@@@@@@@@                                                                                  
@@@@@@@@@@@@@@@@@@@@@                                                                               
@@@@@@@@@@@@@@@@@@@@@@@@                                                                            
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                                     
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                               
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                           
 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                        
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                      
   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                    
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                  
    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                 
     @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@               
       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@              
        @@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@            
         @@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@           
           @@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@         
      @@@   @@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@        
      @@@@@       @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      
      @@@@@@@      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    
      @@@@@@@@@@    @@@@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@   
     @@@@@@@@@@@@@   @@@@@@@@@@@@@@   @@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@ 
    @@@@@@@@@@@@@@    @@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@  @@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@
  @@@@@@@@@@@@@@      @@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@@@@   @@@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@@@@
 @@@@@@@@@@@@          @@@@@@@@@@@@                              @@@@@@@@@@@@              @@@@@@@@@
@@@@@@@@@@@            @@@@@@@@@@@@                              @@@@@@@@@@@@               @@@@@@@@
@@@@@@@@@@@            @@@@@@@@@@@@                              @@@@@@@@@@@@                @@@@@@@
@@@@@@@@@@@             @@@@@@@@@@@                              @@@@@@@@@@@@               @@@@@@@@
@@@@@@@@@@@            @@@@@@@@@@@@                              @@@@@@@@@@@@              @@@@@@@@ 
@@@@@@@@@@             @@@@@@@@@@@@              @@@@@@@@@@@@@   @@@@@@@@@@@@  @@@@@@@@@@@@@@@@@@   
 @@@@@@               @@@@@@@@@@@@@             @@@@@@@@@@@@   @@@@@@@@@@@@@@  @@@@@@@@@@@@@@@@     
                    @@@@@@@@@@@@@@@                           @@@@@@@@@@@@@@@                       
                    @@@@@@@@@@@@@@@                           @@@@@@@@@@@@@@                        )" << endl << endl;
        cout << "________________________________________________________________________" << endl << endl;
cout << "                   LANCEMENT DE LA PARTIE"<<endl;
cout << "________________________________________________________________________" << endl << endl;
    }

    void lancerJeu(int nombresDinos) {
        bool enJeu = true;
        ajouterDinosaure(nombresDinos);
        Viedinos();
        ajouterPlante();
        while (enJeu) {
            demandeInteraction();
            system("cls");
            Age_dinos();
            deplacement();
            chasses();
            fuites();
            attaqueDeDino();
            gestionNourriture();
            Mort();
            gestionAccouplement();
            if (dinosaures.size() <= 0) {
                system("cls");
                cout << endl << "Fin de la simulation : tous les dinosaures sont morts." << endl;
                enJeu = false;
                break;
            }
             afficherInfos();
        }
    }
};

int main() {
    srand(time(0));
    Jeu jeu;
    jeu.preGame();
    jeu.verif();
    return 0;

}
