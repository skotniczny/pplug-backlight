# Backlight plugin for wf-panel-pi

A [wf-panel-pi](https://github.com/raspberrypi-ui/wf-panel-pi) plugin that adds a backlight brightness control to the panel.

Provides a scale button with brightness icons — click to open a slider, adjust display backlight from 0 to 100%.

Tested with Raspberry Pi Touch Display.

## Building

Requires `gtkmm-3.0` (>= 3.24) and `wf-panel-pi` development headers.

```bash
meson setup builddir
meson compile -C builddir
sudo meson install -C builddir
```

After installing, add the `backlight` plugin to your panel configuration.

## Generating translations

```bash
meson compile -C builddir wfplug_backlight-pot
meson compile -C builddir wfplug_backlight-update-po
```

