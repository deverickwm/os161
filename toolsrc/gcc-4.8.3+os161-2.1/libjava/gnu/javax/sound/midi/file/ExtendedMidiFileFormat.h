
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_javax_sound_midi_file_ExtendedMidiFileFormat__
#define __gnu_javax_sound_midi_file_ExtendedMidiFileFormat__

#pragma interface

#include <javax/sound/midi/MidiFileFormat.h>
extern "Java"
{
  namespace gnu
  {
    namespace javax
    {
      namespace sound
      {
        namespace midi
        {
          namespace file
          {
              class ExtendedMidiFileFormat;
          }
        }
      }
    }
  }
}

class gnu::javax::sound::midi::file::ExtendedMidiFileFormat : public ::javax::sound::midi::MidiFileFormat
{

public:
  virtual jint getNumberTracks();
  ExtendedMidiFileFormat(jint, jfloat, jint, jint, jlong, jint);
private:
  jint __attribute__((aligned(__alignof__( ::javax::sound::midi::MidiFileFormat)))) ntracks;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_javax_sound_midi_file_ExtendedMidiFileFormat__
