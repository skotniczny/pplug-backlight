#ifndef BACKLIGHT_HPP
#define BACKLIGHT_HPP

#include <memory>
#include <widget.hpp>
#include <gtk-utils.hpp>

extern "C" {
#include "backlight.h"
#include "brightness.h"
}

static constexpr conf_table_t conf_table[] = {
  {CONF_TYPE_NONE, NULL, NULL, NULL}
};

class WayfireBacklight : public WayfireWidget
{
  std::unique_ptr <Gtk::HBox> plugin;
  BacklightPlugin *backlight = nullptr;

  public:
    void init(Gtk::HBox *container) override;
    virtual ~WayfireBacklight ();
};

#endif

