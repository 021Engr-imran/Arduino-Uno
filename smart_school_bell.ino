/*
************* Engr IMRAN *****************
*/

#include <LiquidCrystal.h>
#include <EEPROM.h>
#include <Wire.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

#define bt_set  A0
#define bt_next A1
#define bt_up   A2
#define bt_down A3

#define relay  8
#define buzzer 13

#define DS3231_I2C_ADDRESS 0x68

int hh = 0, mm = 0, ss = 0, set_day = 0, run_time = 0;
int StartHH = 0, StartMM = 0, Alarm = 0;
int DurationSec = 3;
int set = 0, setMode = 0;
int flag1 = 0, flag2 = 0;
int flash = 0;

word MilliSecond = 0;
bool timerStart = false;
bool selectedDays[8] = {false, false, false, false, false, false, false, false};
int daySelectionIndex = 1;
int editingDayIndex = 1;
int bellEditIndex = 1;
bool showWelcome = true;

String show_day[8] = {"", "Mon", "Tue", "Wed", "Thr", "Fri", "Sat", "Sun"};

void setup() {
  Wire.begin();
  pinMode(bt_set, INPUT_PULLUP);
  pinMode(bt_next, INPUT_PULLUP);
  pinMode(bt_up, INPUT_PULLUP);
  pinMode(bt_down, INPUT_PULLUP);
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  digitalWrite(relay, 1);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Welcome to ABC");
  lcd.setCursor(0, 1);
  lcd.print("    School");

  noInterrupts();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 1999;
  TCCR1B |= (1 << WGM12);
  TCCR1B |= (1 << CS11);
  TIMSK1 |= (1 << OCIE1A);
  interrupts();
}

void loop() {
  if (showWelcome) {
    if (digitalRead(bt_set) == 0) {
      showWelcome = false;
      lcd.clear();
      delay(300);
    }
    return;
  }

  GetRtc();

  if (ss == 0 && !timerStart) {
    Alarm = EEPROM.read(set_day);
    for (int x = 1; x <= Alarm; x++) {
      ReadEeprom(set_day, x);
      if (StartHH == hh && StartMM == mm) {
        run_time = DurationSec;
        digitalWrite(relay, 0);
        timerStart = true;
        break;
      }
    }
  }

  updateNextBell(); // <<== Important Fix

  if (digitalRead(bt_set) == 0) {
    digitalWrite(buzzer, 1);
    if (flag1 == 0) {
      flag1 = 1;
      if (setMode == 0) {
        setMode = 1;
        daySelectionIndex = 1;
      } else if (setMode == 1) {
        for (int i = 1; i <= 7; i++) {
          if (selectedDays[i]) {
            editingDayIndex = i;
            bellEditIndex = 1;
            set = 1;
            setMode = 2;
            StartHH = 0;
            StartMM = 0;
            DurationSec = 3;
            break;
          }
        }
      } else if (setMode == 2) {
        EEPROM.write(editingDayIndex, bellEditIndex - 1);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Saved ");
        lcd.print(bellEditIndex - 1);
        lcd.print(" Bell(s)");
        delay(1000);
        setMode = 0;
      }
      lcd.clear();
    }
  } else {
    flag1 = 0;
  }

  if (digitalRead(bt_next) == 0) {
    digitalWrite(buzzer, 1);
    if (flag2 == 0) {
      flag2 = 1;
      if (setMode == 1) {
        daySelectionIndex++;
        if (daySelectionIndex > 7) daySelectionIndex = 1;
      } else if (setMode == 2) {
        set++;
        if (set > 3) {
          WriteEeprom(editingDayIndex, bellEditIndex);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Saved Bell ");
          lcd.print(bellEditIndex);
          delay(1000);
          bellEditIndex++;
          set = 1;
        }
      }
    }
  } else {
    flag2 = 0;
  }

  if (digitalRead(bt_up) == 0) {
    digitalWrite(buzzer, 1);
    if (setMode == 1) {
      selectedDays[daySelectionIndex] = !selectedDays[daySelectionIndex];
    } else if (setMode == 2) {
      if (set == 1) {
        StartHH = (StartHH + 1) % 24;
      } else if (set == 2) {
        StartMM = (StartMM + 1) % 60;
      } else if (set == 3) {
        DurationSec = (DurationSec == 3) ? 8 : 3;
      }
    }
    delay(200);
  }

  if (digitalRead(bt_down) == 0) {
    digitalWrite(buzzer, 1);
    if (setMode == 2) {
      if (set == 1) {
        StartHH = (StartHH - 1 + 24) % 24;
      } else if (set == 2) {
        StartMM = (StartMM - 1 + 60) % 60;
      } else if (set == 3) {
        DurationSec = (DurationSec == 3) ? 8 : 3;
      }
    }
    delay(200);
  }

  flash = !flash;
  Display();
  delay(150);
  digitalWrite(buzzer, LOW);
}

void Display() {
  lcd.clear();
  if (setMode == 0) {
    lcd.setCursor(0, 0);
    lcd.print(show_day[set_day]);
    lcd.setCursor(8, 0);
    lcd.print((hh / 10) % 10); lcd.print(hh % 10); lcd.print(":");
    lcd.print((mm / 10) % 10); lcd.print(mm % 10); lcd.print(":");
    lcd.print((ss / 10) % 10); lcd.print(ss % 10);

    lcd.setCursor(0, 1);
    if (timerStart) {
      lcd.print("Bell On ");
      lcd.print(run_time); lcd.print("s");
    } else {
      lcd.print("Next Bell:");
      lcd.print((StartHH / 10) % 10); lcd.print(StartHH % 10); lcd.print(":");
      lcd.print((StartMM / 10) % 10); lcd.print(StartMM % 10);
    }
  } else if (setMode == 1) {
    lcd.setCursor(0, 0);
    lcd.print("Select Days:");
    lcd.setCursor(0, 1);
    lcd.print(show_day[daySelectionIndex]);
    lcd.print(selectedDays[daySelectionIndex] ? " <ON>" : " <OFF>");
  } else if (setMode == 2) {
    lcd.setCursor(0, 0);
    lcd.print("Set ");
    lcd.print(show_day[editingDayIndex]);
    lcd.print(" Bell ");
    lcd.print(bellEditIndex);
    lcd.setCursor(0, 1);
    if (set == 1) {
      lcd.print("Hour:"); lcd.print(StartHH);
    } else if (set == 2) {
      lcd.print("Min:"); lcd.print(StartMM);
    } else if (set == 3) {
      lcd.print("Dur(sec): "); lcd.print(DurationSec);
    }
  }
}

void SetRtc(byte second, byte minute, byte hour, byte dayOfWeek) {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(dayOfWeek));
  Wire.endTransmission();
}

void GetRtc() {
  Wire.beginTransmission(DS3231_I2C_ADDRESS);
  Wire.write(0);
  Wire.endTransmission();
  Wire.requestFrom(DS3231_I2C_ADDRESS, 7);
  ss = bcdToDec(Wire.read() & 0x7f);
  mm = bcdToDec(Wire.read());
  hh = bcdToDec(Wire.read() & 0x3f);
  set_day = bcdToDec(Wire.read());
}

byte decToBcd(byte val) { return ((val / 10 * 16) + (val % 10)); }
byte bcdToDec(byte val) { return ((val / 16 * 10) + (val % 16)); }

void ReadEeprom(int _day, int _alarm) {
  int eeprom = (_day * 100) + _alarm * 3;
  StartHH = EEPROM.read(eeprom);
  StartMM = EEPROM.read(eeprom + 1);
  DurationSec = EEPROM.read(eeprom + 2);
}

void WriteEeprom(int _day, int _alarm) {
  int eeprom = (_day * 100) + _alarm * 3;
  EEPROM.write(eeprom, StartHH);
  EEPROM.write(eeprom + 1, StartMM);
  EEPROM.write(eeprom + 2, DurationSec);
}

void updateNextBell() {
  int currentMin = hh * 60 + mm;
  int nextBellMin = 24 * 60;  // max possible
  int tempHH = 0, tempMM = 0;
  bool found = false;

  Alarm = EEPROM.read(set_day);
  for (int i = 1; i <= Alarm; i++) {
    ReadEeprom(set_day, i);
    int bellMin = StartHH * 60 + StartMM;
    if (bellMin >= currentMin && bellMin < nextBellMin) {
      nextBellMin = bellMin;
      tempHH = StartHH;
      tempMM = StartMM;
      found = true;
    }
  }

  if (found) {
    StartHH = tempHH;
    StartMM = tempMM;
  }
}

ISR(TIMER1_COMPA_vect) {
  if (timerStart) {
    MilliSecond++;
    if (MilliSecond >= 1000) {
      MilliSecond = 0;
      run_time--;
      if (run_time <= 0) {
        timerStart = false;
        digitalWrite(relay, 1);
      }
    }
  }
}
