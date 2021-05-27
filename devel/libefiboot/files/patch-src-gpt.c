--- src/gpt.c
+++ src/gpt.c
@@ -22,7 +22,6 @@
  *
  */
 
-#include <asm/byteorder.h>
 #include <errno.h>
 #include <fcntl.h>
 #include <inttypes.h>
@@ -44,6 +43,17 @@
 #define BLKGETLASTSECT _IO(0x12,108) /* get last sector of block device */
 #endif
 
+#if BYTE_ORDER == BIG_ENDIAN
+#define __le64_to_cpu(n) bswap64(n)
+#define __le32_to_cpu(n) bswap32(n)
+#define __le16_to_cpu(n) bswap16(n)
+#else
+#define __le64_to_cpu(n) (n)
+#define __le32_to_cpu(n) (n)
+#define __le16_to_cpu(n) (n)
+#endif
+#define __cpu_to_le32(n) __le32_to_cpu(n)
+
 struct blkdev_ioctl_param {
 	unsigned int block;
 	size_t content_length;
@@ -151,12 +161,12 @@ _get_num_sectors(int filedes)
 	uint64_t bytes=0;
 	int rc;
 	if (kernel_has_blkgetsize64()) {
-		rc = ioctl(filedes, BLKGETSIZE64, &bytes);
+		rc = 1;//ioctl(filedes, BLKGETSIZE64, &bytes); XXX
 		if (!rc)
 			return bytes / get_sector_size(filedes);
 	}
 
-	rc = ioctl(filedes, BLKGETSIZE, &sectors);
+	rc = 1;//ioctl(filedes, BLKGETSIZE, &sectors); XXX
 	if (rc)
 		return 0;
 
