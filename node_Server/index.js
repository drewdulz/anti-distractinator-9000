var express = require('express');
var bodyParser = require('body-parser');
var open = require('open');
const tweets = require('./data.js')
var SerialPort = require('serialport');


//var SerialPort = serialport.SerialPort;
var app = express();
var port; // arduino port
var tweetIndex = 0;

app.set('port', (process.env.PORT || 3000));
app.use(express.static(__dirname + '/public'));
app.set('views', __dirname + '/views');
app.engine('html', require('ejs').renderFile);
app.set('view engine', 'html');

app.use(bodyParser.urlencoded({
  extended: true
}));
app.use(bodyParser.json());

// Figure out what port the Arduino is on
var SerialComName;
SerialPort.list(function (err, ports) {
  ports.forEach(function(port) {
    if(port.comName.includes("usbmodem")) {
      SerialComName = port.comName;
      console.log("Using serial port: ",SerialComName);
    }
  });
});


app.get('*', function(req, res){
  port = new SerialPort(SerialComName, {
    baudRate: 19200
  });


  console.log("Now serving pics of doggos.");
  setInterval(displayTweet, 15000);
});

app.listen(app.get('port'), function() {
  console.log("Node server running.")
});

function sendToSerial(data) {
  console.log("sending to serial: " + data);
  port.write(data);
}

function displayTweet() {
  console.log("Displaying tweet " + tweets[tweetIndex].tweet_url);
  open( tweets[tweetIndex].tweet_url, function (err) {
    if (err) throw err;
  });
  sendToSerial(padRating(tweets[tweetIndex].rating));
  tweetIndex++;
}

function padRating(rating) {
  console.log(rating);
  if(rating.length == 5) {
    return rating;
  } else {
    return padRating("0"+rating);
  }
}
