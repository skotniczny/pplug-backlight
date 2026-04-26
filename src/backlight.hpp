#ifndef BACKLIGHT_HPP
#define BACKLIGHT_HPP

#include <widget.hpp>
#include <gtkmm/button.h>

extern "C" {
#include "backlight.h"
}

class WayfireBacklight : public WayfireWidget
{
  std::unique_ptr <Gtk::Button> plugin;

  WfOption <int> min_brightness {"panel/backlight_min_brightness"};

  BacklightPlugin *backlight = nullptr;

  public:
    void init(Gtk::HBox *container) override;
    bool set_icon (void);
    void read_settings(void);
    void settings_changed_cb(void);
    virtual ~WayfireBacklight ();
};

#endif

