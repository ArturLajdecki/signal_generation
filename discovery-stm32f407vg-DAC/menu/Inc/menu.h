/*
 * Copyright (c) 2021 Artur Lajdecki
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of Application.
 *
 * Author:          Artur Lajdecki <249116@student.pwr.edu.pl>
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

/* Include headers */
#include <ugui.h>

/* -------------------------------------------------------------------------------- */
/* Declare new µGUI structure */
/* -------------------------------------------------------------------------------- */
UG_GUI gui1;

/* -------------------------------------------------------------------------------- */
/* Declare new µGUI structure */
/* -------------------------------------------------------------------------------- */
#define MAX_OBJECTS        10
#define window_1_button_no 7
#define window_2_button_no 7
#define window_3_button_no 7
#define window_4_button_no 7

/* Sine frequency */
UG_WINDOW window_1;
UG_OBJECT obj_buff_wnd_1[MAX_OBJECTS];
UG_BUTTON window_1_button[window_1_button_no];

/* Sine amplitude */
UG_WINDOW window_2;
UG_OBJECT obj_buff_wnd_2[MAX_OBJECTS];
UG_BUTTON window_2_button[window_2_button_no];

/* Ramp frequency */
UG_WINDOW window_3;
UG_OBJECT obj_buff_wnd_3[MAX_OBJECTS];
UG_BUTTON window_3_button[window_3_button_no];

/* Ramp amplitude */
UG_WINDOW window_4;
UG_OBJECT obj_buff_wnd_4[MAX_OBJECTS];
UG_BUTTON window_4_button[window_4_button_no];


typedef void (*menuitemfuncptr)();

struct menuitem
{
	char *text;          //Nazwa pozycji menu
	menuitemfuncptr menuitemfunc;       //Funkcja callback zwiazana z pozycja menu
	const struct menuitem *parent;      //Obiekt - rodzic
	const struct menuitem *submenu;     //Podmenu, lub NULL jesli nie ma
	const struct menuitem *next;        //Kolejna pozycja lub NULL jesli nie ma
};

void Menu_Show();
void Menu_SelectNext();
void Menu_SelectPrev();
void Menu_Click();
void Menu_Back();

extern const struct menuitem menu_link;                 //Struktura menu


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/* Function prototypes, name aligned, lowercase names */
void GUI_init(void);
void window_1_callback( UG_MESSAGE* msg );
void window_2_callback( UG_MESSAGE* msg );
void window_3_callback( UG_MESSAGE* msg );
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* INC_MENU_H_ */

