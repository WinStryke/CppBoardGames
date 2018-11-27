#include <sstream>
#include <algorithm>
#include "PlateauDamier.h"

PlateauDamier::PlateauDamier(int dimension) : Plateau(dimension) {}

std::ostream &operator<<(std::ostream &os, const PlateauDamier &damier) {
    os << static_cast<const Plateau &>(damier);
    return os;
}

const void PlateauDamier::initialize() const {
    Pion p("PION", "\u26C0", Couleur::NOIR);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < dimension; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    cases[i][j].setPion(p);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPion(p);
                }
            }
        }
    }
    Pion p2("PION", "\u26C2", Couleur::BLANC);
    for (int i = 6; i < dimension; i++) {
        for (int j = 0; j < 10; j++) {
            if (i % 2 == 0) {
                if (j % 2 == 0) {
                    cases[i][j].setPionBis(p2);
                }
            } else {
                if (j % 2 != 0) {
                    cases[i][j].setPionBis(p2);
                }
            }
        }
    }
}


const bool PlateauDamier::posOk(int i_src, int j_src, int i_dst, int j_dst) const {
    bool cartesianConstraint =
            i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension && i_dst >= 0 && i_dst < dimension &&
            j_dst >= 0 && j_dst < dimension;
    return cartesianConstraint;
}


const bool PlateauDamier::pionMove(int i_src, int j_src, int i_dst, int j_dst, Couleur c) {
    if (posOk(i_src, j_src, i_dst, j_dst)) {
        if (cases[i_src][j_src].getPion().getColor() == Couleur::BLANC && c == Couleur::BLANC) {
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::NOIR) {
                    if (i_dst == i_src - 1) {
                        if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                            if (cases[i_dst - 1][j_dst + 1].isEmpty()) {
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst - 1, j_dst + 1);
                            } else {
                                return false;
                            }
                        } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                            if (cases[i_dst - 1][j_dst - 1].isEmpty()) {
                                std::cout << "here" << std::endl;
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst - 1, j_dst - 1);
                            } else {
                                return false;
                            }
                        } else {
                            return false;
                        }
                    } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                        move(i_src, j_src, i_dst, j_dst);
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src + 1) {
                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                        if (cases[i_dst + 1][j_dst + 1].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst + 1, j_dst + 1);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        if (cases[i_dst + 1][j_dst - 1].isEmpty()) {
                            std::cout << "here" << std::endl;
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst + 1, j_dst - 1);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                } else {
                    return false;
                }

            } else {
                std::cout << "Illegal movement" << std::endl;
                return false;
            }
        } else if (cases[i_src][j_src].getPion().getColor() == Couleur::NOIR && c == Couleur::NOIR) {
            if (((j_dst == j_src + 1) || j_dst == j_src - 1)) {
                if (i_dst == i_src + 1) {
                    if (!cases[i_dst][j_dst].isEmpty() && cases[i_dst][j_dst].getPion().getColor() == Couleur::BLANC) {
                        if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                            if (cases[i_dst + 1][j_dst + 1].isEmpty()) {
                                scoreJ2 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst + 1, j_dst + 1);
                            } else {
                                return false;
                            }
                        } else if (j_dst - 1 < dimension && j_dst - 1 > 0) {
                            if (cases[i_dst + 1][j_dst - 1].isEmpty()) {
                                scoreJ1 += 1;
                                cases[i_dst][j_dst] = Case(i_dst, j_dst);
                                move(i_src, j_src, i_dst + 1, j_dst - 1);
                            } else {
                                return false;
                            }
                        } else if (i_dst - 1 > 0 && i_dst - 1) {
                            return false;
                        }
                    } else if (i_dst == i_src + 1 && cases[i_dst][j_dst].isEmpty()) {
                        move(i_src, j_src, i_dst, j_dst);
                    } else {
                        return false;
                    }
                } else if (i_dst == i_src - 1) {
                    if (j_dst == j_src + 1 && j_dst + 1 < dimension && j_dst + 1 > 0) {
                        if (cases[i_dst - 1][j_dst + 1].isEmpty()) {
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst - 1, j_dst + 1);
                        } else {
                            return false;
                        }
                    } else if (j_dst == j_src - 1 && j_dst - 1 < dimension && j_dst - 1 > 0) {
                        if (cases[i_dst - 1][j_dst - 1].isEmpty()) {
                            std::cout << "here" << std::endl;
                            scoreJ1 += 1;
                            cases[i_dst][j_dst] = Case(i_dst, j_dst);
                            move(i_src, j_src, i_dst - 1, j_dst - 1);
                        } else {
                            return false;
                        }
                    } else {
                        return false;
                    }
                } else if (cases[i_dst][j_dst].isEmpty() && i_dst == i_src - 1) {
                    move(i_src, j_src, i_dst, j_dst);
                } else {
                    return false;
                }

            } else {
                return false;
            }
        } else {
            return false;
        }

    } else {
        return false;
    }

    return true;
}


bool PlateauDamier::bot() {
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            if (pionSelect(i, j, Couleur::NOIR)) {
                bool move1 = pionMove(i, j, i + 1, j - 1, Couleur::NOIR);
                bool move2 = pionMove(i, j, i + 1, j + 1, Couleur::NOIR);
                if (move1) {
                    turn -= 1;
                    return true;
                } else if (move2) {
                    turn -= 1;
                    return true;
                }
            }
        }
    }
    return false;
}

const void PlateauDamier::playerTurn() {
    firstSelect:
    if (turn == 0) {
        std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                  << std::endl;
        std::string s;
        std::cin >> s;
        std::vector<int> t = split(s, ',');
        long sizeEntry = t.size();
        bool pionSel = pionSelect(t[0], t[1], Couleur::BLANC);
        std::cout << pionSel << std::endl << sizeEntry << std::endl;
        while ((sizeEntry != 2 || !pionSel)) {
            std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
            std::cout << "Veuillez entrez les coordonnées du pion que vous souhaitez deplacer " << "Exemple: 2,0"
                      << std::endl;
            std::cin >> s;
            t = split(s, ',');
            sizeEntry = t.size();
            pionSel = pionSelect(t[0], t[1], Couleur::BLANC);
        }

        std::cout << "Veuillez entrez les coordonnées de la case ou vous souhaitez le deplacer" << "Exemple: 2,0"
                  << std::endl;
        std::string x;
        std::cin >> x;
        std::vector<int> h = split(x, ',');
        if ((h.size() != 2 || !pionMove(t[0], t[1], h[0], h[1], Couleur::BLANC))) {
            std::cout << "Mauvaise entrée ! Try Again !" << std::endl;
            /*std::cin >> x;
            h = split(x, ',');*/
            goto firstSelect;
        }
    }
    turn += 1;
    return;
}

std::vector<int> PlateauDamier::split(const std::string &s, char delimiter) {
    std::vector<int> Data;
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (std::getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    std::transform(tokens.begin(), tokens.end(), std::back_inserter(Data),
                   [](const std::string &str) { return std::stoi(str); });
    return Data;
}

const void PlateauDamier::launcher() {
    std::cout << "Jeu de dames International:" << std::endl;
    std::cout << "Menu Principal:" << std::endl;
    std::cout << "Selectionnez votre type de jeu :" << std::endl;
    std::cout << "\t 1) Single Player" << std::endl;
    std::cout << "\t 2) 2P Game" << std::endl;
    int gameType = 0;
    std::cin >> gameType;
    if (gameType != 1 && gameType != 2) {
        std::cout << "Mauvais Choix : Veuillez Selectionner 1 ou 2" << std::endl;
        launcher();
    } else {
        if (gameType == 1) {
            this->singlePlayer();
        }
    }
    return;
}

const void PlateauDamier::singlePlayer() {
    this->initialize();
    std::cout << *(this) << std::endl;
    std::cout << "IT'S P1 TURN !!" << std::endl;
    while (true) {
        this->playerTurn();
        std::cout << *(this) << std::endl;
        this->bot();
        std::cout << *(this) << std::endl;

    }
    return;
}

const bool PlateauDamier::pionSelect(int i_src, int j_src, Couleur c) {
    bool selectOk = false;
    if (i_src >= 0 && i_src < dimension && j_src >= 0 && j_src < dimension) {
        if (cases[i_src][j_src].getPion().getColor() == c) {
            selectOk = true;
        }
    }
    return selectOk;
}












