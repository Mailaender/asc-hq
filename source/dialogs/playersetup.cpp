/*
     This file is part of Advanced Strategic Command; http://www.asc-hq.de
     Copyright (C) 1994-1999  Martin Bickel  and  Marc Schellenberger
 
     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.
 
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
 
     You should have received a copy of the GNU General Public License
     along with this program; see the file COPYING. If not, write to the 
     Free Software Foundation, Inc., 59 Temple Place, Suite 330, 
     Boston, MA  02111-1307  USA
*/


#include <sstream>
#include <pgimage.h>

#include "playersetup.h"






PlayerSetupWidget::PlayerSetupWidget( tmap* gamemap, Mode mode, PG_Widget *parent, const PG_Rect &r, const std::string &style ) : PG_ScrollWidget( parent, r, style ) , actmap ( gamemap )
{
   this->mode = mode;
   
   int counter = 0; 
   for ( int i = 0; i < actmap->getPlayerCount(); ++i ) 
      if ( actmap->player[i].exist() ) {
      
         PlayerWidgets pw;
         pw.pos  = i;
         
         int y = 20 + counter * spacing;
         
         ColoredBar* colbar = new ColoredBar( actmap->player[i].getColor(), this, PG_Rect( 20, y, Width() - 60, 30 ));
         colbar->SetTransparency( 128 );
         
         
         int y1 = Width() * 4 / 10;
         
         pw.name = new PG_LineEdit( colbar, PG_Rect( 40, 5, y1 - 40, 20 ));
         pw.name->SetText( actmap->player[i].getName());
         
         
         PG_Rect r = PG_Rect( y1 + 20, 5, colbar->Width() - y1 - 40, 20 );
         if ( mode != SelfEditable  || actmap->actplayer == i ) {
            pw.type = new PG_DropDown( colbar, r);
            
            int pos = 0;
            while ( tmap :: Player :: playerStatusNames[pos] ) {
               pw.type->AddItem( tmap :: Player :: playerStatusNames[pos] );
               ++pos;
            }
            
            pw.type->SelectItem( actmap->player[i].stat );
            pw.type->SetEditable(false);
         } else {
            pw.name->SetEditable( false );
            pw.type = NULL;
            PG_LineEdit* le = new PG_LineEdit( colbar, r );
            le->SetText( tmap :: Player :: playerStatusNames[ actmap->player[i].stat ] );
            le->SetEditable( false );
         }
         
         PG_ThemeWidget* col = new PG_ThemeWidget( colbar, PG_Rect( 5, 5, 20, 20 ));
         col->SetSimpleBackground(true);
         col->SetBackgroundColor ( actmap->player[i].getColor());
         col->SetBorderSize(0);

         playerWidgets.push_back( pw );
                        
         ++counter;
      } else
         actmap->player[i].stat = Player::off;
      
   SetTransparency(255);
};

bool PlayerSetupWidget::Valid() {
   if ( mode == AllEditableSinglePlayer ) {
      int humanNum = 0;
      for ( vector<PlayerWidgets>::iterator i = playerWidgets.begin(); i != playerWidgets.end(); ++i ) 
         if ( i->type )
            if (    Player::tplayerstat( i->type->GetSelectedItemIndex()) == Player::human
                 || Player::tplayerstat( i->type->GetSelectedItemIndex()) == Player::supervisor
                 || Player::tplayerstat( i->type->GetSelectedItemIndex()) == Player::suspended  ) 
               ++humanNum;
               
       if ( humanNum > 1 ) {
         MessagingHub::Instance().error("Only a single human player allowed in SinglePlayer mode allowed!");
         return false;
       }
   }
   return true;
}


bool PlayerSetupWidget::Apply() {
   if ( !Valid() )
      return false;
      
   for ( vector<PlayerWidgets>::iterator i = playerWidgets.begin(); i != playerWidgets.end(); ++i ) {
      actmap->player[i->pos].setName( i->name->GetText() );
      if ( i->type )
         actmap->player[i->pos].stat = Player::tplayerstat( i->type->GetSelectedItemIndex() );
   }
   return true;
};
