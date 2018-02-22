Bewegungsmelder mit ESP-01 und PIR SR HC501

Die Hardware ist recht einfach: <br>
Gleich-Spannung kommt aus einem Steckernetzteil und kann zwischen 5 und 15V liegen.<br>
Diese Spannung wird für den PIR benötigt. Ein Step-Down Wandler macht daraus 3,3V für den ESP-01.<br>
Das ist alles, der Rest ist Software.

Die Software funktioniert grob so:<br>
Der ESP-01 meldet sich am Netzwerk an (Dafür die Einträge für SSID und password).<br>
Ist das erledigt, meldet er sich beim mqtt Broker an und bucht die "mqtt_intopic" Meldung. 
Dort erwartet er eine Rückmeldung, ob seine "mqtt_topic" Meldung erfolgreich abgesetzt wurde.
Dies muss natürlich ein Programm wie z.B. Openhab2, was ich zur Haussteuerung einsetze, erledigen.

Ausgelöst wird so eine Meldung durch den PIR. Der wird so eingestellt, dass er in dem Bereich auslöst, 
der überwacht werden soll. Die Zeit sollte nicht zu lang gewählt werden, da der PIR ständig nachtriggert 
(kann man aber ändern, dann natürlich so lange, wie erforderlich einstellen).

Ich habe das im Keller installiert und auf eine Minute eingestellt. 
Nur wenn man länger als eine Minute absolut still steht, bekommt man ein Problem ;-)
