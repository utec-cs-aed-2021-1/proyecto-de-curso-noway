#ifndef HELPER_FUNCTS_HPP
#define HELPER_FUNCTS_HPP

#include "nlohmann/json.hpp"
#include <cmath>
#define pi 3.14159265358979323846
using namespace std;

// for convenience
using json = nlohmann::json;

/////////////////////////////////////////////////////////////////////
/////////////////// Funciones de ayuda /////////////////////////////


// para convertir longitudes y latitudes a radianes
long double toRadians(const long double grados)
{
    long double grado = (pi) / 180;
    return (grado * grados);
}


//para calcular la distancia entre dos latitudes y longitudes

long double distance(string lat1, string long1, string lat2, string long2)
{
    long double lat_1 = stoi(lat1);
    long double long_1 = stoi(long1);           // se convierten las latitudes y longitudes
    long double lat_2 = stoi(lat2);             // a long doubles para calcular la distancia
    long double long_2 = stoi(long2);

    lat_1 = toRadians(lat_1);
    long_1 = toRadians(long_1);           // Se convierten las latitudes
    lat_2 = toRadians(lat_2);             // y longitudes a radianes
    long_2 = toRadians(long_2);

    // Haversine Formula
    long double dlong = long_2 - long_1;
    long double dlat = lat_2 - lat_1;

    long double ans = pow(sin(dlat / 2), 2) + cos(lat_1) * cos(lat_2) * pow(sin(dlong / 2), 2);

    ans = 2 * asin(sqrt(ans));


    long double R = 6371; // Radio de la Tierra en KM

    ans = ans * R;

    return ans;
}

// funcion para encontrar la ubicación de un aeropuerto en el jsonGraph teniendo como base el AirportID

int findByAirportID(json jsonGraph, string id) {
    for (int i = 0; i < jsonGraph.size(); i++) {
        if (jsonGraph[i]["Airport ID"] == id)
            return i;
    }
    return 215;                              // si no existe el destino, se fijará Nueva York como destino
}



#endif // HELPER_FUNCTS_HPP
