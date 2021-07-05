--- src/linux.c.orig	2016-06-30 14:50:32 UTC
+++ src/linux.c
@@ -23,12 +23,9 @@
 #include <fcntl.h>
 #include <inttypes.h>
 #include <limits.h>
-#include <linux/ethtool.h>
-#include <linux/version.h>
-#include <linux/sockios.h>
 #include <net/if.h>
-#include <scsi/scsi.h>
 #include <stdio.h>
+#include <ctype.h>
 #include <sys/ioctl.h>
 #include <sys/socket.h>
 #include <sys/types.h>
@@ -124,34 +121,29 @@ int
 __attribute__((__visibility__ ("hidden")))
 get_partition_number(const char *devpath)
 {
-	struct stat statbuf = { 0, };
 	int rc;
-	unsigned int maj, min;
-	char *linkbuf;
-	uint8_t *partbuf;
+	char *partnum;
+	char *separator;
 	int ret = -1;
 
-	rc = stat(devpath, &statbuf);
-	if (rc < 0)
+	partnum = strrchr(devpath, '/');
+	if (!partnum)
 		return -1;
+	partnum++;
 
-	if (!S_ISBLK(statbuf.st_mode)) {
-		errno = EINVAL;
-		return -1;
-	}
+        while (*partnum++ != '\0')
+                if (isdigit(*partnum))
+			break;
 
-	maj = major(statbuf.st_rdev);
-	min = minor(statbuf.st_rdev);
-
-	rc = sysfs_readlink(&linkbuf, "/sys/dev/block/%u:%u", maj, min);
-	if (rc < 0)
+ 	if (*partnum == '\0')
 		return -1;
-
-	rc = read_sysfs_file(&partbuf, "/sys/dev/block/%s/partition", linkbuf);
-	if (rc < 0)
-		return -1;
-
-	rc = sscanf((char *)partbuf, "%d\n", &ret);
+	
+	/* nvme devices have a number before partnum */
+	separator = strrchr(partnum, 'p');
+	if (separator)
+		partnum = separator + 1;
+	
+	rc = sscanf(partnum, "%d\n", &ret);
 	if (rc != 1)
 		return -1;
 	return ret;
@@ -163,37 +155,41 @@ find_parent_devpath(const char * const child, char **p
 {
 	int ret;
 	char *node;
-	char *linkbuf;
+	char *last;
+	char save;
 
 	/* strip leading /dev/ */
 	node = strrchr(child, '/');
 	if (!node)
 		return -1;
 	node++;
-
-	/* look up full path symlink */
-	ret = sysfs_readlink(&linkbuf, "/sys/class/block/%s", node);
-	if (ret < 0)
-		return ret;
-
-	/* strip child */
-	node = strrchr(linkbuf, '/');
-	if (!node)
+	
+	/* strip partition number */
+	last = node;
+	while (*last++ != '\0') 
+		if (isdigit(*last))
+			break;
+	
+	if (*last == '\0') 
 		return -1;
-	*node = '\0';
+	
+	/* nvme devices have a number before partnum */
+	/* are there any other such devices ? */
+	if (strstr(node, "nv"))
+		last++;
+	
+	/* back up original child */
+	save = *last;
 
-	/* read parent */
-	node = strrchr(linkbuf, '/');
-	if (!node)
-		return -1;
-	*node = '\0';
-	node++;
-
 	/* write out new path */
+	*last = '\0';
 	ret = asprintf(parent, "/dev/%s", node);
+
+	/* restore original child */
+	*last = save;
+
 	if (ret < 0)
 		return ret;
-
 	return 0;
 }
 
@@ -886,16 +882,8 @@ eb_disk_info_from_fd(int fd, struct disk_info *info)
 		perror("stat");
 		return 1;
 	}
-	if (S_ISBLK(buf.st_mode)) {
-		info->major = buf.st_rdev >> 8;
-		info->minor = buf.st_rdev & 0xFF;
-	} else if (S_ISREG(buf.st_mode)) {
-		info->major = buf.st_dev >> 8;
-		info->minor = buf.st_dev & 0xFF;
-	} else {
-		printf("Cannot stat non-block or non-regular file\n");
-		return 1;
-	}
+	info->major = buf.st_rdev >> 8;
+	info->minor = buf.st_rdev & 0xFF;
 
 	/* IDE disks can have up to 64 partitions, or 6 bits worth,
 	 * and have one bit for the disk number.
@@ -962,7 +950,8 @@ eb_disk_info_from_fd(int fd, struct disk_info *info)
 	}
 
 	errno = ENOSYS;
-	return -1;
+	// Major is 0 on BSD, but we still make use of the rest of the info
+	return 0;
 }
 
 static ssize_t
@@ -1000,6 +989,13 @@ ssize_t
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
@@ -1042,4 +1038,5 @@ err:
 	if (fd >= 0)
 		close(fd);
 	return ret;
+#endif
 }
