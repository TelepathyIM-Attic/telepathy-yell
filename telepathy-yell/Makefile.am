pkgincludedir = $(includedir)/telepathy-1.0/telepathy-yell
genincludedir = $(pkgincludedir)/_gen

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = telepathy-yell.pc

EXTRA_DIST = \
    Call_Content_Codec_Offer.xml \
    Call_Content_Interface_Media.xml \
    Call_Content.xml \
    Call_Stream_Endpoint.xml \
    Call_Stream_Interface_Media.xml \
    Call_Stream.xml \
    Channel_Type_call.xml \
    call.xml

lib_LTLIBRARIES = libtelepathy-yell.la

libtelepathy_yell_la_LDFLAGS = -static
libtelepathy_yell_la_LIBADD = $(ALL_LIBS)

pkginclude_HEADERS = \
    extensions.h

libtelepathy_yell_la_SOURCES = \
    extensions.c \
    extensions-cli.c

nodist_libtelepathy_yell_la_SOURCES = \
    _gen/signals-marshal.c \
    _gen/signals-marshal.h \
    _gen/signals-marshal.list \
    _gen/register-dbus-glib-marshallers-body.h \
    _gen/gtypes-body.h \
    _gen/interfaces-body.h \
    _gen/cli-call-body.h \
    _gen/svc-call.c

nodist_geninclude_HEADERS = \
    _gen/enums.h \
    _gen/gtypes.h \
    _gen/interfaces.h \
    _gen/cli-call.h \
    _gen/svc-call.h

BUILT_SOURCES = \
    _gen/all.xml \
    _gen/call.xml \
    $(nodist_geninclude_HEADERS) \
    $(nodist_libtelepathy_yell_la_SOURCES) \
    extensions.html

CLEANFILES = $(BUILT_SOURCES)

AM_CFLAGS = \
    -DG_LOG_DOMAIN=\"tp-yell\" \
    -I$(top_srcdir) -I$(top_builddir) \
    $(ERROR_CFLAGS) \
    $(TP_GLIB_CFLAGS) \
    $(DBUS_CFLAGS) \
    $(GLIB_CFLAGS)

ALL_LIBS = \
    $(DBUS_LIBS) \
    $(GLIB_LIBS) \
    $(TP_GLIB_LIBS)

distclean-local:
	rm -rf _gen

check_c_sources = \
    $(pkginclude_HEADERS) \
    $(libtelepathy_yell_la_SOURCES)
include $(top_srcdir)/tools/check-coding-style.mk

check-local: check-coding-style

### Code generation from here on down

tools_dir = $(top_srcdir)/tools

XSLTPROCFLAGS = --nonet --novalid

# Generated files which can be generated for all categories simultaneously

extensions.html: _gen/all.xml $(tools_dir)/doc-generator.xsl Makefile.am
	$(AM_V_GEN)$(XSLTPROC) $(XSLTPROCFLAGS) \
		--param 'allow-undefined-interfaces' 'true()' \
		$(tools_dir)/doc-generator.xsl \
		$< > $@

_gen/gtypes.h _gen/gtypes-body.h: _gen/all.xml \
	$(top_srcdir)/tools/glib-gtypes-generator.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(top_srcdir)/tools/glib-gtypes-generator.py \
		$< _gen/gtypes Tpy

_gen/signals-marshal.list: _gen/all.xml \
	$(tools_dir)/glib-signals-marshal-gen.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(tools_dir)/glib-signals-marshal-gen.py $< > $@

_gen/signals-marshal.h: _gen/signals-marshal.list Makefile.am
	$(AM_V_GEN)$(GLIB_GENMARSHAL) --header --prefix=_tpy_marshal $< > $@

_gen/signals-marshal.c: _gen/signals-marshal.list Makefile.am
	$(AM_V_GEN){ echo '#include "_gen/signals-marshal.h"' && \
	$(GLIB_GENMARSHAL) --body --prefix=_tpy_marshal $< ; } > $@

_gen/register-dbus-glib-marshallers-body.h: _gen/all.xml \
	$(tools_dir)/glib-client-marshaller-gen.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(tools_dir)/glib-client-marshaller-gen.py $< \
		_tpy > $@

_gen/enums.h: _gen/all.xml $(tools_dir)/c-constants-gen.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(tools_dir)/c-constants-gen.py Tpy $< _gen/enums

_gen/interfaces-body.h _gen/interfaces.h: _gen/all.xml \
	$(tools_dir)/glib-interfaces-gen.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(tools_dir)/glib-interfaces-gen.py \
		Tpy _gen/interfaces-body.h _gen/interfaces.h $<

# Generated files which must be generated per "category". Each TpProxy
# subclass you want to use with --subclass will need to have its own category,
# although you can subdivide further if you want.

_gen/%.xml: %.xml $(wildcard *.xml)
	@$(mkdir_p) _gen
	$(AM_V_GEN)$(XSLTPROC) $(XSLTPROCFLAGS) --xinclude $(tools_dir)/identity.xsl \
		$< > $@

_gen/cli-%-body.h _gen/cli-%.h: _gen/%.xml \
	$(tools_dir)/glib-client-gen.py Makefile.am
	$(AM_V_GEN)set -e; \
	case "$*" in \
	call) \
		subclass="TpProxy"; \
		assert="TP_IS_PROXY"; \
		;; \
	esac; \
	$(PYTHON) $(tools_dir)/glib-client-gen.py \
		--group=`echo $* | tr x- x_` \
		--subclass=$$subclass \
		--subclass-assert=$$assert \
		--tp-proxy-api=0.7.6 \
		--iface-quark-prefix=TPY_IFACE_QUARK \
		$< Tpy_Cli _gen/cli-$*

_gen/svc-%.c _gen/svc-%.h: _gen/%.xml \
	$(tools_dir)/glib-ginterface-gen.py Makefile.am
	$(AM_V_GEN)$(PYTHON) $(tools_dir)/glib-ginterface-gen.py \
		--filename=_gen/svc-$* \
		--signal-marshal-prefix=_tpy \
		--include='<telepathy-glib/dbus.h>' \
		--include='"_gen/signals-marshal.h"' \
		--not-implemented-func='tp_dbus_g_method_return_not_implemented' \
		--allow-unstable \
		$< Tpy_Svc_
