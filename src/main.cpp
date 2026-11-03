#include <iostream>
#include "Modelo/BaseDatos.cpp"
#include "Modelo/InfoCancion.hpp"

int main(){
    BaseDatos base_de_datos;

    InfoCancion cancion;
    cancion.name_performer = "Daft Punk";
    cancion.path_album = "/musica/discovery";
    cancion.name_album = "Discovery";
    cancion.path_rola = "/musica/discovery/01_one_more_time.mp3";
    cancion.title_rola = "One More Time";
    cancion.genre_rola = "House";
    cancion.year = 2001;
    cancion.track_rola = 1;

    InfoCancion cancion2;
    cancion2.name_performer = "NCT 127";
    cancion2.path_album = "/musica/Walk";
    cancion2.name_album = "Walk";
    cancion2.path_rola = "/home/techu/musica/walk/suddenly.mp3";
    cancion2.title_rola = "Suddenly";
    cancion2.genre_rola = "K-Pop";
    cancion2.year = 2024;
    cancion2.track_rola = 10;

    InfoCancion cancion3;
    cancion3.name_performer = "NCT 127";
    cancion3.path_album = "/musica/Loveholic";
    cancion3.name_album = "Loveholic";
    cancion3.path_rola = "/home/techu/musica/loveholic/first_love.mp3";
    cancion3.title_rola = "First Love";
    cancion3.genre_rola = "Pop";
    cancion3.year = 2021;
    cancion3.track_rola = 3;

    base_de_datos.agregar_cancion(cancion);
    base_de_datos.agregar_cancion(cancion2);
    base_de_datos.agregar_cancion(cancion3);
    
    return 0;
}
