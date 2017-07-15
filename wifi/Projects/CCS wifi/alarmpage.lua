<html>
<head>
<style>
body {margin:0;}
ul {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #0a0;
    --position: fixed;
    top: 0;
    width: 100%;
    font-size: 34pt
}

li {
    float: left;
}

li a {
    display: block;
    color: white;
    padding: 16px;
    text-decoration: none;
}

.main {
    padding: 16px;
    margin-top: 30px;
    height: 1500px; /* Used in this example to enable scrolling */
}
</style>
</head>
<ul>
  <li><a href="Home">Home</a></li>
  <li><a href="settinglight">Light</a></li>
  <li><a href="settingscene">Scene</a></li>
  <li><a href="settingalarm">Alarm</a></li>
  <li><a href="settingremote">Remote</a></li>
  <li><a href="settingwifi">Wifi</a></li>
</ul>

<body style='background: #048C04; color: #FFFFFF'>
<div id='id03'></div><br>
<div id='id02'></div><br>
<div id='id01'></div>
<br><br><br>
<div style='font-size: 15pt'>
<form action='footer' method='get'>
<div align='center'>Designed by Tran - Duy</div>
</div>
</div>
<script>
var b_style = 'style="height:80px; width:180px; font-size:200%" onclick="'
var alarm_data = '';
var http_alarm = new XMLHttpRequest();
http_alarm.onreadystatechange=function() {
 if (http_alarm.readyState == 4 && http_alarm.status == 200) {
 alarm_data = http_alarm.responseText;
 }
}
http_alarm.open('GET', 'alarm', false);
http_alarm.send();
var del = 0;
alarm_edit();
function alarm_edit() {
 var arr = alarm_data.split(';');
 var i;
 var out ='';
 var en = 'checked';
 
 out +='<table><tr><td>No</td><td>Message</td><td>Code</td><td>Comd</td><td>Enable</td></tr>';
 out +='<td><input size="1" type="text" name="" value="0" disabled></td><td><input type="text" name="ad" value=""maxlength="15"></td>';
 out +='<td><input type="text" size="4" name="ad" value="" maxlength="6"></td>';
 out +='<td><input type="text" size="1" name="ad" value="" maxlength="1"></td>';
 out +='<td><input type="checkbox" name="ad" value="" checked></td>';
 out +='<td><button onclick="add_alarm(0)">Add</button></td>';
 out +='</table></form>';
 for(i = 0; i < (arr.length / 5); i++) {
 if ((i+1)==del) {}
        else
         {
 out += '<table><tr>';
 out += '<td><input size="1" type="text" name="n" disabled value="' + (i+1).toString() + '"> </td>';
 out += '<td><input type="text" name="d" value="' + arr[i*5 + 1] + '"maxlength="15"></td>';
 out += '<td><input type="text" size="4" name="d" value="' + arr[i*5 + 2] + '"maxlength="6" ></td>';
 out += '<td><input type="text" size="1" name="d" value="' + arr[i*5 + 3] + '"maxlength="1"></td>';
 out += '<td><input type="checkbox" name="d" value="' + arr[i*5] +'"';
 if(arr[i*5 + 4] == '1')
 out += en;
 out += '></td>';
         out +='<td><button onclick="del_alarm('+i+')">Del</button></td>';
 out += '</tr></table>';
     }
 }
 out += '<button onclick="editAlarm()">-- EDIT --</button></td>';
 document.getElementById('id01').innerHTML = out;
}

function del_alarm(i){
 if ((document.getElementsByName('d').length) < 5)
 return;
 del = i + 1;
 alarm_edit();
 editAlarm();
 del=0;
}

function add_alarm(a){
 if ((document.getElementsByName('d').length/4) > 14)
 return;
 if (document.getElementsByName('ad')[a*4 + 0].value == '' )
 return;
 alarm_data += ';' + document.getElementsByName('ad')[a*4 + 3].value;
 alarm_data += ';' + document.getElementsByName('ad')[a*4 + 0].value;
 alarm_data += ';' + document.getElementsByName('ad')[a*4 + 1].value;
 alarm_data += ';' + document.getElementsByName('ad')[a*4 + 2].value + ';';
 if (document.getElementsByName('ad')[a*4 + 3].checked)
 alarm_data +='1';
 else
 alarm_data +='0';
 alarm_edit();
 editAlarm();
}

var http_edit = new XMLHttpRequest();
http_edit.onreadystatechange=function() {
 if (http_edit.readyState == 4 && http_edit.status == 200) {
 
 }
}
function editAlarm(){
 var request = '1;';
 var l = document.getElementsByName('d').length;
 for ( var i=0; i < l ; i++){
 if ((i%4) == 3){
 if (document.getElementsByName('d')[i].checked)
 request +='1';
 else
 request +='0';
 if (i<l-1)
     request += ';' + document.getElementsByName('d')[i+4].value;
    }
 else
 request += document.getElementsByName('d')[i].value;
 if (i< l - 1)
 request +=';';
 }
 var str = request;
 var str1 = str.substring(0,150);
 http_edit.open('GET', 'edit?d:' + str1 + '/', false);
 http_edit.send();
     while (str.length>150){
     str = str.slice(150);
     var str1 = str.substring(0,150);
 http_edit.open('GET', 'edit?a:' + str1 + '/', false);
 http_edit.send();
 }
 alarm_data = request;
}
</script>
</body>
</html>
