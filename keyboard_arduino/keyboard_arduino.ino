#include <Keyboard.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

static const unsigned char PROGMEM judgement[] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xDF, 0xFB, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xDF, 0xFB, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xCF, 0xF3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xC7, 0xE3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x63, 0xC6, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x31, 0x8C, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 引用了oled库

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
// 开启OLED

#define row1 0
#define row2 1
#define row3 11
#define row4 4
#define row5 14
#define row6 16
#define row7 15

#define col1 22
#define col2 21
#define col3 20
#define col4 19
#define col5 18
#define col6 13
#define col7 5
#define col8 10
#define col9 9
#define col10 8
#define col11 6
#define col12 12


//定义按键按放命令
#define key11_release Keyboard.release(KEY_ESC);
#define key11_press Keyboard.press(KEY_ESC);
#define key12_press Keyboard.press('`');
#define key12_release Keyboard.release('`');
#define key13_press Keyboard.press(KEY_TAB);
#define key13_release Keyboard.release(KEY_TAB);
#define key14_press Keyboard.press(KEY_CAPS_LOCK);
#define key14_release Keyboard.release(KEY_CAPS_LOCK);
#define key15_press Keyboard.press(KEY_LEFT_SHIFT);
#define key15_release Keyboard.release(KEY_LEFT_SHIFT);
#define key16_press Keyboard.press(KEY_LEFT_CTRL);
#define key16_release Keyboard.release(KEY_LEFT_CTRL);
#define key17_press Keyboard.press(KEY_LEFT_CTRL);
#define key17_release Keyboard.release(KEY_LEFT_CTRL);
//2
#define key21_release Keyboard.release(KEY_F1);
#define key21_press Keyboard.press(KEY_F1);
#define key22_press Keyboard.press('1');
#define key22_release Keyboard.release('1');
#define key23_press Keyboard.press('q');
#define key23_release Keyboard.release('q');
#define key24_press Keyboard.press('a');
#define key24_release Keyboard.release('a');
#define key25_press Keyboard.press('z');
#define key25_release Keyboard.release('z');
#define key26_press Keyboard.press('-');
#define key26_release Keyboard.release('-');
#define key27_press Keyboard.press('a');
#define key27_release Keyboard.release('a');
//3
#define key31_release Keyboard.release(KEY_F2);
#define key31_press Keyboard.press(KEY_F2);
#define key32_press Keyboard.press('2');
#define key32_release Keyboard.release('2');
#define key33_press Keyboard.press('w');
#define key33_release Keyboard.release('w');
#define key34_press Keyboard.press('s');
#define key34_release Keyboard.release('s');
#define key35_press Keyboard.press('x');
#define key35_release Keyboard.release('x');
#define key36_press Keyboard.press('=');
#define key36_release Keyboard.release('=');
#define key37_press Keyboard.press('s');
#define key37_release Keyboard.release('s');
//4
#define key41_release Keyboard.release(KEY_F3);
#define key41_press Keyboard.press(KEY_F3);
#define key42_press Keyboard.press('3');
#define key42_release Keyboard.release('3');
#define key43_press Keyboard.press('e');
#define key43_release Keyboard.release('e');
#define key44_press Keyboard.press('d');
#define key44_release Keyboard.release('d');
#define key45_press Keyboard.press('c');
#define key45_release Keyboard.release('c');
#define key46_press Keyboard.press(KEY_LEFT_ALT);
#define key46_release Keyboard.release(KEY_LEFT_ALT);
#define key47_press Keyboard.press('d');
#define key47_release Keyboard.release('d');
//5
#define key51_release Keyboard.release(KEY_F4);
#define key51_press Keyboard.press(KEY_F4);
#define key52_press Keyboard.press('4');
#define key52_release Keyboard.release('4');
#define key53_press Keyboard.press('r');
#define key53_release Keyboard.release('r');
#define key54_press Keyboard.press('f');
#define key54_release Keyboard.release('f');
#define key55_press Keyboard.press('v');
#define key55_release Keyboard.release('v');
#define key56_press Keyboard.press(' ');
#define key56_release Keyboard.release(' ');
#define key57_press Keyboard.press('f');
#define key57_release Keyboard.release('f');
//6
#define key61_release Keyboard.release(KEY_F5);
#define key61_press Keyboard.press(KEY_F5);
#define key62_press Keyboard.press('5');
#define key62_release Keyboard.release('5');
#define key63_press Keyboard.press('t');
#define key63_release Keyboard.release('t');
#define key64_press Keyboard.press('g');
#define key64_release Keyboard.release('g');
#define key65_press Keyboard.press('b');
#define key65_release Keyboard.release('b');
#define key66_press Keyboard.press('g');
#define key66_release Keyboard.release('g');
#define key67_press Keyboard.press('g');
#define key67_release Keyboard.release('g');
//
#define key71_release Keyboard.release(KEY_F6);
#define key71_press Keyboard.press(KEY_F6);
#define key72_press Keyboard.press('6');
#define key72_release Keyboard.release('6');
#define key73_press Keyboard.press('y');
#define key73_release Keyboard.release('y');
#define key74_press Keyboard.press('h');
#define key74_release Keyboard.release('h');
#define key75_press Keyboard.press('n');
#define key75_release Keyboard.release('n');
#define key76_press Keyboard.press(KEY_RIGHT_ALT);
#define key76_release Keyboard.release(KEY_RIGHT_ALT);
#define key77_press Keyboard.press('h');
#define key77_release Keyboard.release('h');
//
#define key81_release Keyboard.release(KEY_F7);
#define key81_press Keyboard.press(KEY_F7);
#define key82_press Keyboard.press('7');
#define key82_release Keyboard.release('7');
#define key83_press Keyboard.press('u');
#define key83_release Keyboard.release('u');
#define key84_press Keyboard.press('j');
#define key84_release Keyboard.release('j');
#define key85_press Keyboard.press('m');
#define key85_release Keyboard.release('m');
#define key86_press Keyboard.press('j');
#define key86_release Keyboard.release('j');
#define key87_press Keyboard.press('j');
#define key87_release Keyboard.release('j');
//
#define key91_release Keyboard.release(KEY_F8);
#define key91_press Keyboard.press(KEY_F8);
#define key92_press Keyboard.press('8');
#define key92_release Keyboard.release('8');
#define key93_press Keyboard.press('i');
#define key93_release Keyboard.release('i');
#define key94_press Keyboard.press('k');
#define key94_release Keyboard.release('k');
#define key95_press Keyboard.press(',');
#define key95_release Keyboard.release(',');
#define key96_press Keyboard.press(KEY_LEFT_GUI);
#define key96_release Keyboard.release(KEY_LEFT_GUI);
#define key97_press Keyboard.press(KEY_LEFT_ARROW);
#define key97_release Keyboard.release(KEY_LEFT_ARROW);
//
#define key101_release Keyboard.release(KEY_F9);
#define key101_press Keyboard.press(KEY_F9);
#define key102_press Keyboard.press('9');
#define key102_release Keyboard.release('9');
#define key103_press Keyboard.press('o');
#define key103_release Keyboard.release('o');
#define key104_press Keyboard.press('l');
#define key104_release Keyboard.release('l');
#define key105_press Keyboard.press('.');
#define key105_release Keyboard.release('.');
#define key106_press Keyboard.press('[');
#define key106_release Keyboard.release('[');
#define key107_press Keyboard.press(KEY_UP_ARROW);
#define key107_release Keyboard.release(KEY_UP_ARROW);
//
#define key111_release Keyboard.release(KEY_F10);
#define key111_press Keyboard.press(KEY_F10);
#define key112_press Keyboard.press('0');
#define key112_release Keyboard.release('0');
#define key113_press Keyboard.press('p');
#define key113_release Keyboard.release('p');
#define key114_press Keyboard.press(KEY_RIGHT_SHIFT);
#define key114_release Keyboard.release(KEY_RIGHT_SHIFT);
#define key115_press Keyboard.press(';');
#define key115_release Keyboard.release(';');
#define key116_press Keyboard.press(']');
#define key116_release Keyboard.release(']');
#define key117_press Keyboard.press(KEY_RIGHT_ARROW);
#define key117_release Keyboard.release(KEY_RIGHT_ARROW);
//
#define key121_release Keyboard.release(KEY_DELETE);
#define key121_press Keyboard.press(KEY_DELETE);
#define key122_press Keyboard.press(KEY_BACKSPACE);
#define key122_release Keyboard.release(KEY_BACKSPACE);
#define key123_press Keyboard.press('\\');
#define key123_release Keyboard.release('\\');
#define key124_press Keyboard.press('\n');
#define key124_release Keyboard.release('\n');
#define key125_press Keyboard.press(0x27);
#define key125_release Keyboard.release(0x27);
#define key126_press Keyboard.press('/');
#define key126_release Keyboard.release('/');
#define key127_press Keyboard.press(KEY_DOWN_ARROW);
#define key127_release Keyboard.release(KEY_DOWN_ARROW);


//定义记录变量
byte key11;
byte key12;
byte key13;
byte key14;
byte key15;
byte key16;
byte key17;
//
byte key21;
byte key22;
byte key23;
byte key24;
byte key25;
byte key26;
byte key27;
//
byte key31;
byte key32;
byte key33;
byte key34;
byte key35;
byte key36;
byte key37;
//
byte key41;
byte key42;
byte key43;
byte key44;
byte key45;
byte key46;
byte key47;
//
byte key51;
byte key52;
byte key53;
byte key54;
byte key55;
byte key56;
byte key57;
//
byte key61;
byte key62;
byte key63;
byte key64;
byte key65;
byte key66;
byte key67;
//
byte key71;
byte key72;
byte key73;
byte key74;
byte key75;
byte key76;
byte key77;
//
byte key81;
byte key82;
byte key83;
byte key84;
byte key85;
byte key86;
byte key87;
//
byte key91;
byte key92;
byte key93;
byte key94;
byte key95;
byte key96;
byte key97;
//
byte key101;
byte key102;
byte key103;
byte key104;
byte key105;
byte key106;
byte key107;
//
byte key111;
byte key112;
byte key113;
byte key114;
byte key115;
byte key116;
byte key117;
//
byte key121;
byte key122;
byte key123;
byte key124;
byte key125;
byte key126;
byte key127;

void setup() {
  //扫描输入IO设置
  pinMode(30, INPUT_PULLUP);
  pinMode(row1, INPUT_PULLUP);
  pinMode(row2, INPUT_PULLUP);
  pinMode(row3, INPUT_PULLUP);
  pinMode(row4, INPUT_PULLUP);
  pinMode(row5, INPUT_PULLUP);
  pinMode(row6, INPUT_PULLUP);
  pinMode(row7, INPUT_PULLUP);
  //扫描输出IO设置
  pinMode(col1, OUTPUT);
  pinMode(col2,OUTPUT);
  pinMode(col3, OUTPUT);
  pinMode(col4,OUTPUT);
  pinMode(col5,OUTPUT);
  pinMode(col6,OUTPUT);
  pinMode(col7,OUTPUT);
  pinMode(col8,OUTPUT);
  pinMode(col9,OUTPUT);
  pinMode(col10,OUTPUT);
  pinMode(col11,OUTPUT);
  pinMode(col12,OUTPUT);
  // ADC设置
  pinMode(A5, INPUT);
  // OLED设置
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
  display.drawBitmap(0, 0,judgement, 128, 32, 1);
  display.display();

  // 时钟中断设置
  noInterrupts();           // 停止所有中断
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;               // 清空寄存器
  OCR1A = 2000;                // compare match register 16MHz/256/2Hz
  TCCR1B |= (1 << WGM12);   // CTC 模式
  TCCR1B |= (1 << CS12);    // 256 预分频器
  TIMSK1 |= (1 << OCIE1A);  // 启动时钟对比中断
  interrupts();             // 启用中断

  
}

ISR(TIMER1_COMPA_vect)          // Timer1中断处理
{
  TCCR1B &= 0b11111011;         // 停止时钟
  key_scan();
  TCCR1B |= (1 << CS12);        // 启动时钟
}


void loop(){
//  int voltage;
//  voltage = analogRead(A0);
}
void key_scan() {
///////////////////////////////// 第一列扫描
  digitalWrite(col1,LOW);
  //第一行第一列扫描
  if(digitalRead(row1)){
    if(key11)
      {
      key11 = 0;
      key11_release
      }
  }
   else
   {
    key11 = 1;
    key11_press
   }
   //第二行第一列扫描
  if(digitalRead(row2)){
    if(key12)
      {
      key12 = 0;
      key12_release
      }
  }
   else
   {
    key12 = 1;
    key12_press
   }
      //第三行第一列扫描
  if(digitalRead(row3)){
    if(key13)
      {
      key13 = 0;
      key13_release
      }
  }
   else
   {
    key13 = 1;
    key13_press
   }
      //第四行第一列扫描
  if(digitalRead(row4)){
    if(key14)
      {
      key14 = 0;
      key14_release
      }
  }
   else
   {
    key14 = 1;
    key14_press
   }
  if(digitalRead(row5)){
    if(key15)
      {
      key15 = 0;
      key15_release
      }
  }
   else
   {
    key15 = 1;
    key15_press
   }
     if(digitalRead(row6)){
    if(key16)
      {
      key16 = 0;
      key16_release
      }
  }
   else
   {
    key16 = 1;
    key16_press
   }
     if(digitalRead(row7)){
    if(key17)
      {
      key17 = 0;
      key17_release
      }
  }
   else
   {
    key17 = 1;
    key17_press
   }
  digitalWrite(col1,HIGH);
  ///////////////////////////////// 第二列扫描
  digitalWrite(col2,LOW);
  //第一行第二列扫描
  if(digitalRead(row1)){
    if(key21)
      {
      key21 = 0;
      key21_release
      }
  }
   else
   {
    key21 = 1;
    key21_press
   }
   //第二行第二列扫描
  if(digitalRead(row2)){
    if(key22)
      {
      key22 = 0;
      key22_release
      }
  }
   else
   {
    key22 = 1;
    key22_press
   }
      //第三行第二列扫描
  if(digitalRead(row3)){
    if(key23)
      {
      key23 = 0;
      key23_release
      }
  }
   else
   {
    key23 = 1;
    key23_press
   }
      //第四行第二列扫描
  if(digitalRead(row4)){
    if(key24)
      {
      key24 = 0;
      key24_release
      }
  }
   else
   {
    key24 = 1;
    key24_press
   }
     if(digitalRead(row5)){
    if(key25)
      {
      key25 = 0;
      key25_release
      }
  }
   else
   {
    key25 = 1;
    key25_press
   }
     if(digitalRead(row6)){
    if(key26)
      {
      key26 = 0;
      key26_release
      }
  }
   else
   {
    key26 = 1;
    key26_press
   }
     if(digitalRead(row7)){
    if(key27)
      {
      key27 = 0;
      key27_release
      }
  }
   else
   {
    key27 = 1;
    key27_press
   }
  digitalWrite(col2,HIGH);
///////////////////////////////// 第三列扫描
  digitalWrite(col3,LOW);
  //第一行第三列扫描
  if(digitalRead(row1)){
    if(key31)
      {
      key31 = 0;
      key31_release
      }
  }
   else
   {
    key31 = 1;
    key31_press
   }
   //第二行第三列扫描
  if(digitalRead(row2)){
    if(key32)
      {
      key32 = 0;
      key32_release
      }
  }
   else
   {
    key32 = 1;
    key32_press
   }
      //第三行第三列扫描
  if(digitalRead(row3)){
    if(key33)
      {
      key33 = 0;
      key33_release
      }
  }
   else
   {
    key33 = 1;
    key33_press
   }
      //第四行第三列扫描
  if(digitalRead(row4)){
    if(key34)
      {
      key34 = 0;
      key34_release
      }
  }
   else
   {
    key34 = 1;
    key34_press
   }
     if(digitalRead(row5)){
    if(key35)
      {
      key35 = 0;
      key35_release
      }
  }
   else
   {
    key35 = 1;
    key35_press
   }
     if(digitalRead(row6)){
    if(key36)
      {
      key36 = 0;
      key36_release
      }
  }
   else
   {
    key36 = 1;
    key36_press
   }
     if(digitalRead(row7)){
    if(key37)
      {
      key37 = 0;
      key37_release
      }
  }
   else
   {
    key37 = 1;
    key37_press
   }
  digitalWrite(col3,HIGH);
///////////////////////////////// 第四列扫描
  digitalWrite(col4,LOW);
  //第一行第四列扫描
  if(digitalRead(row1)){
    if(key41)
      {
      key41 = 0;
      key41_release
      }
  }
   else
   {
    key41 = 1;
    key41_press
   }
   //第二行第四列扫描
  if(digitalRead(row2)){
    if(key42)
      {
      key42 = 0;
      key42_release
      }
  }
   else
   {
    key42 = 1;
    key42_press
   }
      //第三行第四列扫描
  if(digitalRead(row3)){
    if(key43)
      {
      key43 = 0;
      key43_release
      }
  }
   else
   {
    key43 = 1;
    key43_press
   }
      //第四行第四列扫描
  if(digitalRead(row4)){
    if(key44)
      {
      key44 = 0;
      key44_release
      }
  }
   else
   {
    key44 = 1;
    key44_press
   }
     if(digitalRead(row5)){
    if(key45)
      {
      key45 = 0;
      key45_release
      }
  }
   else
   {
    key45 = 1;
    key45_press
   }
     if(digitalRead(row6)){
    if(key46)
      {
      key46 = 0;
      key46_release
      }
  }
   else
   {
    key46 = 1;
    key46_press
   }
     if(digitalRead(row7)){
    if(key47)
      {
      key47 = 0;
      key47_release
      }
  }
   else
   {
    key47 = 1;
    key47_press
   }
  digitalWrite(col4,HIGH);
///////////////////////////////// 第五列扫描
  digitalWrite(col5,LOW);
  //第一行第五列扫描
  if(digitalRead(row1)){
    if(key51)
      {
      key51 = 0;
      key51_release
      }
  }
   else
   {
    key51 = 1;
    key51_press
   }
   //第二行第五列扫描
  if(digitalRead(row2)){
    if(key52)
      {
      key52 = 0;
      key52_release
      }
  }
   else
   {
    key52 = 1;
    key52_press
   }
      //第三行第五列扫描
  if(digitalRead(row3)){
    if(key53)
      {
      key53 = 0;
      key53_release
      }
  }
   else
   {
    key53 = 1;
    key53_press
   }
      //第四行第五列扫描
  if(digitalRead(row4)){
    if(key54)
      {
      key54 = 0;
      key54_release
      }
  }
   else
   {
    key54 = 1;
    key54_press
   }
     if(digitalRead(row5)){
    if(key55)
      {
      key55 = 0;
      key55_release
      }
  }
   else
   {
    key55 = 1;
    key55_press
   }
     if(digitalRead(row6)){
    if(key56)
      {
      key56 = 0;
      key56_release
      }
  }
   else
   {
    key56 = 1;
    key56_press
   }
     if(digitalRead(row7)){
    if(key57)
      {
      key57 = 0;
      key57_release
      }
  }
   else
   {
    key57 = 1;
    key57_press
   }
  digitalWrite(col5,HIGH);
///////////////////////////////// 第六列扫描
  digitalWrite(col6,LOW);
  //第一行第六列扫描
  if(digitalRead(row1)){
    if(key61)
      {
      key61 = 0;
      key61_release
      }
  }
   else
   {
    key61 = 1;
    key61_press
   }
   //第二行第六列扫描
  if(digitalRead(row2)){
    if(key62)
      {
      key62 = 0;
      key62_release
      }
  }
   else
   {
    key62 = 1;
    key62_press
   }
      //第三行第六列扫描
  if(digitalRead(row3)){
    if(key63)
      {
      key63 = 0;
      key63_release
      }
  }
   else
   {
    key63 = 1;
    key63_press
   }
      //第四行第六列扫描
  if(digitalRead(row4)){
    if(key64)
      {
      key64 = 0;
      key64_release
      }
  }
   else
   {
    key64 = 1;
    key64_press
   }
     if(digitalRead(row5)){
    if(key65)
      {
      key65 = 0;
      key65_release
      }
  }
   else
   {
    key65 = 1;
    key65_press
   }
     if(digitalRead(row6)){
    if(key66)
      {
      key66 = 0;
      key66_release
      }
  }
   else
   {
    key66 = 1;
    key66_press
   }
     if(digitalRead(row7)){
    if(key67)
      {
      key67 = 0;
      key67_release
      }
  }
   else
   {
    key67 = 1;
    key67_press
   }
  digitalWrite(col6,HIGH);
///////////////////////////////// 第七列扫描
  digitalWrite(col7,LOW);
  //第一行第七列扫描
  if(digitalRead(row1)){
    if(key71)
      {
      key71 = 0;
      key71_release
      }
  }
   else
   {
    key71 = 1;
    key71_press
   }
   //第二行第七列扫描
  if(digitalRead(row2)){
    if(key72)
      {
      key72 = 0;
      key72_release
      }
  }
   else
   {
    key72 = 1;
    key72_press
   }
      //第三行第七列扫描
  if(digitalRead(row3)){
    if(key73)
      {
      key73 = 0;
      key73_release
      }
  }
   else
   {
    key73 = 1;
    key73_press
   }
      //第四行第七列扫描
  if(digitalRead(row4)){
    if(key74)
      {
      key74 = 0;
      key74_release
      }
  }
   else
   {
    key74 = 1;
    key74_press
   }
     if(digitalRead(row5)){
    if(key75)
      {
      key75 = 0;
      key75_release
      }
  }
   else
   {
    key75 = 1;
    key75_press
   }
     if(digitalRead(row6)){
    if(key76)
      {
      key76 = 0;
      key76_release
      }
  }
   else
   {
    key76 = 1;
    key76_press
   }
     if(digitalRead(row7)){
    if(key77)
      {
      key77 = 0;
      key77_release
      }
  }
   else
   {
    key77 = 1;
    key77_press
   }
  digitalWrite(col7,HIGH);
  ///////////////////////////////// 第八列扫描
  digitalWrite(col8,LOW);
  //第一行第八列扫描
  if(digitalRead(row1)){
    if(key81)
      {
      key81 = 0;
      key81_release
      }
  }
   else
   {
    key81 = 1;
    key81_press
   }
   //第二行第八列扫描
  if(digitalRead(row2)){
    if(key82)
      {
      key82 = 0;
      key82_release
      }
  }
   else
   {
    key82 = 1;
    key82_press
   }
      //第三行第八列扫描
  if(digitalRead(row3)){
    if(key83)
      {
      key83 = 0;
      key83_release
      }
  }
   else
   {
    key83 = 1;
    key83_press
   }
      //第四行第八列扫描
  if(digitalRead(row4)){
    if(key84)
      {
      key84 = 0;
      key84_release
      }
  }
   else
   {
    key84 = 1;
    key84_press
   }
     if(digitalRead(row5)){
    if(key85)
      {
      key85 = 0;
      key85_release
      }
  }
   else
   {
    key85 = 1;
    key85_press
   }
     if(digitalRead(row6)){
    if(key86)
      {
      key86 = 0;
      key86_release
      }
  }
   else
   {
    key86 = 1;
    key86_press
   }
     if(digitalRead(row7)){
    if(key87)
      {
      key87 = 0;
      key87_release
      }
  }
   else
   {
    key87 = 1;
    key87_press
   }
  digitalWrite(col8,HIGH);
///////////////////////////////// 第九列扫描
  digitalWrite(col9,LOW);
  //第一行第九列扫描
  if(digitalRead(row1)){
    if(key91)
      {
      key91 = 0;
      key91_release
      }
  }
   else
   {
    key91 = 1;
    key91_press
   }
   //第二行第九列扫描
  if(digitalRead(row2)){
    if(key92)
      {
      key92 = 0;
      key92_release
      }
  }
   else
   {
    key92 = 1;
    key92_press
   }
      //第三行第九列扫描
  if(digitalRead(row3)){
    if(key93)
      {
      key93 = 0;
      key93_release
      }
  }
   else
   {
    key93 = 1;
    key93_press
   }
      //第四行第九列扫描
  if(digitalRead(row4)){
    if(key94)
      {
      key94 = 0;
      key94_release
      }
  }
   else
   {
    key94 = 1;
    key94_press
   }
     if(digitalRead(row5)){
    if(key95)
      {
      key95 = 0;
      key95_release
      }
  }
   else
   {
    key95 = 1;
    key95_press
   }
     if(digitalRead(row6)){
    if(key96)
      {
      key96 = 0;
      key96_release
      }
  }
   else
   {
    key96 = 1;
    key96_press
   }
     if(digitalRead(row7)){
    if(key97)
      {
      key97 = 0;
      key97_release
      }
  }
   else
   {
    key97 = 1;
    key97_press
   }
  digitalWrite(col9,HIGH);
///////////////////////////////// 第十列扫描
  digitalWrite(col10,LOW);
  //第一行第十列扫描
  if(digitalRead(row1)){
    if(key101)
      {
      key101 = 0;
      key101_release
      }
  }
   else
   {
    key101 = 1;
    key101_press
   }
   //第二行第十列扫描
  if(digitalRead(row2)){
    if(key102)
      {
      key102 = 0;
      key102_release
      }
  }
   else
   {
    key102 = 1;
    key102_press
   }
      //第三行第十列扫描
  if(digitalRead(row3)){
    if(key103)
      {
      key103 = 0;
      key103_release
      }
  }
   else
   {
    key103 = 1;
    key103_press
   }
      //第四行第十列扫描
  if(digitalRead(row4)){
    if(key104)
      {
      key104 = 0;
      key104_release
      }
  }
   else
   {
    key104 = 1;
    key104_press
   }
     if(digitalRead(row5)){
    if(key105)
      {
      key105 = 0;
      key105_release
      }
  }
   else
   {
    key105 = 1;
    key105_press
   }
     if(digitalRead(row6)){
    if(key106)
      {
      key106 = 0;
      key106_release
      }
  }
   else
   {
    key106 = 1;
    key106_press
   }
     if(digitalRead(row7)){
    if(key107)
      {
      key107 = 0;
      key107_release
      }
  }
   else
   {
    key107 = 1;
    key107_press
   }
  digitalWrite(col10,HIGH);
///////////////////////////////// 第十一列扫描
  digitalWrite(col11,LOW);
  //第一行第十一列扫描
  if(digitalRead(row1)){
    if(key111)
      {
      key111 = 0;
      key111_release
      }
  }
   else
   {
    key111 = 1;
    key111_press
   }
   //第二行第十一列扫描
  if(digitalRead(row2)){
    if(key112)
      {
      key112 = 0;
      key112_release
      }
  }
   else
   {
    key112 = 1;
    key112_press
   }
      //第三行第十一列扫描
  if(digitalRead(row3)){
    if(key113)
      {
      key113 = 0;
      key113_release
      }
  }
   else
   {
    key113 = 1;
    key113_press
   }
      //第四行第十一列扫描
  if(digitalRead(row4)){
    if(key114)
      {
      key114 = 0;
      key114_release
      }
  }
   else
   {
    key114 = 1;
    key114_press
   }
     if(digitalRead(row5)){
    if(key115)
      {
      key115 = 0;
      key115_release
      }
  }
   else
   {
    key115 = 1;
    key115_press
   }
     if(digitalRead(row6)){
    if(key116)
      {
      key116 = 0;
      key116_release
      }
  }
   else
   {
    key116 = 1;
    key116_press
   }
     if(digitalRead(row7)){
    if(key117)
      {
      key117 = 0;
      key117_release
      }
  }
   else
   {
    key117 = 1;
    key117_press
   }
  digitalWrite(col11,HIGH);
///////////////////////////////// 第十二列扫描
  digitalWrite(col12,LOW);
  //第一行第十二列扫描
  if(digitalRead(row1)){
    if(key121)
      {
      key121 = 0;
      key121_release
      }
  }
   else
   {
    key121 = 1;
    key121_press
   }
   //第二行第十二列扫描
  if(digitalRead(row2)){
    if(key122)
      {
      key122 = 0;
      key122_release
      }
  }
   else
   {
    key122 = 1;
    key122_press
   }
      //第三行第十二列扫描
  if(digitalRead(row3)){
    if(key123)
      {
      key123 = 0;
      key123_release
      }
  }
   else
   {
    key123 = 1;
    key123_press
   }
      //第四行第十二列扫描
  if(digitalRead(row4)){
    if(key124)
      {
      key124 = 0;
      key124_release
      }
  }
   else
   {
    key124 = 1;
    key124_press
   }
     if(digitalRead(row5)){
    if(key125)
      {
      key125 = 0;
      key125_release
      }
  }
   else
   {
    key125 = 1;
    key125_press
   }
     if(digitalRead(row6)){
    if(key126)
      {
      key126 = 0;
      key126_release
      }
  }
   else
   {
    key126 = 1;
    key126_press
   }
     if(digitalRead(row7)){
    if(key127)
      {
      key127 = 0;
      key127_release
      }
  }
   else
   {
    key127 = 1;
    key127_press
   }
  digitalWrite(col12,HIGH);
}
