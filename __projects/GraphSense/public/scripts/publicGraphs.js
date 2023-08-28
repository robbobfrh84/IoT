var ardData;
var settings = {
  channel: 'test',
  publish_key: 'pub-c-a3ff103c-13da-40f7-9134-45670c77ae43',
  subscribe_key: 'sub-c-8740379a-1fcd-11e6-8b91-02ee2ddab7fe',
  ssl: true
};
var pubnub = PUBNUB(settings);
var audioData=[];
var testy;

pubnub.history({
  channel: 'test',
  callback: function(m){
    console.log(m);
    testy = m;
    for (var i = 0; i < m[0].length; i++) {
      audioData = audioData.concat(m[0][i].audio);
    }
    console.log('thisis', audioData);
    dataAudioCall();
  },
  count: 100,
  reverse: false
});

pubnub.subscribe({
  channel: 'test',
  callback: function(m){
    ardData = m;
    console.log('arduino data: ', m);
    audioData=audioData.concat(ardData.audio);
    console.log(audioData);
    dataAudioCall();
  },
  error: function(err) {
    console.log(err);
  }
});


function dataAudioCall(){
 var chartAudio = new Highcharts.Chart({
   xAxis: {
     type: 'datetime'
   },
   chart: {
     type: 'areaspline',
     renderTo: 'audioTest'
   },
   title: {
     text: 'Audio Sensor Data Friday June 3, 2016'
   },
   series: [{
     animation: false,
     name: 'Audio Sensor',
     data: audioData,
     pointStart: Date.UTC(2016, 05, 02),
     pointInterval: 180 * 1000
    }
   ],
  });
 }

// set the theme
 Highcharts.setOptions({
     colors: ['#058DC7', '#50B432', '#ED561B', '#DDDF00', '#24CBE5', '#64E572', '#FF9655', '#FFF263', '#6AF9C4'],
     chart: {
         backgroundColor: {
             linearGradient: [0, 0, 500, 500],
             stops: [
                 [0, 'rgb(255, 255, 255)'],
                 [1, 'rgb(240, 240, 255)']
             ]
         },
         borderWidth: 2,
         plotBackgroundColor: 'rgba(255, 255, 255, .9)',
         plotShadow: true,
         plotBorderWidth: 1
     },
     title: {
         style: {
             color: '#000',
             font: 'bold 16px "Trebuchet MS", Verdana, sans-serif'
         }
     },
     subtitle: {
         style: {
             color: '#666666',
             font: 'bold 12px "Trebuchet MS", Verdana, sans-serif'
         }
     },
     xAxis: {
         gridLineWidth: 1,
         lineColor: '#000',
         tickColor: '#000',
         labels: {
             style: {
                 color: '#000',
                 font: '11px Trebuchet MS, Verdana, sans-serif'
             }
         },
         title: {
             style: {
                 color: '#333',
                 fontWeight: 'bold',
                 fontSize: '12px',
                 fontFamily: 'Trebuchet MS, Verdana, sans-serif'
             }
         }
     },
     yAxis: {
         alternateGridColor: null,
         minorTickInterval: 'auto',
         lineColor: '#000',
         lineWidth: 1,
         tickWidth: 1,
         tickColor: '#000',
         labels: {
             style: {
                 color: '#000',
                 font: '11px Trebuchet MS, Verdana, sans-serif'
             }
         },
         title: {
             style: {
                 color: '#333',
                 fontWeight: 'bold',
                 fontSize: '12px',
                 fontFamily: 'Trebuchet MS, Verdana, sans-serif'
             }
         }
     },
     legend: {
         itemStyle: {
             font: '9pt Trebuchet MS, Verdana, sans-serif',
             color: 'black'

         },
         itemHoverStyle: {
             color: '#039'
         },
         itemHiddenStyle: {
             color: 'gray'
         }
     },
     credits: {
         style: {
             right: '10px'
         }
     },
     labels: {
         style: {
             color: '#99b'
         }
     }
 });

 // create the chart
 var chart = new Highcharts.Chart({
     xAxis: {
         type: 'datetime'
     },
     chart: {
       type: 'line',
       renderTo: 'container'
     },
     title: {
       text: 'Temperature, Light and Pressure Data Sunday May 28, 2016'
     },
     series: [{
        animation: false,
       name: 'Atmospheric Pressure Sensor',
       data: sunPress,
       pointStart: Date.UTC(2016, 04, 28),
       pointInterval: 180 * 1000 // one hour
       },
       {
          animation: false,
         name: 'Temperature Sensor',
         data: sunTemp,
         pointStart: Date.UTC(2016, 04, 28),
         pointInterval: 180 * 1000 // one hour
         },
         {
        animation: false,
       name: 'Light Sensor',
       data: sunLight,
       pointStart: Date.UTC(2016, 04, 28),
       pointInterval: 180 * 1000 // one hour
       },
     ]
 });

 // create the chart
 var chartOne = new Highcharts.Chart({
     xAxis: {
         type: 'datetime'
     },
     chart: {
       type: 'line',
       renderTo: 'containerOne'
     },
     title: {
       text: 'Audio Data'
     },
     series: [{
         data: [254,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,256,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,257,258,258,259,259,259,259,260,260,260,260,260,260,260,261,261,261,261,260,260,261,260,260,260,261,260,261,261,261,262,262,262,263,262,263,264,265,265,266,266,267,267,267,268,268,268,268,268,268,268,268,268,269,269,270,270,270,271,272,272,272,271,271,270,271,271,271,272,274,274,276,281,287,299,317,335,343,352,364,372,377,381,383,383,385,387,390,389,391,393,387,391,389,395,395,395,394,393,394,394,398,398,401,397,394,397,399,403,412,415,412,412,420,420,421,423,422,423,421,419,422,428,422,421,420,424,425,427,427,426,427,427,428,428,427,423,423,424,424,424,423,422,421,417,413,409,405,401,400,400,397,393,385,376,367,365,365,357,357,348,336,328,323,321,324,320,319,317,312,308,305,302,300,298,296,294,293,292,291,289,288,288,287,286,285,284,284,283,282,282,281,281,280,280,280,280,279,279,279,278,278,278,278,278,277,277,277,277,277,277,277,277,276,276,276,276,276,275,276,276,276,276,276,276,276,276,276,276,276,276,275,275,275,275,275,275,275,275,275,275,275,275,275,275,276,276,276,276,275,275,275,274,274,274,274,274,274,273,273,272,272,271,271,271,270,270,270,270,269,269,269,269,268,268,268,268,267,267,267,267,267,266,266,266,265,265,265,265,264,264,264,264,264,263,263,262,262,262,262,262,261,261,261,260,260,260,259,259,259,259,258,258,257,257,257,257,257,257,256,256,256,255,255,255,255,255,255,255,255,255,255,254,254,254,254,254,254,254,253,253,253,253,253,252,252,252,252,252,251,251,251,251,251,250,251,250,250,250,250,250,250,250,250,250,249,249,249,249,249,249,248,248,248,248,248,248,247,247,247,247,247,247,247],
         pointStart: Date.UTC(2016, 04, 29),
         pointInterval: 180 * 1000
     }]
 });

 // create the chart
 var chartTwo = new Highcharts.Chart({
     xAxis: {
         type: 'datetime'
     },
     chart: {
       type: 'areaspline',
       renderTo: 'containerTwo'
     },
     title: {
       text: 'Atmospheric Pressure Data'
     },
     series: [{
         data: [267,268,268,268,268,268,268,268,268,268,269,269,270,270,270,271,272,272,272,271,271,270,271,271,271,272,274,274,276,281,287,299,317,335,343,352,364,372,377,381,383,383,385,387,390,389,391,393,387,391,389,395,395,395,394,393,394,394,398,398,401,397,394,397,399,403,412,415,412,412,420,420,421,423,422,423,421,419,422,428,422,421,420,424,425,427,427,426,427,427,428,428,427,423,423,424,424,424,423,422,421,417,413,409,405,401,400,400,397,393,385,376,367,365,365,357,357,348,336,328,323,321,324,320,319,317,312,308,305,302,300,298,296,294,293,292,291,289,288,288,287,286,285,284,284,283,282,282,281,281,280,280,280,280,279,279,279,278,278,278,278,278,277,277,277,277,277,277,277,277,276,276,276,276,276,275,276,276,276,276,276,276,276,276,276,276,276,276,275,275,275,275,275,275,275,275,275,275,275,275,275,275,276,276,276,276,275,275,275,274,274,274,274,274,274,273,273,272,272,271,271,271,270,270,270,270,269,269,269,269,268,268,268,268,267,267,267,267,267,266,266,266,265,265,265,265,264,264,264,264,264,263,263,262,262,262,262,262,261,261,261,260,260,260,259,259,259,259,258,258,257,257,257,257,257,257,256,256,256,255,255,255,255,255,255,255,255,255,255,254,254,254,254,254,254,254,253,253,253,253,253,252,252,252,252,252,251,251,251,251,251,250,251,250,250,250,250,250,250,250,250,250,249,249,249,249,249,249,248,248,248,248,248,248,247,247,247,247,247,247,247],
         pointStart: Date.UTC(2016, 04, 29),
         pointInterval: 180 * 1000
     }]
 });

 var chartNext = new Highcharts.Chart({
   xAxis: {
     type: 'datetime'
   },
   chart: {
     type: 'areaspline',
     renderTo: 'containerThree'
   },
   title: {
     text: 'Light, Temperature and Pressure Data Saturday May 29, 2016'
   },
   series: [{
  //  animation: false,
   name: 'Light Sensor',
   data: satLight,
   pointStart: Date.UTC(2016, 04, 29),
   pointInterval: 180 * 1000 // one hour
 },
 {
    //  animation: false,
     name: 'Temperature Sensor',
     data: satTemp,
     pointStart: Date.UTC(2016, 04, 29),
     pointInterval: 180 * 1000 // one hour
   },
   {
      //  animation: false,
     name: 'Atmospheric Pressure Sensor',
     data: satPress,
     pointStart: Date.UTC(2016, 04, 29),
     pointInterval: 180 * 1000 // one hour
     },
   ]
 });

 var chartLast = new Highcharts.Chart({
   xAxis: {
     type: 'datetime'
   },
   chart: {
     type: 'areaspline',
     renderTo: 'containerFour'
   },
   title: {
     text: 'Light, Temperature and Pressure Data Monday May 30, 2016'
   },
   series: [{
  //  animation: false,
   name: 'Light Sensor',
   data: monLight,
   pointStart: Date.UTC(2016, 04, 30),
   pointInterval: 180 * 1000 // one hour
 },
 {
    //  animation: false,
     name: 'Temperature Sensor',
     data: monTemp,
     pointStart: Date.UTC(2016, 04, 30),
     pointInterval: 180 * 1000 // one hour
   },
   {
      //  animation: false,
     name: 'Atmospheric Pressure Sensor',
     data: monPress,
     pointStart: Date.UTC(2016, 04, 30),
     pointInterval: 180 * 1000 // one hour
     },
   ]
 });

 $('#search-criteria').on('keyup', function(){
   var searchText = $(this).val().toLowerCase();
   console.log(searchText);
   $('.graph').each(function(){
     var displayGraph = $(this).text().toLowerCase();
     $(this).closest('.col-xs-12')[displayGraph.indexOf(searchText) !== -1 ? 'show' : 'hide']();
   });
 });
