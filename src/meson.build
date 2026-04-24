gtkmm = dependency('gtkmm-3.0', version: '>=3.24')
wfpanel = dependency('wf-panel-pi')

wsources = files(
  'backlight.c',
  'brightness.c',
  'backlight.cpp',
)

wdeps = [gtkmm, wfpanel]

wargs = ['-DGETTEXT_PACKAGE="wfplug_' + meson.project_name() + '"']

shared_module('lib' + meson.project_name(), wsources,
  dependencies: wdeps,
  install: true,
  install_dir: get_option('libdir') / 'wf-panel-pi',
  c_args: wargs,
  cpp_args: wargs,
  name_prefix: '',
)

