#ifndef MUSIC_H
#define MUSIC_H

#include "pitches.h"

struct Note {
  const int pitch;
  const float duration;
};

struct Song {
  const Note* notes;
  const float bpm;
};

extern const Song its_raining_tacos;
extern const Song happy_birthday;

void play_song(const Song*);
#endif
