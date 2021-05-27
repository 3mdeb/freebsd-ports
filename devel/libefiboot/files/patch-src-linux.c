--- src/linux.c
+++ src/linux.c
@@ -23,11 +23,7 @@
 #include <fcntl.h>
 #include <inttypes.h>
 #include <limits.h>
-#include <linux/ethtool.h>
-#include <linux/version.h>
-#include <linux/sockios.h>
 #include <net/if.h>
-#include <scsi/scsi.h>
 #include <stdio.h>
 #include <sys/ioctl.h>
 #include <sys/socket.h>
@@ -1000,6 +996,13 @@ ssize_t
 __attribute__((__visibility__ ("hidden")))
 make_mac_path(uint8_t *buf, ssize_t size, const char * const ifname)
 {
+	(void)buf;
+	(void)size;
+	(void)ifname;
+	(void)make_net_pci_path;
+	return -1;
+	// XXX
+#if 0
 	struct ifreq ifr;
 	struct ethtool_drvinfo drvinfo = { 0, };
 	int fd, rc;
@@ -1042,4 +1045,5 @@ err:
 	if (fd >= 0)
 		close(fd);
 	return ret;
+#endif
 }
