/* Minimal version of telepathy-glib's debug-internal.h */

#define DEBUG(fmt, ...) g_debug ("%s: " fmt, G_STRFUNC , ##__VA_ARGS__)
