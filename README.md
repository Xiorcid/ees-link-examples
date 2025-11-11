# EES-link barošanas bloks
Šis repozitorijs satur EES-link barošanas bloka aprakstu un dokumenāciju
## Koda piemēra apraksts
Piedāvātais koda piemērs ir paredzēts ESP32 mikrokontrolierim ar MCP2562 transiveru.
Piemērs nolasa informāciju no CAN un izvada to _Serial_ portā. Piemērs izvada visus pieejamus datus.
CAN bibliotēka ir pieejama [šeit](https://github.com/sandeepmistry/arduino-CAN).
## Dokumentācija
CAN bitrate ir 500 kbps.

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

### Cita informācija par parraidāmo informāciju
1) Spriegums, strāva un enerģija tiek nolasīti no bloka un pilnībā atbilst tiem, kuri teik sūtīti uz organizatoru serveru.
2) Ātrums tiek nolasīts no GPS un pilnībā atbilst tam, kas teik sūtīts uz organizatoru serveru. Ātruma ierobežojuma pārkāpšanas gadījumā nekāda papildus informācija netiek sūtīta. Ir jānodrošina vadītāja informēšana par šo notikumu, vai izmantot organizatoru nodrošināto iekārtu (izņemot U25).
3) Ne visos blokos ir iestādīts akselerometrs. Ja tas ir vajadzīgs, lūgums informēt organizatorus laicīgi.
4) GPS informācija tiek atjaunota reizi 2 sekundēs, visa cita - reizi 0.5 sekundēs.

## Informācija par barošanas bloku
### Elektiskie parametri
| Parametrs     | Vērtība       |
| ------------- | ------------- |
| MAX Spriegums | 63V           |
| MAX Strāva    | 20A           |
| MAX Jauda     | 1200W         |
| Ieteicams U   | <48V          |

### Bloka kontroles plates parametri
1) Mikrokontrolieris ir ESPRESSIF ESP32, GSM modulis - SIMCOM A7670E.
2) Pēc mikrokontroliera pārstartēšanas drošības nolūkos barošanas bloka izeja tiek izslēgta.
3) Organsizatoriem tiek sūtīti sekojošie mašinas parametri:
   - Strāva
   - Patērētā enerģija
   - GPS ātrums
   - GPS koordinātes
4) Organizatori attālināti var kontrolēt sekojošus parametrus:
   - Strāvas ierobežojums
   - Bloka izejas stāvoklis (ON/OFF)
      NB! Organizatori patur tiesības izslēgt bloku nedrošas braukšanas vai noteikumu pārkāpšanas gadījumā!
   - Spriegums

## Errata
1) CAN bitrate ir 250 kbps.
