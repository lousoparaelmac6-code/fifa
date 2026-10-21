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
    page.on('pageerror', error => errors.push(error.message));
    await page.goto('http://127.0.0.1:4173', { waitUntil: 'load' });
    await page.locator('#pitch').waitFor();
    assert.equal(await page.locator('#hs').innerText(), '0');
    await page.locator('#start').click();
    await page.waitForFunction(() => document.querySelector('#overlay').classList.contains('hidden'));
    await page.keyboard.down('ArrowRight');
    await page.waitForTimeout(500);
    await page.keyboard.up('ArrowRight');
    await page.locator('#pause').click();
    assert.match(await page.locator('#status').innerText(), /pausado/i);
    await page.locator('#start').click();
    await page.locator('#restart').click();
    assert.equal(await page.locator('#hs').innerText(), '0');
    assert.deepEqual(errors, [], 'La página produjo errores JavaScript');
    console.log('OK: carga, canvas, inicio, controles, pausa y reinicio; sin errores JavaScript.');
  } finally {
    if (browser) await browser.close();
    await new Promise(resolve => server.close(resolve));
  }
})().catch(error => { console.error(error); process.exitCode = 1; });
