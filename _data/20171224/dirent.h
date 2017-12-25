#define NAME_MAX 64 /* longest filename component; */
/* system-dependent */
typedef struct { /* portable directory entry */
		long ino; /* inode number */
		char name[NAME_MAX+1]; /* name + '\0' terminator */
} Dirent;

typedef struct { /* minimal DIR: no buffering, etc. */
		int fd; /* file descriptor for the directory */
		Dirent d; /* the directory entry */
} Dir;

Dir *my_opendir(char *dirname);
Dirent *my_readdir(Dir *dfd);
void my_closedir(Dir *dfd);
