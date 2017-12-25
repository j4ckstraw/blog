#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h> /* flags for read and write */
#include <sys/types.h> /* typedefs */
#include <sys/stat.h> /* structure returned by stat */
#include "dirent.h"

// int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));
/* fsize: print the name of file "name" */
void fsize(char *name)
{
		struct stat stbuf;
		if (stat(name, &stbuf) == -1) {
				fprintf(stderr, "fsize: can't access %s\n", name);
				return;
		}
		if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
				dirwalk(name, fsize);
		printf("%8ld %s\n", stbuf.st_size, name);
}


#define MAX_PATH 1024
/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
		char name[MAX_PATH];
		Dirent *dp;
		Dir *dfd;
		if ((dfd = my_opendir(dir)) == NULL) {
				fprintf(stderr, "dirwalk: can't open %s\n", dir);
				return;
		}
		while ((dp = my_readdir(dfd)) != NULL) {
				if (strcmp(dp->name, ".") == 0
								|| strcmp(dp->name, ".."))
						continue; /* skip self and parent */
				if (strlen(dir)+strlen(dp->name)+2 > sizeof(name))
						fprintf(stderr, "dirwalk: name %s %s too long\n",
										dir, dp->name);
				else {
						sprintf(name, "%s/%s", dir, dp->name);
						printf("name is %s\n",name);
						(*fcn)(name);
				}
		}
		my_closedir(dfd);
}


/* my_opendir: open a directory for my_readdir calls */
Dir *my_opendir(char *dirname)
{
		int fd;
		struct stat stbuf;
		Dir *dp;
		if ((fd = open(dirname, O_RDONLY, 0)) == -1
						|| fstat(fd, &stbuf) == -1
						|| (stbuf.st_mode & S_IFMT) != S_IFDIR
						|| (dp = (Dir *) malloc(sizeof(Dir))) == NULL)
				return NULL;
		dp->fd = fd;
		return dp;
}

/* my_closedir: close directory opened by my_opendir */
void my_closedir(Dir *dp)
{
		if (dp) {
				close(dp->fd);
				free(dp);
		}
}

#include <sys/dir.h> /* local directory structure */
/* my_readdir: read directory entries in sequence */
#define DIRSIZ 64
Dirent *my_readdir(Dir *dp)
{
		struct direct dirbuf; /* local directory structure */
		static Dirent d; /* return: portable structure */
		while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf))
						== sizeof(dirbuf)) {
				if (dirbuf.d_ino == 0) /* slot not in use */
						continue;
				d.ino = dirbuf.d_ino;
				strncpy(d.name, dirbuf.d_name, DIRSIZ);
				d.name[DIRSIZ] = '\0'; /* ensure termination */
				return &d;
		}
		return NULL;
	// 	struct dirent *de;
	// 	static Dirent d;
	// 	while (de = readdir(dp)){
	// 		if (de->d_ino == 0) continue;
	// 		d.ino = de->d_ino;
	// 		strncpy(d.name,de->d_name,DIRSIZ);
	// 		d.name[DIRSIZ] = '\0';
	// 		return &d;
	// 	}
	// return NULL;
}
