#include <string>
#pragma once

/**
 * @brief La estructura InfoCancion almacena la información de una sola canción,
 * buscando facilitar el manejo de la información en todo el proyecto.
 */
struct InfoCancion{
    std::string name_performer,	path_album, name_album, path_rola, title_rola, genre_rola, path_portada, real_name, birth_date, death_date, start_date, end_date;
    int year, track_rola, type_performer;
    std::vector<std::string> integrantes;
};
