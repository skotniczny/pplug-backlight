#include "backlight.hpp"

extern "C" {
  WayfireWidget *create() { return new WayfireBacklight; }
  void destroy (WayfireWidget *w) { delete w; }

  const conf_table_t *config_params(void) { return conf_table; }
  const char *display_name(void) { return PLUGIN_TITLE; }
  const char *package_name(void) { return GETTEXT_PACKAGE; }
}

void WayfireBacklight::init(Gtk::HBox *container)
{
  if (!find_backlight_path())
    return;

  plugin = std::make_unique<Gtk::HBox>();
  plugin->set_name(PLUGIN_NAME);
  container->pack_start(*plugin, false, false);

  backlight = g_new0(BacklightPlugin, 1);
  backlight->plugin = (GtkWidget*)((*plugin).gobj());
  backlight_init(backlight);
}

WayfireBacklight::~WayfireBacklight()
{
  if (backlight)
    backlight_destructor(backlight);
}

