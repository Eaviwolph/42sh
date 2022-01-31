#ifndef TOKEN_H
#define TOKEN_H

struct dtoken *readlines(int fd);
struct dtoken *str_to_dtoken(struct dtoken *d, char *s, char *quoted);

#endif