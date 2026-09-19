# Impianto di allarme con Arduino

Progetto di un sistema di allarme basato su Arduino, progettato per rilevare movimenti e gestire l'attivazione/disattivazione dell'impianto tramite RFID.

## Funzionalità principali

- Rilevamento del movimento tramite sensore PIR.
- Attivazione dell'allarme con buzzer, LED di stato e display LCD.
- Autenticazione tramite modulo RFID e chiavi autorizzate.
- Ritardo di uscita di 8 secondi prima dell'attivazione dell'allarme.
- Reset e nuova configurazione delle chiavi RFID tramite pulsante.
- Visualizzazione dello stato del sistema sul display LCD.

## Componenti utilizzati

- Arduino
- Sensore PIR
- Modulo RFID
- Display LCD
- Buzzer
- LED rosso, giallo e verde
- Pulsante di reset
- Breadboard e cablaggi

## Logica di funzionamento

L'impianto può trovarsi negli stati di allarme inserito, allarme in corso e allarme disinserito. Quando il sensore PIR rileva un movimento con l'impianto inserito, vengono attivati buzzer, LED giallo e messaggio di allarme sul display. Una chiave RFID autorizzata permette di disattivare o riattivare il sistema.

## Libreria necessaria

La cartella `Libreria_rfid` è inclusa per rendere il progetto completo e permettere l’esecuzione degli sketch senza dover cercare dipendenze esterne.

Prima di aprire gli sketch nell’IDE Arduino, copia o installa la libreria nella cartella delle librerie di Arduino.
