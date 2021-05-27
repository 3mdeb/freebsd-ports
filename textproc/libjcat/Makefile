# $FreeBSD$

PORTNAME=	libjcat
DISTVERSION=	0.1.8
CATEGORIES=	textproc

MAINTAINER=	norbert.kaminski@3mdeb.com
COMMENT=	Library for reading and writing JSON catalog files

LICENSE=	LGPL21

BUILD_DEPENDS=	gobject-introspection>=1.36:devel/gobject-introspection \
		gtkdocize:textproc/gtk-doc \
		help2man:misc/help2man \
		vala:lang/vala
LIB_DEPENDS=	libgnutls.so:security/gnutls \
		libgpg-error.so:security/libgpg-error \
		libgpgme.so:security/gpgme \
		libjson-glib-1.0.so:devel/json-glib

USES=		gnome localbase:ldflags meson pkgconfig
USE_GITHUB=	yes
GH_ACCOUNT=	hughsie
USE_GNOME=	glib20
USE_LDCONFIG=	yes

.include <bsd.port.mk>
