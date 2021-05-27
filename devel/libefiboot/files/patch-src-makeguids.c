--- src/makeguids.c
+++ src/makeguids.c
@@ -150,18 +150,18 @@ main(int argc, char *argv[])
 	fprintf(header, "#ifndef EFIVAR_GUIDS_H\n#define EFIVAR_GUIDS_H 1\n\n");
 
 	fprintf(symout, "#include <efivar.h>\n");
-	fprintf(symout, "#include <endian.h>\n");
+	fprintf(symout, "#include <sys/endian.h>\n");
 	fprintf(symout, """\n\
 #if BYTE_ORDER == BIG_ENDIAN\n\
 #define cpu_to_be32(n) (n)\n\
 #define cpu_to_be16(n) (n)\n\
-#define cpu_to_le32(n) (__bswap_constant_32(n))\n\
-#define cpu_to_le16(n) (__bswap_constant_16(n))\n\
+#define cpu_to_le32(n) (__builtin_bswap32(n))\n\
+#define cpu_to_le16(n) (__builtin_bswap16(n))\n\
 #else\n\
 #define cpu_to_le32(n) (n)\n\
 #define cpu_to_le16(n) (n)\n\
-#define cpu_to_be32(n) (__bswap_constant_32(n))\n\
-#define cpu_to_be16(n) (__bswap_constant_16(n))\n\
+#define cpu_to_be32(n) (__builtin_bswap32(n))\n\
+#define cpu_to_be16(n) (__builtin_bswap16(n))\n\
 #endif\n\
 """);
 
