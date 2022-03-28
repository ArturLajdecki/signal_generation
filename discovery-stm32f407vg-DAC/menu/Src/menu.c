/*
 * ui_functions.c
 *
 *  Created on: May 18, 2021
 *      Author: Artur
 */

#include <menu.h>
#include <system.h>

static const  struct menuitem *currMenuPtr = &menu_link;   //Bie¿¹ca pozycja menu
static int8_t menuindex;                                    //Numer aktualnie wybrane pozycji menu
static int8_t menufirstpos;                                 //Numer pozycji menu wyœwietlanej w górnym rzêdzie

uint8_t Menu_GetMenuItemsNo()            //Policz ile dane menu ma pozycji
{
	const struct menuitem *tmpmenuitem=currMenuPtr;
	uint8_t index=0;

	while(tmpmenuitem)
	{
		tmpmenuitem=tmpmenuitem->next;
		index++;
	}
	return index;
}

const struct menuitem *Menu_GetMenuItem(uint8_t index)
{
	const struct menuitem *tmpmenuitem=currMenuPtr;

	while((tmpmenuitem) && (index>0)) {
	 tmpmenuitem=tmpmenuitem->next;
	 index--;
	}
	return tmpmenuitem;
}

uint8_t Menu_GetMenuRows()
{
	return 5;
}

void Menu_Show()
{
	const struct menuitem *tmpmenuitem=Menu_GetMenuItem(menufirstpos);
	uint8_t menuitemsno=Menu_GetMenuItemsNo();

	//UG_FillFrame(0, 10+(i*10), UG_GetXDim(), (gui1.font.char_height)+(10+(i*10)), C_BLACK);
	for(uint8_t i=0; i < Menu_GetMenuRows(); i++) {
		if(menuindex == ((menufirstpos + i) % menuitemsno)) {
			UG_FillFrame(0, 10+(i*10), UG_GetXDim(), (gui1.font.char_height)+(10+(i*10)), C_BLUE);
			UG_PutString( 2, 10+(i*10), ">" );
		}
		else {
			UG_FillFrame(0, 10+(i*10), UG_GetXDim(), (gui1.font.char_height)+(10+(i*10)), C_BLACK);
			UG_PutString( 2, 10+(i*10), " " );  //Dana pozycja menu jest zaznaczona
		}

		UG_PutString( 30, 10+(i*10), tmpmenuitem->text); //Wyœwietl pozycjê menu

		if(tmpmenuitem->submenu) {
			UG_PutString( 2, 10+(i*10), "*"); //Zaznacz, ze mamy submenu
		}

		tmpmenuitem = tmpmenuitem->next;

		if(tmpmenuitem == NULL)  //Koniec listy
		{
			if(Menu_GetMenuItemsNo() > Menu_GetMenuRows()){
				tmpmenuitem=currMenuPtr; //Zawijamy listê jeœli jest d³u¿sza ni¿ liczba wyœwietlanych pozycji
			}
			else {
				break;   //lub koñczymy, ¿eby unikn¹æ powtarzania elementów
			}
		}
	}
}

void Menu_SelectNext()
{
	uint8_t no = Menu_GetMenuItemsNo();
	menuindex++;
	if(no > Menu_GetMenuRows())        //Czy liczba pozycji menu jest wiêksza ni¿ liczba wyœwietlanych pozycji?
		{
			int8_t dist;               //Odleg³oœæ pomiêdzy pierwsz¹ wyœwietlan¹ pozycj¹, a pozycj¹ podœwietlon¹
			if(menuindex < menufirstpos) dist = no - menufirstpos + menuindex; //Jest zale¿na od tego, któa z pozycji jest wiêksza
			   else dist=menuindex-menufirstpos;
			if(dist >= Menu_GetMenuRows()) menufirstpos++;  //Koniec ekranu, trzeba przewijaæ
		}

	menuindex %= no;     //Liczymy wszysko modulo liczba pozycji w menu
	menufirstpos %= no;
	Menu_Show();      //Wyœwietl menu
}

void Menu_SelectPrev()
{
	if(menuindex > 0)
	{
		if(menuindex == menufirstpos) menufirstpos--;
		menuindex--;               //Poprzedni element
	}
	 else
	{
		if(menufirstpos == 0)
		{
			menuindex=Menu_GetMenuItemsNo()-1;  //Zawijamy menu
			if(Menu_GetMenuItemsNo()>Menu_GetMenuRows()) menufirstpos = menuindex;  //Jezeli mamy mniej pozycji menu niz linii na LCD to nie zmieniamy numeru pierwszej pozycji menu
		} else menuindex = Menu_GetMenuItemsNo()-1;
	}
	Menu_Show();     //Wyswietl menu
}

void Menu_Back()
{
	menufirstpos = 0;
	menuindex = 0;
	currMenuPtr = currMenuPtr->parent;
}

void Menu_Click()
{
  const struct menuitem *tmpmenuitem = Menu_GetMenuItem(menuindex);
  const struct menuitem *submenu = tmpmenuitem->submenu;

  menuitemfuncptr mfptr = tmpmenuitem->menuitemfunc;
  if(mfptr) (*mfptr)();
  if(submenu) {
	  currMenuPtr = submenu;
	  menuindex = 0;
	  menufirstpos = 0;
   }
  UG_FillScreen( C_BLACK );
  Menu_Show();
}

void GUI_init(void) {

  /* -------------------------------------------------------------------------------- */
  /* Define µGUI structure (ST7735 128x160)                              			  */
  /* -------------------------------------------------------------------------------- */
  UG_Init(&gui1,(void(*)(UG_S16,UG_S16,UG_COLOR))ST7735_DrawPixel,ST7735_HEIGHT,ST7735_WIDTH);
  /* Clear Screen */
  UG_FillScreen( C_BLACK );
  UG_FontSelect ( &FONT_6X8 ) ;UG_SetBackcolor ( C_BLACK ) ;UG_SetForecolor ( C_CYAN ) ;
//  /* -------------------------------------------------------------------------------- */
//  /* Create window_1 structure                                                     			  */
//  /* -------------------------------------------------------------------------------- */
//  UG_WindowCreate( &window_1, obj_buff_wnd_1, MAX_OBJECTS, window_1_callback );
//  UG_WindowResize(&window_1, 2, 3, 159, 30);
//  UG_WindowSetTitleHeight ( &window_1, 12 );
//  UG_WindowSetTitleText( &window_1, "Sine frequency" );
//  UG_WindowSetTitleTextFont( &window_1, &FONT_4X6 );
//
//  UG_WindowSetTitleColor(&window_1, C_BLACK);
//  UG_WindowSetTitleTextColor(&window_1, C_WHITE );
//
//  UG_WindowSetForeColor(&window_1, C_WHITE );
//  UG_WindowSetBackColor(&window_1, C_WHITE);
//
//  UG_WindowSetTitleInactiveTextColor(&window_1, C_WHITE);
//
//  /* Define 7 Buttons */
//  uint8_t window_1_width = UG_WindowGetInnerWidth(&window_1);
//  uint8_t window_1_buton_width = (window_1_width/window_1_button_no);
//  uint8_t decimal = 2;
//  for (int i = 0; i <= window_1_button_no; i++) {
//	  if(i < (window_1_button_no-decimal)) {
//		  UG_ButtonCreate( &window_1, &window_1_button[i], i, (window_1_buton_width*i), 1,
//				  ((window_1_buton_width)*i)+((window_1_buton_width))-1, UG_WindowGetInnerHeight(&window_1) - 2 );
//	  }
//	  else {
//		  UG_ButtonCreate( &window_1, &window_1_button[i], i, 3 + (window_1_buton_width*i), 1,
//		 				  2 + ((window_1_buton_width)*i)+((window_1_buton_width)), UG_WindowGetInnerHeight(&window_1) - 2 );
//	  }
//  }
//
//  /* Configure 7 buttons */
//  for (int i = 0; i <= 8; i++) {
//	  UG_ButtonSetFont( &window_1, i, &FONT_4X6 );
//	  UG_ButtonSetBackColor( &window_1, i, C_BLACK );
//	  UG_ButtonSetText( &window_1, i, "9" );
//    }
//
////  /* -------------------------------------------------------------------------------- */
////  /* Create Window 2 structure */
////  /* -------------------------------------------------------------------------------- */
////
//    UG_WindowCreate( &window_2, obj_buff_wnd_2, MAX_OBJECTS, window_2_callback );
//    UG_WindowResize(&window_2, 2, 33, 159, 63);
//    UG_WindowSetTitleHeight ( &window_2, 12 );
//    UG_WindowSetTitleText( &window_2, "Sine amplitude" );
//    UG_WindowSetTitleTextFont( &window_2, &FONT_4X6 );
//
//    UG_WindowSetTitleColor(&window_2, C_BLACK);
//    UG_WindowSetTitleTextColor(&window_2, C_WHITE );
//
//    UG_WindowSetForeColor(&window_2, C_WHITE );
//    UG_WindowSetBackColor(&window_2, C_WHITE);
//
//    UG_WindowSetTitleInactiveTextColor(&window_2, C_WHITE);
//
//    /* Define 4 Buttons */
//    uint8_t window_2_width = UG_WindowGetInnerWidth(&window_2);
//    uint8_t window_2_buton_width = (window_2_width/window_2_button_no);
//    uint8_t windows_2_decimal = 2;
//    for (int i = 0; i <= window_2_button_no; i++) {
//  	  if(i < (window_2_button_no - windows_2_decimal)) {
//  		  UG_ButtonCreate( &window_2, &window_2_button[i], i, (window_2_buton_width*i), 1,
//  				  ((window_2_buton_width)*i)+((window_2_buton_width)), UG_WindowGetInnerHeight(&window_2) - 2 );
//  	  }
//  	  else {
//  		  UG_ButtonCreate( &window_2, &window_2_button[i], i, 3 + (window_2_buton_width*i), 1,
//  		 				  2 + ((window_2_buton_width)*i)+((window_2_buton_width)), UG_WindowGetInnerHeight(&window_2) - 2 );
//  	  }
//    }
//
//    /* Configure 7 buttons */
//    for (int i = 0; i <= 8; i++) {
//  	  UG_ButtonSetFont( &window_2, i, &FONT_4X6 );
//  	  UG_ButtonSetBackColor( &window_2, i, C_BLACK );
//  	  UG_ButtonSetText( &window_2, i, "9" );
//      }
//
//  /* -------------------------------------------------------------------------------- */
//  /* Start demo application                                                           */
//  /* -------------------------------------------------------------------------------- */
//  /* Show Window 1 */
//  UG_WindowShow( &window_1 );
//  UG_Update();
//  UG_WindowShow( &window_2 );
//  UG_Update();
}


void window_1_callback( UG_MESSAGE* msg )
{
   if ( msg->type == MSG_TYPE_OBJECT )
   {
      if ( msg->id == OBJ_TYPE_BUTTON )
      {
         switch( msg->sub_id )
         {
            case BTN_ID_0:
            {

               break;
            }
            case BTN_ID_1:
            {

               break;
            }
            case BTN_ID_2:
            {
               break;
            }
            case BTN_ID_3:
            {

            }
            case BTN_ID_4:
            {
               break;
            }
            case BTN_ID_5:
            {

               break;
            }
         }
      }
   }
}


void window_2_callback( UG_MESSAGE* msg )
{
   if ( msg->type == MSG_TYPE_OBJECT )
   {
      if ( msg->id == OBJ_TYPE_BUTTON )
      {
         switch( msg->sub_id )
         {
            case BTN_ID_0:
            {

               break;
            }
         }
      }
   }
}


void window_3_callback( UG_MESSAGE* msg )
{
   if ( msg->type == MSG_TYPE_OBJECT )
   {
      if ( msg->id == OBJ_TYPE_BUTTON )
      {
         switch( msg->sub_id )
         {
            case BTN_ID_0:
            {

               break;
            }
         }
      }
   }
}
