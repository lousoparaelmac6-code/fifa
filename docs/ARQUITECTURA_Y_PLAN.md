# Arquitectura y plan de producción — Football Arena

## Estado real del proyecto

La rama principal contiene un prototipo web 2D autocontenido en `index.html`. Esta versión no equivale a un juego comercial 3D y todavía no implementa todas las reglas del fútbol ni los modos de una producción completa. El objetivo de este documento es guiar una evolución incremental con pruebas, sin afirmar sistemas que aún no existen.

## Capas de diseño

1. **Simulación:** posiciones, velocidades, contactos, balón, reloj y marcador.
2. **Decisión:** intención de jugadores controlados por IA y elección de objetivos.
3. **Control:** teclado y controles táctiles traducidos a acciones.
4. **Presentación:** dibujo del campo, jugadores, marcador, mensajes y cámara.
5. **Flujo de partido:** inicio, pausa, reanudación, goles y final.
6. **Persistencia/servicios:** todavía fuera del alcance de esta versión; no hay multijugador ni guardado de carrera.

La presentación no debe decidir goles ni cambiar el estado competitivo. Las acciones de juego deben resolverse en la lógica de simulación y luego reflejarse en el dibujo.

## Fases priorizadas

### Fase 1 — Núcleo jugable
- Partido con once jugadores de campo por equipo y un portero por equipo.
- Controles consistentes, aceleración/frenado y posesión coherente.
- Pase, tiro, recuperación, colisiones y goles.
- Inicio, pausa, reinicio y final sin bucles de animación duplicados.
- Pruebas de sintaxis y estructura en cada cambio.

### Fase 2 — Simulación y reglas
- Paso lógico fijo independiente de la frecuencia de dibujo.
- Resolver contactos en un único lugar; límites para velocidades y penetraciones.
- Saques, faltas, tarjetas, córneres, saques de banda, fuera de juego y tiempo añadido.
- Casos de prueba repetibles para goles, rebotes, atajadas y reinicios.

### Fase 3 — IA y táctica
- Estados de decisión con transiciones explícitas.
- Apoyo, desmarque, cobertura, presión y repliegue.
- Formaciones, anchura, profundidad y perfiles de dificultad versionados.
- Registrar razones básicas de las decisiones para depurar comportamientos.

### Fase 4 — Animación y presentación
- Recursos propios o licenciados, con procedencia y licencia documentadas.
- Sincronización de contactos del balón con las acciones visuales.
- Sonido, cámara, accesibilidad y opciones de control.
- No usar marcas, plantillas, música, escudos ni recursos protegidos sin autorización.

### Fase 5 — Modos y datos
- Selección de equipos ficticios, alineaciones y partido rápido.
- Torneo y calendario solo después de estabilizar el núcleo.
- Datos separados de la lógica y guardados versionados.

### Fase 6 — Distribución y online
- Definir primero plataformas objetivo y requisitos de rendimiento.
- Multijugador solo con servidor autoritativo, validación de acciones y pruebas de latencia.
- Empaquetado y artefactos de distribución después de elegir motor y alcance. El prototipo actual no tiene instalador ni APK.

## Criterios mínimos de aceptación

- El mismo input no inicia dos bucles de actualización.
- El reloj avanza solo mientras el partido está activo.
- Los goles actualizan marcador, posesión y posiciones de reinicio.
- El balón no queda fuera de límites ni adquiere velocidades infinitas.
- El jugador controlado responde en teclado y pantalla táctil.
- Los errores de sintaxis y estructura bloquean la validación automática.
- No se afirma que las pruebas de navegador, dispositivos o jugabilidad manual se ejecutaron si no se ejecutaron.

## Verificación

`npm test` ejecuta comprobaciones estructurales y valida la sintaxis del JavaScript integrado. Esto no sustituye pruebas manuales en navegador ni confirma por sí solo que el juego se sienta bien o que cada regla esté correctamente implementada.
