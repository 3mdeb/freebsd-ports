--- src/util.h
+++ src/util.h
@@ -125,14 +125,34 @@ static inline int
 __attribute__((unused))
 get_sector_size(int filedes)
 {
+#if 0
 	int rc, sector_size = 512;
 
 	rc = ioctl(filedes, BLKSSZGET, &sector_size);
 	if (rc)
 		sector_size = 512;
 	return sector_size;
+#else
+	// XXX
+	(void)filedes;
+	return 512;
+#endif
 }
 
+#define strdupa(str)							\
+	({								\
+		char *_tmp = NULL;					\
+		asprintf(&_tmp, "%s", (str));				\
+	 	_tmp;							\
+	})
+
+#define strndupa(str, len)						\
+	({								\
+		char *_tmp = NULL;					\
+		asprintf(&_tmp, "%.*s", (int)(len), (str));		\
+	 	_tmp;							\
+	})
+
 #define asprintfa(str, fmt, args...)					\
 	({								\
 		char *_tmp = NULL;					\
