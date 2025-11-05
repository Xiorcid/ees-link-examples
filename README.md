# EES-link barošanas bloks
Šis repozitorijs satur EES-link barošanas bloka aprakstu un dokumenāciju
## Koda piemēra apraksts
Piedāvātais koda piemērs ir paredzēts ESP32 mikrokontrolierim ar MCP2562 transiveru.
Piemērs nolasa informāciju no CAN un izvada to _Serial_ portā. Piemērs izvada visus pieejamus datus.
CAN bibliotēka ir pieejama [šeit](https://github.com/sandeepmistry/arduino-CAN).
## Dokumentācija
CAN notiek sekojošo ziņojumu parraide:
1) Barošanas bloka parametri (0x12)
2) Ātrums                    (0xED)
3) Akselerometra parametri   (0xC3)

Visas _float_ vērtības (izņemot enerģiju) tiek parraidītas _int_ veidā - _float_ * 100 (* 1000).
Visas vērtības ir kodētas ar diviem baitiem, to atšifrēšana notiek šādā veidā:

`param = (data[i] << 8) | data[i + 1];`
### 0x12 paketes uzbūve
1) Spriegums: baiti 0 un 1
2) Strāvas stiptums: baiti 2 un 3
3) Patērētā enerģija: baiti 4 un 5

### 0xED paketes uzbūve
1) Ātrums: baiti 0 un 1
   
### 0xC3 paketes uzbūve
1) Paātrinājums X: baiti 0 un 1
2) Paātrinājums Y: baiti 2 un 3
3) Paātrinājums Z: baiti 4 un 5
   
## Errata
1) CAN bitrate ir 250 kbps.
