/* file: minunit.h */

#ifndef MINUNIT_H
#define MINUNIT_H

#define mu_assert(message, test) if (!(test)) return message;
#define mu_run_test(test) char *message = test(); tests_run++; if (message) return message;
extern int tests_run;

#endif
