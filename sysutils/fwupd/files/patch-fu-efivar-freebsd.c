--- libfwupdplugin/fu-efivar-freebsd.c.orig	2022-01-27 22:48:19.741597000 +0100
+++ libfwupdplugin/fu-efivar-freebsd.c	2022-01-27 22:48:33.389659000 +0100
@@ -172,7 +172,7 @@
 {
 	efi_guid_t guidt;
 	efi_str_to_guid(guid, &guidt);
-
+/*
 	if (efi_set_variable(guidt, name, (guint8 *)data, sz, attr) != 0) {
 		g_set_error(error,
 			    G_IO_ERROR,
@@ -181,7 +181,7 @@
 			    name);
 		return FALSE;
 	}
-
+*/
 	/* success */
 	return TRUE;
 }
