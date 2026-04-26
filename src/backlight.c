#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "lxutils.h"
#include "backlight.h"
#include "brightness.h"

/*----------------------------------------------------------------------------*/
/* Global data                                                                */
/*----------------------------------------------------------------------------*/

conf_table_t conf_table[2] = {
  {CONF_TYPE_INT, "min_brightness", N_("Minimum brightness (0-100%)"), NULL },
  {CONF_TYPE_NONE, NULL, NULL, NULL}
};

/*----------------------------------------------------------------------------*/
/* Brightness popup window                                                    */
/*----------------------------------------------------------------------------*/

static const char *icon_for_level(int level) {
  if (level <= 0) return "display-brightness-off-symbolic";
  if (level < 34) return "display-brightness-low-symbolic";
  if (level < 67) return "display-brightness-medium-symbolic";
  return "display-brightness-high-symbolic";
}

static void popup_destroyed(GtkWidget *widget, BacklightPlugin *bl) {
  bl->popup_window = NULL;
  bl->slider = NULL;
}

static void brightness_slider_changed(GtkRange *range, BacklightPlugin *bl) {
  int value = (int) gtk_range_get_value(range);
  set_brightness(value);
  wrap_set_taskbar_icon(bl, bl->tray_icon, icon_for_level(value));
}

static void popup_window_show(BacklightPlugin *bl) {
  backlight_update_icon(bl);
  bl->popup_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_name(bl->popup_window, "panelpopup");

  bl->slider = gtk_scale_new_with_range(GTK_ORIENTATION_VERTICAL, bl->min_brightness, 100, 1);
  g_object_set(bl->slider, "height-request", 120, NULL);
  gtk_scale_set_draw_value(GTK_SCALE(bl->slider), FALSE);
  gtk_range_set_inverted(GTK_RANGE(bl->slider), TRUE);
  gtk_container_add(GTK_CONTAINER(bl->popup_window), bl->slider);

  int actual = get_actual_brightness();
  if (actual >= 0) {
    gtk_range_set_value(GTK_RANGE(bl->slider), actual);
  }

  g_signal_connect(bl->slider, "value-changed", G_CALLBACK(brightness_slider_changed), bl);
  g_signal_connect(bl->popup_window, "destroy", G_CALLBACK(popup_destroyed), bl);

  wrap_popup_at_button(bl, bl->popup_window, bl->plugin);
}

/*----------------------------------------------------------------------------*/
/* wf-panel plugin functions                                                  */
/*----------------------------------------------------------------------------*/

/* Handler for button click */
static void button_clicked(GtkWidget *, BacklightPlugin *bl) {
  if (bl->popup_window)
    close_popup();
  else
    popup_window_show(bl);
}

/* Handler for system config changed message from panel */
void backlight_update_icon(BacklightPlugin *bl) {
  int actual = get_actual_brightness();
  wrap_set_taskbar_icon(bl, bl->tray_icon, icon_for_level(actual));
}

void backlight_update_slider(BacklightPlugin *bl) {
  if (bl->slider) {
    gtk_range_set_range(GTK_RANGE(bl->slider), bl->min_brightness, 100);
  }
}

void backlight_init(BacklightPlugin *bl) {
  gtk_button_set_relief(GTK_BUTTON(bl->plugin), GTK_RELIEF_NONE);

  bl->tray_icon = gtk_image_new();
  gtk_container_add(GTK_CONTAINER(bl->plugin), bl->tray_icon);

  backlight_update_icon(bl);

  g_signal_connect(bl->plugin, "clicked", G_CALLBACK(button_clicked), bl);

  gtk_widget_show_all(bl->plugin);
}

void backlight_destructor(BacklightPlugin *bl) {
  if (bl->popup_window) gtk_widget_destroy(bl->popup_window);
  g_free(bl);
}
