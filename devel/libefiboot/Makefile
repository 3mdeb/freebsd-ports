# Created by: Edward Tomasz Napierala <trasz@FreeBSD.org>

PORTNAME=	libefiboot
PORTVERSION=	0.24
PORTREVISION=	1
CATEGORIES=	devel

MAINTAINER=	ports@FreeBSD.org
COMMENT=	Tools and library to manipulate EFI variables

LICENSE=	LGPL21

NOT_FOR_ARCHS=		powerpc powerpc64 powerpspe sparc64
NOT_FOR_ARCHS_REASON=	specification only supports little-endian processors

LIB_DEPENDS=	libpopt.so:devel/popt

USES=		gmake localbase pkgconfig
USE_GCC=	yes
USE_GITHUB=	yes
GH_ACCOUNT=	rhboot
GH_PROJECT=     efivar
USE_LDCONFIG=	yes

.include <bsd.port.pre.mk>

post-patch:
	@${REINPLACE_CMD} -e 's|%%PREFIX%%|${PREFIX}|g' ${WRKSRC}/src/efiboot.pc.in

do-install:
	${INSTALL_LIB} ${WRKSRC}/src/libefiboot.so ${STAGEDIR}${PREFIX}/lib/libefiboot.so.0.24
	${LN} -fs libefiboot.so.0.24 ${STAGEDIR}${PREFIX}/lib/libefiboot.so.0
	${LN} -fs libefiboot.so.0.24 ${STAGEDIR}${PREFIX}/lib/libefiboot.so
	${MKDIR} ${STAGEDIR}${PREFIX}/include/efivar/
	${INSTALL_DATA} ${WRKSRC}/src/include/efivar/efiboot.h ${STAGEDIR}${PREFIX}/include/efivar/
	${INSTALL_DATA} ${WRKSRC}/src/include/efivar/efiboot-creator.h ${STAGEDIR}${PREFIX}/include/efivar/
	${INSTALL_DATA} ${WRKSRC}/src/include/efivar/efiboot-loadopt.h ${STAGEDIR}${PREFIX}/include/efivar/
	${INSTALL_DATA} ${WRKSRC}/src/efiboot.pc ${STAGEDIR}${PREFIX}/libdata/pkgconfig

.include <bsd.port.post.mk>
