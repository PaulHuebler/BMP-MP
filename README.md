# BMP-MP

Software zum Editieren und Verarbeiten von Bitmap Bildern.
Dieses Projekt entstand im Rahmen des Multimedia-Moduls der TU Freiberg im Sommersemester 2021 und wurde von Benjamin Backhaus und Paul Hübler erstellt.

## Benutzerhandbuch

### Installation

Nach dem Download der Dateien navigieren Sie in den Ordner `src/` und führen dort mit dem Befehl `make` das Makefile aus. Nun können Sie mit `./bmp-mp` das Programm starten.

### Laden und Speichern eines Bildes

Nach dem Start des Programms navigiert man in der Menu-Bar am oberen Rand des Programmfensters zum Eintrag „File“ und wählt darin den Menüpunkt „**Open**“ aus. Es öffnet sich ein File-Explorer, in dem man zum Speicherort des Bildes, welches man bearbeiten möchte, navigiert. Beachten Sie, dass das Bild das Dateiformat **.bmp** haben muss, um bearbeitet werden zu können. Das Bild sollte nun in der Mitte des Programmfensters angezeigt werden.

Das **Speichern** funktioniert sehr ähnlich: Navigieren Sie dazu wieder zum Menu-bar Eintrag „File“ und wählen Sie dann „**Save as**“. Nun können Sie einen Speicherort und einen Dateinamen auswählen.

### Anwendung der Manipulations-Funktionen

Ist ein Bild geladen und wird es im Programmfenster angezeigt, können Sie es nun **manipulieren**. Dazu finden sie ebenfalls in der Menu-Bar verschiedene Einträge, welche die Namen der Bearbeitungs-Operationen tragen. Klicken Sie eine an, und unter dem Bild erscheinen verschiedene Kontrollknöpfe bzw. Eingabefelder. Durch Klicken auf diese Buttons verändern Sie das Bild und das Ergebnis wird sofort angezeigt.

Wenn Sie aufgefordert werden, **Farbwerte** einzugeben, dann handelt es sich hierbei um Werte **zwischen 0 und 255** aus dem HSV-Farbraum. Ähnlich verhält es sich mit der Eingabe von **Toleranz**werten: Diese legen fest, wie groß der Toleranzbereich um den verwendeten Farbwert sein soll. Farben innerhalb des Bereichs werden von der jeweiligen Funktion verändert, Farben außerhalb nicht.

Durch Betätigen des **Undo-Buttons** können Sie die durchgeführten Änderungen mit der aktuell ausgewählten Funktion rückgängig machen. Beachten Sie, dass Sie nach aktuellem Stand der Implementierung beim Wechseln der Bildbearbeitungs-Funktion die letzten Änderungen nicht mehr rückgängig gemacht werden können. Wenn Sie einen „Checkpoint“ anlegen wollen, zu dem Sie mit Undo zurückspringen können, ohne die aktuelle Manipulations-Funktion zu wechseln, verwenden Sie den „Save“-Button in der Menubar.

## Genutzte Bibliotheken

GTK3 - https://www.gtk.org/
Bitmap Bibliothek - https://github.com/JayTee42/bitmap

