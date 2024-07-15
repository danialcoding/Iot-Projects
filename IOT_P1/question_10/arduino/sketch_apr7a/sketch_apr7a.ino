#include <Keypad.h>
#include <SoftwareSerial.h>

const byte ROWS = 4; 
const byte COLS = 4; 

#define STATE_AMOUNT 0
#define STATE_BUY 1
int currentState = STATE_AMOUNT;

char keys[ROWS][COLS] = {
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

struct Product {
  String name;
  int quantity;
};

Product products[2]; 
int maxQuantity = 0; 
 

SoftwareSerial mySerial1(10, 11); 
SoftwareSerial mySerial2(12, 13); 


void setup() {
  mySerial1.begin(9600); 
  mySerial2.begin(9600);
  Serial.begin(9600); 
  
  // تعریف موجودی اولیه محصولات
  products[0].name = "pen";
  products[0].quantity = 0;
  products[1].name = "book";
  products[1].quantity = 0;
}


void getAmount() {
  char key = NO_KEY;
  int count = 0;

  Serial.println("Enter the number:");

  while (key != '#') {
    char key = keypad.getKey();
    if (key != NO_KEY && (key >= '0' && key <= '9')) {
      int newNum = key - '0';
      maxQuantity = newNum + (maxQuantity * 10);
      count++;
    }
    else if (key == '#') {
        break; 
    }
    
    delay(100);
  }
  
  Serial.print("Received number: ");
  Serial.println(maxQuantity);

  products[0].quantity = maxQuantity;
  products[1].quantity = maxQuantity;

   currentState = STATE_BUY;
}

void buy() {
  char key = keypad.getKey();

  if (key) {
    if (key >= '0' && key <= '1') {

      int productIndex = key - '0';

      if (products[productIndex].quantity > 0) {

        products[productIndex].quantity--;

        if(productIndex == 0) {
          mySerial1.print("product ");
          mySerial1.print(products[productIndex].name);
          mySerial1.println(" added to cart");
        }
        else {
          mySerial2.print("product ");
          mySerial2.print(products[productIndex].name);
          mySerial2.println(" added to cart");
        }
      } else {
        Serial.print("product ");
        Serial.print(products[productIndex].name);
        Serial.println(" finished.");
      }
    }
  }
}

void loop() {
  switch (currentState) {
    case (STATE_AMOUNT) :
      getAmount();
      currentState = STATE_BUY;
      break;
    case (STATE_BUY) :
      buy();
      break;
  }

}
