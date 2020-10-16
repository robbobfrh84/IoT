#define HTML ""

//#define HTML "<body style='text-align:center'><h1 style='color:blue'>OHHH HI</h1></body>"
//"<body style='text-align:center'><h1 style='color:blue'>OHHH HI</h1></body>"


// const char MAIN_page[] PROGMEM = R"=====(

// <html>
//   <head>
//     <title> Serve Html & Api MKR1000 </title>
//     <style>
//     body {
//       background-color: #ccc;
//       font-family: sans-serif;
//     }
//     </style>
//   </head>
// <body>
//   <center>
//     <h1> Serve Html & Api MKR1000 </h1>
//     <input type="checkbox" id="led" onclick="api()"> LED state
//     </br></br>
//     <span id="btn" style="padding: 5px;"></span>
//   </center>
//   <script>
//     const api = function() {
//       fetch("http://192.168.1.126/api/data", {
//         headers: {
//           method: "POST",
//           body: '{"led":'+led.checked+'}",
//         }
//       })
//         .then( res => res.text() )
//         .then( data => {
//           console.log("response data: ", data)
//           const btnState = data.split("=")[1].trim()
//           //btn.innerHTML = btnState == "1" ? "!Button PRESSED!" :" ...button not pressed"
//           //btn.style.backgroundColor =  btnState == "1" ? "black" : "white"
//           //btn.style.color =  btnState == "1" ? "white" : "black"

//         })
//         .catch( err => console.log("oops, looks like we got an error: ", err))
//     }
//     setInterval(function(){
//       api()
//     },1000)
//   </script>
// </body>
// </html>

// )=====";
