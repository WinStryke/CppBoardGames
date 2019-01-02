#ifndef BOARDGAMES_PLATEAUANGLAIS_H
#define BOARDGAMES_PLATEAUANGLAIS_H


#include <vector>
#include "PlateauCombinatoireAbstrait.h"
#include <sstream>
#include <algorithm>
#include <map>

class PlateauAnglais: public PlateauCombinatoireAbstrait {
public:
    PlateauAnglais(int dimension);
    const void playerTurn();
};


#endif //BOARDGAMES_PLATEAUANGLAIS_H