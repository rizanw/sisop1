#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

static const char *dirpath = "/home/rizk/Downloads";

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

static int xmp_access(const char *path, int mask)
{
	int res;

  char fpath[1000];
  sprintf(fpath,"%s%s",dirpath,path);
	res = access(fpath, mask);
	if (res == -1)
		return -errno;

	return 0;
}

static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
		       off_t offset, struct fuse_file_info *fi)
{
  char fpath[1000];
	if(strcmp(path,"/") == 0){
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

    if(strcmp(fpath, "/home/rizk/Downloads") == 0){
      strcat(de->d_name, ".bak");
    }

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

	int res = 0;
  int fd = 0 ;

	(void) fi;
	fd = open(fpath, O_RDONLY);
	if (fd == -1)
		return -errno;


	// char npath[100000];
	// sprintf(npath, "%s.bak", fpath);
	// rename(fpath, npath);

	res = pread(fd, buf, size, offset);
	if (res == -1)
		res = -errno;
	close(fd);
	return res;
}

static int xmp_rename(const char *from, const char *to){
	int res;
	// char to2[256], from2[256];
  //
	// sprintf(to2,"%s%s.bak",dirpath,to);
	// sprintf(from2,"%s%s",dirpath,from);

  char fpath[1000];
  sprintf(fpath,"%s%s",dirpath,from);
  char npath[9999];
	sprintf(npath, "%s.bak", fpath);
	res = rename(fpath, npath);

  if(res == -1)
      return -errno;
  return res;
}

static int xmp_chmod(const char *path, mode_t mode){

  char fpath[999];
  // if(strcmp(path, "/") == 0){
  //   path=dirpath;
  //   sprintf(fpath, "%s", path);
  // }else
  sprintf(fpath, "%s%s", dirpath, path);

  int res;
  mode_t mode2 = 0666;
  res = chmod(fpath, mode2);

  if(res == -1)
    return -errno;
  return res;
}

static int xmp_write(const char *path, const char *buf, size_t size,
		     off_t offset, struct fuse_file_info *fi)
{
	int fd;
	int res;

  char fpath[1000];
  sprintf(fpath,"%s%s",dirpath,path);

	(void) fi;
	fd = open(fpath, O_WRONLY);
	if (fd == -1)
		return -errno;

	res = pwrite(fd, buf, size, offset);
	if (res == -1)
		res = -errno;

	close(fd);
	return res;
}

static struct fuse_operations xmp_oper = {
	.getattr	= xmp_getattr,
  .access		= xmp_access,
	.readdir	= xmp_readdir,
	.read		= xmp_read,
	.rename = xmp_rename,
  .chmod = xmp_chmod,
  .write = xmp_write,
};

int main(int argc, char *argv[])
{
	umask(0);
	return fuse_main(argc, argv, &xmp_oper, NULL);
}
