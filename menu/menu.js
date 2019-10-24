const Menu = require('extended-terminal-menu')
const { exec } = require('child_process')

const menu = new Menu({ width: 60, x: 4, y: 2 })
process.stdin.pipe(menu.createStream()).pipe(process.stdout)

process.stdin.setRawMode(true)
menu.on('close', function () {
  process.stdin.setRawMode(false)
  process.stdin.end()
})

function mainMenu () {

  menu.reset()
  menu.write('UVXAMPLES\n')
  menu.write('-------------------------\n')

  menu.add('Check', () => handleStandardOption('./build/check'))
  menu.add('File system operations', () => fileSystemMenu())
  menu.add('File system events')
  menu.add('Idle', () => handleStandardOption('./build/idle'))
  menu.add('Poll')
  menu.add('Prepare', () => handleStandardOption('./build/prepare'))
  menu.add('Signals', () => handleStandardOption('./build/signals'))
  menu.add('TCP')
  menu.add('Timers', () => handleStandardOption('./build/timer'))
}

function handleStandardOption (cmd) {
  menu.reset()
  menu.close()

  exec(cmd, function (error, stdout, stderr) {
    if (error) {
      console.error(error)
      process.exit(1)
    }

    console.log(stdout)
    console.error(stderr)
  })
}

function fileSystemMenu () {
  console.log('FIle systeem calleeeed')
  const fsMenu = new Menu({ width: 60, x: 4, y: 2 })

  fsMenu.reset()
  fsMenu.write('UVXAMPLES\n')
  fsMenu.write('-------------------------\n')

  fsMenu.add('Chmod', () => console.log('Chmod stuff'))

}

mainMenu()
