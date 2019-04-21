#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <regex.h>

static const char *dirpath = "/home/rizk/Documents";

int isDanger(const char *filename) {
	regex_t pdf, txt, doc;

	regcomp(&pdf, "pdf$", 0);
	regcomp(&txt, "txt$", 0);
	regcomp(&doc, "doc$", 0);

	if ((regexec(&pdf, filename, 0, NULL, 0) == 0) || (regexec(&txt, filename, 0, NULL, 0) == 0)
		|| (regexec(&doc, filename, 0, NULL, 0) == 0))
	{
		regfree(&pdf);
		regfree(&txt);
		regfree(&doc);

		return 1;
	} else {
		regfree(&pdf);
		regfree(&txt);
		regfree(&doc);

		return 0;
	}
}

static int xmp_getattr(const char *path, struct stat *stbuf)
{
	int res;
	char fpath[1000];
	sprintf(fpath,"%s%s",dirpath,path);
	res = lstat(fpath, stbuf);

	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
			   off_t offset, struct fuse_file_info *fi)
{
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);
	int res = 0;

	DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	dp = opendir(fpath);
	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		res = (filler(buf, de->d_name, &st, 0));
			if(res!=0) break;
	}

	closedir(dp);
	return 0;
}

static int xmp_read(const char *path, char *buf, size_t size, off_t offset,
			struct fuse_file_info *fi)
{
	char fpath[1000];
	if(strcmp(path,"/") == 0)
	{
		path=dirpath;
		sprintf(fpath,"%s",path);
	}
	else sprintf(fpath, "%s%s",dirpath,path);

	if (isDanger(fpath) == 1) {
		char npath[1000];
		sprintf(npath, "%s.ditandai", fpath);
		rename(fpath, npath);

		if (opendir(fpath) == NULL)
			system("mkdir /home/rizk/Documents/rahasia");
		char com[1000];
		sprintf(com, "chmod 000 %s", npath);
		system(com);
		sprintf(com, "mv %s /home/rizk/Documents/rahasia", npath);
		system(com);

		system("zenity --error --text=\"Terjadi Kesalahan! File berisi konten berbahaya.\n\" --title=\"Warning!\"");

		return -1;
	} else {
		int res = 0;
		int fd = 0;

		(void) fi;
		fd = open(fpath, O_RDONLY);
		if (fd == -1)
			return -errno;

		res = pread(fd, buf, size, offset);
		if (res == -1)
			res = -errno;

		close(fd);

		return res;
	}
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
