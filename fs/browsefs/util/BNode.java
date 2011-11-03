package browsefs;

import java.util.*;

public class BNode {

	/* Equivalent to POSIX stat structure. */
	public long st_dev;
	public long st_ino;
	public long st_mode;
	public long st_nlink;
	public long st_uid;
	public long st_gid;
	public long st_rdev;
	public long st_size;
	public long st_blksize;
	public long st_blocks;
	public long st_atime;   // This has a special time_t type in c++
	public long st_mtime;
	public long st_ctime;

    public char type;
    public String name;
    public String data;
    public int usecount;
    //vector<void*> *files;   // NOT FOR GENERIC BNODE
    public List<BNode> contents;
    
    public int readcount;
    public int writecount;
    //pthread_mutex_t mutex;    // I MAY NEED TO DO MUTEXES IN JAVA HERE!!!
    //pthread_cond_t cond;

	public BNode (){

		st_dev = 0;
		st_ino = 0;
		st_mode = 0;
		st_nlink = 0;
		st_uid = 0;
		st_gid = 0;
		st_rdev = 0;
		st_size = 0;
		st_blksize = 0;
		st_blocks = 0;
		st_atime = 0;
		st_mtime = 0;
		st_ctime = 0;
		usecount = 0;
		readcount = 0;
		writecount = 0;
		contents = new ArrayList<BNode>();
	}


}
