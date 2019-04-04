/*
 * This file declares functions for
 *  - checking instruction parameters for range
 */

#ifndef MSG_H_
#define MSG_H_

/*
 * verbose output (if flag is set)
 * msg: verbose message
 */
void yyverbose(char* msg);

/*
 * error handler
 * msg: error message
 */
void yyerror(char* msg);

#endif /* MSG_H_ */
