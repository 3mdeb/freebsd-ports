--- src/fu-engine.c.origin	2021-04-02 16:43:34.455611414 +0200
+++ src/fu-engine.c
@@ -6232,7 +6232,7 @@
 	guint backend_cnt = 0;
 	g_autoptr(GPtrArray) checksums_approved = NULL;
 	g_autoptr(GPtrArray) checksums_blocked = NULL;
-#ifdef __linux__
+#ifndef _WIN32
 	g_autoptr(GError) error_local = NULL;
 #endif
 
