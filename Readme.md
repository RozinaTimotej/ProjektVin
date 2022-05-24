# Projekt pri predmetu VIN (RFID "odklepanje" vrat)

## Osnovna ideja
Za svoj projekt bom s pomočjo RFID modula (Rc522) in kartice odklepal  vrata (v mojem primeru bo namesto ključavnice le LED dioda ki bo kazala stanje vrat). Možna bo tudi dodaja nove kartice s pritiskom na gumb. Na koncu pa sem še dodal, da preko serijske komunikacije uporabnik vpiše ime, sistem pa ga nato preko LCD zaslona pozdravi.

## Video demonstracije končnega projekta (pritisk za povezavo na video)
[![Demonstracija projekta](https://img.youtube.com/vi/4G5TbsRWuYs/maxresdefault.jpg)](https://www.youtube.com/shorts/4G5TbsRWuYs)

## Komponente
Pri projektu sem uporabil naslednje komponente:
* Arduino
* RFID modul RC422
* GUMB
* LED
* LCD zaslon 16x2 (LCD 1602)

## Opis komponent
> ### Arduino
> ![image](https://user-images.githubusercontent.com/61662167/170107027-04927a48-d9a3-4d23-9c36-74a2d1f2e103.png)
> > Je mikrokrmilnik, ki nam omogoča lahko uporabno V/I naprav, nanj lahko zato priključimo senzorje, tipke, LED, prikazovalnik, motorje ipd. Programiramo pa z računalnikom v razvojnem okolju ARDUINO IDE.
> ### RFID modul RC422
> > ![image](https://user-images.githubusercontent.com/61662167/170108415-879e903b-97be-4a7e-a2aa-86c8954d5767.png)
> > 
> > RFID ali kar Radiofrekvenčna identifikacija je tehnologija za preos podatkov med bralnikom in elektronsko oznako v namen identifikacije. Sestavljena je iz integriranega vezja (čipa) in pa antene, ki sprejema in oddaja signale. Bralec ima anteno, ki proizvaja visokofrekvenčno magnetno polje. Na drugi strani pa je čip, ki ponavadi ne vsebuje svojega napajanja, tega dobi od antene (preko elektromagnetnega polja), in nato sam odda informacije bralcu.
> >
> > Modul RC422 pride v paru z kartico in ključkom, ki imata 1KB spomina. Modul RC522 ustvarja 13.56MHz elektromagnetno polje, ki je uporabljeno za komunikacijo z RFID čipi (ISO 14443A standard). Bralec komunicra z mikrokontrolerjem preko 4pinskega serijskega perifernega vmesnika (Serial Peripheral Interface - SPI podpira pa tudi I2C in UART) z najhitrejšim prenosom 10Mbps. Modul vsebuje tudi Interrupt pin, ki nam lahko sporoči kadar pride kartica v bližino. Delovno napajanje modula je med 2.5 in 3.3V, logični pini pa podpirajo do 5V napetosti, tako ga lahko povežemo na Arduino brez problemov.
> > * VCC - dovaja napetost modulu, ta je lahko med 2.5 in 3.3 volti (pazimo da ne povežemo na 5V).
> > * RST - je vhod za resetiranje in ugašanje. Ko gre pin na "LOW" se modul "izkluči", tu so ugasnjeni vsi vhodni pini in oscilator. Ko gre pin na "HIGH" se modul resetira.
> > * GND - Je ground pin, katerega povežemo na GND pin na Arduino.
> > * IRQ - je interput pin, ki lahko mikrokontroler opozori ko pride RFID čip v bližino, jaz tega ne uporabljam, ker knižnjica ne podpira.
> > * MISO/SC/Tx - V načinu SPI se pin obnaša kot  Master-In-Slave-Out. V načinu I2C kot serijska ura in v načinu UART kot serijski izhod za podatke.
> > * MOSI - "Master Out Slave In" je SPI input.
> > * SCK - "Serial clock" sprejema urine pulze, ki jih oddaja "SPI bus Master" oz. Arudino.
> > * SS/SDA/Rx - v načinu SPI se obnaša kot vhod signala. V načini I2C se obnaša kot serijski podatki in v načinu UART kot vhod za serijske podatke.
> > 
> > ![image](https://user-images.githubusercontent.com/61662167/170110945-a0a4bec6-bc31-4acd-8359-08a1d5c29a9c.png)
> > 
> > Vsak arduino ima drugačne SPI pine, modul pa more biti povezan kot je prikazano odzgoraj. Ker komunikacija z modulom ni preprosta, sem sam uporabil knjižnico "MFRC522" dostopna na (https://github.com/miguelbalboa/rfid), ki zelo poenostavi branje in pisanje z modulom.
> ### Gumb
> > Uporabil sem navaden Gumb. Ki je povezan na pin 2, ob pritisku na gumb omogočimo, da uporabnik doda nov čip, za odklepanje vrat.
> ### LED
> > Uporabil sem navadno zeleno LED diodo. Ko uporabnik prisloni kartico na bralnik in je ta pravilna (ima dovoljenje za odklepanje) se LED dioda zasveti, kar nakazuje na odklep vrat.
> ### LCD zaslon 16x2
> > ![image](https://user-images.githubusercontent.com/61662167/170117990-522f8e36-b3e2-4563-8724-a9793d009c81.png)
> > 
> > LCD zaslon 16x2 ima možnost dodajanja 16 črtk v 2 vrstici.
> > * VSS - Povezava na gnd
> > * VDD - Povezava na 5V
> > * V0 - Pin za kontrast (0V) - maksimalen kontrast, (5V) - minimalen kontrast
> > * RS - "Register Select", 0: Ukazni register, 1: Podatkovni register
> > * RW - "Read Write", 0: Write mode, 1: read mode
> > * E - "Enable" pin za vključitev LCD
> > * D0-D7 - LCD podatkovno vodilo. So tu za paralelni prenos podatkov
> > * LED+ - Anoda za osvetlitev odzadja (3.3V)
> > * LED- - Katoda za osvetlitev odzadja (GND)
> > 
> > LCD zaslon sem uporabil za izpis vseh pomembnih informacij (Prblizajte kartico, Vpisite ime, Sporocilo o uspesnosti/neuspesnosti in pozdrav z imenom uporabnika.)
> ### Serijska komunikacija z računalnikom
> > Na koncu sem dodal še, da ob dodajanju kartice sistem vpraša za ime, katerega nato asociira s čipom. Ko je kartica dodana in ime vpisano, si lahko uporabnik odklene vrata ( sistem ga tudi pozdravi z: "Zivjo <ime>"), zato bi lahko sistem uporabljali tudi za npr. štetje ur delavcev ipd.
