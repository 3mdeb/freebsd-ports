--- src/disk.c.orig	2016-06-30 14:50:32 UTC
+++ src/disk.c
@@ -18,7 +18,6 @@
  * <http://www.gnu.org/licenses/>.
  *
  */
-#include <asm/byteorder.h>
 #include <errno.h>
 #include <fcntl.h>
 #include <inttypes.h>
@@ -156,7 +155,8 @@ msdos_disk_get_partition_info (int fd, int write_signa
         } else if (num == 0) {
 		/* Whole disk */
                 *start = 0;
-		ioctl(fd, BLKGETSIZE, &disk_size);
+		//XXX
+		//ioctl(fd, BLKGETSIZE, &disk_size);
                 *size = disk_size;
 	} else if (num >= 1 && num <= 4) {
 		/* Primary partition */
