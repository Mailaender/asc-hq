/*
    This file is part of Advanced Strategic Command; http://www.asc-hq.de
    Copyright (C) 1994-2004  Martin Bickel  and  Marc Schellenberger

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

#ifndef blitterH
 #define blitterH

 #include <cmath>
 #include <map>
 #include "../libs/loki/static_check.h"
 #include "../libs/sdlmm/src/sdlmm.h"
 #include "surface.h"

 #include "../misc.h"
 #include "../palette.h"
 #include "../basegfx.h"
 
 typedef SDLmm::Color Color;

 class NullParamType {};
 extern NullParamType nullParam;


 template<int BytesPerPixel> class PixelSize2Type;

 template<> class PixelSize2Type<1> { public: typedef Uint8  PixelType; };
 template<> class PixelSize2Type<2> { public: typedef Uint16 PixelType; };
 template<> class PixelSize2Type<4> { public: typedef Uint32 PixelType; };

 
 
 class TargetPixelSelector_All {
     protected:
        int skipTarget( int x, int y ) { return 0; };
        void init( const Surface& srv ) {};
     public:
        TargetPixelSelector_All ( NullParamType npt = nullParam ) {};   
  };

  class TargetPixelSelector_Valid {
        int w,h;
     protected:
        int skipTarget( int x, int y ) 
        { 
           if ( x >= 0 && y >= 0 && x < w && y < h )
              return 0; 
           else
              if ( x < 0 )
                 return -x;
              else
                 return 1;     
        };
        void init( const Surface& srv ) 
        {
           w = srv.w();
           h = srv.h();
        };
     public:
        TargetPixelSelector_Valid ( NullParamType npt = nullParam ) :w(0xffffff),h(0xffffff) {};   
  };

  
  
  
  
  
  
 template<int pixelsize>
 class SourcePixelSelector_Plain {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       const PixelType* pointer;
       int pitch;
       const Surface* surface;
    protected:
       SourcePixelSelector_Plain() : pointer(NULL), surface(NULL) {};

       void init ( const Surface& srv )
       {
          surface = &srv; 
          pointer = (const PixelType*)(srv.pixels());
          pitch = srv.pitch()/sizeof(PixelType) - srv.w();
       };

       PixelType getPixel(int x, int y)
       {
          if ( x >= 0 && y >= 0 && x < surface->w() && y < surface->h() )
             return surface->GetPixel(SPoint(x,y));
          else
             return surface->GetPixelFormat().colorkey();
       };

       PixelType nextPixel() { return *(pointer++); };
       void nextLine() { pointer += pitch; };
       void skipPixels( int pixNum ) { pointer += pixNum; };

       int getWidth()  { return surface->w(); };
       int getHeight() { return surface->h(); };
    public:   
       SourcePixelSelector_Plain ( NullParamType npt ) {};
 };


 template<
    int BytesPerSourcePixel,
    int BytesPerTargetPixel 
 >
 class ColorConverter {
     public:
       typedef typename PixelSize2Type<BytesPerTargetPixel>::PixelType SourcePixelType;
       typedef typename PixelSize2Type<BytesPerTargetPixel>::PixelType TargetPixelType;
     private:   
       SourcePixelType srcColorKey;
       TargetPixelType destColorKey;
     public:   
       ColorConverter( const Surface& sourceSurface, Surface& targetSurface ) {};
       TargetPixelType convert ( SourcePixelType sp ) { return sp; };
  };   

 
 template<>
 class ColorConverter<4,1> {
       int rshift, gshift, bshift;
     public:
       typedef  PixelSize2Type<4>::PixelType SourcePixelType;
       typedef  PixelSize2Type<1>::PixelType TargetPixelType;
     private:   
       SourcePixelType srcColorKey;
       TargetPixelType destColorKey;
       bool srcHasColorKey;
       int srcColorMask;
     public:   

       ColorConverter( const Surface& sourceSurface, Surface& targetSurface ) {
          rshift = sourceSurface.GetPixelFormat().Rshift() + 2;
          gshift = sourceSurface.GetPixelFormat().Gshift() + 2;
          bshift = sourceSurface.GetPixelFormat().Bshift() + 2;
          srcColorMask = ~sourceSurface.GetPixelFormat().Amask();
          srcColorKey = sourceSurface.GetPixelFormat().colorkey() & srcColorMask;
          
          srcHasColorKey = sourceSurface.flags() & SDL_SRCCOLORKEY;
          if ( targetSurface.flags() & SDL_SRCCOLORKEY )
             destColorKey = targetSurface.GetPixelFormat().colorkey();
          else   
             destColorKey = 0xff;
             
             
       };
       
       TargetPixelType convert ( SourcePixelType sp ) { 
          if ( srcHasColorKey && (sp & srcColorMask) == srcColorKey )
             return destColorKey;
          else   
             return truecolor2pal_table[ ((sp >> rshift) & 0x3f) + (((sp >> gshift) & 0x3f) << 6) + (((sp >> bshift) & 0x3f) << 12)];
       };
           
  };   

 template<>
 class ColorConverter<1,4> {
       SDL_Color* palette;
       int rshift, gshift, bshift,ashift;
     public:
       typedef  PixelSize2Type<1>::PixelType SourcePixelType;
       typedef  PixelSize2Type<4>::PixelType TargetPixelType;

       ColorConverter( const Surface& sourceSurface, Surface& targetSurface ) {
          palette = sourceSurface.GetPixelFormat().palette()->colors;
          rshift = targetSurface.GetPixelFormat().Rshift();
          gshift = targetSurface.GetPixelFormat().Gshift();
          bshift = targetSurface.GetPixelFormat().Bshift();
          if ( targetSurface.GetPixelFormat().Amask() )
             ashift = targetSurface.GetPixelFormat().Ashift();
          else 
             ashift = firstBit( ~( targetSurface.GetPixelFormat().Rmask() | targetSurface.GetPixelFormat().Gmask() | targetSurface.GetPixelFormat().Bmask()));
          
       };
       
       TargetPixelType convert ( SourcePixelType sp ) { 
            if ( sp == 0xff ) 
               return Surface::transparent << ashift;
            else {
               TargetPixelType a = Surface::opaque;
               a <<= ashift;
               return TargetPixelType(palette[sp].r << rshift) + TargetPixelType(palette[sp].g << gshift) + TargetPixelType(palette[sp].b << bshift) + a;
            }   
       };
           
  };   
     
  
     
  template<
     int BytesPerSourcePixel,
     int BytesPerTargetPixel,
     class SourceColorTransform,
     template<int> class ColorMerger,
     template<int> class SourcePixelSelector = SourcePixelSelector_Plain,
     class TargetPixelSelector = TargetPixelSelector_All
  >
  class MegaBlitter : public SourceColorTransform,
                      public ColorMerger<BytesPerTargetPixel>,
                      public SourcePixelSelector<BytesPerSourcePixel>,
                      public TargetPixelSelector {
        typedef typename PixelSize2Type<BytesPerSourcePixel>::PixelType SourcePixelType;
        typedef typename PixelSize2Type<BytesPerTargetPixel>::PixelType TargetPixelType;
    public:
        MegaBlitter() { };
        MegaBlitter( const SourceColorTransform& scm, const ColorMerger<BytesPerTargetPixel>& cm, const SourcePixelSelector<BytesPerSourcePixel>& sps, const TargetPixelSelector& tps ) :
                     SourceColorTransform( scm ),
                     ColorMerger<BytesPerTargetPixel>( cm ),
                     SourcePixelSelector<BytesPerSourcePixel>( sps ),
                     TargetPixelSelector( tps ) { };

        int getWidth()  { return SourcePixelSelector<BytesPerTargetPixel>::getWidth(); };
        int getHeight() { return SourcePixelSelector<BytesPerTargetPixel>::getHeight(); };
        
        void initSource( const Surface& src )
        {
           SourcePixelSelector<BytesPerSourcePixel>::init( src );
        }

        
        void blit( const Surface& src, Surface& dst, SPoint dstPos )
        {
           assert( src.GetPixelFormat().BytesPerPixel() == BytesPerSourcePixel );
           assert( dst.GetPixelFormat().BytesPerPixel() == BytesPerTargetPixel );
           
           SurfaceLock sl( dst );

           ColorMerger<BytesPerTargetPixel>::init( BytesPerSourcePixel == BytesPerTargetPixel ? src : dst );
           SourcePixelSelector<BytesPerSourcePixel>::init( src );
           TargetPixelSelector::init( dst );
           
           ColorConverter<BytesPerSourcePixel,BytesPerTargetPixel> colorConverter( src, dst );

           int h = SourcePixelSelector<BytesPerSourcePixel>::getHeight();
           int w = SourcePixelSelector<BytesPerSourcePixel>::getWidth();

           TargetPixelType* pix = (TargetPixelType*)( dst.pixels() );

           pix += dstPos.y * dst.pitch()/BytesPerTargetPixel + dstPos.x;

           int pitch = dst.pitch()/BytesPerTargetPixel - w;

           typedef SourcePixelSelector<BytesPerTargetPixel> SPS;
           for ( int y = 0; y < h; ++y ) {
              for ( int x = 0; x < w; ++x ) {
                 int s = TargetPixelSelector::skipTarget(x,y);
                 if ( !s ) {
                    ColorMerger<BytesPerTargetPixel>::assign ( colorConverter.convert( SourceColorTransform::transform( SourcePixelSelector<BytesPerSourcePixel>::nextPixel())), pix );
                    ++pix;
                 } else {
                    SourcePixelSelector<BytesPerSourcePixel>::skipPixels( s );   
                    pix += s;
                 }   
              }
              SourcePixelSelector<BytesPerSourcePixel>::nextLine();
              pix += pitch;
           }
       };

};

/*
  template<
     class Src, 
     class Dst,
     class SourceColorTransform,
     template<int> class ColorMerger,
     template<int> class SourcePixelSelector = SourcePixelSelector_Plain
  >
  class MegaBlitter2 : public MegaBlitter< Src::colorDepth,
                                           Dst::colorDepth,
                                           SourceColorTransform,
                                           ColorMerger,
                                           SourcePixelSelector
                                         > {
        Src src;
        Dst dst;
    public:
        MegaBlitter2( Src s, Dst d ) : src(s), dst(d) { };

        MegaBlitter2( Src s, Dst d, const SourceColorTransform& scm, const ColorMerger<Dst::colorDepth>& cm, const SourcePixelSelector<Src::colorDepth>& sps  ) :
                     MegaBlitter< Src::colorDepth,
                                  Dst::colorDepth,
                                  SourceColorTransform,
                                  ColorMerger,
                                  SourcePixelSelector
                                >( scm, cm, sps ), src(s), dst(d) { };
                
        
        void blit( SPoint dstPos ) {
           blit( src, dst, dstPos );
        };   
  };      
*/
/*
   template<
     class Src, 
     class Dst,
     class SourceColorTransform,
     template<int> class ColorMerger,
     template<int> class SourcePixelSelector = SourcePixelSelector_Plain
  >
  void megaBlitter3 ( const Src& src, 
                      Dst& dst, 
                      const SPoint& pos,
                      const SourceColorTransform& scm, 
                      const ColorMerger& cm, 
                      const SourcePixelSelector& sps )
{
   MegaBlitter2<Src,Dst,SourceColorTransform,ColorMerger,SourcePixelSelector> mb ( src, dst, scm, cm, sps );
   mb.Blit( pos );
}
*/

/*
 template<class T> class ParameterProvider() {};
 template<> class ParameterProvider<ColorMerger> {
                       int param;
                    Public:
                       ParameterProvider<ColorMerger>( int i ) {};
  */

 
  template<
     class SourceColorTransform,
     template<int> class ColorMerger,
     template<int> class SourcePixelSelector,
     class TargetPixelSelector,
     typename SourceColorTransformParameter,
     typename ColorMergerParameter,
     typename SourcePixelSelectorParameter,
     typename TargetPixelSelectorParameter
  >
  void megaBlitter  ( const Surface& src, 
                      Surface& dst, 
                      const SPoint& pos,
                      const SourceColorTransformParameter& scmp = nullParam, 
                      const ColorMergerParameter& cmp  = nullParam, 
                      const SourcePixelSelectorParameter spsp  = nullParam,
                      const TargetPixelSelectorParameter tpsp  = nullParam )
{
   switch ( src.GetPixelFormat().BytesPerPixel() ) {
      case 1: {   
                 switch ( dst.GetPixelFormat().BytesPerPixel() ) {
                     case 1: { 
                               MegaBlitter< 
                                            1,1,
                                            SourceColorTransform,
                                            ColorMerger,
                                            SourcePixelSelector,
                                            TargetPixelSelector
                                          >  blitter ( 
                                                        (SourceColorTransform)( scmp ),
                                                        (ColorMerger<1>)( cmp ), 
                                                        (SourcePixelSelector<1>)( spsp ),
                                                        TargetPixelSelector(tpsp)
                                                      );
                               blitter.blit( src, dst, pos );
                             }   
                             break;
                     case 3:        
                     case 4: { 
                               MegaBlitter< 
                                            1,4,
                                            SourceColorTransform,
                                            ColorMerger,
                                            SourcePixelSelector,
                                            TargetPixelSelector
                                          >  blitter ( 
                                                        (SourceColorTransform)( scmp ),
                                                        (ColorMerger<4>)( cmp ), 
                                                        (SourcePixelSelector<1>)( spsp ),
                                                        TargetPixelSelector(tpsp)
                                                      );
                           blitter.blit( src, dst, pos );
                        }   
                        break;
                 };       
               }
               break;  
      case 3:
      case 4:  {
                 switch ( dst.GetPixelFormat().BytesPerPixel() ) {
                     case 1: { 
                               MegaBlitter< 
                                            4,1,
                                            SourceColorTransform,
                                            ColorMerger,
                                            SourcePixelSelector,
                                            TargetPixelSelector
                                          >  blitter ( 
                                                        (SourceColorTransform)( scmp ),
                                                        (ColorMerger<1>)( cmp ), 
                                                        (SourcePixelSelector<4>)( spsp ),
                                                        TargetPixelSelector(tpsp)
                                                      );
                               blitter.blit( src, dst, pos );
                             }   
                             break;
                     case 3:        
                     case 4: { 
                               MegaBlitter< 
                                            4,4,
                                            SourceColorTransform,
                                            ColorMerger,
                                            SourcePixelSelector,
                                            TargetPixelSelector
                                          >  blitter ( 
                                                        (SourceColorTransform)( scmp ),
                                                        (ColorMerger<4>)( cmp ), 
                                                        (SourcePixelSelector<4>)( spsp ),
                                                        TargetPixelSelector(tpsp)
                                                      );
                           blitter.blit( src, dst, pos );
                        }   
                        break;
                 };       
              }
              break; 
   }
}      
    
  

//////////////////// Color transformations ////////////////////////////////////


 class ColorTransform_None {
     protected:
        ColorTransform_None(){};
        Color transform( Color col) { return col; };
     public:   
        ColorTransform_None ( NullParamType npt ) {};
 };

  class ColorTransform_PlayerCol {
        int shift;

    protected:
        ColorTransform_PlayerCol() : shift(0) {};

        Color transform( Color col)
        {
           if ( col >= 16 && col < 24 )
              return col + shift;
           else
              return col;
        };

     public:
        ColorTransform_PlayerCol( int player )
        {
           setPlayer( player );
        };
        
        ColorTransform_PlayerCol ( NullParamType npt ) : shift(0) {};
        
        void setPlayer( int player )
        {
           shift = player*8;
        };
 };

 class ColorTransform_XLAT {
        const char* table;

     protected:
        ColorTransform_XLAT() : table(NULL) {};


        Color transform( Color col)
        {
           if ( table )
              return table[col];
           else
              return col;
        };

     public:
        void setTranslationTable( const char* translationTable )
        {
           table = translationTable;
        };
        
        ColorTransform_XLAT ( NullParamType npt ) : table(NULL) {};
        
        ColorTransform_XLAT ( const char* t ) : table ( t ) {};
 };


//////////////////////// Color Merger ////////////////////////////////////

 template<int pixelsize>
 class ColorMerger_PlainOverwrite {
         typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
      protected:
         ColorMerger_PlainOverwrite(){};
         void init( const Surface& dst ) {};
         void assign ( PixelType src, PixelType* dest ) { *dest = src; };
      public:
         ColorMerger_PlainOverwrite ( NullParamType npt ) {};
 };

 
 template<int pixelsize>
 class ColorMerger_AlphaHandler {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       int colorKey;
       int mask;
    protected:
       ColorMerger_AlphaHandler() : mask ( -1 ) {};
       
       void init( const Surface& srf )
       {
            if ( srf.flags() & SDL_SRCCOLORKEY ) {
               colorKey = srf.GetPixelFormat().colorkey();
               if ( pixelsize > 1 )
                  mask = srf.GetPixelFormat().Rmask() | srf.GetPixelFormat().Gmask() | srf.GetPixelFormat().Bmask();
            } else
               if ( pixelsize == 1 )
                  colorKey = 0xff;
               else   
                  colorKey = 0xfefefe00;
       };
       
       bool isOpaque( PixelType src ) 
       {
          return (src & mask ) != colorKey;
       }
  };

 
 template<>
 class ColorMerger_AlphaHandler<1> {
       typedef PixelSize2Type<1>::PixelType PixelType;
       int colorKey;
       int mask;
    protected:
       ColorMerger_AlphaHandler() : mask ( -1 ) {};
       
       void init( const Surface& srf )
       {
            if ( srf.flags() & SDL_SRCCOLORKEY ) {
               colorKey = srf.GetPixelFormat().colorkey();
            } else
               colorKey = 0xff;
       };
       
       bool isOpaque( PixelType src ) 
       {
          return (src & mask ) != colorKey;
       }
  };

 template<>
 class ColorMerger_AlphaHandler<4> {
       typedef PixelSize2Type<4>::PixelType PixelType;
       int amask, ashift;
       PixelType colorKey;
       bool hasColorKey;
       int ckmask;
    protected:
       ColorMerger_AlphaHandler() : amask ( -1 ), ashift(0), hasColorKey(false) {};
       
       void init( const Surface& srf )
       {
            if ( srf.flags() & SDL_SRCCOLORKEY ) {
               hasColorKey = true;
               colorKey = srf.GetPixelFormat().colorkey();
               ckmask = srf.GetPixelFormat().Rmask() | srf.GetPixelFormat().Gmask() | srf.GetPixelFormat().Bmask();
            } else {
               if ( srf.GetPixelFormat().Amask() ) {
                  amask = srf.GetPixelFormat().Amask();
                  ashift = srf.GetPixelFormat().Ashift();
               } else {
                  amask = ~( srf.GetPixelFormat().Rmask() | srf.GetPixelFormat().Gmask() | srf.GetPixelFormat().Bmask() );
                  ashift = firstBit(amask);
               }   
            }
       };
       
       bool isOpaque( PixelType src ) 
       {
          if ( hasColorKey )
             return (src & ckmask) != colorKey;
          else   
             return PixelType((src & amask ) >> ashift) >= PixelType(Surface::opaque/2);
       };
  };

  
 template<int pixelsize>
 class ColorMerger_AlphaOverwrite : public ColorMerger_AlphaHandler<pixelsize> {
         typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
      protected:

         void assign ( PixelType src, PixelType* dest )
         {
            if ( isOpaque(src ) ) {
               *dest = src;
            }   
         };
         
      public:   
         ColorMerger_AlphaOverwrite( NullParamType npt = nullParam ) {};
 };

 
 
  template<int pixelsize>
  class ColorMerger_AlphaShadow {}; /* : public ColorMerger_AlphaHandler<pixelsize> {
  
         typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
      protected:
         void assign ( PixelType src, PixelType* dest )
         {
            if ( isNotAlpha(src ) ) 
               *dest = src;
         };
      public:
         ColorMerger_AlphaShadow ( NullParamType npt = nullParam) : table ( xlattables.a.dark1 ) {};   
         
 };
*/
 
 
  template<>
  class ColorMerger_AlphaShadow<1> : public ColorMerger_AlphaHandler<1> {
         typedef PixelSize2Type<1>::PixelType PixelType;
         const char* table;
      protected:

         void assign ( PixelType src, PixelType* dest )
         {
            // STATIC_CHECK ( pixelsize == 1, wrong_pixel_size );
            if ( isOpaque(src ) ) {
               *dest = table[*dest];
            }   
         };
      public:
         ColorMerger_AlphaShadow ( NullParamType npt = nullParam) : table ( xlattables.a.dark1 ) {};   
         ColorMerger_AlphaShadow ( const char* translationTable ) : table ( translationTable ) {};   
 };

  template<>
  class ColorMerger_AlphaShadow<4> : public ColorMerger_AlphaHandler<4> {
         typedef PixelSize2Type<4>::PixelType PixelType;
      protected:

         void init( const Surface& srf )
         {
             ColorMerger_AlphaHandler<4>::init(srf);
         };
      
      
         void assign ( PixelType src, PixelType* dest )
         {
            if ( isOpaque(src ) ) {
               *dest = (*dest >> 1) & 0x8f8f8f8f;
            }   
         };
      public:
         ColorMerger_AlphaShadow ( NullParamType npt = nullParam) {};   
         ColorMerger_AlphaShadow ( const char* translationTable ) {};   
 };
 
 
 

 template<int pixelsize>
 class ColorMerger_AlphaMixer {}; /* : public ColorMerger_AlphaHandler<pixelsize> {
 
         typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
      protected:
         void assign ( PixelType src, PixelType* dest )
         {
            // STATIC_CHECK ( pixelsize == 1, wrong_pixel_size );
            if ( isNotAlpha(src ) ) {
               *dest = colormixbufchar[*dest + src*256 ];
            }   
         };
      public:
         ColorMerger_AlphaMixer ( NullParamType npt = nullParam ) {};   
         
 };
 */

template<>
 class ColorMerger_AlphaMixer<1> : public ColorMerger_AlphaHandler<1> {
         typedef  PixelSize2Type<1>::PixelType PixelType;
      protected:
         void assign ( PixelType src, PixelType* dest )
         {
            if ( isOpaque(src ) ) 
               *dest = colormixbufchar[*dest + src*256 ];
         };
      public:
         ColorMerger_AlphaMixer ( NullParamType npt = nullParam ) {};   
 };

 template<>
 class ColorMerger_AlphaMixer<4> : public ColorMerger_AlphaHandler<4> {
         typedef  PixelSize2Type<4>::PixelType PixelType;
      protected:
         void assign ( PixelType src, PixelType* dest )
         {
            // STATIC_CHECK ( pixelsize == 1, wrong_pixel_size );
            if ( isOpaque(src ) ) {
               *dest = ((*dest >> 1) & 0x8f8f8f8f) + (src >> 1) & 0x8f8f8f8f;
            }   
         };
      public:
         ColorMerger_AlphaMixer ( NullParamType npt = nullParam ) {};   
 };
 
 

 template<int pixelsize>
 class ColorMerger_Alpha_XLAT_TableShifter : public ColorMerger_AlphaHandler<pixelsize> {
         typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
         const char* table;
      protected:
         void assign ( PixelType src, PixelType* dest )
         {
            // STATIC_CHECK ( pixelsize == 1, wrong_pixel_size );
            if ( isOpaque(src ) ) {
               *dest = table[ *dest + src*256 ];
            }   
         };
         
     public:    
         void setNeutralTranslationTable( const char* translationTable )
         {
            table = translationTable;
         };
         
         ColorMerger_Alpha_XLAT_TableShifter( NullParamType npt = nullParam ) : table ( NULL ) {};
         ColorMerger_Alpha_XLAT_TableShifter ( const char* translationTable ) : table ( translationTable ) {};
};



//////////////////// Source Pixel Selector  ///////////////////////////////////



 template<int pixelsize, class SourcePixelSelector = SourcePixelSelector_Plain<pixelsize> >
 class SourcePixelSelector_Rotation: public SourcePixelSelector {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       int degrees;
       int x,y;
       int w,h;
    protected:

       void init ( const Surface& srv )
       {
          SourcePixelSelector::init(srv);
          w = SourcePixelSelector::getWidth();
          h = SourcePixelSelector::getHeight();
       };


       PixelType getPixel(int x, int y)
       {
         SPoint newpos = ::getPixelRotationLocation( SPoint(x,y), w, h, degrees );
         return SourcePixelSelector::getPixel ( newpos.x, newpos.y );
       };

       PixelType nextPixel()
       {
          return getPixel(x++, y);
       };
       
       void skipPixels( int pixNum ) { x += pixNum; };

       void nextLine() { x = 0; y +=1; };

    public:
       void setAngle( int degrees )
       {
          this->degrees = degrees;
       };
       
       SourcePixelSelector_Rotation( NullParamType npt = nullParam )  : degrees(0),x(0),y(0),w(0),h(0) {}
       
       SourcePixelSelector_Rotation( int degreesToRotate )  : degrees(degreesToRotate),x(0),y(0),w(0),h(0) {}
 };


 class RotationCache {
    protected:
       static map<int,int*> cache;
       static int xsize;
       static int ysize;
 };

 template<int pixelsize>
 class SourcePixelSelector_CacheRotation : public RotationCache {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       const Surface* surface;
       int degrees;
       bool useCache;
       const PixelType* pixelStart;
       const PixelType* currentPixel;
       int tableIndex;
       int pitch;
       int* cacheIndex;
    protected:

       void init ( const Surface& srv )
       {
          if ( !surface ) {
             surface = &srv;
          } else {
             assert ( surface == &srv );
          }
          tableIndex = 0;
          pixelStart = currentPixel = (PixelType*)surface->pixels();
          pitch = srv.pitch()/sizeof(PixelType) - srv.w();
       }

       PixelType nextPixel()
       {
          if ( useCache && degrees != 0 ) {
             ++currentPixel;

             assert ( cacheIndex );
             int index = cacheIndex[tableIndex++];
             if ( index >= 0 )
                return pixelStart[index];
             else
                return surface->GetPixelFormat().colorkey();
          } else {
             ++tableIndex;
             return *(currentPixel++);
          }
       };

       void skipPixels( int pixNum ) { currentPixel += pixNum; tableIndex += pixNum; };
       
       
       void nextLine()
       {
          currentPixel += pitch;
       };

       int getWidth()  { return surface->w(); };
       int getHeight() { return surface->h(); };

    public:
       void setAngle( const Surface& srv, int degrees )
       {
          init ( srv );

          if ( xsize == -1 ) {
             xsize = surface->w();
             ysize = surface->h();
          }

          this->degrees = degrees;
          if ( degrees != 0 && surface->w() == xsize && surface->h() == ysize ) {
             useCache = true;
             if ( cache.find( degrees ) == cache.end() ) {
                int* index = new int[surface->w() * surface->h()];
                cache[degrees] = index;
                for ( int y = 0; y < surface->h(); ++y )
                    for ( int x = 0; x < surface->w(); ++x ) {
                        SPoint pnt = getPixelRotationLocation( SPoint(x,y), surface->w(),surface->h(), degrees );
                        if ( pnt.x >= 0 && pnt.y >= 0 && pnt.x < surface->w() && pnt.y < surface->h() )
                           *index++ = pnt.x + pnt.y * surface->pitch()/pixelsize;
                        else
                           *index++ = -1;
                    }
             }
             cacheIndex = cache[degrees];
          }
       }
       
       SourcePixelSelector_CacheRotation( NullParamType npt = nullParam ) : surface(NULL), degrees(0), useCache(false),pixelStart(NULL), currentPixel(NULL),tableIndex(0),pitch(0), cacheIndex(NULL) {};
       
       SourcePixelSelector_CacheRotation( const Surface& srv, int degrees ) : surface(NULL), degrees(0), useCache(false),pixelStart(NULL), currentPixel(NULL),tableIndex(0),pitch(0), cacheIndex(NULL) 
       {
          setAngle ( srv, degrees );
       };


 };


 template<int pixelsize, class SourcePixelSelector = SourcePixelSelector_Plain<pixelsize> >
 class SourcePixelSelector_Zoom: public SourcePixelSelector {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       float zoomFactor;
       int x,y;
    protected:

       int getWidth()  { return int( zoomFactor * SourcePixelSelector::getWidth()  );  };
       int getHeight() { return int( zoomFactor * SourcePixelSelector::getHeight() );  };

       PixelType getPixel(int x, int y)
       {
          return SourcePixelSelector::getPixel( int(float(x) / zoomFactor), int(float(y) / zoomFactor));
       };

       PixelType nextPixel()
       {
          return getPixel(x++, y);
       };
       
       void skipPixels( int pixNum ) { x += pixNum; };

       void nextLine() { x= 0; ++y;};

    public:
       void setZoom( float factor )
       {
          this->zoomFactor = factor;
       };
       void setSize( int sourceWidth, int sourceHeight, int targetWidth, int targetHeight )
       {
          float zw = float(targetWidth) / float(sourceWidth);
          float zh = float(targetHeight)/ float(sourceHeight);
          setZoom( min ( zw,zh));
       };

       SourcePixelSelector_Zoom( NullParamType npt = nullParam) : zoomFactor(1),x(0),y(0) {};
       
 };

 
 
 
template<int pixelsize, class SourcePixelSelector = SourcePixelSelector_Plain<pixelsize> >
 class SourcePixelSelector_Flip: public SourcePixelSelector {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       bool hflip;
       bool vflip;
       int x,y;
       int w,h;
    protected:

       void init ( const Surface& srv )
       {
          SourcePixelSelector::init(srv);
          w = SourcePixelSelector::getWidth()-1;
          h = SourcePixelSelector::getHeight()-1;
       };

              
       
       PixelType getPixel(int x, int y)
       {
         return SourcePixelSelector::getPixel( hflip? w-x : x , vflip ? h-y : y );
       };

       PixelType nextPixel()
       {
          return getPixel(x++, y);
       };

       void skipPixels( int pixNum ) { x += pixNum; };
       
       void nextLine() { x= 0; ++y;};

    public:
       void setFlipping( bool horizontal, bool vertical )
       {
          hflip = horizontal;
          vflip = vertical;
       };
       
       SourcePixelSelector_Flip( NullParamType npt = nullParam) : hflip(false),vflip(false),x(0),y(0),w(0),h(0) {};

       SourcePixelSelector_Flip( int flip) : hflip(flip&1),vflip(flip&2),x(0),y(0),w(0),h(0) {};
             
 };


template<int pixelsize, class SourcePixelSelector = SourcePixelSelector_Plain<pixelsize> >
 class SourcePixelSelector_Rectangle: public SourcePixelSelector {
       typedef typename PixelSize2Type<pixelsize>::PixelType PixelType;
       int x,y,x1,y1;
       int w,h;
    protected:
       SourcePixelSelector_Rectangle() : x(0),y(0),x1(0),y1(0),w(0),h(0) {};

       int getWidth()  { return min(w, SourcePixelSelector::getWidth() -x1 ); };
       int getHeight() { return min(h, SourcePixelSelector::getHeight()-y1 ); };
                     
       
       PixelType getPixel(int x, int y)
       {
         return SourcePixelSelector::getPixel( x + x1, y + y1 );
       };

       PixelType nextPixel()
       {
          return getPixel(x++, y);
       };

       void skipPixels( int pixNum ) { x += pixNum; };
       
       void nextLine() { x= 0; ++y;};

    public:
       void setRectangle( SPoint pos, int width, int height )
       {
          x1 = pos.x;
          y1 = pos.y;
          w = width;
          h = height;
       };   
       void setRectangle( const SDLmm::SRect& rect )
       {
          x1 = rect.x;
          y1 = rect.y;
          w = rect.w;
          h = rect.h;
       };   
      
 };
 
 
 
/*

 template<class SourceColorTransform, class ColorMerger, class SourcePixelSelector>
 void megaBlit( const Surface& src, Surface& dst, SPoint dstPos )
 {
    switch ( dst.GetPixelFormat().BytesPerPixel() ) {
       case 1: megaBlit<1,SourceColorTransform,ColorMerger,SourcePixelSelector>( src, dst, dstPos ); break;
       case 2: megaBlit<2,SourceColorTransform,ColorMerger,SourcePixelSelector>( src, dst, dstPos ); break;
       case 4: megaBlit<4,SourceColorTransform,ColorMerger,SourcePixelSelector>( src, dst, dstPos ); break;
    };
 }

*/

#endif

