/* * TETRIS THEME (Korobeiniki) - FEHLERFREI
 * Im professionellen Klassen-Style für den ESP32-S3 an Pin 4
 */

#include <Arduino.h>

int speakerPin = 4; // DEIN PIN! Rotes Kabel an Pin 4

typedef void(*PlayNoteCallback)(int note, int duration);

class TetrisPlayer
{
public:
  PlayNoteCallback playNoteCallback;

  void playSong()
  {
    partA();
    partB();
  }

  void playNote(int note, int duration)
  {
    playNoteCallback(note, duration);
    delay(25); // Kleine Pause zwischen den Noten für den "Stakkato"-Effekt
  }

private:
  // Noten-Frequenzen
  const int e5 = 659;  const int b4 = 494;  const int c5 = 523;  const int d5 = 587;
  const int a4 = 440;  const int f5 = 698;  const int g5 = 784;  const int c6 = 1047;
  const int a5 = 880;  const int gSH4 = 415; 
  const int R = 0;     // Pause

  void partA()
  {
    playNote(e5, 400); playNote(b4, 200); playNote(c5, 200); playNote(d5, 400); playNote(c5, 200); playNote(b4, 200);
    playNote(a4, 400); playNote(a4, 200); playNote(c5, 200); playNote(e5, 400); playNote(d5, 200); playNote(c5, 200);
    playNote(b4, 600); playNote(c5, 200); playNote(d5, 400); playNote(e5, 400);
    playNote(c5, 400); playNote(a4, 400); playNote(a4, 400); playNote(R, 200);
  }

  void partB()
  {
    playNote(d5, 600); playNote(f5, 200); playNote(a5, 400);  playNote(g5, 200); playNote(f5, 200);
    playNote(e5, 600); playNote(c5, 200); playNote(e5, 400); playNote(d5, 200); playNote(c5, 200);
    playNote(b4, 400); playNote(b4, 200); playNote(c5, 200); playNote(d5, 400); playNote(e5, 400);
    playNote(c5, 400); playNote(a4, 400); playNote(a4, 400); playNote(R, 400);
  }
};

TetrisPlayer gameBoy;

// Die Hardware-Brücke zum ESP32-S3
void hardwarePlay(int note, int duration) {
  if (note == 0) {
    delay(duration);
  } else {
    tone(speakerPin, note, duration);
    delay(duration);
    noTone(speakerPin);
  }
}

void setup() {
  gameBoy.playNoteCallback = hardwarePlay;
}

void loop() {
  gameBoy.playSong();
  delay(3000); // 3 Sekunden Pause vor der nächsten Runde Klötzchenstapeln!