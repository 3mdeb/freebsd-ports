--- src/efivarfs.c
+++ src/efivarfs.c
@@ -20,23 +20,20 @@
 
 #include <errno.h>
 #include <fcntl.h>
-#include <linux/magic.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <sys/endian.h>
 #include <sys/mman.h>
 #include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/uio.h>
-#include <sys/vfs.h>
 #include <unistd.h>
 
 #include "lib.h"
 #include "generics.h"
 #include "util.h"
 
-#include <linux/fs.h>
-
 #ifndef EFIVARFS_MAGIC
 #  define EFIVARFS_MAGIC 0xde5e81e4
 #endif
@@ -85,7 +82,7 @@ efivarfs_probe(void)
 #define make_efivarfs_path(str, guid, name) ({				\
 		asprintf(str, "%s%s-" GUID_FORMAT, get_efivarfs_path(),	\
 			name, (guid).a, (guid).b, (guid).c,		\
-			bswap_16((guid).d),				\
+			bswap16((guid).d),				\
 			(guid).e[0], (guid).e[1], (guid).e[2],		\
 			(guid).e[3], (guid).e[4], (guid).e[5]);		\
 	})
@@ -93,6 +90,7 @@ efivarfs_probe(void)
 static int
 efivarfs_set_fd_immutable(int fd, int immutable)
 {
+#if 0
 	unsigned int flags;
 	int rc = 0;
 
@@ -111,6 +109,11 @@ efivarfs_set_fd_immutable(int fd, int immutable)
 	}
 
 	return rc;
+#else
+	(void)fd;
+	(void)immutable;
+	return -1;
+#endif
 }
 
 static int
