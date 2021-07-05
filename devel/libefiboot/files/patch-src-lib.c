--- src/lib.c.orig	2016-06-30 14:50:32 UTC
+++ src/lib.c
@@ -69,7 +69,8 @@ efi_set_variable(efi_guid_t guid, const char *name, ui
 {
 	return ops->set_variable(guid, name, data, data_size, attributes, mode);
 }
-__asm__(".symver efi_set_variable,efi_set_variable@@LIBEFIVAR_0.24");
+//XXX
+//__asm__(".symver efi_set_variable,efi_set_variable@@LIBEFIVAR_0.24");
 
 int
 __attribute__((__nonnull__ (2, 3)))
