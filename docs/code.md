# `pplug-backlight`

Plugin for [wf-panel-pi](https://github.com/raspberrypi-ui/wf-panel-pi). Loaded as `libbacklight.so` from `/usr/lib/aarch64-linux-gnu/wf-panel-pi/`.

## Structure

```
src/
├── backlight.hpp    — defines WayfireBacklight class (inherits WayfireWidget)
├── backlight.cpp    — implements WayfireBacklight, exports extern "C" plugin API
├── backlight.h      — defines BacklightPlugin struct, declares C interface
├── backlight.c      — implements UI: button, popup, slider, icon switching
├── brightness.h     — declares brightness read/write API
├── brightness.c     — implements brightness via /sys/class/backlight
└── backlight.xml    — wf-panel-pi config schema (min_brightness option)

data/icons/          — panel icons (16–96px PNG + SVG)
po/                  — gettext translations (`wfplug_backlight.mo`)
```

### `backlight.hpp`

Defines `WayfireBacklight` class — inherits `WayfireWidget`, declares:

- `init()`,
- `set_icon()`,
- `read_settings()`,
- `settings_changed_cb()`.

### `backlight.cpp`

Implements `WayfireBacklight`. Exports five `extern "C"` functions:

- `create()`,
- `destroy()`,
- `config_params()` — returns `conf_table` (min brightness setting),
- `display_name()`,
- `package_name()`.

`init()` sets up the button, allocates `BacklightPlugin` and registers settings callback.  
`set_icon()` delegates to `backlight_update_icon()`.  
`read_settings()` applies clamped `min_brightness`.  
`settings_changed_cb()` re-reads settings and updates the slider range.

### `backlight.h`

Defines `PLUGIN_TITLE` macro. Defines `BacklightPlugin` struct:

```c
typedef struct {
  GtkWidget *plugin;
  GtkWidget *tray_icon;
  GtkWidget *popup_window;
  GtkWidget *slider;
  int min_brightness;
} BacklightPlugin;
```

Declares `conf_table[2]` and four functions:

- `backlight_init()` — sets up button, icon, click handler
- `backlight_update_slider()` — updates slider range with current `min_brightness`
- `backlight_update_icon()` — refreshes icon based on current brightness
- `backlight_destructor()` — destroys popup, frees struct

### `backlight.c`

Defines `conf_table` with one `CONF_TYPE_INT` entry for `min_brightness`.

Implements 

- `backlight_init()`,
- `backlight_update_icon()`,
- `backlight_update_slider()`,
- `backlight_destructor()`.

`icon_for_level()` maps brightness percentage to one of four symbolic icon names (off/low/medium/high).

Click toggles a popup with vertical GtkScale (`min_brightness`–100%). Slider changes call `set_brightness()` and update the icon. Uses `wrap_popup_at_button()`, `wrap_set_taskbar_icon()`, `close_popup()` from `<lxutils.h>`.

### `brightness.h`

Declares brightness API:

- `find_brightness_dir()` — returns `gboolean`,
- `get_max_brightness()`,
- `get_actual_brightness()`,
- `set_brightness()`.

### `brightness.c`

Implements brightness API using GLib (`GDir`, `g_build_filename`, `g_free`). Finds first device in `/sys/class/backlight/`, converts between raw values and percentage via `max_brightness`. Prints localized error via `g_printerr()` if brightness file cannot be opened for writing.

### `data/icons/`

Panel icons in 16–96px PNG + SVG.

### `po/`

Gettext translations, domain `wfplug_backlight`.
