#include "defs.h"
#include "music.h"

const Note its_raining_tacos_melody[] = {
  {NOTE_DS5, 1 / 4.0},
  {NOTE_DS5, 1 / 4.0},
  {NOTE_F5, 1 / 8.0},
  {NOTE_G5, 3 / 16.0},
  {NOTE_AS4, 3 / 4.0},
  {NOTE_G5, 1 / 16.0},
  {NOTE_F5, 1 / 8.0},
  {NOTE_DS5, 1 / 8.0},
  {NOTE_F5, 1 / 8.0},
  {NOTE_D5, 1 / 2.0},
  {NOTE_DS5, 1 / 4.0},
  {NOTE_G4, 1 / 2.0},
  {0, 1 / 8.0},
  {NOTE_DS5, 1 / 16.0},
  {NOTE_D5, 1 / 8.0},
  {NOTE_C5, 1 / 8.0},
  {NOTE_D5, 1 / 8.0},
  {NOTE_D5, 1 / 2.0},
  {NOTE_AS4, 1 / 16.0},
  {NOTE_C5, 1 / 8.0},
  {NOTE_AS4, 1 / 8.0},
  {NOTE_C5, 1 / 8.0},
  {NOTE_DS5, 3 / 8.0},
  {NOTE_GS5, 1 / 4.0},
  {NOTE_G5, 1 / 4.0},
  {NOTE_G5, 1 / 8.0},
  {NOTE_DS5, 1 / 2.0},
  {0, 3 / 8.0 },
  {NOTE_GS5, 1 / 4.0},
  {NOTE_GS5, 1 / 4.0},
  {NOTE_G5, 1 / 8.0},
  {NOTE_G5, 1 / 8.0 + 1 / 16.0 },
  {NOTE_F5, 3 / 8.0},
  {0, 0}
};

const Song its_raining_tacos = { its_raining_tacos_melody, 150 };

const Note happy_birthday_melody[] = {
  {NOTE_G4, 1 / 8.0},
  {NOTE_G4, 1 / 8.0},
  {NOTE_A4, 1 / 4.0},
  {NOTE_G4, 1 / 4.0},
  {NOTE_C5, 1 / 4.0},
  {NOTE_B4, 1 / 2.0},
  {0, 1 / 16.0},
  {NOTE_G4, 1 / 8.0},
  {NOTE_G4, 1 / 8.0},
  {NOTE_A4, 1 / 4.0},
  {NOTE_G4, 1 / 4.0},
  {NOTE_D5, 1 / 4.0},
  {NOTE_C5, 1 / 2.0},
  {0, 1 / 16.0},
  {NOTE_G4, 1 / 8.0},
  {NOTE_G4, 1 / 8.0},
  {NOTE_G5, 1 / 4.0},
  {NOTE_E5, 1 / 4.0},
  {NOTE_C5, 1 / 4.0},
  {NOTE_B4, 1 / 4.0},
  {NOTE_A4, 1 / 2.0},
  {0, 1 / 16.0},
  {NOTE_F5, 1 / 8.0},
  {NOTE_F5, 1 / 8.0},
  {NOTE_E5, 1 / 4.0},
  {NOTE_C5, 1 / 4.0},
  {NOTE_D5, 1 / 4.0},
  {NOTE_C5, 1 / 2.0},
  {0, 0}
};

const Song happy_birthday = { happy_birthday_melody, 180 };

static inline bool end_of_song(const Note* n) {
  return n->pitch == 0 && n->duration == 0;
}

// Derived from https://www.arduino.cc/en/Tutorial/toneMelody
// but edited for notation clarity and to capture accurate song timings
void play_song(const Song* song) {
  float whole_length = 60.0 / song->bpm * 4.0;

  for ( const Note* n = song->notes; !end_of_song(n); n++ ) {
    int note_duration = whole_length * n->duration * 1000;
    int on_duration = note_duration * 3 / 4;
    int off_duration = note_duration / 4;

    if ( n->pitch == 0 )
      delay(note_duration);
    else {
      tone(PIEZO, n->pitch);
      delay(on_duration);
      noTone(PIEZO);
      delay(off_duration);
    }
  }
}


