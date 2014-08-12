#ifndef __DLPART_H__
#define __DLPART_H__

struct DLpart {
  char * url;
  char * filename;
  short unsigned int downloading; // is set to 1 when we start downloading
  struct DLpart * next;
};

struct DLset {
  char * name;
  struct DLpart * dlparts;
};

struct DLset * new_dlset(char * name, char * filename);
struct DLpart * dlset_getNextDlpart(struct DLset * dlset);
int dlset_toString(struct DLset * dlset);

#endif