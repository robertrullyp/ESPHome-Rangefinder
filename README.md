# ESPHome Rangefinder
DIY Water Level for Smart Home (Home Assistant)
Memanfaatkan sensor jarak untuk mengukur level ketinggian air (isi) hingga volume air dalam Tandon.
![Image](https://github.com/user-attachments/assets/9ebe9335-35d4-4976-8d0a-18a0714ce7b2)


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
1. Sesuaikan konfigurasi esphome dengan board esp yang digunakan lalu flash ke MCU.
2. Buat/tambahkan integrasi di Home Assistant, Template(helper) integration pilih tipe entity number atau boleh disesuaikan saja, ini untuk melakukan kalkulasi menggunakan jinja template agar mendapatkan nilai persentase air hingga volume air dalam Tandon berdasarkan ketinggian (nilai jarak dari sensor ultrasonic). 
    ![NumberTemplate](https://github.com/user-attachments/assets/ac4871af-614a-47db-940f-e56a662399ed)
    ![JinjaTemplate](https://github.com/user-attachments/assets/5606ed03-c174-4ef0-93e7-a545b08e3a16)
    
    Pada Template Options, State Template silahkan disesuaikan kembali :

        {% set jarak = states('sensor.esp32c3_mqtt_hcsr04_ultrasonic_distance')|float(0) %} 
        {% set gap = 20 %} 
        {% set tinggitank = 180 %} 
        {% set totaltinggi = tinggitank + gap %} 
        {% set persen = ( (jarak - totaltinggi) / (gap - totaltinggi) * 100 )|round(0) %} 
        {{ persen if 0 <= persen <= 100 else (0 if persen < 0 else 100) }}

3. Buat card untuk entity number yang telah dibuat tadi, untuk card seperti pada deskripsi perlu install custom components di hacs, diantaranya :
    - fluid-level-background-card
    - card-templater

Code cardnya silahkan disesuaikan :

        type: picture-elements
        elements:
        - type: custom:fluid-level-background-card
            entity: number.waterlevel
            style:
            z-index: 1
            top: 50%
            left: 50%
            transform: translate(-50%, -50%)
            width: 100%
            height: 100%
            card_mod:
            style: |
                ha-card {
                text-align: center;
                --ha-card-border-color: transparent !important;
                box-shadow: none !important;
                background: none !important;
                border-radius: 50px;
                overflow: hidden;
                }  
                #container, .container {
                width: 23.3% !important;
                height: 70% !important;
                position: relative !important;
                border-radius: 14px !important;
                margin-left: 38.2%;
                margin-top: 8%;
                # transform: translate(150%, -50%);
                opacity: 0.8;
                overflow: hidden;
                }
            level_color:
            - 82
            - 171
            - 255
            severity:
            - color:
                - 34
                - 0
                - 204
                value: 80
            - color:
                - 42
                - 250
                - 0
                value: 50
            - color:
                - 200
                - 255
                - 0
                value: 20
            - color:
                - 168
                - 0
                - 0
                value: 0
            full_value: "100"
            card:
            type: custom:card-templater
            card:
                type: entity
                entity: number.waterlevel
                title_template: "{{states('number.waterlevel') | float(0) %}}"
                show_header_toggle: false
                show_name: false
                show_icon: false
                icon: mdi.water
                position:
                value: "on"
                card_mod:
                style: |
                    ha-card {
                    --ha-card-header-font-size: 14px;
                    height: 225px !important;
                    
                    }
                    .card-header {
                    justify-content: center !important;
                    }
                    .name {
                    overflow: unset !important;
                    }
        image: >-
        https://community-assets.home-assistant.io/original/4X/5/f/b/5fbcfaef479c8ebbf70ae790b9814ea0baa352f9.png
        card_mod:
        style:
            hui-image $: |
            img {
                z-index: 1 !important;
                position: relative !important;
                right: 0px;
                top: 0px;
                width: 100% !important;
                opacity: 1
            }
