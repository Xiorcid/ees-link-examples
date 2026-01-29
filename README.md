# EES-link barošanas bloks
Šis repozitorijs satur EES-link barošanas bloka aprakstu un dokumenāciju
## Savienojumi
| Savienojums           | Konektors   |
| --------------------- | ----------- |
| Bateriju bloka izeja  | XT90-F      |
| Barošanas bloka ieeja | XT90-M      |
| Barošanas bloka izeja | XT60-F (2+4)|

Izejas konektora pinu konfigurācija:

![XT-60-M (2+4) pinout](/ees-psu-pinout.png)
## Koda piemēra apraksts
Piedāvātais koda piemērs ir paredzēts ESP32 mikrokontrolierim ar MCP2562 transiveru.
Piemērs nolasa informāciju no CAN un izvada to _Serial_ portā. Piemērs izvada visus pieejamus datus.
CAN bibliotēka ir pieejama [šeit](https://github.com/sandeepmistry/arduino-CAN).

**NB! Nemodifcētā piemēra izmantošana iekārtā netiek ieskaitīta punkta 6.5.l prasībās. Izveidotajai iekārtai jābūt praktiski pielietojamai brauciena laikā.**
## Dokumentācija
CAN bitrate ir 500 kbps.

CAN notiek sekojošo ziņojumu parraide:
1) Barošanas bloka parametri; (0x12)
2) Ātrums;                    (0xED)
3) Akselerometra parametri;   (0xC3)
4) Informācija par karogu;    (0xFE)
5) Cita telemetrija, kas netiek aprakstīta šajā dokumentā, jo nav paredzēta dalībniekiem.

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

### 0xFE paketes uzbūve
1) Karogs uz trases: baits 0
#### Baita 0 atbilstības tabula
| Kods | Karogs      |
| -----| ---------   |
| 0x7F | Sarkans     |
| 0x3E | Dzeltens    |
| 0x4B | Zaļš        |
| 0x9A | Melns-balts |

NB! Bait 0x9A tiek parraidīts tikai iesaistītai mašīnai.

### Cita informācija par parraidāmo informāciju
1) Spriegums, strāva un enerģija tiek nolasīti no bloka un pilnībā atbilst tiem, kuri tiek sūtīti uz organizatoru serveri.
2) Ātrums tiek nolasīts no GPS un pilnībā atbilst tam, kas teik sūtīts uz organizatoru serveru. Ātruma ierobežojuma pārkāpšanas gadījumā nekāda papildus informācija netiek sūtīta. Ir jānodrošina vadītāja informēšana par šo notikumu, vai izmantot organizatoru nodrošināto iekārtu (izņemot U25).
3) Informācija par karogiem tiek parraidīta visām mašīnām (izņemot melnbaltu), neievērojot karogu darbības zonu.
4) Visa informācija tiek atjaunota reizi 0.5 sekundēs.

## Informācija par barošanas bloku
### Elektiskie parametri
| Parametrs     | Vērtība       |
| ------------- | ------------- |
| MAX Spriegums | 52V           |
| MAX Strāva    | 20A           |
| MAX Jauda     | 1000W         |
| Ieteicams U   | <48V          |

### Bloka kontroles plates parametri
1) Mikrokontrolieris ir ESPRESSIF ESP32, GSM modulis - SIMCOM A7670E.
2) Pēc mikrokontroliera pārstartēšanas drošības nolūkos barošanas bloka izeja tiek izslēgta.
3) Organsizatoriem tiek sūtīti sekojošie mašinas parametri:
   - Strāva;
   - Spriegums;
   - Patērētā enerģija;
   - GPS ātrums;
   - GPS koordinātes;
   - Rezerves akumulatora spriegums;
   - Galvenā akumulatora stāvoklis (ir/nav pieslēgts);
   - Galvenā akumulatora spriegums.
4) Organizatori attālināti var kontrolēt sekojošus parametrus:
   - Strāvas ierobežojums;
     NB! Organizatori patur tiesības samazinat jaudu, ja uz trases ir izveidojusies bīstama situācija!
   - Spriegums;
   - Bloka izejas stāvoklis (ON/OFF);
      NB! Organizatori patur tiesības izslēgt bloku nedrošas braukšanas vai noteikumu pārkāpšanas gadījumā!
   - Informācija par karogiem uz trases.

## Cita informācija
1) Dalībnieki var pieprasīt paketes identifikatora maiņu, ja tas sakrīt ar citu CAN ierīču pakešu identifikatoriem, sazinoties ar organizatoriem.
2) Dalībniekiem nav atļauts veikt bloka programmatūras modifikācijas.

## BUJ
### Kāds ir bloka ieslēgšanas laiks pēc baterijas pārslēgšanas?
   Bloks satur rezerves akumulatoru, tāpēc dažu sekunžu laikā parametri tiks uzstādīti uz bloka izejas. Ja rezerves akumulators ir izlādēts, ieslēģšana var aizņemt līdz 30 s.
   
### Kas notiek, ja sacensību dienā attalinātā kontrole nestrādā?
   Bloka parametru uzstādīšana un nolasīšana tiks veikta manuāli, izmantojot ekrānu vai WEB interfeisu. Informācija CAN interfeisā būs pieejama (izņemot karogus).

## Errata
1) CAN bitrate ir 250 kbps.
