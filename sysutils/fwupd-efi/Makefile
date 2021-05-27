# Created by: Norbert Kamiński <norbert.kaminski@3mdeb.com>
# $FreeBSD$

PORTNAME=	fwupd-efi
DISTVERSION=	1.0
GH_TAGNAME=	d74ab0fe
CATEGORIES=	sysutils

MAINTAINER=	norbert.kaminski@3mdeb.com
COMMENT=	EFI Application used by uefi-capsule plugin in fwupd

LICENSE=	LGPL21

BUILD_DEPENDS=	${LOCALBASE}/lib/libgnuefi.a:devel/gnu-efi \
		gcc:lang/gcc

USES=		meson pkgconfig python:3.7+ shebangfix
USE_GITHUB=	yes
GH_ACCOUNT=	fwupd
USE_LDCONFIG=	yes

USE_GCC=	yes
SHEBANG_GLOB=	*.py

MESON_ARGS=	-Defi-includedir=/usr/local/include/efi \
		-Defi-ldsdir=/usr/local/lib

.include <bsd.port.mk>
