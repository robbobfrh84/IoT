const queryString = function(queryString, callback) {
  fetch(IP_address+'/q?'+queryString)
    .then(res => res.json())
    .then(data => {
      if (callback) { callback(data) }
    })
}

const getWifiConfig = function(callback) {
  // 🔥 Maybe this should be a reg request? it won't work on none-served local file:///...
  fetch(IP_address+'/wifiConfig.json')
    .then(res => res.json())
    .then(data => {
      if (callback) { callback(data) }
    })
}


