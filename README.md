# PROG3 Lab 03

Autor: Prof. Dr.-Ing. Enrico Schröder, OHM Technische Hochschule Nürnberg, Fakultät EFI

**Willkommen zur dritten Übung zur Veranstaltung PROG3 / Teil B!**

# Übersicht

In dieser Übung werden wir unser Spiel fertigstellen. Wir werden uns um Kollisionsabfrage und die Bewegungsphysik
unseres Raumschiffs kümmern. Ziel ist es, am Ende ein fertiges kleines Spiel zu haben!

![](screenshots/screenshot_asteroids.png)

Sie können mit Ihrem Code aus der letzten Übung weiterarbeiten oder den Code aus diesem Repository als Grundlage nehmen.

Arbeiten Sie dieses Dokument bitte von oben nach unten komplett ab! Lesen Sie die einzelnen Abschnitte zuerst komplett
durch, bevor Sie loslegen!

# Aufgabe 01

**Implementieren Sie eine simple Bewegungsphysik für Ihr Raumschiff.**

Vermutlich bewegt sich Ihr Schiff aktuell wie ein Fahrzeug, d.h. es bewegt sich immer in Blickrichtung. Wir wollen uns
nun anschauen, wie wir eine realistischere Bewegungsphysik implementieren können, bei der das Raumschiff mittels seines
Antriebs Schub in Blickrichtung erzeugen kann, sich aber dann unabhängig von der Blickrichtung weiterbewegt. Hinweis:
Falls Sie schon eine Bewegungsphysik direkt in Ihrer Spaceship-Klasse implementiert haben, bearbeiten Sie diese Aufgabe
bitte trotzdem!

Wahrscheinlich bewegen Sie das Raumschiff aktuell direkt mittels der Pfeiltasten, d.h. seine Position auf dem Bildschirm
wird um einen fixen Wert verändert. Wir wollen nun Geschwindigkeit, Beschleunigung und Reibung berücksichtigen.

Ziel ist es, eine Klasse `PhysicsObject` zu implementieren, die die Bewegungsphysik für Objekte in Ihrem Spiel
übernimmt. Diese Klasse soll von Ihrer GameObject-Klasse (der Basisklasse für alle Ihre Objekte) ableiten. Wenn Sie
alles sauber implementiert haben, werden Sie merken, dass Sie dann an Ihrer Spaceship-Klasse selbst nur minimale
Änderungen vornehmen müssen, um die neue Bewegungsphysik zu nutzen.

#### Aufgabe 01_a

Vorbereitungen in Ihrer GameObject-Klasse: Sie benötigen eine Update-Methode in Ihrer GameObject-Klasse,
z.B. `virtual void update()`. Diese Methode soll einmal pro Frame für jedes Objekt aufgerufen werden. Sinn der Methode
ist es, periodische Updates der Zustände ihrer Spielobjekte zu ermöglichen. Vielleicht habe Sie eine solche Methode
bereits genutzt, um Asteroiden und Projektile zu bewegen. Falls nicht, fügen Sie diese Methode bitte hinzu. Die Methode
in ihrer GameObject-Klasse ist leer, sie soll von den abgeleiteten Klassen überschrieben werden können.

#### Aufgabe 01_b

Zuerst müssen wir uns darum kümmern, dass das Raumschiff seine Geschwindigkeit über mehrere Frames hinweg beibehält.

Erstellen Sie eine neue Klasse `PhysicsObject`. Diese soll von Ihrer GameObject-Klasse ableiten. Als Member-Variablen
soll sie zunächst nur einen Geschwindigkeitsvektor (x- und y-Komponente) haben. Nutzen Sie am besten die
Klasse `raylib::Vector2` dafür. Dieser Vektor soll mittels setter-Methode von außen setzbar sein.

Überschreiben Sie in Ihrer PhysicsObject-Klasse die Update-Methode. In dieser Methode soll die Position des Objekts um
den Geschwindigkeitsvektor verändert werden.

Verändern Sie Ihre Spaceship-Klasse so, dass sie von Ihrer PhysicsObject-Klasse ableitet. Nutzen Sie die setter-Methode,
um die Geschwindigkeit des Raumschiffs zu setzen. Ihr Raumschiff sollte sich nun mit konstanter Geschwindigkeit über den
Bildschirm bewegen.

#### Aufgabe 01_c

Nun schauen wir uns Beschleunigung und Reibung an. Beschleunigung ist Veränderung der Geschwindigkeit über die Zeit.
Reibung ist eine Kraft, die der Bewegungsrichtung entgegenwirkt und die Geschwindigkeit über die Zeit verringert. Zwar
gibt es im Weltraum nur sehr geringe Reibungskräfte, allerdings steuert sich das Raumschiff mit stärkerer Reibung
angenehmer.

Implementieren Sie in Ihrer PhysicsObject-Klasse zwei weitere Member-Variablen: Beschleunigung und Reibung.
Beschleunigung soll mittels einer geeigneten Methode von außen setzbar sein (
z.B. `void accelerate(raylib::Vector2 acceleration)`). Reibung soll konstant sein und nicht veränderbar.

Nun aktualisieren Sie die Update-Methode Ihrer PhysicsObject-Klasse, sodass sie die Geschwindigkeit abhängig von der
Beschleunigung und Reibung verändert. Sie können folgende vereinfachte Formeln nutzen:

```
dt = 1/60                                                       // Zeit zwischen zwei Frames
Geschwindigkeit = Geschwindigkeit + Beschleunigung * dt         // Beschleunigung
Geschwindigkeit = Geschwindigkeit - Geschwindigkeit * Reibung   // Reibung
move(Geschwindigkeit)                                           // Position aktualisieren
Beschleunigung = 0                                              // Beschleunigung zurücksetzen
```

Wenn Sie nun, anstatt die Geschwindigkeit direkt zu setzen, die Beschleunigung des Raumschiffs mittels Tastendruck
setzen, sollte sich das Raumschiff realistischer verhalten.

Verändern Sie die Update-Methode Ihrer Spaceship-Klasse z.B. wie folgt:

```
    if(IsKeyDown(KEY_W))
        accelerate(raylib::Vector2{0.f, -thrust}.Rotate(DEG2RAD * rot));
```

Dies beschleunigt das Raumschiff in Blickrichtung um den Wert `thrust` (`rot` ist die aktuelle Rotation des Schiffs in
Grad). Experimenten Sie mit geeigneten Werten für `thrust` und der Reibung, bis Sie ein realistisches Verhalten haben.
Hinweis: Geeignete Startwerte können sein: `thrust = 600` und `Reibung = 0.01`.

Fügen Sie den Code Ihrer PhysicsObject-Klasse dem Protokoll hinzu! Notieren Sie außerdem, welche Änderungen Sie an Ihrer
Spaceship-Klasse vorgenommen haben.

# Aufgabe 02

**Implementieren Sie Kollisionsabfrage.**

Sie haben sich vielleicht in der letzten Übung schon Gedanken gemacht, wie Sie Kollisionsabfrage implementieren können.
Dabei sind eventuell auf Probleme gestoßen, die sich nur umständlich (d.h. durch viel Code) lösen lassen, z.B. durch
große if-else Konstrukte, die alle möglichen Kombinationen von Kollisionen (Raumschiff-Asteroid, Asteroid-Raumschiff,
Projektil-Asteroid, Asteroid-Projektil usw.) behandelt.

Wir werden in diese Aufgabe Features von C++ aktiv nutzen, die das Ganze einfacher machen. Konkret werden wir uns
anschauen, wie wir virtuelle Funktionen nutzen können, um Kollisionsabfrage zu implementieren.

Die Idee dabei ist, dass jede Klasse selbst bestimmt, wie sie mit Kollisionen umgeht.

#### Aufgabe 02_a

Erweitern sie Ihre GameObject-Klasse um eine virtuelle Methode `virtual void handleCollision(GameObject* other)`
bzw. `virtual void handleCollision(std::shared_ptr<GameObject> other)`. Diese Methode soll von den abgeleiteten Klassen
überschrieben werden können. Die Methode soll als Parameter ein GameObject übergeben bekommen, mit dem die Kollision
stattgefunden hat.

#### Aufgabe 02_b

Implementieren Sie in Ihrer GameManager-Klasse (bzw. in Ihrer main.cpp-Datei, falls Sie keine eigene GameManager-Klasse
haben), eine Methode `void checkCollisions()`. Diese Methode soll für jedes GameObject in Ihrer Liste mit allen anderen
GameObjects in Ihrer Liste prüfen, ob eine Kollision stattgefunden hat. Falls ja, soll die `handleCollision`-Methode des
GameObjects aufgerufen werden, mit dem die Kollision stattgefunden hat.

Hinweis: Nutzen Sie die raylib-Methode `CheckCollisionCircles(...)` zur Überprüfung, ob zwei Kreise sich überschneiden.
Berechnen Sie einen geeigneten Kreis, der das jeweilige Objekt überdeckt.

Folgender Algorithmus könnte Ihnen als Vorlage dienen:

```
Für jedes GameObject in der Liste:
    Für jedes andere GameObject in der Liste:
        Wenn die GameObjects nicht gleich sind:
            Wenn die GameObjects sich überschneiden:
                Rufe handleCollision des ersten GameObjects mit dem zweiten GameObject als Parameter auf
                Rufe handleCollision des zweiten GameObjects mit dem ersten GameObject als Parameter auf
```

#### Aufgabe 02_c

Implementieren Sie die `handleCollision`-Methoden Ihrer einzelnen Klassen. Um herauszufinden, von welchem Typ ein
GameObject ist, können Sie `dynamic_cast` bzw. `dynamic_pointer_cast` nutzen. Diese gibt einen Zeiger auf das GameObject
zurück, falls es sich um ein GameObject vom angegebenen Typ handelt, ansonsten einen Null-Zeiger.

Beispiel:

```
void Spaceship::handleCollision(std::shared_ptr<GameObject> otherObj)
{
    std::shared_ptr<Asteroid> asteroid = std::dynamic_pointer_cast<Asteroid>(otherObj);
    if(asteroid != nulltpr)
    {
        // otherObj ist vom Typ Asteroid, also können wir die Kollision behandeln...
    }
}
```

Es reicht für diese Aufgabe aus, dass Sie sämtliche Kollisionen auf einfache Art und Weise komplett in der jeweiligen
handleCollision-Methode behandeln.

Fügen Sie Ihre Kollisionsbehandlungsmethoden dem Protokoll hinzu! Beschreiben Sie das Verhalten Ihrer Klassen bei
Kollisionen!

Sie werden einige Kollisionen haben, die eigentlich zusätzlich noch an anderer Stelle behandelt werden müssten.
Beispiele dafür sind:

- Das Projektil soll zerstört werden, wenn es mit einem Asteroiden kollidiert (aber das Projektil kann sich nicht selbst
  zerstören).
- Der Asteroid soll in kleinere Asteroiden zerfallen (aber ein Asteroid kann keine anderen Asteroiden spawnen).
- Kollisionen des Raumschiffs mit einem Asteroiden sollen nur einmal zum Lebenspunktabzug führen (allerdings wird
  aktuell die Kollision in jedem Frame behandelt).

Hierfür brauchen Sie noch etwas mehr Logik, die wir der Bonusaufgabe überlassen.

# Aufgabe 03 (Bonusaufgabe)

**Feinschliff: Implementieren Sie die restlichen Elemente, die für Ihr fertiges Spiel noch fehlen.**

Es kann nicht schaden, wenn Sie sich noch etwas mehr mit Ihrem Spiel beschäftigen und es vervollständigen. Die beste
Übung, um C++ zu lernen, ist, C++-Code zu schreiben!

Machen Sie also aus Ihrem Spiel ein fertiges Spiel! Hier ein paar Ideen, was Sie noch implementieren könnten:

- Komplettieren Sie die Kollisionsabfrage, sodass die oben genannten Probleme gelöst sind.
- Implementieren Sie Punktestand, Leben und Game-Over Bildschirm.
- Implementieren Sie das Spawnen von neuen Asteroiden.
- ...

--------------

### Art Credit

Spaceship: opengameart.org, License Creative Commons 0 - Public Domain,
Bullets: opengameart.org, License Creative Commons 4 - (c) @janachumi,
Background: generated with Adobe Firefly,
Ohmsteroid: License Creative Commons 4 - (c) E.Schröder