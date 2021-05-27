# $FreeBSD$

PORTNAME=	libxmlb
DISTVERSION=	0.3.2
CATEGORIES=	textproc

MAINTAINER=	norbert.kaminski@3mdeb.com
COMMENT=	Help create and query binary XML blobs

LICENSE=	LGPL21

BUILD_DEPENDS=	gobject-introspection>=1.36:devel/gobject-introspection \
		gtkdocize:textproc/gtk-doc

USES=		gnome meson pkgconfig python:3.7+
USE_GITHUB=	yes
GH_ACCOUNT=	hughsie
USE_GNOME=	glib20
USE_LDCONFIG=	yes

OPTIONS_DEFINE=	DOCS

DOCS_MESON_TRUE=	docs

.include <bsd.port.mk>
