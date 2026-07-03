/*
==========================================================
 Mini Automotive Dashboard ECU
----------------------------------------------------------
 Version : v0.8.0
 Module  : Driver Controls Manager
 Author  : Boluwatife Ekundayo
 Platform: Arduino Uno
 Display : LCD 16x2 (MCP23008 I2C)
==========================================================
*/ 

#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

Adafruit_LiquidCrystal lcd(0);

//==================================================
// Pins
//==================================================

const byte THROTTLE_SENSOR_PIN = A0;
const byte FUEL_SENSOR_PIN  = A1;
const byte TEMP_SENSOR_PIN  = A2;
const byte BUZZER_PIN = 8;
const byte LEFT_LED_PIN   = 2;
const byte RIGHT_LED_PIN  = 3;
const byte ENGINE_LED_PIN = 4;
const byte FUEL_LED_PIN   = 5;
const byte HIGH_LED_PIN   = 6;
const byte LEFT_BUTTON_PIN  = 9;
const byte RIGHT_BUTTON_PIN = 10;
const byte HAZARD_BUTTON_PIN = 11;
const byte LIGHT_BUTTON_PIN = 12;

//==================================================
// Constants
//==================================================

const int MAX_SPEED = 200;
const int MAX_FUEL  = 100;

const int MIN_ENGINE_TEMP = 20;
const int MAX_ENGINE_TEMP = 120;

const int LOW_FUEL_LEVEL    = 15;
const int HIGH_ENGINE_TEMP  = 105;
const int OVERSPEED_LIMIT   = 120;

const int IDLE_RPM = 850;
const int MAX_RPM  = 6000;
const int MAX_THROTTLE = 100;

//==================================================
// Vehicle State
//==================================================

enum VehicleState
{
    BOOTING,
    READY,
    DRIVING
};

//==================================================
// Warning Types
//==================================================

enum WarningType
{
    ENGINE_HOT,
    LOW_FUEL,
    OVER_SPEED
};

struct WarningMessage
{
    WarningType type;
    const char *text;
};

const WarningMessage warningMessages[] =
{
    {ENGINE_HOT, "ENGINE HOT"},
    {LOW_FUEL,   "LOW FUEL"},
    {OVER_SPEED, "OVERSPEED"}
};
struct SoundProfile
{
    uint16_t frequency;
    uint16_t beepTime;
    uint16_t silenceTime;
};

const SoundProfile sounds[] =
{
    {2200,300,300},   // ENGINE HOT
    {1500,120,350},   // OVERSPEED
    {1000,150,2500}   // LOW FUEL
};

//==================================================
// Vehicle Data
//==================================================

struct VehicleData
{
      // Vehicle
    int speed;
    int rpm;

    // Driver input
    byte throttle;

    // Transmission
    byte gear;

    int fuel;
    int temperature;
   
    bool lowFuel;
    bool engineHot;
    bool overSpeed;

    bool headlights = false;
    bool leftIndicator = false;
    bool rightIndicator = false;
  	
  	bool leftButton;
    bool rightButton;
    bool hazardButton;
    bool lightButton;
  	
  	// Engine
    bool engineRunning;
};

VehicleData vehicle;


//==================================================
// Display Cache
//==================================================

struct DisplayCache
{
    int speed = -1;
    int fuel = -1;
    int temperature = -1;

    byte displayPage = 255;
};

DisplayCache cache;

//==================================================
// Globals
//==================================================

VehicleState currentState = BOOTING;

WarningType activeWarnings[5];
WarningType currentSoundWarning;
byte activeWarningCount = 0;

const unsigned long DISPLAY_INTERVAL = 500;
unsigned long soundTimer = 0;
bool buzzerOn = false;
unsigned long displayTimer = 0;
byte displayPage = 0;
unsigned long blinkTimer = 0;
bool blinkState = false;

const unsigned long BLINK_INTERVAL = 500;

char line1[17];

//==================================================
// Function Prototypes
//==================================================

void initializeDashboard();

void showScreen(const char*, const char*, int);

void loadingBar();

void readSensors();

void processVehicleState();

void updateWarnings();
void updateLighting();
void updateIndicators();

void drawDisplay();
void updateSound();
void updateDisplayScheduler();
void readDriverControls();
void processDriverControls();
bool displayNeedsUpdate();
void updateEngine();
void updateDisplayCache();
void drawWarningScreen(WarningType warning);

//==================================================
// Setup
//==================================================

void setup()
{
    lcd.begin(16,2);
    lcd.setBacklight(HIGH);
    initializeDashboard();
  	pinMode(BUZZER_PIN, OUTPUT);
	noTone(BUZZER_PIN);
  
  	pinMode(LEFT_LED_PIN, OUTPUT);
    pinMode(RIGHT_LED_PIN, OUTPUT);
    pinMode(ENGINE_LED_PIN, OUTPUT);
    pinMode(FUEL_LED_PIN, OUTPUT);
    pinMode(HIGH_LED_PIN, OUTPUT);
  
  	pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(HAZARD_BUTTON_PIN, INPUT_PULLUP);
    pinMode(LIGHT_BUTTON_PIN, INPUT_PULLUP);
}

//==================================================
// Loop
//==================================================

void loop()
{
    readSensors();

    readDriverControls();

    updateEngine();

    processVehicleState();

    processDriverControls();

    updateWarnings();

    updateSound();

    updateLighting();

    updateDisplayScheduler();

    drawDisplay();
}
//==================================================
// Boot Sequence
//==================================================

void initializeDashboard()
{
    showScreen("AUTOMOTIVE","ECU v0.8",1200);

    showScreen("Loading","Drivers...",800);

    loadingBar();

    showScreen("Checking","Speed.....OK",500);

    showScreen("Checking","Fuel......OK",500);

    showScreen("Checking","Temp......OK",500);

    showScreen("Checking","Display...OK",500);

    showScreen("Simulation","Mode",800);

    showScreen("Dashboard","Ready",1000);

    currentState = READY;
  	
  	tone(BUZZER_PIN, 523, 100);
    delay(120);

    tone(BUZZER_PIN, 659, 100);
    delay(120);

    tone(BUZZER_PIN, 784, 150);
  }

void showScreen(const char *top,const char *bottom,int delayTime)
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(top);

    lcd.setCursor(0,1);
    lcd.print(bottom);

    delay(delayTime);
}

void loadingBar()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("Initializing");

    lcd.setCursor(0,1);
    lcd.print("[          ]");

    for(int i=1;i<=10;i++)
    {
        lcd.setCursor(i,1);
        lcd.write(byte(255));
        delay(150);
    }

    delay(400);
}

//==================================================
// Sensors
//==================================================

void readSensors()
{
    vehicle.throttle =
    map(analogRead(THROTTLE_SENSOR_PIN),
        0,1023,
        0,MAX_THROTTLE);
    vehicle.fuel =
        map(analogRead(FUEL_SENSOR_PIN),0,1023,0,MAX_FUEL);

    vehicle.temperature =
        map(analogRead(TEMP_SENSOR_PIN),
            0,
            1023,
            MIN_ENGINE_TEMP,
            MAX_ENGINE_TEMP);
}

//==================================================
// Vehicle Logic
//==================================================

void processVehicleState()
{
    vehicle.lowFuel =
        vehicle.fuel <= LOW_FUEL_LEVEL;

    vehicle.engineHot =
        vehicle.temperature >= HIGH_ENGINE_TEMP;

    vehicle.overSpeed =
        vehicle.speed >= OVERSPEED_LIMIT;

    currentState =
        (vehicle.speed == 0) ? READY : DRIVING;
  	
}

//==================================================
// Warning Manager
//==================================================

void updateWarnings()
{
    activeWarningCount = 0;

    // Priority order
    if (vehicle.engineHot)
        activeWarnings[activeWarningCount++] = ENGINE_HOT;

    if (vehicle.overSpeed)
        activeWarnings[activeWarningCount++] = OVER_SPEED;

    if (vehicle.lowFuel)
        activeWarnings[activeWarningCount++] = LOW_FUEL;

    // Select the warning that controls the buzzer
    if (activeWarningCount > 0)
        currentSoundWarning = activeWarnings[0];

    // Display page logic
    if (activeWarningCount == 0)
    {
        displayPage = 0;
    }
    else if (displayPage > activeWarningCount)
    {
        displayPage = 0;
    }
}

//==================================================
// Display
//==================================================

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

//==================================================
// Cache
//==================================================

bool displayNeedsUpdate()
{
    if(vehicle.speed != cache.speed) return true;
    if(vehicle.fuel != cache.fuel) return true;
    if(vehicle.temperature != cache.temperature) return true;
    if(displayPage != cache.displayPage) return true;

    return false;
}

void updateDisplayCache()
{
    cache.speed = vehicle.speed;
    cache.fuel = vehicle.fuel;
    cache.temperature = vehicle.temperature;
    cache.displayPage = displayPage;
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

void updateIndicators()
{
    if (millis() - blinkTimer >= BLINK_INTERVAL)
    {
        blinkTimer = millis();
        blinkState = !blinkState;
    }
}

void updateLighting()
{
    updateIndicators();

    digitalWrite(LEFT_LED_PIN,
        vehicle.leftIndicator && blinkState);

    digitalWrite(RIGHT_LED_PIN,
        vehicle.rightIndicator && blinkState);

    digitalWrite(ENGINE_LED_PIN,
        vehicle.engineHot);

    digitalWrite(FUEL_LED_PIN,
        vehicle.lowFuel);

    digitalWrite(HIGH_LED_PIN,
        vehicle.headlights);
}

void readDriverControls()
{
    vehicle.leftButton =
        !digitalRead(LEFT_BUTTON_PIN);

    vehicle.rightButton =
        !digitalRead(RIGHT_BUTTON_PIN);

    vehicle.hazardButton =
        !digitalRead(HAZARD_BUTTON_PIN);

    vehicle.lightButton =
        !digitalRead(LIGHT_BUTTON_PIN);
}

void processDriverControls()
{
    vehicle.leftIndicator =
        vehicle.leftButton;

    vehicle.rightIndicator =
        vehicle.rightButton;

    vehicle.headlights =
        vehicle.lightButton;

    if(vehicle.hazardButton)
    {
        vehicle.leftIndicator = true;
        vehicle.rightIndicator = true;
    }
}

void updateEngine()
{
    vehicle.engineRunning = true;

    vehicle.rpm =
        map(vehicle.throttle,
            0,
            100,
            IDLE_RPM,
            MAX_RPM);

    vehicle.speed =
        map(vehicle.rpm,
            IDLE_RPM,
            MAX_RPM,
            0,
            MAX_SPEED);
}