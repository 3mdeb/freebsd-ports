--- src/include/efivar/efivar.h
+++ src/include/efivar/efivar.h
@@ -20,15 +20,14 @@
 #ifndef EFIVAR_H
 #define EFIVAR_H 1
 
-#include <endian.h>
 #include <errno.h>
 #include <stdarg.h>
 #include <stdint.h>
 #include <string.h>
+#include <sys/endian.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
-#include <byteswap.h>
 
 typedef struct {
 	uint32_t	a;
@@ -44,7 +43,7 @@ typedef struct {
 
 #if BYTE_ORDER == LITTLE_ENDIAN
 #define EFI_GUID(a,b,c,d,e0,e1,e2,e3,e4,e5) \
-((efi_guid_t) {(a), (b), (c), bswap_16(d), { (e0), (e1), (e2), (e3), (e4), (e5) }})
+((efi_guid_t) {(a), (b), (c), bswap16(d), { (e0), (e1), (e2), (e3), (e4), (e5) }})
 #else
 #define EFI_GUID(a,b,c,d,e0,e1,e2,e3,e4,e5) \
 ((efi_guid_t) {(a), (b), (c), (d), { (e0), (e1), (e2), (e3), (e4), (e5) }})
