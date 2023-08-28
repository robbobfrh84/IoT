var ardData;
var settings = {
  channel: '1a',
  publish_key: 'pub-c-6d531795-b849-4e94-b216-b518015fa7df',
  subscribe_key: 'sub-c-65f59724-23b5-11e6-8bc8-0619f8945a4f',
  ssl: true
};
var pubnub = PUBNUB(settings);
var tempData=[];
var pressData=[];
var lightData=[];
var testy;

pubnub.history({
  channel: '1a',
  callback: function(m){
    console.log(m);
    testy = m;
    for (var i = 0; i < m[0].length; i++) {
      lightData = lightData.concat((m[0][i].light)/2);
      tempData = tempData.concat((m[0][i].temp-8000000)/800);
      pressData = pressData.concat((m[0][i].press-6700000)/330);
      console.log(m[0][i].light);
      dataCall();
    }
    console.log(lightData);
  },
  count: 100,
  reverse: false
});

pubnub.subscribe({
  channel: '1a',
  callback: function(m){
    ardData = m;
    console.log('arduino data: ', m);
    tempData=tempData.concat((ardData.temp-8000000)/800);
    pressData=pressData.concat((ardData.press-6700000)/330);
    lightData=lightData.concat(ardData.light/2);
    console.log(tempData);
    dataCall();
  },
  error: function(err) {
    console.log(err);
  }
});


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

function dataCall(){
 // create the chart
   var chartOne = new Highcharts.Chart({
       xAxis: {
           type: 'datetime'
          //  categories: timeToken //breaks Angular
       },
       chart: {
         type: 'areaspline',
         renderTo: 'containerOne'
       },
       title: {
         text: 'Sensor Data'
       },
       series: [{
           animation: false,
           name: 'Light Sensor',
           data: lightData,
           pointStart: Date.UTC(2016, 05, 01),
           pointInterval: 180 * 1000 // one hour
         },
         {
           animation: false,
           name: 'Temperature Sensor',
           data: tempData,
           pointStart: Date.UTC(2016, 05, 01),
           pointInterval: 180 * 1000 // one hour
         },
         {
           animation: false,
           name: 'Pressure Sensor',
           data: pressData,
           pointStart: Date.UTC(2016, 05, 01),
           pointInterval: 180 * 1000 // one hour
         }
       ],
   });
 }
