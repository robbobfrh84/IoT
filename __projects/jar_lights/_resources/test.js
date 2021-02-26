/*  - - - - -  TESTS - - - - -  */

const saveForHtml = `
<br><button onclick="testStrip('pallete')">testStrip</button>
<br><button onclick="testStrip('clear')">clear</button>
`

const testStrip = function(test) {
  if (test == "pallete") {
    let q = "req=custom"
    const keys = Object.keys(cols)
    for (let i = 0; i < Object.keys(cols).length; i++) {
      if (cols[keys[i]].s) {
        q+="&"+(i+1)+"="+cols[keys[i]].c
      } else {
        q+="&"+(i+1)+"="+cols[keys[i]].c
      }
    }
    query(q)
  } else if (test === "clear") {
    let q = "req=custom"
    let cnt = data.NUM_LEDS || 24
    for (let i = 0; i < cnt; i++) {
      q+="&"+(i+1)+"=0,0,0"
    }
    query(q)
  }

}

