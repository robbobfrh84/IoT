const j1 = "{TestString:'bob'}"
const j2 = '{testString:"bob"}'

const api = function() {
  console.log('get api')
  fetch('http://192.168.1.126/api')
    .then(res => res.json())
    .then(data => {
      console.log('data: ', data)
      apiLink.href = data.api
    })
}

const ledToggle = function() {
  console.log('post led state')
  fetch('http://192.168.1.126/api/ledToggle', {
    method: 'POST',
    body: '{"led":'+led.checked+'}',
  })
    .then(res => res.json())
    .then(data => console.log('data: ', data))
}


const checkBtnState = function() {
  console.log('get button state')
  fetch('http://192.168.1.126/api/checkBtnState')
    .then(res => res.json())
    .then(data => {
      console.log('data: ', data)
      if (data["pin12"] == true) {
        btn.innerHTML = "<br>Button<br>!PRESSED!"
      } else {
        btn.innerHTML = "<br>Button not pressed"
      }
    })
}

api()

setInterval(function(){
  checkBtnState()
},1000)
