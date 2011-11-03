. ./build.conf

LD_LIBRARY_PATH=build:$JDK_HOME/jre/lib/i386/server ./javafuse -f -o big_writes -o auto_cache -Cbrowsefs/BrowseFS:browsefs/selenium-server-standalone-2.7.0.jar -Ffs/browsefs/browsefs.config BrowseFS_Mount/
