const { chromium } = require('playwright');
const http = require('node:http');
const fs = require('node:fs');
const path = require('node:path');
const assert = require('node:assert/strict');

const html = fs.readFileSync(path.join(process.cwd(), 'index.html'));
const server = http.createServer((req, res) => {
  res.writeHead(200, { 'content-type': 'text/html; charset=utf-8' });
  res.end(html);
});

(async () => {
  await new Promise(resolve => server.listen(4173, '127.0.0.1', resolve));
  let browser;
  try {
    browser = await chromium.launch({ headless: true });
    const page = await browser.newPage({ viewport: { width: 1280, height: 900 } });
    const errors = [];
    const consoleErrors = [];
    const failedRequests = [];
    page.on('pageerror', error => errors.push(error.message));
    page.on('console', message => { if (message.type() === 'error') consoleErrors.push(message.text()); });
    page.on('requestfailed', request => failedRequests.push(request.url() + ': ' + request.failure()?.errorText));
    await page.goto('http://127.0.0.1:4173', { waitUntil: 'load' });
    await page.locator('#pitch').waitFor();
    assert.equal(await page.locator('#hs').innerText(), '0');
    const idleFrame = await page.locator('#pitch').evaluate(canvas => canvas.toDataURL());
    await page.locator('#start').click();
    await page.waitForFunction(() => document.querySelector('#overlay').classList.contains('hidden'));
    assert.match(await page.locator('#status').innerText(), /a jugar/i);
    await page.keyboard.down('ArrowRight');
    await page.waitForTimeout(500);
    await page.keyboard.up('ArrowRight');
    const playingFrame = await page.locator('#pitch').evaluate(canvas => canvas.toDataURL());
    assert.notEqual(playingFrame, idleFrame, 'El canvas no se actualizó al iniciar el partido');
    await page.locator('#pause').click();
    assert.match(await page.locator('#status').innerText(), /pausado/i);
    await page.locator('#start').click();
    await page.locator('#restart').click();
    assert.equal(await page.locator('#hs').innerText(), '0');
    assert.deepEqual(errors, [], 'La página produjo errores JavaScript');
    assert.deepEqual(consoleErrors, [], 'La consola produjo errores');
    assert.deepEqual(failedRequests, [], 'Hubo solicitudes fallidas');

    const mobile = await browser.newPage({ viewport: { width: 390, height: 844 }, isMobile: true, hasTouch: true });
    mobile.on('pageerror', error => errors.push(error.message));
    await mobile.goto('http://127.0.0.1:4173', { waitUntil: 'load' });
    assert.equal(await mobile.locator('.touch').isVisible(), true, 'Los controles táctiles no aparecen en móvil');
    await mobile.locator('#start').click();
    await mobile.waitForFunction(() => document.querySelector('#overlay').classList.contains('hidden'));
    await mobile.locator('[data-action="pass"]').dispatchEvent('pointerdown', { pointerId: 1, pointerType: 'touch', isPrimary: true });
    await mobile.close();
    assert.deepEqual(errors, [], 'La página produjo errores JavaScript');
    console.log('OK: carga, renderizado, inicio, teclado, pausa, reinicio, controles móviles y sin errores.');
  } finally {
    if (browser) await browser.close();
    await new Promise(resolve => server.close(resolve));
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
