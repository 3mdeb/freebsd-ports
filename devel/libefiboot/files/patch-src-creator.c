--- src/creator.c.orig	2016-06-30 14:50:32 UTC
+++ src/creator.c
@@ -21,12 +21,11 @@
 #include <fcntl.h>
 #include <inttypes.h>
 #include <limits.h>
-#include <mntent.h>
+#include <sys/types.h>
 #include <netinet/in.h>
 #include <netinet/ip.h>
 #include <stdlib.h>
 #include <stdio.h>
-#include <sys/types.h>
 #include <sys/stat.h>
 #include <sys/socket.h>
 
@@ -39,6 +38,197 @@
 #include "list.h"
 #include "util.h"
 
+/*
+ *  mntent
+ *  mntent.h - compatibility header for FreeBSD
+ *
+ *  Copyright (c) 2001 David Rufino <daverufino@btinternet.com>
+ *  All rights reserved.
+ *
+ * Redistribution and use in source and binary forms, with or without
+ * modification, are permitted provided that the following conditions
+ * are met:
+ * 1. Redistributions of source code must retain the above copyright
+ *    notice, this list of conditions and the following disclaimer.
+ * 2. Redistributions in binary form must reproduce the above copyright
+ *    notice, this list of conditions and the following disclaimer in the
+ *    documentation and/or other materials provided with the distribution.
+ *
+ * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
+ * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
+ * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
+ * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
+ * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
+ * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
+ * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
+ * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
+ * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
+ * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
+ * SUCH DAMAGE.
+ */
+
+#ifndef VIFM__UTILS__MNTENT_H__
+#define VIFM__UTILS__MNTENT_H__
+
+#include <stddef.h>
+#include <stdio.h>
+
+#define MOUNTED "dummy"
+
+#define MNTTYPE_NFS "nfs"
+
+struct mntent
+{
+	char *mnt_fsname;
+	char *mnt_dir;
+	char *mnt_type;
+	char *mnt_opts;
+	int mnt_freq;
+	int mnt_passno;
+};
+
+#define setmntent(x,y) ((FILE *)0x1)
+struct mntent * getmntent(FILE *fp);
+char * hasmntopt(const struct mntent *mnt, const char option[]);
+#define endmntent(x) ((int)1)
+
+#endif /* VIFM__UTILS__MNTENT_H__ */
+
+#include <sys/param.h>
+#include <sys/ucred.h>
+#include <sys/mount.h>
+
+#include <stdlib.h>
+#include <string.h>
+
+#ifdef __NetBSD__
+#define statfs statvfs
+#define f_flags f_flag
+#endif
+
+static struct mntent * statfs_to_mntent(struct statfs *mntbuf);
+static char * flags2opts(int flags);
+static char * catopt(char s0[], const char s1[]);
+
+char *
+hasmntopt(const struct mntent *mnt, const char option[])
+{
+	char *opt, *optbuf;
+
+	optbuf = strdup(mnt->mnt_opts);
+	for(opt = optbuf; (opt = strtok(opt, " ")) != NULL; opt = NULL)
+	{
+		if(!strcasecmp(opt, option))
+		{
+			opt = opt - optbuf + mnt->mnt_opts;
+			free(optbuf);
+			return (opt);
+		}
+	}
+	free(optbuf);
+	return NULL;
+}
+
+struct mntent *
+getmntent(FILE *fp)
+{
+	static int pos = -1;
+	static int mntsize = -1;
+
+	static struct statfs *mntbuf;
+
+	(void)fp;
+
+	if(pos == -1 || mntsize == -1)
+	{
+		mntsize = getmntinfo(&mntbuf, MNT_NOWAIT);
+	}
+
+	pos++;
+	if(pos == mntsize)
+	{
+		pos = mntsize = -1;
+		return NULL;
+	}
+
+	return statfs_to_mntent(&mntbuf[pos]);
+}
+
+static struct mntent *
+statfs_to_mntent(struct statfs *mntbuf)
+{
+	static struct mntent _mntent;
+	static char opts_buf[40], *tmp;
+
+	_mntent.mnt_fsname = mntbuf->f_mntfromname;
+	_mntent.mnt_dir = mntbuf->f_mntonname;
+	_mntent.mnt_type = mntbuf->f_fstypename;
+	tmp = flags2opts (mntbuf->f_flags);
+	if(tmp != NULL)
+	{
+		opts_buf[sizeof(opts_buf) - 1] = '\0';
+		strncpy(opts_buf, tmp, sizeof(opts_buf) - 1);
+		free(tmp);
+	}
+	else
+	{
+		*opts_buf = '\0';
+	}
+	_mntent.mnt_opts = opts_buf;
+	_mntent.mnt_freq = _mntent.mnt_passno = 0;
+	return &_mntent;
+}
+
+static char *
+flags2opts(int flags)
+{
+	char *res = catopt(NULL, (flags & MNT_RDONLY) ? "ro" : "rw");
+	if(flags & MNT_SYNCHRONOUS) res = catopt(res, "sync");
+	if(flags & MNT_NOEXEC)      res = catopt(res, "noexec");
+	if(flags & MNT_NOSUID)      res = catopt(res, "nosuid");
+#ifndef __OpenBSD__
+	if(flags & MNT_UNION)       res = catopt(res, "union");
+#endif
+	if(flags & MNT_ASYNC)       res = catopt(res, "async");
+	if(flags & MNT_NOATIME)     res = catopt(res, "noatime");
+#if !defined(__APPLE__) && !defined(__OpenBSD__) && !defined(__NetBSD__)
+	if(flags & MNT_NOCLUSTERR)  res = catopt(res, "noclusterr");
+	if(flags & MNT_NOCLUSTERW)  res = catopt(res, "noclusterw");
+	if(flags & MNT_NOSYMFOLLOW) res = catopt(res, "nosymfollow");
+	if(flags & MNT_SUIDDIR)     res = catopt(res, "suiddir");
+#endif
+
+	return res;
+}
+
+static char *
+catopt(char s0[], const char s1[])
+{
+	char *cp;
+
+	if(s1 == NULL || *s1 == '\0')
+	{
+		return s0;
+	}
+	if(s0 && *s0)
+	{
+		const size_t i = strlen(s0) + strlen(s1) + 1 + 1;
+		if((cp = malloc(i)) == NULL)
+		{
+			return NULL;
+		}
+		(void)snprintf(cp, i, "%s %s", s0, s1);
+	}
+	else
+	{
+		cp = strdup(s1);
+	}
+
+	free(s0);
+	return cp;
+}
+
+
 static int
 __attribute__((__nonnull__ (1,2,3)))
 find_file(const char * const filepath, char **devicep, char **relpathp)
@@ -77,21 +267,15 @@ find_file(const char * const filepath, char **devicep,
 		}
 	} while (1);
 
-	mounts = fopen("/proc/self/mounts", "r");
+	mounts = fopen("/compat/linux/proc/self/mounts", "r");
 	if (mounts == NULL)
-		return rc;
+		return -1;
 
 	struct mntent *me;
-	while (1) {
+	while ((me = getmntent(mounts))) {
 		struct stat dsb = { 0, };
 
 		errno = 0;
-		me = getmntent(mounts);
-		if (!me) {
-			if (feof(mounts))
-				errno = ENOENT;
-			goto err;
-		}
 
 		if (me->mnt_fsname[0] != '/')
 			continue;
@@ -100,12 +284,8 @@ find_file(const char * const filepath, char **devicep,
 		if (rc < 0) {
 			if (errno == ENOENT)
 				continue;
-			goto err;
 		}
 
-		if (!S_ISBLK(dsb.st_mode))
-			continue;
-
 		if (dsb.st_rdev == fsb.st_dev) {
 			ssize_t mntlen = strlen(me->mnt_dir);
 			if (mntlen >= linklen) {
@@ -124,12 +304,10 @@ find_file(const char * const filepath, char **devicep,
 				goto err;
 			}
 			ret = 0;
-			break;
 		}
 	}
 err:
-	if (mounts)
-		endmntent(mounts);
+	(void)fclose(mounts);
 	return ret;
 }
 
@@ -211,12 +389,22 @@ efi_va_generate_file_device_path_from_esp(uint8_t *buf
 	if (!(options & EFIBOOT_ABBREV_FILE)) {
 		int disk_fd;
 		int saved_errno;
-		int rc;
 
-		rc = set_disk_and_part_name(&info);
-		if (rc < 0)
-			goto err;
+		char *node = strrchr(devpath, '/');
+		if (!node) {
+			errno = EINVAL;
+			return -1;
+		}
+		node++;
+		info.disk_name = strdup(node);
 
+		info.part_name = malloc(PATH_MAX+1);
+		if (!strncmp (info.disk_name, "nv", 2)) {
+			sprintf(info.part_name, "%sp%d", info.disk_name, info.part);
+		} else {
+			sprintf(info.part_name, "%s%d", info.disk_name, info.part);
+		}
+				
 		disk_fd = open_disk(&info,
 		    (options& EFIBOOT_OPTIONS_WRITE_SIGNATURE)?O_RDWR:O_RDONLY);
 		if (disk_fd < 0)
@@ -323,7 +511,7 @@ err:
 	if (child_devpath)
 		free(child_devpath);
 	if (parent_devpath)
-			free(parent_devpath);
+		free(parent_devpath);
 	if (relpath)
 		free(relpath);
 	errno = saved_errno;
