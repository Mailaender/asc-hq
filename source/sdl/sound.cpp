/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <cstring>
#include <stdlib.h>


#include "../global.h"
#include sdlheader
#include sdlmixerheader

#include "sound.h"

#include "../basestrm.h"
#include "../sgstream.h"

/** How long should this process sleep while waiting for a sound to play
 */
const int WAIT_SLEEP_MSEC = 50;




SoundSystem* SoundSystem::instance = NULL;

SoundSystem  :: SoundSystem ( bool mute, bool _off )
{
   musicState = uninitialized;
   currentPlaylist = NULL;
   musicBuf = NULL;
   this->mute = mute;
   this->off = _off;

   for ( int i = 0; i < MIX_CHANNELS; i++ )
       channel[i] = NULL;


   if ( instance )
      fatalError ( "Only one instance of SoundSystem possible !");

   instance = this;

   if( off )
      return;

   if ( SDL_Init ( SDL_INIT_AUDIO ) < 0 ) {
      warning("Couldn't initialize SDL audio interface !");
      off = true;
      sdl_initialized = false;
      return;
   } else
      sdl_initialized = true;

   int audio_rate = MIX_DEFAULT_FREQUENCY;
   Uint16 audio_format = MIX_DEFAULT_FORMAT;
   int audio_channels = 2;

   if ( Mix_OpenAudio ( audio_rate, audio_format, audio_channels, 1024 ) < 0 ) {
      mix_initialized = false;
      warning("Couldn't initialize SDL_mixer !");
      off = true;
      return;
   } else {
      mix_initialized = true;
		Mix_QuerySpec(&audio_rate, &audio_format, &audio_channels);
      displayLogMessage ( 5, "Opened audio at %d Hz %d bit %s\n", audio_rate,
			(audio_format&0xFF),
			(audio_channels > 1) ? "stereo" : "mono");
      Mix_HookMusicFinished ( trackFinished );
   }
}


void SoundSystem::setMute ( bool mute )
{
   if ( off )
      return;

   if ( mute != this->mute ) {
      if ( mute ) {
         for ( int i = 0; i < MIX_CHANNELS; i++ )
            if ( Mix_Playing(i)  )
                Mix_HaltChannel( i );

      }
      this->mute = mute;
   }
}


void SoundSystem :: trackFinished( void )
{
   getInstance()->nextTrack();
}

void SoundSystem :: nextTrack( void )
{
  if ( musicBuf ) {
     Mix_FreeMusic( musicBuf );
     musicBuf = NULL;
  }

  if ( currentPlaylist ) {
     ASCString filename = currentPlaylist->getNextTrack();
     if ( !filename.empty() ) {
        musicState = playing;
        musicBuf = Mix_LoadMUS( filename.c_str() );

        Mix_PlayMusic ( musicBuf, 1 );
     }
  }
}

void SoundSystem :: playMusic ( MusicPlayList* playlist )
{
  currentPlaylist = playlist;

  nextTrack();
}


void SoundSystem :: pauseMusic()
{
   if ( musicState == playing ) {
      Mix_PauseMusic ();
      musicState = paused;
   }
}

void SoundSystem :: resumeMusic()
{
   if ( musicState == paused ) {
      Mix_ResumeMusic ();
      musicState = playing;
   }
}

void SoundSystem :: resumePauseMusic()
{
   if ( musicState == playing )
      pauseMusic();
   else
      resumeMusic();
}


SoundSystem::~SoundSystem()
{
   Mix_HaltMusic();

   if ( musicBuf ) {
      Mix_FreeMusic( musicBuf );
      musicBuf = NULL;
   }

   if( mix_initialized )
      Mix_CloseAudio();

   if( sdl_initialized )
      SDL_CloseAudio();


   instance = NULL;
}



Mix_Chunk* SoundSystem::loadWave ( const ASCString& name )
{
   if ( off )
      return NULL;

   if ( !exist ( name.c_str() )) {
      warning ( "can't open " + name );
      return NULL;
   }

   tnfilestream stream ( name, tnstream::reading );

   return Mix_LoadWAV_RW( SDL_RWFromStream ( &stream ), 1);
}



Sound::Sound( const ASCString& filename, int _fadeIn ) : name ( filename ), wave(NULL), fadeIn ( _fadeIn ) 
{
   if ( !SoundSystem::instance )
      fatalError ( "Sound::Sound failed, because there is no SoundSystem initialized");

   wave = SoundSystem::instance->loadWave( filename );
}


void Sound::play(void)
{
   if( SoundSystem::instance->isMuted() || !wave)
      return;

   int channel;
   if ( fadeIn )
      channel = Mix_FadeInChannel ( -1, wave, 0, fadeIn );
   else {
      channel = Mix_PlayChannel ( -1, wave, 0 );
      Mix_Volume ( channel, 128 );
   }
   SoundSystem::instance->channel[ channel ] = this;
}

void Sound::playLoop()
{
   if( SoundSystem::instance->isMuted() || !wave)
      return;

   int channel;
   if ( fadeIn )
      channel = Mix_FadeInChannel ( -1, wave, -1, fadeIn );
   else
      channel = Mix_PlayChannel ( -1, wave, -1 );

   SoundSystem::instance->channel[ channel ] = this;
}

void Sound::stop()
{
   for ( int i = 0; i < MIX_CHANNELS; i++ )
      if ( SoundSystem::instance->channel[ i ] == this  && Mix_Playing(i)  )
          Mix_HaltChannel( i );
}


void Sound::playWait(void)
{
   if( SoundSystem::instance->isMuted() || !wave)
      return;

   int channel = Mix_PlayChannel ( -1, wave, 0 );
   SoundSystem::instance->channel[ channel ] = this;

   do {
      SDL_Delay(WAIT_SLEEP_MSEC);
   } while( SoundSystem::instance->channel[ channel ] == this  && Mix_Playing(channel)  );
}

void Sound :: fadeOut ( int ms )
{
   for ( int i = 0; i < MIX_CHANNELS; i++ )
      if ( SoundSystem::instance->channel[ i ] == this  && Mix_Playing(i)  )
          Mix_FadeOutChannel( i, ms );
}



Sound::~Sound(void)
{
   stop();

   if ( wave )
      Mix_FreeChunk ( wave );
}


