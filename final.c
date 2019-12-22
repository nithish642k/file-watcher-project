#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <linux/inotify.h>
#include <unistd.h>
#include <sys/stat.h>
#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
int main( )
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[EVENT_BUF_LEN];
  fd = inotify_init();
  if ( fd < 0 ) {
    perror( "inotify_init" );
  }
  wd = inotify_add_watch( fd, "/home/hp-3564/project", IN_CREATE | IN_DELETE | IN_CLOSE_WRITE | IN_MOVED_FROM | IN_MOVED_TO); //give the location of the directory to be watched here
  length = read( fd, buffer, EVENT_BUF_LEN );
  if ( length < 0 ) {
    perror( "read" );
  }
  while ( i < length ) {
	  struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
	  if ( event->len ) {
      if ( event->mask & IN_CREATE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "New directory %s created.\n", event->name );
	  system("./a.out");
        }
        else
      {
          printf( "New file %s created.\n", event->name );
	  system("./a.out");
      }
      }
      else if ( event->mask & IN_DELETE ) {
        if ( event->mask & IN_ISDIR ) {
          printf( "Directory %s deleted.\n", event->name );
	  system("./a.out");
        }
        else {
          printf( "File %s deleted.\n", event->name);
	  system("./a.out");
        }
      }

            else if(event->mask & IN_CLOSE_WRITE)
      {
              if(event->mask & IN_ISDIR)
              {
                      printf("Directory %s modified.\n",event->name);
		      system("./a.out");
              }
              else
              {
                      printf("File %s modified.\n",event->name);
		      system("./a.out");
              }
    }
	                else if(event->mask & IN_MOVED_FROM)
      {
              if(event->mask & IN_ISDIR)
              {
                      printf("Directory %s moved out of watch directory.\n",event->name);
		      system("./a.out");
              }
              else
              {
                      printf("File %s moved out of watch directory.\n",event->name);
		      system("./a.out");
              }
    }
            else if(event->mask & IN_MOVED_TO)
      {
              if(event->mask & IN_ISDIR)
              {
                      printf("Directory %s moved to watch directory.\n",event->name);
		      system("./a.out");

              }
              else
              {
                      printf("File %s moved to watch directory.\n",event->name);
		      system("./a.out");
              }
    }

  }
    i += EVENT_SIZE + event->len;
  }
   inotify_rm_watch( fd, wd );
   close( fd );

}
