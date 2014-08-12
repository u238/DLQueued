#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dlpart.h"
#include "config.h"
#include "log.h"

struct DLpart * new_dlpart() {
  struct DLpart * dlpart;
  // calloc already setmems all to zero
  dlpart = calloc(1, sizeof(struct DLpart));
  return dlpart;
}

/*
 * add a DLpart to a DLset
 * the DLpart should already be allocated!!
 */
struct DLpart * dlpart_addDlpart(struct DLpart * dlpart_dest, struct DLpart * dlpart) {
  struct DLpart * dlpart_pointer = dlpart_dest;
  
  // special case if destination is NULL
  if (dlpart_dest == NULL) {
#ifdef __DEBUG
    printlogf("[+] dlparts_dest is null,returning dlpart pointer (0x%x)\n", dlpart);
#endif
    return dlpart;
  }
  
  do {
    if (dlpart_pointer->next == NULL) {
      dlpart_pointer->next = dlpart;
#ifdef __DEBUG
      printlogf("[+] setting pointer->next to dlpart (0x%x)\n", dlpart);
#endif
    }
#ifdef __DEBUG
    else {
      printlogf("[i] pointer->next not NULL (0x%x)\n", dlpart);
    }
#endif
  } while ((dlpart_pointer = dlpart_pointer->next) != NULL);
  
  return dlpart_dest;
}

struct DLpart * alloc_dlparts(char * filename) {
  // allocate new object
  struct DLpart * dlparts = NULL;

#ifdef __DEBUG
  printlogf("[i] opening file '%s' for reading..\n", filename);
#endif  
  // open file for reading
  FILE * fp;
  fp = fopen(filename, "r");
  if (fp == NULL) {
      printlogf("[-] Unable to open '%s' for reading.\n", filename);
      return NULL;
  }
  
#ifdef __DEBUG
  printlogf("[i] reading '%s'..\n", filename);
#endif  
  // create a dlpart for each line
  char * url_str;
  while (fscanf(fp, "%ms\n", &url_str) == 1) {
    struct DLpart * dlpart = new_dlpart();
    dlpart->url = url_str;
    
    // add dlpart to DLset
    dlparts = dlpart_addDlpart(dlparts, dlpart);
#ifdef __DEBUG
    printlogf("[i] added new dlpart (url:%s) to dlparts (0x%x)\n", url_str, dlparts);
#endif
  }
  
#ifdef __DEBUG
  printlogf("[+] finished adding to dlset\n", url_str);
#endif
  fclose(fp);
  
  return dlparts;
}


struct DLset * new_dlset(char * name, char * filename) {
  // allocate new dlset
  struct DLset * dlset;
  dlset = calloc(1, sizeof(struct DLset));
  
  // extract name from filename:
  dlset->name = strdup(name);
  
  // allocate dlparts
  dlset->dlparts = alloc_dlparts(filename);
  
  return dlset;
}


/*
 * returns the first dlpart that is not already in downloading state
 */
struct DLpart * dlset_getNextDlpart(struct DLset * dlset) {
  struct DLpart * dlpart_pointer = dlset->dlparts;
  
  // special case if no dlparts are defined
  if (dlpart_pointer == NULL)
    return NULL;
  
  do {
    if (!dlpart_pointer->downloading)
      return dlpart_pointer;
  } while ((dlpart_pointer = dlpart_pointer->next));
  
  return NULL;
}

int dlset_toString(struct DLset * dlset) {
  printlogf("DLSET: name: %s\n", dlset->name);
  
  struct DLpart * dlpart_pointer = dlset->dlparts;
  
  if (dlpart_pointer)
    do {
      printlogf("part:%s\n", dlpart_pointer->url);
    }
    while ((dlpart_pointer = dlpart_pointer->next));
    
  return 0;
}