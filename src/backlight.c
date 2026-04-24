#include <gtk/gtk.h>
#include "backlight.h"
#include "brightness.h"

static const char *brightness_icons[] = {
  "display-brightness-off-symbolic",
  "display-brightness-high-symbolic",
  "display-brightness-low-symbolic",
  "display-brightness-medium-symbolic",
  NULL
};

static void on_value_changed(GtkScaleButton *button, gdouble value, gpointer data) {
  set_brightness((int) value);
}

void backlight_init(BacklightPlugin *bl) {
  GtkWidget *scale_button = gtk_scale_button_new(GTK_ICON_SIZE_BUTTON, 0, 100, 1, brightness_icons);

  int actual = get_actual_brightness();
  if (actual >= 0) {
    gtk_scale_button_set_value(GTK_SCALE_BUTTON(scale_button), actual);
  }

  g_signal_connect(scale_button, "value-changed", G_CALLBACK(on_value_changed), NULL);

  gtk_container_add(GTK_CONTAINER(bl->plugin), scale_button);
  gtk_widget_show_all(bl->plugin);
}

void backlight_destructor(BacklightPlugin *bl) {
  g_free(bl);
}

