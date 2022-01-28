--- src/guid.c.orig	2016-06-30 14:50:32 UTC
+++ src/guid.c
@@ -21,6 +21,7 @@
 #include <dlfcn.h>
 #include <errno.h>
 #include <stdio.h>
+#include <sys/endian.h>
 
 #include "efivar.h"
 #include "guid.h"
