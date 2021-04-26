const SerialPort = require('serialport')
const Readline = require('@serialport/parser-readline')

// const port = new SerialPort('/dev/cu.usbmodem14201', { // MAC
const port = new SerialPort('/dev/ttyACM0', { // PI

  baudRate: 115200
})

const parser = port.pipe(new Readline({ delimiter: '\n' }))

port.on("open", () => {
  console.log('serial port open')
})

// const messages = [
//   "x10067\n"
// ]
const messages = [
  "x1234567 123456789 123456789 123456789 123456789 123456789 123456\n"
]

// const messages = [
//   "x10067\n","x1006\n","x1006\n","x10001\n",
//   "y16060\n","x1006\n","x1006\n","x10002\n",
//   "z20567\n","x1006\n","x1006\n","x10003\n",
//   "a30567\n","x1006\n","x1006\n","x10004\n",
//   "b12300\n","x1006\n","x1006\n","x10005\n",
//   "c34567\n","x1006\n","x1006\n","x10006\n",
// ]

// const messages = [
//   "x100\n",
//   "y1600\n",
//   "z20\n",
//   "a30\n",
//   "b12300\n",
//   "c34\n",
// ]

let start;
const startTime = false
parser.on('data', data =>{
  // console.log('TOP end (ms):', Date.now()-start)
  console.log("A: ",data, " /chars: ", data.length)
  if (!start) {
    start = Date.now()
  }
  if (messages.length > 0) {
    const command = messages[0]
    messages.shift()
    sendCommand(command)
  } else {
    console.log('end (ms):', Date.now()-start)
  }
})



// const messageTester = setInterval(function(){
//   sendCommand(messages[0])
//   messages.shift()
//   if (messages.length <= 0) {
//     setTimeout(()=>{console.log('\n    ! End of messages !\n')},1000)
//     clearInterval(messageTester)
//   }
// },1*1000)


function sendCommand(command) {
  port.write(command, (err) => {
    if (err) {
      return console.log('Error on write: ', err.message)
    }
  })
}
