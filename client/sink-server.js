// This is a node.js server
// Uses external module "serialport" to read serial port (assuming name "rfcomm*"
// Uses external module "glob-fs"
//
// This server is designed to run on the sink with a Linux OS. It serves the data
// forward to the browser-client.

const SerialPort = require("serialport");
const fs = require("fs");
const path = require("path");
var glob = require("glob-fs")({ gitignore: true });

var p = path.relative(".","/dev") + "/rfcomm*";
var commports = glob.readdirSync(p, {});

const Readline = SerialPort.parsers.Readline;

var ports = [];
var parsers = [];
var sensorlines = [];
for (i in commports) {
  ports.push(new SerialPort(commports[i]));
  parsers.push(new Readline());
  ports[i].pipe(parsers[i]);
  parsers[i].id = i;
  parsers[i].on("data", function (e) {
    e = e.replace("\n","");
    e = e.replace("\r","");
    sensorlines[this.id] = e;
  });
}

setInterval(function() {
  for (i in commports) {
    console.log("sensor "+i+":"+sensorlines[i]);
  }
}, 1000);

var http = require("http");

http.createServer(function (req, res) {
  console.log('request received');
  var jsonMsg = '{"sensors":[';
  for (i in sensorlines) {
    jsonMsg += sensorlines[i];
    if (i != sensorlines.length - 1) {
      jsonMsg += ',';
    }
  }
  jsonMsg += '],';
  jsonMsg += '"timestamp":' + new Date().getTime() + '}';
  console.log(jsonMsg);
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end("_testcb('" + jsonMsg + "')");
}).listen(8080);

