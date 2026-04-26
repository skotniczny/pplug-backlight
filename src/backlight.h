#define PLUGIN_TITLE N_("Backlight")

typedef struct {
  GtkWidget *plugin;
  GtkWidget *tray_icon; /* Displayed image */
  GtkWidget *popup_window; /* Top level window for popup */
  GtkWidget *slider; /* GtkScale for brightness */
  int min_brightness; /* Minimum brightness (%) */
} BacklightPlugin;

extern conf_table_t conf_table[2];

extern void backlight_init(BacklightPlugin *bl);
extern void backlight_update_slider(BacklightPlugin *bl);
extern void backlight_update_icon(BacklightPlugin *bl);
extern void backlight_destructor(BacklightPlugin *bl);

