# Created by: Norbert Kamiński <norbert.kaminski@3mdeb.com>
# $FreeBSD$

PORTNAME=	fwupd
DISTVERSION=	1.5.8
GH_TAGNAME=	f3c64ad
CATEGORIES=	sysutils

MAINTAINER=	norbert.kaminski@3mdeb.com
COMMENT=	Update firmware automatically, safely, and reliably

LICENSE=	LGPL21

BUILD_DEPENDS=	gtkdoc-scan:textproc/gtk-doc \
		help2man:misc/help2man \
		vala:lang/vala
LIB_DEPENDS=	libcurl.so:ftp/curl \
		libelf.so:devel/libelf \
		libgcab-1.0.so:archivers/gcab \
		libgnutls.so:security/gnutls \
		libgpg-error.so:security/libgpg-error \
		libgpgme.so:security/gpgme \
		libgusb.so:devel/libgusb \
		libjcat.so:textproc/libjcat \
		libjson-glib-1.0.so:devel/json-glib \
		libxmlb.so:textproc/libxmlb

USES=		gnome libarchive meson pkgconfig python:3.7+ shebangfix sqlite
USE_GITHUB=	yes
USE_GNOME=	glib20 introspection:build
INSTALLS_ICONS=	yes
USE_LDCONFIG=	yes

SHEBANG_GLOB=	*.py

MESON_ARGS=	-Dgudev=false \
		-Dplugin_altos=false \
		-Dplugin_amt=false \
		-Dplugin_dell=false \
		-Dplugin_emmc=false \
		-Dplugin_nvme=false \
		-Dplugin_redfish=false \
		-Dplugin_synaptics_mst=false \
		-Dplugin_synaptics_rmi=false \
		-Dplugin_thunderbolt=false \
		-Dplugin_tpm=false \
		-Dplugin_uefi_capsule=false \
		-Dpolkit=false \
		-Dsystemd=false \
		-Dtests=false

.include <bsd.port.mk>
