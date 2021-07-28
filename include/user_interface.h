#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H

void init_ui(void);
bool loop_vocabs_ui(void);
void cleanup_ui(void);
void get_user_passwd(char *user, char *pass);
void get_voclst(char *list_id_str);

#endif
