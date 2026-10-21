const test = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { spawnSync } = require('node:child_process');

const html = fs.readFileSync(path.join(__dirname, '..', 'index.html'), 'utf8');
function inlineGameScript(source) {
  // Evitar regex aquí: el patrón anterior quedó mal escapado y rompía Node antes de ejecutar los tests.
  const tagStart = source.indexOf('<script');
  const contentStart = tagStart < 0 ? -1 : source.indexOf('>', tagStart) + 1;
  const end = contentStart > 0 ? source.indexOf('</script>', contentStart) : -1;
  assert.ok(tagStart >= 0 && contentStart > tagStart && end > contentStart,
    'Debe existir el script principal del juego');
  return source.slice(contentStart, end);
}

test('el JavaScript integrado del juego tiene sintaxis válida', () => {
  const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'football-arena-'));
  const file = path.join(dir, 'game.js');
  fs.writeFileSync(file, inlineGameScript(html));
  const result = spawnSync(process.execPath, ['--check', file], { encoding: 'utf8' });
  assert.equal(result.status, 0, result.stderr || result.stdout);
  fs.rmSync(dir, { recursive: true, force: true });
});

test('la interfaz conserva controles y marcadores esenciales', () => {
  for (const id of ['pitch', 'overlay', 'start', 'pause', 'restart', 'homeScore', 'awayScore', 'time', 'shots', 'passes', 'saves', 'possession', 'touchPass', 'touchShoot']) {
    assert.ok(html.includes('id="' + id + '"'), 'Falta el elemento #' + id);
  }
});

test('la simulación representa once jugadores de campo por lado y dos porteros', () => {
  const script = inlineGameScript(html);
  const matesStart = script.indexOf('const mates=[');
  const foesStart = script.indexOf('const foes=[');
  const matesEnd = script.indexOf('];', matesStart);
  const foesEnd = script.indexOf('];', foesStart);
  assert.ok(matesStart >= 0 && matesEnd > matesStart, 'Falta la plantilla local');
  assert.ok(foesStart >= 0 && foesEnd > foesStart, 'Falta la plantilla rival');
  const mates = script.slice(matesStart, matesEnd);
  const foes = script.slice(foesStart, foesEnd);
  assert.equal((mates.match(/num:/g) || []).length, 10, 'El equipo local debe tener diez compañeros más el jugador controlado');
  assert.equal((foes.match(/num:/g) || []).length, 10, 'El equipo rival debe tener diez jugadores de campo más el portero');
  assert.ok(script.includes('homeKeeper='));
  assert.ok(script.includes('const keeper='));
});

test('pausar y continuar no instala un segundo manejador de inicio', () => {
  const script = inlineGameScript(html);
  assert.ok(script.includes("$('start').addEventListener('click',start)"));
  assert.ok(!script.includes("$('start').onclick="));
});
