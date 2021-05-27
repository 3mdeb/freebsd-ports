--- src/vars.c
+++ src/vars.c
@@ -24,6 +24,7 @@
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
+#include <sys/endian.h>
 #include <sys/stat.h>
 #include <sys/types.h>
 #include <sys/utsname.h>
@@ -239,7 +240,7 @@ vars_get_variable_size(efi_guid_t guid, const char *name, size_t *size)
 
 	char *path = NULL;
 	int rc = asprintf(&path, "%s%s-"GUID_FORMAT"/size", get_vars_path(),
-			  name, guid.a, guid.b, guid.c, bswap_16(guid.d),
+			  name, guid.a, guid.b, guid.c, bswap16(guid.d),
 			  guid.e[0], guid.e[1], guid.e[2], guid.e[3],
 			  guid.e[4], guid.e[5]);
 	if (rc < 0)
@@ -292,7 +293,7 @@ vars_get_variable(efi_guid_t guid, const char *name, uint8_t **data,
 	char *path;
 	int rc = asprintf(&path, "%s%s-" GUID_FORMAT "/raw_var",
 			  get_vars_path(),
-			  name, guid.a, guid.b, guid.c, bswap_16(guid.d),
+			  name, guid.a, guid.b, guid.c, bswap16(guid.d),
 			  guid.e[0], guid.e[1], guid.e[2],
 			  guid.e[3], guid.e[4], guid.e[5]);
 	if (rc < 0)
@@ -365,7 +366,7 @@ vars_del_variable(efi_guid_t guid, const char *name)
 	char *path;
 	int rc = asprintf(&path, "%s%s-" GUID_FORMAT "/raw_var",
 			  get_vars_path(),
-			  name, guid.a, guid.b, guid.c, bswap_16(guid.d),
+			  name, guid.a, guid.b, guid.c, bswap16(guid.d),
 			  guid.e[0], guid.e[1], guid.e[2],
 			  guid.e[3], guid.e[4], guid.e[5]);
 	if (rc < 0)
@@ -463,7 +464,7 @@ vars_chmod_variable(efi_guid_t guid, const char *name, mode_t mode)
 
 	char *path;
 	int rc = asprintf(&path, "%s%s-" GUID_FORMAT, get_vars_path(),
-			  name, guid.a, guid.b, guid.c, bswap_16(guid.d),
+			  name, guid.a, guid.b, guid.c, bswap16(guid.d),
 			  guid.e[0], guid.e[1], guid.e[2], guid.e[3],
 			  guid.e[4], guid.e[5]);
 	if (rc < 0)
@@ -495,7 +496,7 @@ vars_set_variable(efi_guid_t guid, const char *name, uint8_t *data,
 
 	char *path;
 	int rc = asprintf(&path, "%s%s-" GUID_FORMAT "/data", get_vars_path(),
-			  name, guid.a, guid.b, guid.c, bswap_16(guid.d),
+			  name, guid.a, guid.b, guid.c, bswap16(guid.d),
 			  guid.e[0], guid.e[1], guid.e[2], guid.e[3],
 			  guid.e[4], guid.e[5]);
 	if (rc < 0)

