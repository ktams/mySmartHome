Batterie betriebene Tür/Fenster Überwachung mit dem ESP-01

Die Hardware muss extrem sparsam sein, damit die Batterien/Akkus lange halten.
Deshalb werden die Widerstände wo nötig sehr hoch gewählt. 
Zusätzlich kommt ein CMOS-EXOR zum Einsatz, der den ESP-01 bei Änderung am Eingang kurz mit Spannung versorgt.
Der ESP muss sofort nach dem Power up selbst für den Erhalt der Spannung sorgen.
Die Schaltung ist so aufgebaut, dass sowohl beim Öffnen, wie auch beim Schließen eines (REED)Kontaktes ein kurzer 
Low-Impuls generiert wird, der den Transistor (FET) durch schaltet. Die Schaltung verbraucht nur wenige µA.
Der grösste Stromverbraucher ist dann noch die rote LED auf dem ESP-01, die fest mit der Versorgungsspannung 
verbunden ist und nicht abgeschaltet wrden kann. Hier die Empfehlung, die LED aus zu löten oder anders 
(brutal mechanisch) zu entfernen,wenn sie stört. Sie ist nur während der Wach-Phase an, so dass sie auch getrost dran bleiben kann.

Die Software funktioniert im wesentlichen so:<br>
Als erstes muss der ESP dafür sorgen, dass der Transistor durchgeschaltet bleibt.
Der ESP meldet sich dann am Netzwerk an (dafür die Einträge SSID und password) Danach meldet er sich beim mqtt Broker an.
Er meldet den Status des Eingang (offen oder geschlossen) und legt sich dann schlafen, indem er den Transistor abschaltet und sich damit die Spannung entzieht.. 
Eine Änderung am Kontakt weckt ihn auf und das Spiel beginnt von vorn.
