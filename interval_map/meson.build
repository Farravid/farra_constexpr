project('interval_map', 'cpp',
  version : '0.1',
  default_options : ['warning_level=3',
                     'cpp_std=c++23',
                     'buildtype=release',])

exe = executable('interval_map', 'src/interval_map.cpp',
  install : true)

test('basic', exe)
