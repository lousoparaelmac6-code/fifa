# Football Arena

Prototipo independiente de fútbol 2D en evolución. La versión actual es un punto de partida jugable, no un clon comercial 3D de EA SPORTS FC ni de eFootball.

## Ejecutar

No requiere dependencias externas. Abrí `index.html` en un navegador moderno.

## Controles

- **WASD / flechas:** mover al jugador.
- **J:** pase.
- **K / Espacio:** rematar.
- **Q:** cambiar el jugador controlado.
- En pantallas táctiles aparecen controles de movimiento, pase y remate.
- Dificultad: Amateur, Pro o Leyenda.

## Estado implementado

- Campo 2D, marcador, reloj, pausa, reinicio y pantalla final.
- Once jugadores de campo por equipo y un portero por lado.
- Compañeros y rivales con comportamiento básico de seguimiento y presión.
- Pase, remate, recuperación, goles y atajadas.
- Estadísticas sencillas, dificultad y controles táctiles.
- Interfaz adaptable a pantallas pequeñas.
- Pruebas automáticas iniciales y flujo de validación de GitHub Actions.

## Validación

Con Node.js 22 o compatible:

```sh
npm test
```

Estas pruebas verifican sintaxis y elementos estructurales básicos; no reemplazan jugar partidos manualmente ni prueban todas las reglas.

## Próximas fases

Consultar [docs/ARQUITECTURA_Y_PLAN.md](docs/ARQUITECTURA_Y_PLAN.md) para la hoja de ruta: simulación estable, reglas, IA táctica, animación, modos y, más adelante, distribución y online.

## Derechos

Proyecto independiente. No incluye recursos oficiales de FIFA, EA SPORTS o Konami, ni pretende estar afiliado a esas marcas. Los equipos y recursos deberán ser originales o contar con licencias adecuadas.
