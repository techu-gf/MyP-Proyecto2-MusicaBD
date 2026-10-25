project('minero', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

taglib_dep = dependency('taglib')

executable('minero',
           'src/main.cpp',
           'src/Modelo/Minero.cpp',
           'src/Modelo/Lector.cpp',
           'src/Modelo/ErrorMinado.cpp',
           dependencies : [taglib_dep],
           install : true)
