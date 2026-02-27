--- libfwupdplugin/fu-uefi-device.c.orig	2025-12-19 09:50:21 UTC
+++ libfwupdplugin/fu-uefi-device.c
@@ -248,7 +248,7 @@ fu_uefi_device_probe(FuDevice *device, GError **error)
 {
 	return fu_device_build_instance_id_full(device,
 						FU_DEVICE_INSTANCE_FLAG_QUIRKS,
-						NULL,
+						error,
 						"UEFI",
 						"GUID",
 						"NAME",
