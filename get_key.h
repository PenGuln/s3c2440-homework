#ifndef GET_KEY_H
#define GET_KEY_H


int   kbd_init();
int   kbd_close();
char  get_key(void);
char*   get_line_key(char *cmd);


#endif // GET_KEY_H
