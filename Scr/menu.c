  #include "menu.h"
  #include "buttons.h"
  #include "un_drebezg.h"
  #include "modbus.h" 
  #include "led_digit.h" 

  uint8_t   stmenu        = MAIN_MENU_UI,                      
            KodKey,
            kursor        = 0,
            flmenu        = 0,
            current_menu  = 0;
  uint16_t  delaykey      = 3000,
	    cdelkey       = 0,
            tentmenu      = 0;
			
  //_selection SELECTION;
  
  void print_menu(void);
  void fprmenu(void);
  void (*pStateFunc)(void);	
  
   SELECTION menu_[]   = {fprmenu, NOALM, (uint8_t *)&D_pc.ModBUS_rw_reg[T_MAX], NONDT, DTNO}; //Punkt 1
	
   SELECTION menu_m0[] = {fprmenu, NOALM, (uint8_t *)&D_pc.ModBUS_rw_reg[T_MIN], NONDT, DTNO}; //Punkt 1
	   
   SELECTION menu_m1[] = {fprmenu, NOALM, NODAT, NONDT, DTNO}; //Punkt 1	    	  
	   
  //Главный массив хранит в себе все меню/подменю
  //Все меню/подменю должны описываться в таком же порядке как и в   enum __menu__id ...
  MENU  menu_all[SIZE_MENU] = {
						{ 0, 0, menu_ },					//0
						{ 0, 0, menu_m0 },				//1
						{ 0, 0, menu_m1 },				//2
					 },
   *menu;

void mstate_menu(void)
{
  if (stmenu >= MAIN_MENU_UI)
  {	       	       
       KodKey = 0;
       if (cdelkey >= delaykey) 
       {
          cdelkey   = 0;	            
                if (	!(Test_IN_0.fin & (1 << ENT_UP))
		    &&  !(Test_IN_0.fin & (1 << ESC_DOWN)) )
		{
			
			//KodKey = K_BOTH;
			BUT_Check(1, K_BOTH);
		}
		else {
			BUT_Check(0, K_BOTH);
		}

		if (Test_IN_0.fin & (1 << ESC_DOWN))
		{       
			BUT_Check(0, K_ESC);
		}
		else {
				BUT_Check(1, K_ESC);
			 }
		if (Test_IN_0.fin & (1 << ENT_UP))
		{
			BUT_Check(0, K_ENT_UP);
		}
		else {
				BUT_Check(1, K_ENT_UP);
			 }
                
                if (stateBut[K_BOTH-1] & (FLAG_BUT_PRESSED))					 
                {
                        KodKey = K_BOTH;
                }
                else if (stateBut[K_ENT_UP-1] & (FLAG_BUT_PRESSED))
                {
                    KodKey = K_ENT_UP;
                }
                else if (stateBut[K_ESC-1] & (FLAG_BUT_PRESSED))
                {
                    KodKey = K_ESC;
		}

                if ( (stateBut[KodKey-1] & (FLAG_BUT_PRESSED)) && KodKey)					 
                {
                        delaykey  = 200;
                }
                else if ( (stateBut[KodKey-1] & (FLAG_BUT_HOLD)) && KodKey)					 
                {
                    delaykey  = 0;
                }
                else
                {
                        delaykey  = 10;
                }
	   }

			 
        if(     (stmenu == MAIN_MENU_UI)
            &&  (KodKey == K_BOTH)   )
        {
            flmenu |= (1 << 0);
        //      if(tentmenu > 1000 && (flmenu & (1 << F_KEY_PAD)))
        //      {
                delaykey                = 2000;
                flmenu                 &= ~(1 << F_DATA_EDIT | 1 << F_MENU_EDIT);
				flmenu				   |= (1 << F_MENU_REDRAW);
                stmenu                  = MAIN_PASS;
                kursor                  = 0;
                current_menu            = 0;
                KodKey                  = 10;
                cdelkey                 = 0;
                print_menu();
        //      }
        }
           
		if (stmenu == MAIN_PASS)
		{
              
				 /*   if(    (KodKey==UP || KodKey==DOWN)
					   && !(D_pc.ModBUS_rbit[F_01]&(1<<F_MENU_EDIT)))
					{
						Lcd_Putc_Buffer(0x80,0+20*kursor,NORUS);
						*/		            
			switch (KodKey) 
			{
						case K_ENT_UP:                                                        
								if(   !(flmenu & (1 << F_MENU_EDIT)) )
								{
									if (++current_menu >= SIZE_MENU)
									{
										current_menu = 0;
									}
									flmenu |= (1 << F_MENU_REDRAW);
								}
								break;
						case K_ESC:
							if( !(flmenu & (1 << F_MENU_EDIT)) )
							{
								if (current_menu == 0)
								{
                                                                        udate_str("    ", 0);
									flled &= ~(1 << UPD_H0);  
									stmenu = MAIN_MENU_UI;								
								}
					/*			else {
									current_menu--;
									kursor = 0;
									flmenu |= (1 << F_MENU_REDRAW);
								}								
					*/			
							}
							else {
								if (flmenu & (1 << F_DATA_EDIT))
								{
									flmenu &= ~(1 << F_DATA_EDIT);
								}
								else {
										flmenu &= ~(1 << F_MENU_EDIT);
									 }	
							}						
								 break;
						case K_BOTH:
								 if (!(flmenu & (1 << F_MENU_EDIT)))
								 {
									 flled &= ~(1 << UPD_H0);
									 udate_str("---", 0);
									 if(    menu[current_menu].m[0].function
										&&  menu[current_menu].m[0].ndat != NONDT)
									 {
										 //Lcd_Puts_Buffer("!",0+20*kursor,RUS);
																			 flled &= ~(1 << UPD_H0); 
																			 udate_str("---", 0); 
										 flmenu |= 1 << F_MENU_EDIT;
										 break;
									 }
								 }							 							 
						break;							 
							default:
									break;
			}//switch

			if (KodKey)
			{
				print_menu();
			}
		}
	}
}


void print_menu(void) 
{
    if (!(flmenu & (1 << F_MENU_EDIT)))
    {
        if (flmenu & (1 << F_MENU_REDRAW))
        {			 			
          flled |= (1 << UPD_H0);
           udate_str("p   ", 0);       //udate_str_flash(menu[current_menu].mas);
           psym  = 2;
            tdled = current_menu;
             div_date(); 
				    //flled |= (1 << UPD_CALC);
            flmenu &= ~(1 << F_MENU_REDRAW);
	}
    }
    else //MenuEdit == On
        {            			  
			pStateFunc = menu[current_menu].m[0].function;
            if (pStateFunc) pStateFunc();                    
         }
}

void fprmenu(void)
{
	static uint8_t kmax = 0;
	static uint16_t dat = 0;
			
    if((KodKey == K_BOTH) && (flmenu & (1 << F_MENU_EDIT)))
    {
        if(!(flmenu & (1 << F_DATA_EDIT)))
        {		   
		   dat = *(uint16_t*)menu[current_menu].m[0].fdat;
		   tdled = dat;			   
		   div_date();	
			kmax = 3;
			if(dat > 9999) kmax = 5;
			else if (dat > 999) kmax = 4;            
            flmenu |= (1 << F_DATA_EDIT);		
        }       
    }

    if (KodKey == K_ENT_UP) 
    {
		if (flmenu & (1 << F_DATA_EDIT))
		{
		}
		else {
				if (++kursor > kmax)
				{
					kursor = 0;
				}
		}
    }

    if (KodKey == K_ESC && (flmenu & (1 << F_DATA_EDIT)))
    {
        //if
    }
}