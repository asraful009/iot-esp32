
import express from 'express';
import { faker } from '@faker-js/faker';
import noisejs from "noisejs";

const app = express();
app.use(express.json());
app.use(express.static('public'));
const { Noise } = noisejs;

const PORT = 8080;
const HOST = '0.0.0.0';

const noiseTemp = new Noise();
noiseTemp.seed(Math.random());
const noiseHumidity = new Noise();
noiseHumidity.seed(Math.random());
let noiseIndex = 0;

let replay = {};
let cmd = { fan: false, light: false, pump: false };

function createDeviceData(deviceId) {
  
  const temperature = Number((((noiseTemp.perlin2(noiseIndex * 0.1, 0) + 1) / 2) * 9 + 25).toFixed(2));
  const humidity = Number((noiseHumidity.perlin2(noiseIndex * 0.1, 0) * 25 + 40).toFixed(1));
  noiseIndex += 1;

  return {
    device: {
      id: deviceId,
      name: `ESP32-${faker.string.alphanumeric(4).toUpperCase()}`,
      online: faker.datatype.boolean()
    },
    cmd,
    sensor: {
      temperature: temperature,
      humidity: humidity      
    }
  };
}


app.get('/api/device/:id', (req, res) => {
  const deviceId = req.params.id;
  replay = createDeviceData(deviceId);  
  res.json(replay);
});

app.post('/api/device/:id/cmd', (req, res) => {

  const deviceId = req.params.id;
  console.log(`Received command for device ${deviceId}:`, req.body);

  cmd["fan"] = req.body.cmd.fan;
  cmd["light"] = req.body.cmd.light;
  cmd["pump"] = req.body.cmd.pump;

  console.log(`Device ${deviceId} command:`, cmd);

  res.json(cmd);
});

app.get('/api/device/:id/status', (req, res) => {
  res.json(replay);
});

app.get('/', (req, res) => {
  let html = fs.readFileSync(
    './public/index.html',
    'utf8'
  );  
  res.send(html);
});

app.listen(PORT, HOST, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
