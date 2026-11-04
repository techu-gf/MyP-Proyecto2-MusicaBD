project('musica', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3', 'cpp_std=c++17'])

taglib_dep = dependency('taglib')
sqlite3_dep = dependency('sqlite3')

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Widgets'])

qt6_files = qt6.preprocess(
  moc_headers : ['src/Vista/Vista.hpp']
)

executable('vista',
           ['src/main.cpp', 'src/Vista/Vista.cpp', qt6_files],
           dependencies : [taglib_dep, sqlite3_dep, qt6_dep],
           install : true)
