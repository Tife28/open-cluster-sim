#include "Sound.h"
#include "Globals.h"

void updateSound()
{
    if(activeWarningCount == 0)
    {
        noTone(BUZZER_PIN);
        buzzerOn = false;
        return;
    }

    SoundProfile s = sounds[currentSoundWarning];

    if(!buzzerOn)
    {
        if(millis() - soundTimer >= s.silenceTime)
        {
            tone(BUZZER_PIN, s.frequency);

            buzzerOn = true;
            soundTimer = millis();
        }
    }
    else
    {
        if(millis() - soundTimer >= s.beepTime)
        {
            noTone(BUZZER_PIN);

            buzzerOn = false;
            soundTimer = millis();
        }
    }
}