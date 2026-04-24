#ifndef BACKLIGHT_HPP
#define BACKLIGHT_HPP

#include <widget.hpp>
#include <gtkmm/button.h>

extern "C" {
#include "backlight.h"
}

static constexpr conf_table_t conf_table[] = {
  {CONF_TYPE_NONE, NULL, NULL, NULL}
};

class WayfireBacklight : public WayfireWidget
{
  std::unique_ptr <Gtk::Button> plugin;
  BacklightPlugin *backlight = nullptr;

  public:
    void init(Gtk::HBox *container) override;
    bool set_icon (void);
    virtual ~WayfireBacklight ();
};

#endif

