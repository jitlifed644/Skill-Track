#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  //screen width
#define SCREEN_HEIGHT 64  //screen height
#define OLED_RESET    -1  // Reset 
#define SCREEN_ADDRESS 0x3C  //I2C direction

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// button1 = next, button2 = back, button3 = confirm
void setup() {
  int button1_pin = 13;
  int button2_pin = 12;
    Wire.begin(21, 22); // SDA=GPIO21, SCL=GPIO22
    Serial.begin(115200);
    int pagina = 0;

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("Error al inicializar la pantalla OLED"));
        for (;;);
    }

    display.clearDisplay();
    display.setTextSize(.5);
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    display.println("Hola, ESP32!");
    display.println("Hola, ESP32!");
    if (pagina == 0){
      display.clearDisplay();
      display.setTextSize(1.7);
      display.setTextColor(WHITE);
      display.setCursor(0, 10);
      display.println();
      display.println("SKILL TRACKER");
    }


    
    display.display(); // Mostrar en pantalla
}

void loop() {
 
    
  
}