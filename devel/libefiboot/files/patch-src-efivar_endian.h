--- src/efivar_endian.h
+++ src/efivar_endian.h
@@ -20,7 +20,7 @@
 #ifndef _EFIVAR_ENDIAN_H
 #define _EFIVAR_ENDIAN_H
 
-#include <endian.h>
+#include <sys/endian.h>
 
 #if __BYTE_ORDER == __LITTLE_ENDIAN
 #define cpu_to_le16(x) (x)
@@ -29,12 +29,12 @@
 #define le16_to_cpu(x) (x)
 #define le32_to_cpu(x) (x)
 #define le64_to_cpu(x) (x)
-#define cpu_to_be16(x) __bswap_16(x)
-#define cpu_to_be32(x) __bswap_32(x)
-#define cpu_to_be64(x) __bswap_64(x)
-#define be16_to_cpu(x) __bswap_16(x)
-#define be32_to_cpu(x) __bswap_32(x)
-#define be64_to_cpu(x) __bswap_64(x)
+#define cpu_to_be16(x) bswap16(x)
+#define cpu_to_be32(x) bswap32(x)
+#define cpu_to_be64(x) bswap64(x)
+#define be16_to_cpu(x) bswap16(x)
+#define be32_to_cpu(x) bswap32(x)
+#define be64_to_cpu(x) bswap64(x)
 #else
 #define cpu_to_be16(x) (x)
 #define cpu_to_be32(x) (x)
@@ -42,12 +42,12 @@
 #define be16_to_cpu(x) (x)
 #define be32_to_cpu(x) (x)
 #define be64_to_cpu(x) (x)
-#define cpu_to_le16(x) __bswap_16(x)
-#define cpu_to_le32(x) __bswap_32(x)
-#define cpu_to_le64(x) __bswap_64(x)
-#define le16_to_cpu(x) __bswap_16(x)
-#define le32_to_cpu(x) __bswap_32(x)
-#define le64_to_cpu(x) __bswap_64(x)
+#define cpu_to_le16(x) bswap16(x)
+#define cpu_to_le32(x) bswap32(x)
+#define cpu_to_le64(x) bswap64(x)
+#define le16_to_cpu(x) bswap16(x)
+#define le32_to_cpu(x) bswap32(x)
+#define le64_to_cpu(x) bswap64(x)
 #endif
 
 #endif /* _EFIVAR_ENDIAN_H */
