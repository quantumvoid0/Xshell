project('xshell', 'c',
        meson_version: '>=1.4.0',
        version:       '0.0.1',
        license:       'GPL-3.0-or-later',
        license_files: [ 'LICENSE' ],
        default_options: [ 'warning_level=3', 'c_std=c23' ])

subdir('src')
compile_args = [ '-DPROJECT_NAME="@0@"'.format(meson.project_name()),
                 '-DPROJECT_VERSION="@0@"'.format(meson.project_version()), ]
dependencies = []

cmake = import('cmake')
argparse = cmake.subproject('argparse')
dependencies += argparse.dependency('argparse_static')

executable(meson.project_name(), src,
           c_args:       compile_args,
           dependencies: dependencies,
           install:      true)