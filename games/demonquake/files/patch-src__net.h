--- ./src/net.h.orig	Sun May 30 22:34:26 2004
+++ ./src/net.h	Tue May 16 14:33:39 2006
@@ -253,7 +253,7 @@
 extern int hostCacheCount;
 extern hostcache_t hostcache[HOSTCACHESIZE];
 
-#if !defined(_WIN32 ) && !defined (__linux__)
+#if !defined(_WIN32 ) && !defined (__unix__)
 #ifndef htonl
 extern unsigned long htonl (unsigned long hostlong);
 #endif
