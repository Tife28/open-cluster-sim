#include "Display.h"
#include "Globals.h"

void drawDisplay()
{
    if (!displayNeedsUpdate())
        return;

    if (displayPage == 0)
    {
      drawDashboardScreen();
    }
  else
  {
    WarningType warning = activeWarnings[displayPage - 1];
    drawWarningScreen(warning);
  }

    updateDisplayCache();
}


void drawDashboardScreen()
{
    lcd.clear();

    sprintf(line1,
            "SPD:%3d F:%3d",
            vehicle.speed,
            vehicle.fuel);

    lcd.setCursor(0,0);
    lcd.print(line1);

    lcd.setCursor(0,1);

    if(vehicle.leftIndicator)
        lcd.print("<");
    else
        lcd.print(" ");

    lcd.print("TMP:");
    lcd.print(vehicle.temperature);

    if(vehicle.rightIndicator)
        lcd.print(">");
}

void drawWarningScreen(WarningType warning)
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("*** WARNING ***");

    lcd.setCursor(0,1);
    lcd.print(warningMessages[warning].text);
}

void updateDisplayScheduler()
{
    if (millis() - displayTimer < DISPLAY_INTERVAL)
        return;

    displayTimer = millis();

    if (activeWarningCount == 0)
    {
        displayPage = 0;
        return;
    }

    displayPage++;

    if (displayPage > activeWarningCount)
        displayPage = 0;
}