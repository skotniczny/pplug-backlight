project ('backlight', ['c', 'cpp'],
  default_options: [
    'cpp_std=c++17',
    'c_std=c11',
  ],
)

share_dir = join_paths(get_option('prefix'), 'share')
metadata_dir = join_paths(share_dir, 'wf-panel-pi', 'metadata')

add_project_arguments('-DPACKAGE_LOCALE_DIR="' + share_dir + '/locale"', language: ['c', 'cpp'])
add_project_arguments('-DPLUGIN_NAME="' + meson.project_name() + '"', language: ['c', 'cpp'])

subdir('data')
subdir('po')
subdir('src')

