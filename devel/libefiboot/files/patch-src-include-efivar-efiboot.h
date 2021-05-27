--- src/include/efivar/efiboot.h
+++ src/include/efivar/efiboot.h
@@ -25,12 +25,13 @@
 #include <stdarg.h>
 #include <stdint.h>
 #include <string.h>
+#include <sys/endian.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <unistd.h>
-#include <byteswap.h>
 
 #include <efivar.h>
+#include <efivar-dp.h>
 
 #include <efiboot-creator.h>
 #include <efiboot-loadopt.h>
