--- plugins/uefi-capsule/fu-uefi-common.c.orig	2025-12-19 09:50:21 UTC
+++ plugins/uefi-capsule/fu-uefi-common.c
@@ -35,6 +35,12 @@ fu_uefi_bootmgr_get_suffix(GError **error)
 	    {0, NULL}};
 	g_autofree gchar *sysfsefidir = fu_path_build(FU_PATH_KIND_SYSFSDIR_FW, "efi", NULL);
 	firmware_bits = fu_uefi_read_file_as_uint64(sysfsefidir, "fw_platform_size");
+#if defined(__FreeBSD__)
+	/* no means to determine this on FreeBSD? assume it matches the application when unambiguous */
+	if (firmware_bits == 0 && sizeof(suffixes)/sizeof(suffixes[0]) == 2) {
+		return suffixes[0].arch;
+	}
+#endif
 	if (firmware_bits == 0) {
 		g_set_error(error,
 			    FWUPD_ERROR,
