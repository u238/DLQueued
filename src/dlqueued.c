#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <curl/curl.h>

#include "config.h"
#include "log.h"
#include "dlpart.h"
 
#define NUMT 4

 
/*
  List of URLs to fetch.
 
  If you intend to use a SSL-based protocol here you MUST setup the OpenSSL
  callback functions as described here:
 
  http://www.openssl.org/docs/crypto/threads.html#DESCRIPTION
 
*/ 
const char * const urls[NUMT]= {
  "http://curl.haxx.se/",
  "ftp://cool.haxx.se/",
  "http://www.contactor.se/",
  "www.haxx.se"
};
 
static void *pull_one_url(void *url)
{
  CURL *curl;
 
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, url);
  curl_easy_perform(curl); /* ignores error */ 
  curl_easy_cleanup(curl);
 
  return NULL;
}
 
 
/*
   int pthread_create(pthread_t *new_thread_ID,
   const pthread_attr_t *attr,
   void * (*start_func)(void *), void *arg);
*/ 

int main(int argc, char **argv)
{
  int numt = 0, fflag = 0;
  char * filename;
  int c;
  
  extern char *optarg;
  //extern int optind;
  //opterr = 0;
  
  while ((c = getopt(argc, argv, "t:f:")) != -1)
    switch (c)
    {
      case 't':
	numt = strtol(optarg, NULL, 10);
	break;
      case 'f':
	fflag = 1;
	filename = optarg;
	break;
      default:
	abort();
    }
    
  if (fflag == 0) {
    printlogf("[-] %s: missing -f option\n", argv[0]);
    
  }
  
  printlogf("[i] creating dlset download\n");
  
  char name[] = "Test Film";
  struct DLset * dlset = new_dlset(name, filename);
  
  printlogf("[i] printing dlset\n");
  
  dlset_toString(dlset);
  exit(0);
  
   pthread_t tid[NUMT];
   int i;
   int error;
 
  
  
  
  
  
  
  
  // Must initialize libcurl before any threads are started
  curl_global_init(CURL_GLOBAL_ALL);
  
  for(i=0; i< NUMT; i++) {
    error = pthread_create(&tid[i],
			   NULL, // default attributes please 
			   pull_one_url,
			   (void *)urls[i]);
    if(0 != error)
      fprintf(stderr, "Couldn't run thread number %d, errno %d\n", i, error);
    else
      fprintf(stderr, "Thread %d, gets %s\n", i, urls[i]);
  }
  
  /* now wait for all threads to terminate */ 
  for(i=0; i< NUMT; i++) {
    error = pthread_join(tid[i], NULL);
    fprintf(stderr, "Thread %d terminated\n", i);
  }
  
 
  return 0;
}