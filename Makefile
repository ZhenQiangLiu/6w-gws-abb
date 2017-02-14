# 6Harmonics Inc.
# by Qige: qige@6harmonics.com, qige.zhao@6wilink.com
# 2017.02.14 v1.0-1 Apply 6Harmonics Linux C Coding Rules 2017

include $(TOPDIR)/rules.mk

APP_NAME:=gws-abb
PKG_NAME:=gws-abb
PKG_VERSION:=1.0
PKG_RELEASE:=1

include $(INCLUDE_DIR)/package.mk

define Package/$(PKG_NAME)
  SECTION:=utils
  CATEGORY:=Utilities
  TITLE:=Analog Baseband
  MAINTAINER:=Qige Zhao <qige@6harmonics.com>
  DEPENDS:=+libiwinfo
endef

define Package/$(PKG_NAME)/description
  Analog Baseband data collector;
  Depends on libiwinfo, share data via shm/files.
endef


define Build/Prepare
	mkdir -p $(PKG_BUILD_DIR)
	$(CP) ./src/* $(PKG_BUILD_DIR)
endef

define Build/Configure
endef

define Package/$(PKG_NAME)/install
	$(INSTALL_DIR) $(1)/etc/config
	$(INSTALL_DIR) $(1)/etc/init.d
	$(INSTALL_DIR) $(1)/usr/sbin

	$(INSTALL_CONF) $(PKG_BUILD_DIR)/$(APP_NAME).conf $(1)/etc/config/$(APP_NAME)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(APP_NAME).init $(1)/etc/init.d/$(APP_NAME)
	$(INSTALL_BIN) $(PKG_BUILD_DIR)/$(APP_NAME) $(1)/usr/sbin/
endef

$(eval $(call BuildPackage,$(PKG_NAME)))


