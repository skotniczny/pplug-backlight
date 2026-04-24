#define PLUGIN_TITLE N_("Backlight")

typedef struct {
  GtkWidget *plugin;
} BacklightPlugin;

extern void backlight_init(BacklightPlugin *bl);
extern void backlight_destructor(BacklightPlugin *bl);

