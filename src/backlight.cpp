#include "backlight.hpp"

extern "C" {
#include "brightness.h"
}

extern "C" {
  WayfireWidget *create() { return new WayfireBacklight; }
  void destroy (WayfireWidget *w) { delete w; }

  const conf_table_t *config_params(void) { return conf_table; }
  const char *display_name(void) { return PLUGIN_TITLE; }
  const char *package_name(void) { return GETTEXT_PACKAGE; }
}

void WayfireBacklight::read_settings(void) {
  if (!backlight) return;
  backlight->min_brightness = CLAMP((int) min_brightness, 0, 100);
}

void WayfireBacklight::settings_changed_cb(void) {
  if (!backlight) return;
  read_settings();
  backlight_update_slider(backlight);
}

void WayfireBacklight::init(Gtk::HBox *container)
{
  if (!find_brightness_dir()) return;

  plugin = std::make_unique<Gtk::Button>();
  plugin->set_name(PLUGIN_NAME);
  container->pack_start(*plugin, false, false);

  backlight = g_new0(BacklightPlugin, 1);
  backlight->plugin = GTK_WIDGET(plugin->gobj());

  /* Initialise the plugin */
  read_settings();
  backlight_init(backlight);

  /* Setup callbacks */
  min_brightness.set_callback(sigc::mem_fun(*this, &WayfireBacklight::settings_changed_cb));
}

bool WayfireBacklight::set_icon()
{
  if (backlight)
    backlight_update_icon(backlight);
  return false;
}

WayfireBacklight::~WayfireBacklight()
{
  if (backlight)
    backlight_destructor(backlight);
}
