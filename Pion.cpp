#include "Pion.h"


std::ostream &operator<<(std::ostream &os, const Pion &pion) {
    return os;
}

Pion::Pion(const std::string &name) : name(name), img(" ") {}

Pion::Pion(const std::string &name, const std::string &img, Couleur c) : name(name), img(img), color(c) {}

Pion::Pion(): name(""), img(" "), color(Couleur::null) {

}

std::string Pion::getNom() {
    return name;
}

Couleur Pion::getColor() {
    return color;
}

void Pion::setNom(std::string n) {
    name = n;
}

void Pion::setImg(std::string i) {
    img = i;
}

std::string Pion::getImg() {
    return img;
}
