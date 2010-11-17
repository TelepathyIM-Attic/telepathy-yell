/*
 * call-content-codecoffer.h - Header for TpyCallContentCodecoffer
 * Copyright (C) 2009 Collabora Ltd.
 * @author Sjoerd Simons <sjoerd.simons@collabora.co.uk>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __TPY_CALL_CONTENT_CODECOFFER_H__
#define __TPY_CALL_CONTENT_CODECOFFER_H__

#include <glib-object.h>
#include <gio/gio.h>
#include <telepathy-glib/handle.h>

G_BEGIN_DECLS

typedef struct _TpyCallContentCodecoffer TpyCallContentCodecoffer;
typedef struct _TpyCallContentCodecofferPrivate
  TpyCallContentCodecofferPrivate;
typedef struct _TpyCallContentCodecofferClass
  TpyCallContentCodecofferClass;

struct _TpyCallContentCodecofferClass {
    GObjectClass parent_class;

    TpDBusPropertiesMixinClass dbus_props_class;
};

struct _TpyCallContentCodecoffer {
    GObject parent;

    TpyCallContentCodecofferPrivate *priv;
};

GType tpy_call_content_codecoffer_get_type (void);

/* TYPE MACROS */
#define TPY_TYPE_CALL_CONTENT_CODECOFFER \
  (tpy_call_content_codecoffer_get_type ())
#define TPY_CALL_CONTENT_CODECOFFER(obj) \
  (G_TYPE_CHECK_INSTANCE_CAST((obj), \
  TPY_TYPE_CALL_CONTENT_CODECOFFER, TpyCallContentCodecoffer))
#define TPY_CALL_CONTENT_CODECOFFER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_CAST((klass), \
  TPY_TYPE_CALL_CONTENT_CODECOFFER, TpyCallContentCodecofferClass))
#define TPY_IS_CALL_CONTENT_CODECOFFER(obj) \
  (G_TYPE_CHECK_INSTANCE_TYPE((obj), TPY_TYPE_CALL_CONTENT_CODECOFFER))
#define TPY_IS_CALL_CONTENT_CODECOFFER_CLASS(klass) \
  (G_TYPE_CHECK_CLASS_TYPE((klass), TPY_TYPE_CALL_CONTENT_CODECOFFER))
#define TPY_CALL_CONTENT_CODECOFFER_GET_CLASS(obj) \
  (G_TYPE_INSTANCE_GET_CLASS ((obj), TPY_TYPE_CALL_CONTENT_CODECOFFER, \
  TpyCallContentCodecofferClass))

TpyCallContentCodecoffer *tpy_call_content_codecoffer_new (
  const gchar *object_path,
  TpHandle remote_contact,
  GPtrArray *codecs);

void tpy_call_content_codecoffer_offer (TpyCallContentCodecoffer *offer,
  GCancellable *cancellable,
  GAsyncReadyCallback callback,
  gpointer user_data);

GPtrArray *tpy_call_content_codecoffer_offer_finish (
  TpyCallContentCodecoffer *offer,
  GAsyncResult *result,
  GError **error);


G_END_DECLS

#endif /* #ifndef __TPY_CALL_CONTENT_CODECOFFER_H__*/
