Batterie betriebene Tür/Fenster Überwachung mit dem ESP-01

Die Hardware muss extrem sparsam sein, damit die Batterien/Akkus lange halten.
Deshalb werden die Widerstände wo nötig sehr hoch gewählt. 
Zusätzlich kommt ein CMOS-EXOR zum Einsatz, der den ESP-01 bei Änderung am Eingang auf weckt.
Warum die Schaltung: Der ESP8266 hat keinen Interrupt on change. Deshalb muss der ESP nach 
Änderung des Eingangszustandes aus dem deep sleep geweckt werden, in dem er wegen Strom sparen versetzt wurde.
Die Schaltung ist so aufgebaut, dass sowohl beim öffnen, wie auch beim schließen eine (REED)Kontaktes ein kurzer 
Low-Impuls generiert wird, der auf den RESET Eingang des ESP gelegt wird. Die Schaltung verbraucht nur wenige µA.
Der grösste Stromverbraucher ist dann noch die rote LED auf dem ESP-01, die fest mit der Versorgungsspannung 
verbunden ist und nicht abgeschaltet wrden kann. Hier die Empfehlung,die LED aus zu löten oder anders 
(brutal mechanisch) zu entfernen.

Die Software funktioniert im wesentlichen so:<br>
Der ESP meldet sich am Netzwerk an (dafür die Einträge SSID und password) Danach meldet er sich beim mqtt Broker an.
Er meldet den Status des Eingang (offen oder geschlossen) und legt sich dann schlafen. 
Ein Reset weckt ihn auf und das Spiel beginnt von vorn.
