PORTNAME=	gnu-efi
PORTVERSION=	3.0.18
CATEGORIES=	devel
MASTER_SITES=	SF/gnu-efi

MAINTAINER=	egypcio@FreeBSD.org
COMMENT=	SDK for EFI applications
WWW=		https://gnu-efi.sourceforge.net/

LICENSE=	BSD3CLAUSE

ONLY_FOR_ARCHS=	amd64 i386

BUILD_DEPENDS=	${LOCALBASE}/bin/ar:devel/binutils

USES=		compiler:c++11-lib gmake tar:bz2

CPPFLAGS+=	-Wno-incompatible-pointer-types
MAKE_ARGS+=	CC=${CC} HOSTCC=${CC} AR=${AR}

.include <bsd.port.pre.mk>

.if ${ARCH} == amd64
PLIST_SUB+=	ARCH_amd64="" ARCH_i386="@comment "
.elif ${ARCH} == i386
PLIST_SUB+=	ARCH_i386="" ARCH_amd64="@comment "
.endif

# This port installs object files as lib/*.o.  Previously it stripped those
# objects, but it MUST NOT be done.  Stripping removes all symbols from CRTs
# and breaks applications linked against gnu-efi (everything builds, but
# resulting file is not a valid PE executable due to the way objcopy
# operates).

.include <bsd.port.post.mk>
