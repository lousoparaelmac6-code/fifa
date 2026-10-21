const test = require('node:test');
const assert = require('node:assert/strict');
const fs = require('node:fs');
const os = require('node:os');
const path = require('node:path');
const { spawnSync } = require('node:child_process');

const html = fs.readFileSync(path.join(__dirname, '..', 'index.html'), 'utf8');
function inlineGameScript(source) {
  const scripts = [...source.matchAll(/<script>([\\s\\S]*?)<\\/script>/gi)];
  assert.ok(scripts.length, 'Debe existir el script principal del juego');
  return scripts[scripts.length - 1][1];
}

test('el JavaScript integrado del juego tiene sintaxis válida', () => {
  const dir = fs.mkdtempSync(path.join(os.tmpdir(), 'football-arena-'));
  const file = path.join(dir, 'game.js');
  fs.writeFileSync(file, inlineGameScript(html));
  const result = spawnSync(process.execPath, ['--check', file], { encoding: 'utf8' });
  assert.equal(result.status, 0, result.stderr || result.stdout);
});

test('la interfaz conserva controles y marcadores esenciales', () => {
  for (const id of ['pitch', 'overlay', 'start', 'pause', 'restart', 'homeScore', 'awayScore', 'time', 'shots', 'passes', 'saves', 'possession']) {
    assert.match(html, new RegExp('id=["\\']' + id + '["\\']'), 'Falta el elemento #' + id);
  }
  for (const key of ['touchPass', 'touchShoot']) assert.ok(html.includes('id="' + key + '"'));
});

test('la simulación representa once jugadores de campo por lado y dos porteros', () => {
  const script = inlineGameScript(html);
  assert.match(script, /const mates=\\[([^;]+)\\];/);
  assert.match(script, /const foes=\\[([^;]+)\\];/);
  const mates = script.match(/const mates=\\[([^;]+)\\];/)[1];
  const foes = script.match(/const foes=\\[([^;]+)\\];/)[1];
  assert.equal((mates.match(/num:/g) || []).length, 10, 'El equipo local debe tener diez compañeros más el jugador controlado');
  assert.equal((foes.match(/num:/g) || []).length, 10, 'El equipo rival debe tener diez jugadores de campo más el portero');
  assert.match(script, /homeKeeper=/);
  assert.match(script, /const keeper=/);
});

test('pausar y continuar no instala un segundo manejador de inicio', () => {
  const script = inlineGameScript(html);
  assert.match(script, /\$\('start'\)\.addEventListener\('click',start\)/);
  assert.doesNotMatch(script, /\$\('start'\)\.onclick=/);
});
