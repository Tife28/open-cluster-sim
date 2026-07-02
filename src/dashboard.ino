#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// MCP23008 I2C LCD
Adafruit_LiquidCrystal lcd(0);

//==================================================
// Vehicle Data
//==================================================

int vehicleSpeed = 0;
int fuelLevel = 100;
int engineTemperature = 25;


//==================================================
// Dashboard Status
//==================================================

bool headlightsOn = false;
bool leftIndicator = false;
bool rightIndicator = false;
bool hazardsOn = false;


//==================================================
// Warning Flags
//==================================================

bool lowFuel = false;
bool engineHot = false;


//==================================================
// LCD Buffers
//==================================================

char line1[17];
char line2[17];


// =====================================
// Function Prototypes
// =====================================
void initializeDashboard();
void showScreen(const char *top,const char *bottom,int delayMs);
void loadingBar();

void readSensors();
void processVehicleState();
void updateWarnings();
void drawDashboard();


// =====================================
// SETUP
// =====================================
void setup()
{
  lcd.begin(16, 2);
  lcd.setBacklight(HIGH);

  initializeDashboard();
}


// =====================================
// LOOP
// =====================================
void loop()
{
    readSensors();

    processVehicleState();

    updateWarnings();

    drawDashboard();
}

// =====================================
// ECU BOOT SEQUENCE
// =====================================
void initializeDashboard()
{
  showScreen("AUTOMOTIVE", "ECU v1.0", 2000);

  showScreen("Loading", "Drivers...", 1000);

  loadingBar();

  showScreen("Checking...", "Speed.....OK", 700);
  showScreen("Checking...", "Fuel......OK", 700);
  showScreen("Checking...", "Temp......OK", 700);
  showScreen("Checking...", "Display...OK", 700);

  showScreen("CAN BUS", "Not Detected", 1200);

  showScreen("Simulation", "Mode", 1200);

  showScreen("Dashboard", "Ready", 1500);
}


// =====================================
// SHOW ONE SCREEN
// =====================================
void showScreen(const char *top, const char *bottom, int delayMs)
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(top);

  lcd.setCursor(0, 1);
  lcd.print(bottom);

  delay(delayMs);
}


// =====================================
// LOADING BAR
// =====================================
void loadingBar()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Initializing");

  lcd.setCursor(0, 1);
  lcd.print("[          ]");

  for (int i = 1; i <= 10; i++)
  {
    lcd.setCursor(i, 1);
    lcd.write(byte(255));

    delay(200);
  }

  delay(700);
}


// =====================================
// MAIN DASHBOARD
// =====================================
void drawDashboard()
{
    sprintf(line1,
            "SPD:%3d F:%3d",
            vehicleSpeed,
            fuelLevel);

    sprintf(line2,
            "TMP:%3dC",
            engineTemperature);

    lcd.setCursor(0,0);
    lcd.print(line1);

    lcd.setCursor(0,1);
    lcd.print(line2);

    delay(100);
}

void readSensors()
{
    vehicleSpeed = map(analogRead(A0),0,1023,0,200);

    fuelLevel = map(analogRead(A1),0,1023,0,100);

    engineTemperature = map(analogRead(A2),0,1023,20,120);
}

void processVehicleState()
{
    lowFuel = (fuelLevel < 15);

    engineHot = (engineTemperature > 105);
}

void updateWarnings()
{

}