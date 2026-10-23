# IoT Projects

Arduino Uno sketches and matching Proteus schematics from two course sets, `IOT_P1` and `IOT_P2`. Each circuit is built around an Arduino Uno R3 model. The repository contains questions 6–11 of the first set and questions 5–9 of the second set.

Three sketches (`IOT_P2` questions 7, 8, and 9) talk to the Blynk app with `BlynkSimpleStream` on the Uno’s hardware serial port at 9600 baud. No sketch connects to Wi-Fi, and the tree has no ESP board, SSID, or Wi-Fi password.

## Repository layout

```
IOT_P1/question_<n>/
  arduino/<sketch>/<sketch>.ino
  proteus/<name>.pdsprj
IOT_P2/question_<n>/
  arduino/<sketch>/<sketch>.ino
  proteus/<name>.pdsprj
```

`IOT_P2/question_5` and `question_6` each have two sketches. Question 5’s schematic is `q5.pdsprj`. It places both Unos and points them at both hex files. The folder also contains `q5sender.pdsprj.DANIAL.Padidar.workspace`, left over from an earlier sender file name.

Proteus `*.workspace` files store window layout for one computer. They are left as they were committed.

## Opening and simulating a project

1. Install the Arduino IDE (or `arduino-cli`) with the Arduino AVR board package. Install the libraries the sketch includes: `Keypad` (questions P1-8 and P1-10), `HX711` (P1-9), and `Blynk` (P2-7, P2-8, P2-9). `Servo` and `SoftwareSerial` ship with the Arduino core.
2. For a Blynk sketch, put your own device Auth Token in `BLYNK_AUTH_TOKEN` before compiling. See [Blynk setup](#blynk-setup).
3. Open the `.ino`, select the board **Arduino Uno**, and compile. The IDE writes `build/arduino.avr.uno/<sketch>.ino.hex` next to the sketch. That directory is gitignored.
4. Open the `.pdsprj` in Proteus. Each Uno’s Program property already points at that relative hex path. Run the simulation after the hex file exists.
5. Where the schematic includes a virtual terminal, open it to type or read serial text. XBee modules in these schematics are COMPIM models with a virtual baud of 9600 and a host COM-port property (`COM2`, `COM3`, or `COM4`, set on each module). Change the host port to one that exists on your machine before you bridge that link to a real serial program.

Compiled `.hex`, `.elf`, `.bin`, and `.eep` files are not stored in git. Proteus will not run a board until you compile its sketch.

## Blynk setup

The Blynk sketches use the Blynk IoT template defines plus `BlynkSimpleStream`:

```cpp
#define BLYNK_TEMPLATE_ID   "..."
#define BLYNK_TEMPLATE_NAME "..."
#define BLYNK_AUTH_TOKEN    "YOUR_BLYNK_AUTH_TOKEN"
Blynk.begin(Serial, BLYNK_AUTH_TOKEN);  // hardware Serial, 9600
```

Create a Blynk template and device, then replace `BLYNK_TEMPLATE_ID`, `BLYNK_TEMPLATE_NAME`, and `BLYNK_AUTH_TOKEN` with the values from that device. The Auth Token placeholder is the string `YOUR_BLYNK_AUTH_TOKEN`. The template id and name still in the file are the ones the sketches were saved with (`controler`, `thermometer`, `burglar alarm`); they only work with a device on that same template.

Auth tokens that used to be hard-coded in these three sketches, and in their compiled `.elf` and `.bin` files, are removed from the current tree. Revoke them in the Blynk console. Older git commits still contain the original token strings.

In Proteus, questions 7, 8, and 9 each place one XBee S1 (COMPIM) beside the Uno, and the sketches also print debug text on a `SoftwareSerial` port at pins 6 and 7. `Blynk.begin` itself uses hardware `Serial` (pins 0 and 1) at 9600. Point the COMPIM host port at the serial path your Blynk serial connection uses.

| Sketch | Template name in source | Datastreams the sketch uses |
| --- | --- | --- |
| `IOT_P2/question_7/arduino/q7/q7.ino` | `controler` | `V1` integer switch: motor on or off. `V0` integer slider: power reading. |
| `IOT_P2/question_8/arduino/q8/q8.ino` | `thermometer` | `V0` float slider: desired temperature. `V1` is written once a second with the measured temperature (Label or Gauge). |
| `IOT_P2/question_9/arduino/q9/q9.ino` | `burglar alarm` | `V0` integer switch: alarm armed or disarmed. `V1` integer slider: sensitivity, used as `0` or `1`. |

Widget behavior is the behavior in the sketch, described in the project table below.

## Projects

| Project | Sketch | Proteus file | Components on the schematic | What the sketch does |
| --- | --- | --- | --- | --- |
| Serial name print | `IOT_P1/question_6/arduino/sketch_apr5a/sketch_apr5a.ino` | `IOT_P1/question_6/proteus/New Project.pdsprj` | Arduino Uno, virtual terminal | `setup` prints a fixed name and a fixed student number to `Serial` at 9600, then the loop is empty. |
| LDR switch | `IOT_P1/question_7/arduino/sketch_apr5a/sketch_apr5a.ino` | `IOT_P1/question_7/proteus/q7.pdsprj` | Arduino Uno, LDR, 330 Ω resistor, green LED | LED on pin 13 is on while `analogRead(A0)` is greater than 3, and off otherwise. The check repeats every 1 second. |
| Smart door lock | `IOT_P1/question_8/arduino/sketch_apr6a/sketch_apr6a.ino` | `IOT_P1/question_8/proteus/q8.pdsprj` | Arduino Uno, 4×3 keypad, hobby servo, buzzer, red LED, green LED | Default code is `1402`. Four correct digits turn the green LED on, move the servo to 180° for 2 seconds, then return it to 90°. A wrong code turns on the red LED and the buzzer for 1 second. `*` starts a change: enter the current code, then the new four-digit code. |
| Pet-food dispenser | `IOT_P1/question_9/arduino/sketch_apr7a/sketch_apr7a.ino` | `IOT_P1/question_9/proteus/q9.pdsprj` | Arduino Uno, HX711, load cell, hobby servo, red LED, green LED, buzzer, 2N4403, and the scale’s passives | Every 6 seconds the HX711 is read (`scale` factor `36.059`, then `/1000`). Weight above 5 opens the servo to 180°, lights the green LED, waits 3 seconds, and closes to 90°. Otherwise the red LED and a 1 kHz buzzer blink until a later reading is heavy enough. Four-hour and five-minute values exist only as comments. |
| Smart shop | `IOT_P1/question_10/arduino/sketch_apr7a/sketch_apr7a.ino` | `IOT_P1/question_10/proteus/q10.pdsprj` | Arduino Uno, 4×4 keypad, three virtual terminals | Digits followed by `#` set one quantity, and that quantity is copied onto both products (`pen` and `book`). Key `0` buys a pen and key `1` buys a book. A sale is printed on `SoftwareSerial` pins 10/11 or 12/13. An empty product prints `finished` on hardware `Serial`. |
| Traffic light | `IOT_P1/question_11/arduino/sketch_apr7a/sketch_apr7a.ino` | `IOT_P1/question_11/proteus/q11.pdsprj` | Arduino Uno, two red LEDs, two yellow LEDs, two green LEDs, buzzer, two multiplexed 2-digit 7-segment displays (`7SEG-MPX2-CC`) | A countdown runs from 10 on segment pins 2–8 and digit-select pins 10 and 11. The open direction is green above 3 and yellow at 3 or below. The closed direction is red above 3 and yellow at 1 or below. At 0 the buzzer pulses for 300 ms and the two directions swap. |
| XBee / Zigbee password check | `IOT_P2/question_5/arduino/p2_sender/p2_sender.ino` and `IOT_P2/question_5/arduino/p1_receiver/p1_receiver.ino` | `IOT_P2/question_5/proteus/q5.pdsprj` (both Unos, both hex files) | Two Arduino Unos, two XBee S1 modules, red LED, green LED, buzzer, virtual terminals | The sender reads a line from `Serial` and forwards it on `SoftwareSerial` pins 6 and 7. The receiver reads hardware `Serial` and compares it with `code123`. A match turns the red LED off, the green LED on, and the buzzer on for 1 second, then restores the red LED. Any other text leaves the red LED on. |
| Smart parking | `IOT_P2/question_6/arduino/controller/controller.ino` and `IOT_P2/question_6/arduino/receiver/receiver.ino` | `IOT_P2/question_6/proteus/q6.pdsprj` | Two Arduino Unos, two XBee S1 modules, two buttons, green LED, hobby servo, virtual terminal | The controller sends `open` from the button on pin 4 and `close` from the button on pin 3 (both `INPUT_PULLUP`) out of `SoftwareSerial` pins 6 and 7, and lights pin 2 for 3 seconds. The receiver’s servo (pin 2) goes to 180° on `open` and 90° on `close`. Ten seconds after `open`, the receiver writes the servo back to 90°. On that timeout the controller lights its own LED for 3 seconds and clears its flag, and leaves the radio silent. The receiver collects characters with `readStringUntil("/n")`, so the terminator it waits for is the two characters `/` and `n`. |
| Blynk motor controller | `IOT_P2/question_7/arduino/q7/q7.ino` | `IOT_P2/question_7/proteus/q7.pdsprj` | Arduino Uno, XBee S1 (COMPIM, host port COM3), hobby servo, buzzer, virtual terminal | `V1` on attaches the servo on pin 2 and writes 180°. `V1` off writes 90° and silences the buzzer. If `V1` is on and the `V0` value is greater than 90, pin 3 goes high 5 seconds later and stays high until `V1` is turned off. The `V0` number is printed on the debug terminal. Servo position follows `V1` only: 180° while on, 90° while off. |
| Smart home (water heater) | `IOT_P2/question_8/arduino/q8/q8.ino` | `IOT_P2/question_8/proteus/q8.pdsprj` | Arduino Uno, XBee S1 (COMPIM, host port COM3), LM35, green LED, hobby servo, virtual terminal | `V0` is the desired temperature. The servo on pin 2 is `map(desired, 0, 50, 0, 180)`. Pin A0 is converted as `(analogRead * 4.88) / 10` and that value is written to `V1` every second. The LED on pin 3 turns on when the reading is below desired − 2, and turns off when the reading is at or above the desired temperature. |
| Blynk light-sensor alarm | `IOT_P2/question_9/arduino/q9/q9.ino` | `IOT_P2/question_9/proteus/q9.pdsprj` | Arduino Uno, XBee S1 (COMPIM, host port COM3), LDR, 1 kΩ resistor, buzzer, virtual terminal | `V0` arms the alarm and `V1` selects sensitivity. While armed, sensitivity `0` sounds the buzzer on pin 3 when the LDR on A0 reads above 80, and sensitivity `1` sounds it when the LDR reads above 40. The buzzer stays on until `V0` is turned off. |

Simulate any row by compiling the sketch in that row and opening the Proteus file in that row, using the steps in [Opening and simulating a project](#opening-and-simulating-a-project). Blynk widget setup for the last three rows is in [Blynk setup](#blynk-setup).

## Credentials

- Blynk Auth Tokens in `q7.ino`, `q8.ino`, and `q9.ino` are the placeholder `YOUR_BLYNK_AUTH_TOKEN`.
- The tree has no Wi-Fi SSID and no Wi-Fi password.
- `1402` and `code123` are the demo codes those two sketches compare against. They are part of the firmware behavior above.

## Assignment notes (Persian)

The English sections describe the sketches and schematics saved in this repository. The notes below are the original course prompts.

### IoT-P1

**Question 6**

با استفاده از يکی از ميكروكنترلرهای خانواده Arduino، نام و نام خانوادگی و شماره دانشجويی خود را روى ترمینال پرینت كنيد.

**Question 7**

با استفاده از LDR یک جایگزین برای کلید فشاری به منظور روشن و خاموش کردن LED درست کنید. توجه کنید که کلید باید حالت قبلی خود را ذخیره کند. برای مثال اگر یک بار دست خود را جلوی LDR قرار داديد و برداشتيد LED روشن شود وروشن بماند و هنگامی که بار دیگر دست خود را نزدیک LDR گرفتید LED خاموش شود. (براى شبيهسازى در پروتئوس، مقاومت LDR را به صورت دستی مقدارش را تغيير بدهید)

**Question 8**

در این سوال میخواهیم یک سيستم ورود و خروج هوشمند طراحی کنيم. برای اینكار به يک موتور سروو و يک صفحه كليد (Keypad) نیاز داریم. رمز عبور پیش فرض ١۴٠٢ است و با زدن دکمه ستاره میتوان پس از وارد كردن رمز عبور فعلى، رمز عبور جدید تعریف کرد و برای ورود باید رمز عبور به درستی در صفحه کلید وارد شود. رمزعبور حتما ۴ عددی است. اگر رمز عبور به درستی وارد شده باشد، موتور سروو میچرخد كه بیانگر باز شدن در است، همچنین به يک Buzzer و LED نياز داريم كه وضعيت در را نشان دهند. اگر رمز به درستی وارد شده باشد، Buzzer صدایی توليد نمى كند و LED سبز روشن مى شود و در غير اين صورت، Buzzer هشدار میدهد و LED قرمز روشن میشود (میتوانید از BIRG-LED استفاده کنید که با یک LED میتوان هردو رنگ سبز و قرمز را داشت).

**Question 9**

در این سوال قصد داریم مخزن غذایی برای حیوانات خانگی بسازیم. این سیستم شامل يک موتور سروو، بازر، چراغ (LED) و سنسور Cell Load است. این سیستم باید هر سه ساعت به حیوان خانگی غذا دهد. به این صورت که هر چهار ساعت، میزان وزن ظرف داخل مخزن را با سنسور Cell Load اندازه گیری میکند. اگر غذا داخل ظرف بود، درب مخزن توسط موتور سروو باز میشود و چراغ سبز روشن میشود و بعد از پنج دقیقه درب بسته میشود و چراغ خاموش میشود. حال اگر مقدار غذا داخل ظرف کم بود و یا اصلا نبود، درب مخزن باز نمیشود و بازر به صدا در میآید و چراغ قرمز چشمک میزند تا زمانی که ظرف غذای داخل مخزن پر شود.

**Question 10**

در این سوال قصد داریم تا با ارتباطات سریال در دنیای شبیهسازی میکروکنترلر آشناتر شویم و با استفاده از آن یک مغازه هوشمند طراحی کنیم. در این سوال قرار است سیستم مغازه هوشمندی را مدیریت کنیم. برای سادگی فعلا برای این مغازه ٢ کالا در نظر می گیریم. در ابتدا صاحب مغازه موجودی دو کالا را با استفاده از یک keypad وارد میکند. برای هر کالا یک کلید و یک ترمینال در نظر گرفته میشود. کاربر با فشار دادن دکمه می تواند یک قلم از کالای مد نظر را خریداری کند. هر مورد خرید توسط خریدار باید در یک ترمینال جدا به مغازه دار نمایش داده شود. هم چنین برای هر کالا زمانی که موجودی آن کالا به اتمام رسید یک پیغام اتمام موجودی بر روی ترمینال نظیر آن کالا به مغازه دار نشان داده شود. (در كل سه ترمينال مجازى)

**Question 11**

در این تمرین قصد داریم چهارراه چراغ قرمزی را شبیه سازی کنیم. در هر سمت چهارراه هم چراغ های راهنمایی، هم شمارش اعداد قابل مشاهده است. همچنین مأمور راهنمایی وجود دارد که پس از سبز شدن چراغ، سوت کوتاهی به معنای حرکت خودرو ها میزند. برای پیاده سازی نیاز به دو سون-سگمنت دو رقمی است و تعداد مشخصی چراغ (هر سمت شامل سه رنگ سبز، زرد و قرمز است). زمان مشخصی به سبز بودن هر چراغ اختصاص داده شود و سپس چراغ دیگری سبز شود و به همین ترتیب ادامه پیدا كند. نحوه نمایش نیز باید منطقی و مطابق با واقعیت باشد. برای پیاده سازی سوت زده شده میتوانید از بازر استفاده کنید.

### IoT-P2

**Question 5**

یک سیستم شامل دو گره Zigbee متصل به میکروکنترلرهایشان راهاندازی کنید. برای گره اول یک عبارت رمز را به صورت هاردکد تعریف کنید (رمز را درون خود کد تعیین کنید) و همچنین یک LED سبز، يک LED قرمز و يک Buzzer برایش در نظر بگیرید. برای گره دوم یک ترمینال مجازی قرار دهید تا از کاربر عبارت رمز را ورودی بگیرد و برای گره اول ارسال کند. درصورتی که کاربر رمز را بهدرستی وارد گره دوم كرده باشد؛ در گره اول به مدت ٣ ثانیه چراغ قرمز خاموش میشود، چراغ سبز روشن شده و بازر به صدا در می آید. در غیر اینصورت چراغ سبز و بازر خاموش هستند و چراغ قرمز روشن است.

**Question 6**

درب پارکینگ هوشمند

در این سناریو قصد داریم دربهای یک پارکینگ را از طریق بوردهای Zigbee به صورت هوشمند کنترل کنیم. برای این منظور، یک گره برای کنترل در و یک گره برای درها در نظر بگیرید که به میکروکنترلرهایشان متصل هستند. هم چنین برای درب مورد نظر یک سروو در نظر بگیرید و از ٢ کلید برای فرمان دادن و یک چراغ برای مشخص شدن نتیجه فرمان در سمت کنترلر استفاده كنید.

سیستم را به گونهای برنامهریزی کنید که با فشردن دکمه اول، سروو موتور ٩٠ درجه در جهت باز کردن درب بچرخد و پس از باز شدن کامل درب، چراغ LED سمت کنترلر چند ثانیه روشن شود. در صورتی که کاربر پیش از گذشت ١٠ ثانیه از بسته شدن در، دکمه دوم را به منظور بسته شدن درب انتخاب کند، سروو باید ٩٠ درجه در جهت بسته شدن درب بچرخد. اما اگر بعد از باز شدن کامل درب و پس از ١٠ ثانیه همچنان درب را باز بگذارد؛ سروو باید به صورت خودکار شروع به بسته شدن کند. بعد از بسته شدن درب در هر دو حالت، چراغ کنترلر باید چند ثانیه روشن شود.

**Question 7**

طراحی و تولید ریموت های کنترلی یکی از کاربردهای رایج اینترنت اشیا در دنیای امروز است. در این سوال قصد طراحی یک ریموت هوشمند برای یک موتور صنعتی الکتریکی را داریم. در اين ريموت كاربر با استفاده از يک switch خاموش و روشن کردن موتور را از طریق Blynk کنترل میکند. هم چنین یک اسلایدر مقداری بین ٠ تا ١٠٠ را از کاربر می گیرد تا توان مصرفی موتور را مشخص کند. اگر کاربر توان مصرفی موتور را بیش از ٩٠ تنظیم کند پس از گذشت ۵ ثانیه موتور داغ می کند. در این حالت یک بازر به صدا در می آید و تا زمانی که کاربر موتور را خاموش نکند بازر متوقف نمی شود. برای نشان دادن موتور از یک سروو موتور استفاده کنید و درجه سروو موتور را نظیر توان مصرفی تنظیم شده توسط کاربر در نظر بگیرید.

**Question 8**

خانه هوشمند

امروزه اینترنت اشیا در تمام ابعاد زندگی در حال ورود کردن است. یک کاربرد رایج آن هوشمندسازی منازل و ساختمانها است. در این سوال میخواهیم سناریوی کنترل کردن آبگرمکن از طریق اپلیکیشن را بررسی کنیم. خیلی اوقات به سفر میرویم و پس از چند روز به منزل برمیگردیم اما موتورخانه و آبگرمکن همچنان فعال است و انرژی مصرف میکند. با کنترل کردن آبگرمکن از طریق اپلیکیشن میتوانیم در طول سفر دمای آن را پایین بیاوریم تا فعالیت نکند و در مصرف انرژی صرفه جویی شود. از طرفی پیش از بازگشت آن را در دمای بالاتر و مطلوب قرار بدهیم تا دمای آب، شوفاژ و محيط متعادل شود. برای پيادهسازى اين سناريو از حرارت‌سنج (LM35) برای تشخیص دمای آب استفاده كنيد. يک سروو موتور برای تنظيم درجه و يک LED براى فعال يا غير فعال بودن دستگاه در نظر بكيريد. در سمت اپليكيشن Blynk هم يك Slider براى تنظيم دما و يك Label يا Gauge براى نمايش دماى فعلی آب به کار ببرید. با اسلایدر مقدار دمای مطلوب را تنظیم کرده و اگر دمای آب پایینتر از حد مطلوب باشد، آبگرمکن فعال میشود، LED روشن میشود و تا زمانی كه دمای حرارت سنج به مقدار مطلوب نرسد روشن میماند. با رسیدن دمای حرارت سنج به مقدار مطلوب، آبگرمکن باید خاموش شود. در شبیه‌ساز زاویه سروو نیز متناسب با مقدار اسلایدر تغییر میکند و درجه حرارت تنظیم شده را نشان میدهد. نکته مهمی که در این بخش باید رعایت شود این است که چنانچه دما بر روی یک عدد مشخص تنظیم شود، دستگاه دائما روشن و خاموش میشود. در نتیجه این اتفاق باعث آسیب دیدن و خراب شدن دستگاه میشود. پس بهتر است بازه‌ای را حول دمای تعیین شده در نظر بگیرید تا نوسانات کمتر شود و به دستگاه فشار وارد نشود.

**Question 9**

در این سوال قصد طراحی یک دزدگیر هوشمند منزل را داریم. این دزدگیر با استفاده از یک سنسور نوری تغییرات نور و وجود حرکت را تشخیص میدهد. در ابتدا در بلینک یک switch برای فعال یا غیر فعال کردن دزدگیر در نظر بگیرید. کاربر میزان حساسیت دزدگیر را نیز توسط یک slider مشخص می کند. برای سادگی کار فقط دو سطح حساسیت برای دزدگیر در نظر می گیریم بنابراین اسلایدر مقداری بین 0 و 1 خواهد داشت. برای سنسور اندازه‌گیری نور از یک LDR استفاده کنید. این دزدگیر به این صورت عمل می کند که اگر کاربر دزدگیر را فعال کرده باشد، با ایجاد تغییرات در مقدار خوانده شده از سنسور با توجه به میزان حساسیت دزدگیر یک بازر به صدا در می آید و تا غیر فعال کردن دزدگیر توسط کاربر روشن می ماند. توجه داشته باشيد كه نتايج تغيير حساسيت دزدگیر باید در شبیه سازی قابل مشاهده باشد.
