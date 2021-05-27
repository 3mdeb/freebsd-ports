--- src/efivar.c
+++ src/efivar.c
@@ -63,7 +63,7 @@ list_all_variables(void)
 	int rc;
 	while ((rc = efi_get_next_variable_name(&guid, &name)) > 0)
 		 printf(GUID_FORMAT "-%s\n",
-			guid->a, guid->b, guid->c, bswap_16(guid->d),
+			guid->a, guid->b, guid->c, bswap16(guid->d),
 			guid->e[0], guid->e[1], guid->e[2], guid->e[3],
 			guid->e[4], guid->e[5], name);
 
@@ -153,7 +153,7 @@ show_variable(char *guid_name, int display_type)
 
 	if (display_type == SHOW_VERBOSE) {
 		printf("GUID: "GUID_FORMAT "\n",
-		       guid.a, guid.b, guid.c, bswap_16(guid.d),
+		       guid.a, guid.b, guid.c, bswap16(guid.d),
 		       guid.e[0], guid.e[1], guid.e[2], guid.e[3],
 		       guid.e[4], guid.e[5]);
 		printf("Name: \"%s\"\n", name);
@@ -280,7 +280,7 @@ prepare_data(const char *filename, void **data, size_t *data_size)
 		goto err;
 
 	buflen = statbuf.st_size;
-	buf = mmap(NULL, buflen, PROT_READ, MAP_PRIVATE|MAP_POPULATE, fd, 0);
+	buf = mmap(NULL, buflen, PROT_READ, MAP_PRIVATE, fd, 0);
 	if (!buf)
 		goto err;
 
@@ -436,7 +436,7 @@ int main(int argc, char *argv[])
 					break;
 				printf("{"GUID_FORMAT"} {%s} %s %s\n",
 					guid[i].guid.a, guid[i].guid.b,
-					guid[i].guid.c, bswap_16(guid[i].guid.d),
+					guid[i].guid.c, bswap16(guid[i].guid.d),
 					guid[i].guid.e[0], guid[i].guid.e[1],
 					guid[i].guid.e[2], guid[i].guid.e[3],
 					guid[i].guid.e[4], guid[i].guid.e[5],
