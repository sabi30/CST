project('CST_LIBRARY', 'cpp', version: '1.0.0', default_options: ['cpp_std=c++17', 'cpp_args=-O2'])

source_files = files()
include_files = include_directories(['src', 'cst'])

subdir('src')

cst_lib = library('cst', source_files, 
                  include_directories: include_files,
                  install: true)

cst_dep = declare_dependency(
  include_directories: include_files,
  link_with: cst_lib
)

meson.override_dependency('cst', cst_dep)

install_subdir('cst', install_dir: get_option('includedir'))

pkg = import('pkgconfig')
pkg.generate(cst_lib,
  name: 'cst',
  filebase: 'cst',
  description: 'A custom CST C++ library',
  subdirs: ['cst'] 
)