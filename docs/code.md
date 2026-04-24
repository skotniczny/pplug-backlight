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
└── brightness.c     — implements brightness via /sys/class/backlight

data/icons/          — panel icons (16–96px PNG + SVG)
po/                  — gettext translations (`wfplug_backlight.mo`)
```

### `backlight.hpp`

Defines `WayfireBacklight` class — inherits `WayfireWidget`, declares `init()` and `set_icon()`.

### `backlight.cpp`

Implements `WayfireBacklight`. Exports five `extern "C"` functions:

- `create()`,
- `destroy()`,
- `config_params()`,
- `display_name()`,
- `package_name()`.

Empty `conf_table_t` (no settings).

### `backlight.h`

Defines `BacklightPlugin` struct — widget state passed between C functions.

```c
typedef struct {
  GtkWidget *plugin;
  GtkWidget *tray_icon;
  GtkWidget *popup_window;
  GtkWidget *slider;
} BacklightPlugin;
```

Declares three functions:

- `backlight_init()` — sets up button, icon, click handler
- `backlight_update_icon()` — refreshes icon based on current brightness
- `backlight_destructor()` — destroys popup, frees struct

### `backlight.c`

Implements 

- `backlight_init()`,
- `backlight_update_icon()`,
- `backlight_destructor()`.

Click toggles a popup with vertical GtkScale (0–100%). Slider changes call `set_brightness()`. Icon switches between off/low/medium/high. Uses `wrap_popup_at_button()`, `wrap_set_taskbar_icon()`, `close_popup()` from `<lxutils.h>`.

### `brightness.h`

Declares brightness API: 

- `find_brightness_dir()`,
- `get_max_brightness()`,
- `get_actual_brightness()`,
- `set_brightness()`.

### `brightness.c`

Implements brightness API. Finds first device in `/sys/class/backlight/`, converts between raw values and percentage via `max_brightness`.

### `data/icons/`

Panel icons in 16–96px PNG + SVG.

### `po/`

Gettext translations, domain `wfplug_backlight`.
