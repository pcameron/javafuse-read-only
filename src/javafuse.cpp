
#define FUSE_USE_VERSION 26

#include <string.h>

#include <stdio.h>
#include <fuse.h>
#include <errno.h>
#include <stdlib.h>
#include <syslog.h>
#include <assert.h>
#include <vector>
#include <libgen.h>
#include <time.h>
#include <pthread.h>

extern "C" {
	#include "javafuse.c"
}


#define CACHE_FILES 1

#define FT_DIR 0
#define FT_FILE 1


using namespace std;

typedef struct
{
    char type;
    char *name;
    char *data;
    off_t size;
    int usecount;
    time_t ctime;
    time_t atime;
    time_t mtime;
    mode_t mode;
    uid_t uid;
    gid_t gid;
    vector<void*> *files;
    
    int readcount;
    int writecount;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
} file;

file *ROOT;

pthread_mutex_t root_mutex;

file *findfile (const char *name, file *parent)
{
    file *fil = NULL;
    if (name!=NULL && parent!=NULL)
    {
	for (int i=0; i<parent->files->size() && fil==NULL; i++)
	{
	    file *fi = (file*)(*parent->files)[i];
	    if (strcmp (fi->name, name)==0) fil = fi;
	}
    }
    return fil;
}

file * find_file (const char *name, file *&parent)
{
    file *fil = NULL;
    if (name!=NULL)
    {
	if (strcmp (name, "/")==0) 
	{
	    parent = NULL;
	    return ROOT;
	}
	char *named = strdup (name);
	char *nameb = strdup (name);
	char *dir = dirname (named);
	char *base = basename (nameb);
	if (strcmp (dir, "/")==0)
	{
	    // printf ("found ROOT\n");
	    parent = ROOT;
	    fil = findfile (base, parent);
	}
	else 
	{
	    file *p;
	    // printf ("searching %s\n", dir);
	    fil = find_file (dir, p);
	    // printf ("found: %s\n", fil->name);
	    if (fil!=NULL)
	    {
		parent = fil;
		fil = findfile (base, parent);
	    }
	}
	free (named);
	free (nameb);
    }
    return fil;
}

#define create_file(name, mode) create_file_data (name, FT_FILE, mode)
#define create_dir(name, mode) create_file_data (name, FT_DIR, mode)

file * create_file_data (const char *name, char type, mode_t mode)
{
    file *fil = (file*)malloc(sizeof (file));
    if (fil!=NULL)
    {
        fil->type = type;
        fil->name = strdup (name);
        fil->data = NULL;
        fil->size = 0;
	if (type == FT_FILE) fil->files = NULL;
	else fil->files = new vector<void*> ();
	fil->usecount = 0;
	time(&fil->ctime);
	time(&fil->atime);
	time(&fil->mtime);
	fil->uid = fuse_get_context()->uid;
	fil->gid = fuse_get_context()->gid;
	fil->mode = mode;
	
	pthread_mutex_init (&fil->mutex, NULL);
	pthread_cond_init (&fil->cond, NULL);
	fil->readcount = 0;
	fil->writecount = 0;
    }
    return fil;
}

#define remove_file(fil) remove_file_data (fil)
#define remove_dir(fil) remove_file_data (fil)

int remove_file_data (file *fil)
{
    int result = 0;
    if (fil!=NULL)
    {
	if (fil->type == FT_FILE && fil->usecount==0)
	{
	    free (fil->name);
	    free (fil->data);
	    pthread_cond_destroy (&fil->cond);
	    pthread_mutex_destroy (&fil->mutex);
	    free (fil);
	    result = 1;
	}
	else
	if (fil->type == FT_DIR && fil->files->size()==0)
	{
	    free (fil->name);
	    free (fil->data);
	    delete fil->files;
	    free (fil);
	    result = 1;
	}
    }
    return result;
}

static int sfs_getattr (const char *path, struct stat *stbuf)
{
    pthread_mutex_lock (&root_mutex);
    syslog (LOG_DEBUG, "getattr %s\n", path);
    int result = -ENOENT;
    memset (stbuf, 0, sizeof (stbuf));
    file *parent;
    file *fil = find_file (path, parent);
    if (fil!=NULL)
    {
	// printf ("fil->name: %s\n", fil->name);
	stbuf->st_mode = ((fil->type==FT_FILE)?S_IFREG:S_IFDIR) | fil->mode;
	stbuf->st_nlink = 1;
	stbuf->st_size = fil->size;
	stbuf->st_ctime = fil->ctime;
	stbuf->st_atime = fil->atime;
	stbuf->st_mtime = fil->mtime;
	stbuf->st_uid = fil->uid;
	stbuf->st_gid = fil->gid;
	// stbuf->st_mode = fil->mode;
	result = 0;
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_readdir (const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi)
{
    pthread_mutex_lock (&root_mutex);
    syslog (LOG_DEBUG, "readdir %s\n", path);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    if (fil!=NULL && fil->type==FT_DIR)
    {
	// printf ("found dir %s\n", path);
	filler (buf, ".", NULL, 0);
	filler (buf, "..", NULL, 0);
	// printf ("fil->files->size(): %d\n", fil->files->size());
	for (int i=0; i<fil->files->size();i++) filler (buf, ((file*)(*fil->files)[i])->name, NULL, 0);
	result = 0;
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_open (const char *path, struct fuse_file_info *f)
{
    syslog (LOG_DEBUG, "open %s (%d)\n", path, f->flags);
    pthread_mutex_lock (&root_mutex);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    uid_t uid = fuse_get_context()->uid;
    uid_t gid = fuse_get_context()->gid;
    if (fil!=NULL && fil->type==FT_FILE)
    {
	if (uid==0 || (uid == fil->uid && fil->mode & S_IRUSR) || (gid == fil->gid && fil->mode & S_IRGRP) || (uid != fil->uid && gid != fil->gid && fil->mode & S_IROTH))
	{
	    fil->usecount++;
	    f->fh = (int)fil;
	    f->keep_cache = CACHE_FILES;
	    result = 0;
	}
	else result = -EACCES;
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_read (const char *path, char *buf, size_t size, off_t offset, struct fuse_file_info *f)
{
    // syslog (LOG_DEBUG,"read file %llu offset %llu length %ld\n", f->fh, offset, size);
    file *fil = (file*)f->fh;
    if (fil==NULL) return -ENOENT;
    pthread_mutex_lock (&fil->mutex);
    while (fil->writecount > 0) pthread_cond_wait (&fil->cond, &fil->mutex);
    fil->readcount++;
    pthread_mutex_unlock (&fil->mutex);
    time (&fil->atime);
    if (offset > fil->size) size = 0;
    else if (offset+size > fil->size) size = fil->size-offset;
    if (size>0) memcpy (buf, fil->data+offset, size);
    // printf ("read file %llu offset %llu length %ld\n", f->fh, offset, size);
    pthread_mutex_lock (&fil->mutex);
    fil->readcount--;
    pthread_cond_signal (&fil->cond);
    pthread_mutex_unlock (&fil->mutex);
    return size;
}

static int sfs_write (const char *path, const char *buf, size_t size, off_t offset, struct fuse_file_info *f)
{
    // syslog (LOG_DEBUG,"write file %llu offset %llu length %ld\n", f->fh, offset, size);
    file *fil = (file*)f->fh;
    if (fil==NULL) return -ENOENT;
    pthread_mutex_lock (&fil->mutex);
    while (fil->readcount > 0 && fil->writecount > 0) pthread_cond_wait (&fil->cond, &fil->mutex);
    fil->writecount++;
    pthread_mutex_unlock (&fil->mutex);
    time (&fil->mtime);
    if (offset+size > fil->size)
    {
	char *data = (char*)realloc (fil->data, offset+size);
	if (data!=NULL) 
	{
	    fil->data = data;
	    fil->size = offset+size;
	}
	else size = 0;
    }
    if (size>0) memcpy (fil->data+offset, buf, size);
    // printf ("write file %llu offset %llu length %ld\n", f->fh, offset, size);
    pthread_mutex_lock (&fil->mutex);
    fil->writecount--;
    pthread_cond_signal (&fil->cond);
    pthread_mutex_unlock (&fil->mutex);
    return size;
}

static int sfs_create (const char *path, mode_t mode, struct fuse_file_info *f)
{
    syslog (LOG_DEBUG, "create %s (%d)\n", path, mode);
    pthread_mutex_lock (&root_mutex);
    int result = -EACCES;
    char *pathd = strdup (path);
    char *pathb = strdup (path);
    char *dir = dirname (pathd);
    char *base = basename (pathb);
    if (strcmp (base,"/")!=0)
    {
	// printf ("dir: %s\n", dir);
	file *parent;
	file *fil = find_file (dir, parent);
	if (fil!=NULL)
	{
	    parent = fil;
	    fil = create_file (base, mode);
	    parent->files->push_back (fil);  
	    fil->usecount++;
	    f->fh = (int)fil;
	    f->keep_cache = CACHE_FILES;
	    result = 0;
	}
	else result = -ENOENT;
    }
    free (pathb);
    free (pathd);
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_unlink (const char *path)
{
    syslog (LOG_DEBUG, "unlink %s\n", path);
    pthread_mutex_lock (&root_mutex);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    if (fil!=NULL && parent!=NULL)
    {
	if (fil->type == FT_FILE)
	{
	    if (fil->usecount == 0)
    	    {
		int n=-1;
		for (int i=0; i<parent->files->size();i++) if (fil == (file*)(*parent->files)[i]) n = i;
		if (remove_file (fil))
		{
		    if (n>-1) parent->files->erase (parent->files->begin()+n);
		    result = 0;
		}
		else result = -EACCES;
	    }
	    else result = -EACCES;
	}
	else
	if (fil->type == FT_DIR)
	{
	    if (fil->files->size()==0)
	    {
		int n=-1;
		for (int i=0; i<parent->files->size();i++) if (fil == (file*)(*parent->files)[i]) n = i;
		remove_dir (fil);
		if (n>-1) parent->files->erase (parent->files->begin()+n);
		result = 0;
	    }
	    else result = -EACCES;
	}
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_truncate (const char *path, off_t size)
{
    syslog (LOG_DEBUG, "truncate %s (%llu)\n", path, size);
    pthread_mutex_lock (&root_mutex);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    if (fil!=NULL && fil->type==FT_FILE)
    {
	pthread_mutex_lock (&fil->mutex);
	while (fil->readcount > 0 && fil->writecount == 0) pthread_cond_wait (&fil->cond, &fil->mutex);
	fil->writecount++;
	pthread_mutex_unlock (&fil->mutex);
	if (size == 0)
	{
	    if (fil->data!=NULL) free (fil->data);
	    fil->data = NULL;
	    fil->size = 0;
	    result = 0;
	}
	else
	{
	    char *data = (char*)realloc (fil->data, size);
	    if (data!=NULL) 
	    {
		fil->data = data;
		fil->size = size;
		result = 0;
	    }
	}
	time(&fil->mtime);
	pthread_mutex_lock (&fil->mutex);
	fil->writecount--;
	pthread_cond_signal (&fil->cond);
	pthread_mutex_unlock (&fil->mutex);
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_mkdir (const char *path, mode_t mode)
{
    syslog (LOG_DEBUG, "mkdir %s (%d)\n", path, mode);
    pthread_mutex_lock (&root_mutex);
    int result = -EACCES;
    char *pathd = strdup (path);
    char *pathb = strdup (path);
    char *dir = dirname (pathd);
    char *base = basename (pathb);
    if (strcmp (base,"/")!=0)
    {
	// printf ("dir: %s\n", dir);
	file *parent;
	file *fil = find_file (dir, parent);
	if (fil!=NULL)
	{
	    parent = fil;
	    fil = create_dir (base, mode);
	    parent->files->push_back (fil);  
	    result = 0;
	}
	else result = -ENOENT;
    }
    free (pathb);
    free (pathd);
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_rmdir (const char *path)
{
    syslog (LOG_DEBUG, "rmdir %s\n", path);
    return sfs_unlink (path);
}

static int sfs_rename (const char *path, const char *newpath)
{
    syslog (LOG_DEBUG, "rename %s to %s\n", path, newpath);
    pthread_mutex_lock (&root_mutex);
    int result = -ENOENT;
    char *pathd = strdup (newpath);
    char *pathb = strdup (newpath);
    char *dir = dirname (pathd);
    char *base = basename (pathb);
    if (strcmp (base,"/")!=0)
    {
	file *nparent;
	file *nfil = find_file (dir, nparent);
	if (nfil!=NULL && nfil->type == FT_DIR)
	{
	    file *parent;
	    file *fil = find_file (path, parent);
	    if (fil!=NULL)
	    {
		int n=-1;
		for (int i=0; i<parent->files->size();i++) if (fil == (file*)(*parent->files)[i]) n = i;
		if (n>-1) parent->files->erase (parent->files->begin()+n);	
		free (fil->name);
		fil->name = strdup (base);
		nfil->files->push_back (fil);
		result = 0;
	    }
	}
    }
    free (pathd);
    free (pathb);
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_release (const char *path, struct fuse_file_info *f)
{
    syslog (LOG_DEBUG, "release %s\n", path);
    int result = -ENOENT;
    file *fil = (file*)f->fh;
    if (fil!=NULL)
    {
	fil->usecount--;
    }
    return result;
}

static int sfs_chmod (const char *path, mode_t mode)
{
    pthread_mutex_lock (&root_mutex);
    syslog (LOG_DEBUG, "chmod %s (%ld)\n", path, mode);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    uid_t uid = fuse_get_context()->uid;
    uid_t gid = fuse_get_context()->gid;
    if (fil!=NULL)
    {
	// printf ("fil->name: %s\n", fil->name);
	if (uid == 0 || uid == fil->uid)
	{
	    fil->mode = mode;
	    result = 0;
	}
	else result = -EACCES;
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static int sfs_chown (const char *path, uid_t uid, gid_t gid)
{
    pthread_mutex_lock (&root_mutex);
    syslog (LOG_DEBUG, "chown %s (%d, %d)\n", path, uid, gid);
    int result = -ENOENT;
    file *parent;
    file *fil = find_file (path, parent);
    uid_t c_uid = fuse_get_context()->uid;
    uid_t c_gid = fuse_get_context()->gid;
    if (fil!=NULL)
    {
	// printf ("fil->name: %s\n", fil->name);
	if (c_uid == 0 || c_uid == fil->uid)
	{
	    fil->uid = uid;
	    fil->gid = gid;
	    result = 0;
	}
	else result = -EACCES;
    }
    pthread_mutex_unlock (&root_mutex);
    return result;
}

static struct fuse_operations functions;

int main (int argc, char *argv[])
{
    pthread_mutex_init (&root_mutex, 0);
    ROOT = create_dir ("/", 0777);
    sfs_chown ("/", 0, 0);
    functions.getattr = sfs_getattr;
    functions.readdir = sfs_readdir; 
    functions.open = sfs_open;
    functions.read = sfs_read;
    functions.write = sfs_write;
    functions.create = sfs_create;
    functions.unlink = sfs_unlink;
    functions.truncate = sfs_truncate;
    functions.rename = sfs_rename;
    functions.release = sfs_release;
    functions.mkdir = sfs_mkdir;
    functions.rmdir = sfs_unlink;
    functions.chmod = sfs_chmod;
    functions.chown = sfs_chown;

    extern "C" {
	    int i;

	    // Parse the command line.
	    read_cmdline(argc, argv);

	    // If user provided config file path then read it. Will overwrite command
	    // line options!
	    if (configfile != NULL)
		read_config(configfile);

	    if (DEBUG) {
		printf("%s config file:\n", configfile);

		printf("%d cmdline fuse arguments:", fuseArgc);
		for (i = 0; i < fuseArgc; i++)
		    printf(" %s", fuseArgv[i]);
		printf("\n");

		printf("%d cmdline java arguments:", javaArgc);
		for (i = 0; i < javaArgc; i++)
		    printf(" %s", javaArgv[i]);
		printf("\n");
	    }

	    // Must have class name of Java FS.
	    if (classname == NULL)
	    {
		printf("Missing option: -CPackagename/ClassName\n");
		return -1;
	    }

	    // Initialize the JVM and the JNI stuff.
	    init_JVM(javaArgc, javaArgv);
    }

    int result = fuse_main(fuseArgc, fuseArgv, &functions, NULL);
    pthread_mutex_destroy (&root_mutex);
    remove_dir (ROOT);

    return result;
}

