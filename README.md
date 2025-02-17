# ESPHome Rangefinder
DIY Water Level for Smart Home (Home Assistant)
Memanfaatkan sensor jarak untuk mengukur level ketinggian air (isi) hingga volume air dalam Tandon.

## PERSIAPAN
1. Pastikan sensor menggunakan **mode uart**, silahkan sesuaikan dengan versi yang kalian punya.
Untuk HC-SR04:
![HC-SR04-jumper](https://ptsolns.com/cdn/shop/files/Modes.jpg?v=1697006723&width=1445)
![HC-SR04-jumper](https://inwfile.com/s-j/afo1mt.jpg)

Untuk SR04M-2 tambahkan resistor 47kΩ pada R27 atau short jumper pada R27 untuk merubah ke mode uart automatic.
![SR04M-2-jumper](https://circuitdigest.com/sites/default/files/inlineimages/u5/R27-jumper-in-Ultrasonic-Module.jpg)


2. Pastikan ESPHome terinstall, untuk langkah istalasi esphome jika diperlukan bisa dicek disini :
    - [Getting Started with the ESPHome Command Line](https://esphome.io/guides/getting_started_command_line.html)
    - [Installing ESPHome Manually](https://esphome.io/guides/installing_esphome)

3. Pastikan header file (.h) ditempatkan didalam direktory project kalian (satu direktori dengan file .yaml)

## LANGKAH INSTALASI
1. 