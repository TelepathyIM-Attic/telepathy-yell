LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

TELEPATHY_YELL_BUILT_SOURCES := \
	telepathy-yell/Android.mk

telepathy-yell-configure-real:
	cd $(TELEPATHY_YELL_TOP) ; \
	CC="$(CONFIGURE_CC)" \
	CFLAGS="$(CONFIGURE_CFLAGS)" \
	LD=$(TARGET_LD) \
	LDFLAGS="$(CONFIGURE_LDFLAGS)" \
	CPP=$(CONFIGURE_CPP) \
	CPPFLAGS="$(CONFIGURE_CPPFLAGS)" \
	PKG_CONFIG_LIBDIR=$(CONFIGURE_PKG_CONFIG_LIBDIR) \
	PKG_CONFIG_TOP_BUILD_DIR=$(PKG_CONFIG_TOP_BUILD_DIR) \
	$(TELEPATHY_YELL_TOP)/$(CONFIGURE) --host=arm-linux-androideabi \
		--disable-Werror && \
	for file in $(TELEPATHY_YELL_BUILT_SOURCES); do \
		rm -f $$file && \
		make -C $$(dirname $$file) $$(basename $$file) ; \
	done

telepathy-yell-configure: telepathy-yell-configure-real

.PHONY: telepathy-yell-configure

CONFIGURE_TARGETS += telepathy-yell-configure

-include $(TELEPATHY_YELL_TOP)/telepathy-yell/Android.mk
