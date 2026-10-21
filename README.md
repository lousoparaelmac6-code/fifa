# Fútbol Arena — reconstrucción Unreal Engine

Esta rama inicia una base nativa de Unreal Engine 5.6 y C++, siguiendo el prompt maestro de ingeniería de juegos de fútbol. La rama `main` y el juego web anterior se conservan intactos como referencia; esta rama no cambia Pages.

## Arquitectura inicial
- `MatchSimulationSubsystem`: reloj de simulación con paso fijo de 1/60 s, seed explícita y diagnóstico.
- `PlayerMotorComponent`: locomoción desacoplada, aceleración y límites de velocidad/giro.
- `BallPhysicsComponent`: estado físico del balón, impulso, gravedad, rebote y fricción inicial.
- Pruebas de contrato para límites del motor y del impulso del balón.

## Estado real
**Andamiaje inicial, no juego completo.** Faltan estadio, cámara, input, equipos, control del balón, IA táctica, reglas arbitrales, animaciones, audio, modos, guardado, red e interfaz. Las componentes todavía no están conectadas al subsistema ni calibradas. Los parámetros son provisionales.

Instalar Unreal Engine 5.6 y Visual Studio 2022 con desarrollo de juegos C++. Abrir `FutbolArena.uproject`, generar archivos del proyecto si se solicita y compilar `FutbolArenaEditor`. Este entorno remoto no tiene Unreal Engine disponible, por lo que no afirmo que compile ni que las pruebas pasen.

Cada sistema debe tener unidades documentadas, parámetros versionados, seeds reproducibles, telemetría y pruebas de regresión. La presentación no decide goles, posesión ni contactos. No se copiará código ni recursos propietarios de EA SPORTS FC o Konami eFootball.
