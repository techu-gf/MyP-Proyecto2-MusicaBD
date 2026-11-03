project('minero', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

taglib_dep = dependency('taglib')
sqlite3_dep = dependency('sqlite3')

executable('minero',
           'src/main.cpp',
           'src/Modelo/Minero.cpp',
           'src/Modelo/Lector.cpp',
           'src/Modelo/ErrorMinado.cpp',
           'src/Modelo/BaseDatos.cpp',
           dependencies : [taglib_dep, sqlite3_dep],
           install : true)
