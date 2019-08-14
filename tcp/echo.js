const { Socket } = require('net')

const PORT = 7000
const HOST = '0.0.0.0'

const msg = 'Echooooo'

const client = new Socket()

client
  .connect(PORT, HOST, () => {
    // client.write(msg)
  })
  .on('error', function onerror (err) {
    console.error(err)
  })
  .on('data', function ondata (data) {
    // client.write('QUIT')
  })
  .on('close', function onclose () {
    console.log('Server closed connection')
  })
