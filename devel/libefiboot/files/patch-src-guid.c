--- src/guid.c
+++ src/guid.c
@@ -21,6 +21,7 @@
 #include <dlfcn.h>
 #include <errno.h>
 #include <stdio.h>
+#include <sys/endian.h>
 
 #include "efivar.h"
 #include "guid.h"
