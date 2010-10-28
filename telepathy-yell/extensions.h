#ifndef __TELEPATHY_YELL_EXTENSIONS_H__
#define __TELEPATHY_YELL_EXTENSIONS_H__

#include <glib-object.h>
#include <telepathy-glib/channel.h>
#include <telepathy-glib/connection.h>

#include <telepathy-yell/_gen/enums.h>
#include <telepathy-yell/_gen/cli-call.h>
#include <telepathy-yell/_gen/svc-call.h>

G_BEGIN_DECLS

#include <telepathy-yell/_gen/gtypes.h>
#include <telepathy-yell/_gen/interfaces.h>

void tpy_cli_init (void);

G_END_DECLS

#endif
