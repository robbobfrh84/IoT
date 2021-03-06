const query = function(queryString) {
  console.log('queryString: ', queryString)
  fetch('http://192.168.1.126/q?'+queryString)
    .then(res => res.json())
    .then(data => {
      console.log('response data: ', data)
      if (data[12] == 1) {
        btn.innerHTML = "<br>Button<br>!PRESSED!"
      } else {
        btn.innerHTML = "<br>Button not pressed"
      }
    })
}

