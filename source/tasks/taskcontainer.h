/*
     This file is part of Advanced Strategic Command; http://www.asc-hq.org
     Copyright (C) 1994-2009  Martin Bickel 
 
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

#ifndef taskcontainerH
#define taskcontainerH

#include <list>
#include "abstracttaskcontainer.h"

class Task;
class GameMap;
class tnstream;

class TaskContainer : public AbstractTaskContainer {
      GameMap* gamemap;
   public:
      
      TaskContainer( GameMap* gamemap );
      typedef std::list<Task*> Tasks;
      Tasks tasks;
   
      void submit( Task* task );
      ~TaskContainer();
      
      void read ( tnstream& stream );
      void write ( tnstream& stream );
      
      static void hook( GameMap& gamemap );
      void add( Task* task );
      
      virtual void foo() {};
};

#endif
