/*
 * This file implements functions for
 *  - handling of labels
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/msg.h"
#include "../inc/label.h"
#include "../inc/global.h"

/*
 * adds a label to the list
 * name: name of the label
 * address: address the label points to
 */
void label_add(char* name, int address) {
	// new element inserted
	label_t* newelement;
	// tail of list
	label_t* tail;

	// verbose message: added label (in second run)
	if (verbose) {
		char msg[64 + LABEL_MAX_NAME_LENGTH];
		char tmpname[LABEL_MAX_NAME_LENGTH];
		strncpy(tmpname, name, LABEL_MAX_NAME_LENGTH);
		sprintf(msg, "adding label '%s' at address '0x%08x'.", tmpname,
				address);
		yyverbose(msg);
	}

	// don't add labels in second run
	if (!isfirstrun) {
		return;
	}

	// check if label already exists
	if (label_absolute(name) != -1) {
		yyerror("label already exists.");
		return;
	}

	// allocate memory for new label
	newelement = malloc(sizeof(label_t));
	if (newelement == 0) {
		fprintf(stderr, "no free memory.");
		return;
	}

	// copy data to new label
	strncpy(newelement->name, name, LABEL_MAX_NAME_LENGTH);
	newelement->address = address;
	newelement->next = 0;

	// find tail of list
	if (label_listhead == 0) {
		// empty list, insert as list head
		label_listhead = newelement;

	} else {

		// list not empty find tail
		tail = label_listhead;
		while (tail->next != 0) {
			tail = tail->next;
		}

		// set next item pointer
		tail->next = newelement;
	}

	// output information to map file
	if (f_map) {
		fprintf(f_map, "0x%x: %s\n", newelement->address, newelement->name);
	}

}

/*
 * returns absolute address of a label
 * name: name of the label
 * return: absolute address of label or -1 if label not found
 */
int label_absolute(char* name) {
	// tail of search
	label_t* tail;

	if (label_listhead == 0) {
		// if empty list, label is not in list, return -1
		return -1;

	} else {
		// list not empty find tail

		// start search at list head
		tail = label_listhead;

		while (1) {

			if (strcmp(tail->name, name) == 0) {
				// name of search tail matches searched name

				// return address
				return tail->address;
			}

			if (tail->next != 0) {
				// end of list not reached, update tail pointer
				tail = tail->next;

			} else {
				// end of list, not found

				if (!isfirstrun) { // second run: label must be found.
					yyerror("label not found.");
				}

				// return -1, as label is not found
				return -1;
			}
		}
	}

	// program does not reach this point due to earlier returns
}

/*
 * returns relative address of a label
 * name: name of the label
 * return: relative address of label or -1 if label not found
 */
int label_relative(char* name) {
	// absolute address of label
	int absolute;

	// find absolute address
	absolute = label_absolute(name);

	if (absolute > 0) {
		// label found, calculate relative address
		return (absolute - address) / 2 - 1;
	} else {
		// label not found, error message already  prompted in label_absolute
		return -1;
	}
}

/*
 * frees the allocated space used for the list of labels
 */
void label_free() {
	// current element pointer
	label_t* ptr;
	// next element pointer
	label_t* next;

	// start at list head
	ptr = label_listhead;

	while (ptr != 0) {
		// walk through list until end of list reached

		// store next pointer
		next = ptr->next;
		// delete current item
		free(ptr);
		// proceed in list
		ptr = next;
	}

	// reset list head
	label_listhead = 0;
}
