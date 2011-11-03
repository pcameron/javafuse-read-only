package browsefs;

import javafuse.*;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.firefox.FirefoxProfile;
import java.lang.Thread;
import java.lang.Runnable;
import java.util.*;
import java.io.*;
import java.nio.*;
import java.nio.channels.*;
import java.nio.channels.ReadableByteChannel;
import java.net.URL;
import java.util.Timer;
import java.util.TimerTask;
import java.awt.event.*;

public class BrowseFS implements JavaFS
{
    //BrowserModule bm;
    FSTree filesystemTree;
    HashMap<String, BNode> namesToNodes;
    public static WebDriver driver;
    public static int driverCount;
    public static int guiContext;
    public static LinkedList<WebDriver> driverList;
    public static ListIterator<WebDriver> driverIterator;
    public static FirefoxProfile securityProfile;
    public static java.util.Timer guiTimer;
    //public static javax.swing.Timer guiTimer;
    public static boolean isLocked;
    final int DELAY_TIME;

    public BrowseFS()
    {
	//bm = new BrowserModule();
	//Thread t = new Thread(bm);
	//t.start();
	

	//FirefoxDriver.ACCEPT_UNTRUSTED_CERTIFICATES = true;
	//FirefoxDriver.ASSUME_UNTRUSTED_ISSUER = true;
	securityProfile = new org.openqa.selenium.firefox.FirefoxProfile();
	securityProfile.setAcceptUntrustedCertificates(true);
	securityProfile.setAssumeUntrustedCertificateIssuer(false);
	driver = new FirefoxDriver(securityProfile);
	driverList = new LinkedList<WebDriver>();
	driverIterator = driverList.listIterator();
	driverIterator.add(driver);
	driverCount = 2;
	//namesToNodes = new HashMap<String, BNode>();
	//filesystemTree = new FSTree();
	//System.out.println("FS is constructed.");
	//guiContext = 0;
	
	DELAY_TIME = 3000;
	isLocked = false;
	/*
	javax.swing.Timer guiTimer = new javax.swing.Timer(DELAY_TIME, new ActionListener() {
          public void actionPerformed(ActionEvent e) {
              isLocked = false;
	      System.out.println("UNLOCKED! TIMER EXPIRED!");
          }
       	});
	guiTimer.setRepeats(false);
	*/

	guiTimer = new java.util.Timer();

    }

    public int getattr_pre(String path, Stat buf)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
		//System.out.println("Timer is running: " + guiTimer.isRunning());
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];
	//String parentPath = path.split(theDirName)[0];


	if (theDirName.equals(".Trash")) {
		isLocked = true;
		System.out.println("LOCKED OUT! TIMER STARTED!");
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;	
	}

	//pre(path);


 	//if (path.equals(parentPath + ".Trash")) guiContext++;
	System.out.println("getattr_pre");
	System.out.println("   path = " + path);
	//buf.printOut();
        return 0;
    }

    public int getattr_post(String path, Stat buf, int result)
    {	
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
		//System.out.println("Timer is running: " + guiTimer.isRunning());
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	//post(path);
	System.out.println("getattr_post");
	System.out.println("   path = " + path);
	System.out.println("   result = " + result);
	//buf.printOut();
        return 0;
    }

    public int readlink_pre(String path, String buf, int bufsize)
    {	
	//pre(path);
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("readlink_pre");
        return 0;
    }

    public int readlink_post(String path, String buf, int bufsize, int result)
    {
	//post(path);
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("readlink_post");
        return 0;
    }

    public int mknod_pre(String path, int mode, int dev)
    {
	System.out.println("mknod_pre");
	System.out.println("   path = " + path);
	System.out.println("   mode = " + mode);
	System.out.println("   path = " + path);
        return 0;
    }

    public int mknod_post(String path, int mode, int dev, int result)
    {
	System.out.println("mknod_post");
        return 0;
    }

    public int mkdir_pre(String path, int mode)
    {
/*
	String dirName = path.substring(1);
	BFolder theNewFolder = new BFolder();

	filesystemTree.root.add(theNewFolder);
	namesToNodes.put(dirName, theNewFolder);
	System.out.println("FOLDER CREATED");
	System.out.println(dirName);
	driver.get("http://" + dirName);
*/
	
	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];
	String parentPath = path.split(theDirName)[0];
	if (path.equals(parentPath + "%WINDOW++")) {
		//if (driverCount != 1) driver = new FirefoxDriver();
		if (!driverIterator.hasNext()){		// If the driverIterator doesn't have a newer driver, make a new one
			driver = new FirefoxDriver(securityProfile);
			driverIterator.add(driver);
			//driverIterator.next();
			driverCount++;
			System.out.println("Creating a new driver..." + driver);
		}
		else {  // If driverIterator does have a newer driver, select it
			driver = driverIterator.next();
			if(driverIterator.hasNext()) driver = driverIterator.next();
			System.out.println("Going forward one driver..."+ driver);
		}
	}
	else if (path.equals(parentPath + "%WINDOW--")) {

		if (driverIterator.hasPrevious()) {  // If driverIterator does have a previous driver, select it

			driver = driverIterator.previous();
			if (driverIterator.hasPrevious()) driver = driverIterator.previous();
			System.out.println("Going back one driver..." + driver);
		}

	}
	else if (path.equals(parentPath + "%LOAD")) {
		String toNav = driver.getCurrentUrl();
		if (toNav.startsWith("http://")) {
			toNav = toNav.substring(6, toNav.length());
			navigate(toNav, parentPath, true, false);
		}
		else if (toNav.startsWith("https://")) {
			toNav = toNav.substring(7, toNav.length());
			navigate(toNav, parentPath, true, true);
		}
		else {
			navigate(toNav, parentPath, true, false);
		}
		System.out.println("Navigating to: " + toNav + " | with theDirName: " + theDirName);
	}
	else if (path.equals(parentPath + "%RELOAD")) {
		String toNav = driver.getCurrentUrl();
		if (toNav.startsWith("http://")) {
			toNav = toNav.substring(6, toNav.length());
			navigate(toNav, parentPath, true, false);
		}
		else if (toNav.startsWith("https://")) {
			toNav = toNav.substring(7, toNav.length());
			navigate(toNav, parentPath, true, true);
		}
		else {
			navigate(toNav, parentPath, true, false);
		}
		System.out.println("Navigating to: " + toNav + " | with theDirName: " + theDirName);

	}
	else if (path.equals(parentPath + "%REFRESH")) {
		String toNav = driver.getCurrentUrl();
		if (toNav.startsWith("http://")) {
			toNav = toNav.substring(6, toNav.length());
			navigate(toNav, parentPath, true, false);
		}
		else if (toNav.startsWith("https://")) {
			toNav = toNav.substring(7, toNav.length());
			navigate(toNav, parentPath, true, true);
		}
		else {
			navigate(toNav, parentPath, true, false);
		}
		System.out.println("Navigating to: " + toNav + " | with theDirName: " + theDirName);
	}
	else if (path.equals(parentPath + "%LOAD_CURRENT")) {
		for (int m=0; m<30; m++) {
 			driver.findElement(By.linkText("Next")).click();
		}
		

	}
/*
	else if (path.equals(parentPath + "%")) {
		driver.get(")
	}
*/
	//System.out.println("Total drivers: " + driverList.size());
	System.out.println("mkdir_pre");
	System.out.println("   path = " + path);
	System.out.println("   mode = " + mode);
        return 0;
    }

    public int mkdir_post(String path, int mode, int result)
    {
/*
	String pageText;
	try{
		// Create files
		FileWriter fstream = new FileWriter(path + "/source.txt");
		BufferedWriter out = new BufferedWriter(fstream);
		pageText = driver.getPageSource();
		out.write(pageText);
		//Close the output stream
		out.close();
	}
	catch (Exception e){//Catch exception if any
		System.err.println("Error: " + e.getMessage());
	}
	try{
		// Create files
		java.util.List<WebElement> linkCollection = driver.findElements(By.tagName("a"));
		FileWriter fstream = new FileWriter(path + "/links.txt");
		BufferedWriter out = new BufferedWriter(fstream);
		for (int i=0; i<linkCollection.size(); i++) {
			pageText = linkCollection.get(i).getText() + "\n";
			out.write(pageText);
		}
		//Close the output stream
		out.close();
	}
	catch (Exception e){//Catch exception if any
		System.err.println("Error: " + e.getMessage());
	}
	try{
		// Create files
		pageText = driver.findElement(By.tagName("html")).getText();
		FileWriter fstream = new FileWriter(path + "/visibleText.txt");
		BufferedWriter out = new BufferedWriter(fstream);
		out.write(pageText);
		//Close the output stream
		out.close();
	}
	catch (Exception e){//Catch exception if any
		System.err.println("Error: " + e.getMessage());
	}
*/
	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];
	String parentPath = path.split(theDirName)[0];
	File f1;

	// Clean up the directories that were created when control commands were issued
	if (path.equals(parentPath + "%WINDOW++")) {
		f1 = new File(parentPath + "%WINDOW++");
		f1.delete();
	}
	else if (path.equals(parentPath + "%WINDOW--")) {
		f1 = new File(parentPath + "%WINDOW--");
		f1.delete();
	}
	else if (path.equals(parentPath + "%LOAD")) {
		f1 = new File(parentPath + "%LOAD");
		f1.delete();
	}
	else if (path.equals(parentPath + "%RELOAD")) {
		f1 = new File(parentPath + "%RELOAD");
		f1.delete();
	}
	else if (path.equals(parentPath + "%REFRESH")) {
		f1 = new File(parentPath + "%REFRESH");
		f1.delete();
	}
	else if (path.equals(parentPath + "%LOAD_CURRENT")) {
		f1 = new File(parentPath + "%LOAD_CURRENT");
		f1.delete();
	}
	//System.out.println("Total drivers: " + driverList.size());
	System.out.println("mkdir_post");
	System.out.println("   path = " + path);
	System.out.println("   mode = " + mode);
	System.out.println("   result = " + result);
        return 0;
    }

    public int unlink_pre(String path)
    {
	System.out.println("unlink_pre");
        return 0;
    }

    public int unlink_post(String path, int result)
    {
	System.out.println("unlink_post");
        return 0;
    }

    public int rmdir_pre(String path)
    {
	System.out.println("rmdir_pre");
        return 0;
    }

    public int rmdir_post(String path, int result)
    {
	System.out.println("rmdir_post");
        return 0;
    }

    public int symlink_pre(String oldpath, String newpath)
    {
	System.out.println("symlink_pre");
        return 0;
    }

    public int symlink_post(String oldpath, String newpath, int result)
    {
	System.out.println("symlink_post");
        return 0;
    }

    public int rename_pre(String oldpath, String newpath)
    {
	System.out.println("rename_pre");
        return 0;
    }

    public int rename_post(String oldpath, String newpath, int result)
    {
	System.out.println("rename_post");
        return 0;
    }

    public int link_pre(String oldpath, String newpath)
    {
	System.out.println("link_pre");
        return 0;
    }

    public int link_post(String oldpath, String newpath, int result)
    {
	System.out.println("link_post");
        return 0;
    }

    public int chmod_pre(String path, int mod)
    {
	System.out.println("chmod_pre");
        return 0;
    }

    public int chmod_post(String path, int mod, int result)
    {
	System.out.println("chmod_post");
        return 0;
    }

    public int chown_pre(String path, int owner, int group)
    {
	System.out.println("chown_pre");
        return 0;
    }

    public int chown_post(String path, int owner, int group, int result)
    {
	System.out.println("chown_post");
        return 0;
    }

    public int truncate_pre(String path, int length)
    {
	System.out.println("truncate_pre");
        return 0;
    }

    public int truncate_post(String path, int length, int result)
    {
	System.out.println("truncate_post");
        return 0;
    }

    public int utime_pre(String filename, Utimbuf buf)
    {
	System.out.println("utime_pre");
        return 0;
    }

    public int utime_post(String filename, Utimbuf buf, int result)
    {
	System.out.println("utime_post");
        return 0;
    }

    public int open_pre(String path, Fuse_file_info info)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("open_pre");
	System.out.println("   path = " + path);
        return 0;
    }

    public int open_post(String path, Fuse_file_info info, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("open_post");
	System.out.println("   path = " + path);
	System.out.println("   result = " + result);
        return 0;
    }

    public int read_pre(String path, String buf, int size, int offset, Fuse_file_info info)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("read_pre");
	System.out.println("   path = " + path);
	System.out.println("   buf = " + buf);
	System.out.println("   size = " + size);
	System.out.println("   offset = " + offset);
        return 0;
    }

    public int read_post(String path, String buf, int size, int offset, Fuse_file_info info, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("read_post");
	System.out.println("   path = " + path);
	System.out.println("   buf = " + buf);
	System.out.println("   size = " + size);
	System.out.println("   offset = " + offset);
	System.out.println("   result = " + result);
        return 0;
    }

    public int write_pre(String path, String buf, int count, int offset, Fuse_file_info info)
    {
	System.out.println("write_pre");
        return 0;
    }

    public int write_post(String path, String buf, int count, int offset, Fuse_file_info info, int result)
    {
	System.out.println("write_post");
        return 0;
    }

    public int statfs_pre(String path, Statvfs buf)
    {
	System.out.println("statfs_pre");
        return 0;
    }

    public int statfs_post(String path, Statvfs buf, int result)
    {
	System.out.println("statfs_post");
        return 0;
    }

    public int flush_pre(String path, Fuse_file_info info)
    {
	System.out.println("flush_pre");
        return 0;
    }

    public int flush_post(String path, Fuse_file_info info, int result)
    {
	System.out.println("flush_post");
        return 0;
    }

    public int release_pre(String path, Fuse_file_info info)
    {
	System.out.println("release_pre");
	System.out.println("path = " + path);
        return 0;
    }

    public int release_post(String path, Fuse_file_info info, int result)
    {
	System.out.println("release_post");
	System.out.println("path = " + path);
        return 0;
    }

    public int fsync_pre(String path, int datasync, Fuse_file_info info)
    {
	System.out.println("fsync_pre");
        return 0;
    }

    public int fsync_post(String path, int datasync, Fuse_file_info info, int result)
    {
	System.out.println("fsync_post");
        return 0;
    }

    public int setxattr_pre(String path, String name, String value, int size, int flags)
    {
	System.out.println("setxattr_pre");
        return 0;
    }

    public int setxattr_post(String path, String name, String value, int size, int flags, int result)
    {
	System.out.println("setxattr_post");
        return 0;
    }

    public int getxattr_pre(String path, String name, String value, int size)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("getxattr_pre");
        return 0;
    }

    public int getxattr_post(String path, String name, String value, int size, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("getxattr_post");
        return 0;
    }

    public int listxattr_pre(String path, String list, int size)
    {
	System.out.println("listxattr_pre");
        return 0;
    }

    public int listxattr_post(String path, String list, int size, int result)
    {
	System.out.println("listxattr_post");
        return 0;
    }

    public int removexattr_pre(String path, String name)
    {
	System.out.println("removexattr_pre");
        return 0;
    }

    public int removexattr_post(String path, String name, int result)
    {
	System.out.println("removexattr_post");
        return 0;
    }

	public int pre(String path) {
	
		String dirName = path.substring(1);
	/*
		BFolder theNewFolder = new BFolder();

		filesystemTree.root.add(theNewFolder);
		namesToNodes.put(dirName, theNewFolder);
	*/
		System.out.println("FOLDER CREATED");
		System.out.println(dirName);
		driver.get("http://" + dirName);
		return 0;
    	}
	public int navigate(String urlPath, String parentPath, Boolean toLoad, Boolean isHttps) {
		System.out.println("parentPath: " + parentPath);
		//String urlPath = path.substring(1);
		String pageText;
		WebElement theForm;
		java.util.List <WebElement> inputs;
		java.util.List <WebElement> textboxes;
		java.util.List <WebElement> buttons;

		if (toLoad && !isHttps) driver.get("http://" + urlPath.substring(1));
		else if (toLoad && isHttps) driver.get("https://" + urlPath.substring(1));
		if (!(new File(parentPath + "/source.txt").exists())){


			try{
				// Create files
				FileWriter fstream = new FileWriter(parentPath + "/source.txt");
				BufferedWriter out = new BufferedWriter(fstream);
				pageText = driver.getPageSource();
				out.write(pageText);
				//Close the output stream
				out.close();
			}
			catch (Exception e){//Catch exception if any
				System.err.println("Error: " + e.getMessage());
			}
			boolean result2 = new File(parentPath + "/Images").mkdir();
			System.out.println("IMAGES CREATED AT: " + parentPath + "/Images");
			String linkText;
			String linkHREF;
			String indexValue = "";
			try{
				// Create links files
				System.out.println("Made it to \"success\"");
				boolean success = (new File(parentPath + "/Links")).mkdir();
				if (success) {
					System.out.println("Directory: " + parentPath + "/Links" + " created");
					java.util.List<WebElement> linkCollection = driver.findElements(By.tagName("a"));
					FileWriter fstream = new FileWriter(parentPath + "/links.txt");
					BufferedWriter out = new BufferedWriter(fstream);
					for (int i=0; i<linkCollection.size(); i++) {
						//System.out.println("linkCollection i: " + i);
						linkText = linkCollection.get(i).getText();
						//if (linkText.equals("\"\"")) ;
						linkHREF = linkCollection.get(i).getAttribute("href");

						pageText = linkText + "     " + linkHREF + "\n";
						out.write(pageText);

	
						/*
						if (linkHREF.startsWith("http://")) {
							System.out.println("True");
							linkHREF = linkHREF.substring(7, linkHREF.length()-1);
							System.out.println(path + "/Links/" + linkText + "_" + linkHREF);
						}
						*/

						// Use triple digit indices for link files
						if (i+1< 100 && i+1 > 9) indexValue = "0" + (i+1);
						else if (i+1 < 10) indexValue = "00" + (i+1);
						else indexValue = "" + (i+1);

						result2 = new File(parentPath + "/Links/" + linkText.trim() + "_" + indexValue).mkdir();

					}
				//Close the output stream
				out.close();
	
				}  

			}
			catch (Exception e){//Catch exception if any
				System.err.println("Error: " + e.getMessage());
			}


			try {   // Download the images
				java.util.List<WebElement> imgCollection = driver.findElements(By.tagName("img"));
				URL imgSrc;
				String[] imgFragArray;
				String imgFileName;
				for (int k=0; k<imgCollection.size(); k++) {
					imgSrc = new URL(imgCollection.get(k).getAttribute("src"));
					imgFragArray = imgSrc.toString().split("/");
					imgFileName = imgFragArray[imgFragArray.length - 1];
    					ReadableByteChannel rbc = Channels.newChannel(imgSrc.openStream());
  					FileOutputStream fos = new FileOutputStream(parentPath + "/Images/" + imgFileName);
   					fos.getChannel().transferFrom(rbc, 0, 1 << 24);
				}

			}
			catch (Exception e){//Catch exception if any
				System.err.println("Error: " + e.getMessage());
			}
			try{
				// Create files
				pageText = driver.findElement(By.tagName("html")).getText();
				FileWriter fstream = new FileWriter(parentPath + "/visibleText.txt");
				BufferedWriter out = new BufferedWriter(fstream);
				out.write(pageText);
				//Close the output stream
				out.close();
			}
			catch (Exception e){//Catch exception if any
				System.err.println("Error: " + e.getMessage());
			}
			textboxes = new LinkedList<WebElement>();
			buttons = new LinkedList<WebElement>();
			boolean result3 = new File(parentPath + "/Forms").mkdir();
			try{
				try {
					theForm = driver.findElement(By.tagName("form"));
					inputs = theForm.findElements(By.tagName("input"));

					for (WebElement currentElement : inputs) {
						if (currentElement.getAttribute("type").equals("text")) {
							textboxes.add(currentElement);
						}
						else if (currentElement.getAttribute("type").equals("submit")) {
							buttons.add(currentElement);
						}
					}

					for (WebElement currentElement : textboxes) {
						FileWriter fstream = new FileWriter(parentPath + "/Forms/" + currentElement.getAttribute("name"));
						BufferedWriter out = new BufferedWriter(fstream);
					}
					for (WebElement currentElement : buttons) {
						System.out.println(currentElement.getAttribute("value"));
						result3 = new File(parentPath + "/Forms/" + currentElement.getAttribute("value")).mkdir();
					}
				}
				catch (Exception e) {
					
				}
			}
			catch (Exception e){//Catch exception if any
				System.err.println("Error: " + e.getMessage());
			}
		}
		return 0;
	}
	
    public int opendir_pre(String path, Fuse_file_info info)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("opendir_pre");
	System.out.println("   path = " + path);
	//info.printOut();
        return 0;
    }

    public int opendir_post(String path, Fuse_file_info info, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];
	String parentPath = path.split(theDirName)[0];

 	//if (path.equals(parentPath + ".ZZZZZ_BFS")) guiContext = 0;
	System.out.println("opendir_post");
	System.out.println("   path = " + path);
	System.out.println("   result = " + result);
	//info.printOut();
        return 0;
    }

    public int readdir_pre(String path, long buf, long filler, int offset, Fuse_file_info info)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("readdir_pre");
	System.out.println("   path = " + path);
	System.out.println("   buf = " + buf);
	System.out.println("   filler = " + filler);
	System.out.println("   offset = " + offset);
	//info.printOut();
        return 0;
    }

    public int readdir_post(String path, long buf, long filler, int offset, Fuse_file_info info, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("readdir_post");
	System.out.println("   path = " + path);
	System.out.println("   buf = " + buf);
	System.out.println("   filler = " + filler);
	System.out.println("   offset = " + offset);
	System.out.println("   result = " + result);
	//info.printOut();
        return 0;
    }

    public int releasedir_pre(String path, Fuse_file_info info)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("releasedir_pre");
	System.out.println("path = " + path);
        return 0;
    }

    public int releasedir_post(String path, Fuse_file_info info, int result)
    {
	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	System.out.println("releasedir_post");
	System.out.println("path = " + path);
	//guiContext--;
        return 0;
    }

    public int fsyncdir_pre(String path, int datasync, Fuse_file_info info)
    {
	System.out.println("fsyncdir_pre");
        return 0;
    }

    public int fsyncdir_post(String path, int datasync, Fuse_file_info info, int result)
    {
	System.out.println("fsyncdir_post");
        return 0;
    }

    public void init(Fuse_conn_info conn)
    {
	System.out.println("init");
    }

    public void destroy(long arg)
    {
	System.out.println("destroy");
    }

    public int access_pre(String path, int mode)
    {

	//System.out.println("Timer is running: " + guiTimer.isRunning());
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		//System.out.println("Timer is running: " + guiTimer.isRunning());
		return 0;
	}

	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];
	if (theDirName.startsWith("^")) return 0;  // Directory names that begin with a ^ symbol are NOT navigated to
	String parentPath = path.split(theDirName)[0];

	String theParentDirName = "";
	//String parentPath = "";
	String toNav = "";
	int currentDirLinkIndex;
	WebElement theForm;
	java.util.List <WebElement> inputs;
	java.util.List <WebElement> textboxes;
	java.util.List <WebElement> buttons;
	
	/*
	if (mode != 1) {
		guiContext = true;
		System.out.println("CONTEXT CHANGED!!");
	}
	else if (theDirName.equals(".ZZZZZ_BFS")) {
		guiContext = false;
		return 0;Context
	}
	*/
	
	//if (guiContext == 0) {
	if (theDirNameArray.length > 1) theParentDirName = theDirNameArray[theDirNameArray.length - 2];

	System.out.println("theDirName = " + theDirName);

	if (path.compareTo("/") != 0) {
		if (!theDirName.equals("Links") && !theDirName.equals("Forms") && !theDirName.equals("Images")) {
			System.out.println("theParentDirName = " + theParentDirName);
			// If you're in a Links directory...
			if (theParentDirName.equals("Links")) {
				System.out.println("It's links");
				//driver.findElement(By.tagName("html")).getText();
				java.util.List<WebElement> linkCollection = driver.findElements(By.tagName("a"));
				currentDirLinkIndex = Integer.parseInt(theDirName.substring(theDirName.length()-3), 10);
				//System.out.println("Navigating to: " + linkCollection.get(currentDirLinkIndex-1).getAttribute("href"));
				toNav = linkCollection.get(currentDirLinkIndex-1).getAttribute("href");
				if (toNav.startsWith("http://")) {
					toNav = toNav.substring(6, toNav.length());
					navigate(toNav, path, true, false);
				}
				else if (toNav.startsWith("https://")) {
					toNav = toNav.substring(7, toNav.length());
					navigate(toNav, path, true, true);
				}
				else {
					navigate(toNav, path, true, false);
				}
				System.out.println("Navigating to: " + toNav + " | with theDirName: " + theDirName);

			}
			/* Nothing changes if you're in images...
			// If you're in an Images directory...
			else if (theParentDirName.equals("Images")) {
				System.out.println("It's images");



			}
			*/
			else if (theParentDirName.equals("Forms")) {
				System.out.println("It's forms");
				
				textboxes = new LinkedList<WebElement>();
				buttons = new LinkedList<WebElement>();

				theForm = driver.findElement(By.tagName("form"));
				inputs = theForm.findElements(By.tagName("input"));
			
				for (WebElement currentElement : inputs) {
					if (currentElement.getAttribute("type").equals("text")) {
						textboxes.add(currentElement);
					}
					else if (currentElement.getAttribute("type").equals("submit")) {
						buttons.add(currentElement);
					}
				}
				//parentPath = path.split(theDirName)[0];
				for (WebElement currentElement : buttons) {
					if (currentElement.getAttribute("value").equals(theDirName)) {
						for (WebElement currentTextBox : textboxes) {
							System.out.println(getContents(new File(parentPath + currentTextBox.getAttribute("name"))));
							currentTextBox.sendKeys(getContents(new File(parentPath + currentTextBox.getAttribute("name"))));
						}
						currentElement.click();
						toNav = driver.getCurrentUrl();
						if (toNav.startsWith("http://")) {
							toNav = toNav.substring(6, toNav.length());
							navigate(toNav, path, false, false);
						}
						else if (toNav.startsWith("https://")) {
							toNav = toNav.substring(7, toNav.length());
							navigate(toNav, path, false, true);
						}
						else {
							navigate(toNav, path, false, false);
						}
						System.out.println("Navigating to: " + toNav + " | with theDirName: " + theDirName);

					}
				}

			}
			else navigate("/" + theDirName, path, true, false);
		}
	}
//	}
	
	System.out.println("access_pre");
	System.out.println("path = " + path);
	System.out.println("int mode = " + mode);
	
        return 0;
    }

  /**
  * Fetch the entire contents of a text file, and return it in a String.
  * This style of implementation does not throw Exceptions to the caller.
  *
  * @param aFile is a file which already exists and can be read.
  */
  static public String getContents(File aFile) {
    //...checks on aFile are elided
    StringBuilder contents = new StringBuilder();
    
    try {
      //use buffering, reading one line at a time
      //FileReader always assumes default encoding is OK!
      BufferedReader input =  new BufferedReader(new FileReader(aFile));
      try {
        String line = null; //not declared within while loop
        /*
        * readLine is a bit quirky :
        * it returns the content of a line MINUS the newline.
        * it returns null only for the END of the stream.
        * it returns an empty String if two newlines appear in a row.
        */
        while (( line = input.readLine()) != null){
	  input.readLine();
          contents.append(line);
          contents.append(System.getProperty("line.separator"));
        }
      }
      finally {
        input.close();
      }
    }
    catch (IOException ex){
      ex.printStackTrace();
    }
    
    return contents.toString();
  }


    public int access_post(String path, int mode, int result)
    {
	System.out.println("ACCESS");
//	if (guiTimer.isRunning()) System.out.println("Timer is running: ");
	if (isLocked) {
	guiTimer.cancel();
	guiTimer = new java.util.Timer();
	guiTimer.schedule( 
        new java.util.TimerTask() {
            @Override
            public void run() {  // Once the DELAY_TIME has expired, unlock the GUI lock
                isLocked = false;
		System.out.println("UNLOCKED! TIMER EXPIRED!");
            }
        }, 
        DELAY_TIME 
	);
		//guiTimer.start();
		return 0;
	}
	/*
	String[] theDirNameArray = path.split("/");
	String theDirName = theDirNameArray[theDirNameArray.length - 1];

	if (mode != 1) {
		guiContext = true;
		System.out.println("CONTEXT CHANGED!!");
	}
	else if (theDirName.equals(".ZZZZZ_BFS")) guiContext = false;
	*/
	System.out.println("access_post");
	System.out.println("path = " + path);
	System.out.println("int mode = " + mode);
        return 0;
    }

    public int create_pre(String path, int mode, Fuse_file_info info)
    {
	System.out.println("create_pre");
        return 0;
    }

    public int create_post(String path, int mode, Fuse_file_info info, int result)
    {
	System.out.println("create_post");
        return 0;
    }

    public int ftruncate_pre(String path, int length, Fuse_file_info info)
    {
	System.out.println("ftruncate_pre");
        return 0;
    }

    public int ftruncate_post(String path, int length, Fuse_file_info info, int result)
    {
	System.out.println("ftruncate_post");
        return 0;
    }

    public int fgetattr_pre(String path, Stat st, Fuse_file_info info)
    {
	System.out.println("fgetattr_pre");
        return 0;
    }

    public int fgetattr_post(String path, Stat st, Fuse_file_info info, int result)
    {
	System.out.println("fgettr_post");
        return 0;
    }

    /*
       public int lock_pre(String path, Fuse_file_info info, int cmd, struct flock *lock)
       {
       return 0;
       }

       public int lock_post(String path, Fuse_file_info info, int cmd, struct flock *lock, int result)
       {
       return 0;
       }

       public int utimens_pre(String path, const struct timespec tv[2])
       {
       return 0;
       }

       public int utimens_post(String path, const struct timespec tv[2], int result)
       {
       return 0;
       }

       public int bmap_pre(String path, int blocksize, uint64_t *idx)
       {
       return 0;
       }

       public int bmap_post(String path, int blocksize, uint64_t *idx, int result)
       {
       return 0;
       }
       */

    protected void finalize()
    {
	System.out.println("finalize");
    }
}
