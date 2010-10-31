/*
     This file is part of Advanced Strategic Command; http://www.asc-hq.org
     Copyright (C) 1994-2010  Martin Bickel 
 
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

#ifndef i18nH
#define i18nH

#include "ascstring.h"

class OpaqueLocaleData;

class Locale {
      OpaqueLocaleData* data;
   public:
      Locale();
      ASCString getLang();
      
      /** Tries to find a file containing native message
          These files are the filename appended by "." and the locale, for example "en_US"
         
          \param filename The base filename onto which the locale is appended
          \param nativeMessageLanguage  if nonempty, a filename will only be searched if the language 
                                        is different from the nativeMessageLanguage
      */
      ASCString getLocalizedFile( const ASCString& filename, const ASCString& nativeMessageLanguage = "" );
      ~Locale();
};


#endif
