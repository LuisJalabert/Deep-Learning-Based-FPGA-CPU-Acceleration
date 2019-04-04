/*
 * This file declares functions and declares variables for
 *  - handling of labels
 * and defines constants, types.
 */

#ifndef LABEL_H_
#define LABEL_H_

// maximum length of label names
#define LABEL_MAX_NAME_LENGTH (64)

// struct of a label item in list
typedef struct {
	// name of the label
	char name[LABEL_MAX_NAME_LENGTH];
	// address the label points to
	int address;
	// next item in list
	void* next;
} label_t;
// head of list
label_t* label_listhead;

/*
 * adds a label to the list
 * name: name of the label
 * address: address the label points to
 */
void label_add(char* name, int address);

/*
 * returns absolute address of a label
 * name: name of the label
 * return: absolute address of label or -1 if label not found
 */
int label_absolute(char* name);

/*
 * returns relative address of a label
 * name: name of the label
 * return: relative address of label or -1 if label not found
 */
int label_relative(char* name);

/*
 * frees the allocated space used for the list of labels
 */
void label_free();

#endif /* LABEL_H_ */
