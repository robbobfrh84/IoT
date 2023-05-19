const queryString = function(queryString) {
  const url = IP_address+'/q?'+queryString
  console.log('url request: ', url)
  fetch(url)
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

