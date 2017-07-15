PROGMEM char wifipage[]  = R"=====(
<!DOCTYPE html><html>
<head>
<style>
body {margin:0;}
ul {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #0a0;
    position: fixed;
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
<br><br><br>
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
var IP = ['IP Address ','Subnet Mask','IP Gateway'];
var ip_data = '';
var wifi_data = '';
var http_ip = new XMLHttpRequest();
http_ip.onreadystatechange=function() {
 if (http_ip.readyState == 4 && http_ip.status == 200) {
 ip_data = http_ip.responseText;
 }
}
http_ip.open('GET', 'ip', false);
http_ip.send();
var http_wifi = new XMLHttpRequest();
http_wifi.onreadystatechange=function() {
 if (http_wifi.readyState == 4 && http_wifi.status == 200) {
 wifi_data = http_wifi.responseText;
 }
}
http_wifi.open('GET', 'wifi', false);
http_wifi.send();
wifi_edit();
function wifi_edit(){
 var setting = ip_data.split(';');
 var wifi_temp = wifi_data.split(';');
 var out = 'Station Setting: <br><table>';
 out += '<tr><td>SSID: </td>';
 out += '<td><input type="text" name="w" value="' + wifi_temp[0] + '"></td></tr>';
 out += '<tr><td>PWD: </td>';
 out += '<td><input type="text" name="w" value="' + wifi_temp[1] + '"></td></tr>';
 out += '</table>';
 out += 'Access Point Setting: <br><table>';
 out += '<tr><td>AP SSID: </td>';
 out += '<td><input type="text" name="w" value="' + wifi_temp[2] + '"></td></tr>';
 out += '<tr><td>AP PWD: </td>';
 out += '<td><input type="text" name="w" value="' + wifi_temp[3] + '"></td></tr>';
 out += '</table>';
 out += 'IP Setting: <br><table>';
 for (var i = 0; i < 3; i++){
 out += '<tr><td>' + IP[i] + '</td>';
 var ip = setting[i].split('.');
 for (var j = 0; j < 4; j ++){
 out += '<td><input type="number" size="1" min="0" max="255" name="a" value="' + ip[j];
 out += '"></td>';
 if (j<3)
 out += '<td>.</td>';
 }
 out += '</tr>';
 }
 out += '</table><button onclick="editWifi()">Edit</button><br><br><br>';
 document.getElementById('id01').innerHTML = out;
}
var http_edit = new XMLHttpRequest();
http_edit.onreadystatechange=function() {
 if (http_edit.readyState == 4 && http_edit.status == 200) {

 }
}
function editWifi(){
 var request = '';
 for (var i = 0; i < 12; i++){
 request += document.getElementsByName('a')[i].value;
 if (i<11)
 request +=';';
 }
 //alert(request);
 http_edit.open('GET', 'edit?i:' + request + ';' + '/', false);
 http_edit.send();
 request = '';
 
 for (var i = 0; i < 4; i++){
 request += document.getElementsByName('w')[i].value;
 if (i<4)
 request +=';';
 }
 http_edit.open('GET', 'edit?w:' + request + '/', false);
 http_edit.send();
}
function wifi(){
 http_setting.open('GET', 'ip', true);
 http_setting.send();
}
</script>
</body>
</html>
)=====";
