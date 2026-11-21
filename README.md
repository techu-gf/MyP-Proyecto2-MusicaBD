# MyP-Proyecto2-MusicaBD

## Lenguajes de Programación, Sistema de Construcción y Bibliotecas

De lenguaje de programación se usó C++, mientras que para el sistema de construcción se usó Meson, por lo que también se necesitó de Ninja y pkg-config.

Para que todo funcione correctamente, es necesario descargar [Qt](https://doc.qt.io/qt-6/get-and-install-qt.html), [sqlite3](https://www.sqlite.org/download.html) y [taglib](https://taglib.org/).

## Ejecución

Posicionate en el directorio raíz del proyecto y ejecuta la siguiente línea:

``` bash
meson setup build
```

A continuación, ejecuta la siguiente línea: 

``` bash
meson compile -C build
```

Finalmente, ejecuta lo siguiente:

``` bash
./build/controlador
```

## Funciones

Ya con el programa en ejecución, se podrán identificar distintos elementos:

* Minar (primer botón de izquierda a derecha en la barra superior): al hacer click en este botón se empezará el minado del directorio. Este directorio tiene que encontrarse en el directorio raíz del proyecto, con el nombre "Musica". En caso de ser distinto, el programa no podrá minar. Aquí se encontrarán todos los archivos de música que desee.
* Agregar artista (segundo botón de izquierda a derecha en la barra superior): al hacer click en este botón se le mostrará un formulario que tendrá que llenar para poder agregar un nuevo artista. Puede elegir que sea solista o un grupo, pero siempre debe llenar al menos el nombre del nuevo artista.
* Búsquedas (cuadro de texto en la barra superior): aquí podrá introducir un texto y realizar búsquedas. Este texto debe seguir un formato en específico (siguiente sección).
* Seleccionar canción: en el panel izquierdo podrá encontrar una lista con canciones después de minar. Podrá hacer click en cada uno de los elementos de esta lista y la información de la canción seleccionada se mostrará en el panel derecho.
* Edición de canciones: una vez seleccionada una canción, podrá modificar su información en este panel derecho. En caso de que la canción le pertenezca a algún solista, podrá modificar también la información del solista. Si le pertenece a un grupo, podrá modificar la información del grupo. 

## Búsquedas

Las búsquedas tendrán 5 elementos: campo, contenedor, negación, búsqueda y conector. A continuación se explican cada uno de estos: 

| Elemento | Uso |
| :--- | :--- |
| campo | Información que desea buscar. Únicamente puede buscar los siguientes campos: artist, album, song, year, genre. |
| contenedor | Debe escribirse después del campo. Tiene dos opciones: = (para búsquedas con el texto exacto) y ~ (para búsquedas que contengan el texto) |
| negación | Este elemento es opcional. Se denota con ! e indica que no quiere que la búsqueda contenga el texto indicado. |
| búsqueda | Cadena de texto que desea buscar. Debe escribirse entre comillas (""). |
| conector | Indica si el siguiente elemento debe estar en los resultados de forma obligatoria (&) o si es opcional (|). |

Tome en cuenta la siguiente estructura para realizar sus consultas:

<CAMPO><TIPO_CONTENCION><NEGACION>"<BÚSQUEDA>" <CONECTOR> ... <CAMPO><TIPO_CONTENCION><NEGACION>"<BÚSQUEDA>"

A continuación se le muestran unos ejemplos para que lo tenga más claro:

* Busca un artista cuyo nombre contenga "DREAM":
``` 
artist~"DREAM"
```
* Busca las canciones que hayan salido el 2016 pero cuyo album no tenga "love":
``` 
year="2016" & album~!"love"
```
* Busca canciones cuyo nombre sea "Love Again" y su artista no tenga "Dua" o pertenezcan a algún género Pop (JPop, KPop, Pop, etc.):
``` 
song="Love Again" & artist~!"Dua" | genre~"Pop"
```
* Busca canciones que tengan "Love" pero no "You":
``` 
song~"Love" & song~!"You"
```

