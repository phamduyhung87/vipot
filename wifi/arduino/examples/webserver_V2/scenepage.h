PROGMEM char scenepage[]  = R"=====(
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
    //position: fixed;
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
var response = '';
var data = '';
var room = '';
var xmlhttp = new XMLHttpRequest();
xmlhttp.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 data = xmlhttp.responseText;
 }
}
xmlhttp.open('GET', 'scene', false);
xmlhttp.send();

var xmlhttp_room = new XMLHttpRequest();
xmlhttp_room.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 room = xmlhttp_room.responseText;
 }
}
xmlhttp_room.open('GET', 'bscene', false);
xmlhttp_room.send();
edit();

var del = 0;
var rdel = 0;
function edit() {
 var arr = data.split(';');
 var room_temp = room.split(';');
 var i;
 var out ='';
 var en = 'checked';
 for (var j=0; j < room_temp.length; j++){
    if ((j+1)== rdel){
     j++;
     rdel = 0;
     if (j >= room_temp.length)
        break;
    }
    out +='<br>. Scene: <input type="text" name="r" value="'+ room_temp[j] + '" maxlength="15">';
 out +='<button onclick="del_room('+j+')">Del</button>';
 out +='<table><tr><td>No</td><td>Name</td><td>S/N</td><td>Port 1</td><td>Port 2</td><td>Port 3</td><td>Port 4</td><td>Port 5</td><td>Port 6</td></tr>';
 out +='<td><input size="1" type="text" name="" value="0" disabled></td><td><input type="text" name="ad" value=""maxlength="15"></td>';
 out +='<td><input type="text" name="ad" value="" maxlength="6" size="5"></td>';
 for (var k = 0; k < 6; k++){
 out += '<td><select name="ap" onChange="this.style.color=this.options[this.selectedIndex].style.color"> <option value="0">OFF</option> <option  value="1" style="color: red">ON</option> </select></td>';
 }
 out +='<td><button name="ad" onclick="add_light('+j+')">Add</button></td>';
 out +='</table></form>';
 for(i = 0; i < (arr.length / 4); i++) {
 if ((i+1)==del) {}
        else
         if (arr[i*4] == (j + 1)){
 out += '<table><tr>';
 out += '<td><input size="1" type="text" name="n" disabled value="' + (i+1).toString() + '"> </td>';
 out += '<td><input type="text" name="d" value="' + arr[i*4 + 1] + '"maxlength="15"></td>';
 out += '<td><input type="text" name="d" value="' + arr[i*4 + 2] + '" maxlength="6" size="5"></td>';
 var n = 256;
 for (var k = 0; k < 6; k++){
   out += '<td><select name = "p"';
   var ion = parseInt(arr[i*4 + 3]);
   n = n/2;
   if (((ion/n)%2)>=1)
     out += ' style="color:red"';
   out += ' onChange="this.style.color=this.options[this.selectedIndex].style.color"> <option value="0">OFF</option> <option  value="1"';
   if (((ion/n)%2)>=1)
     out += 'selected';
   out += ' style="color: red">ON</option></select></td>';
 }
 out +='<td><button name = "d" value ="' + arr[i*4] +'" onclick="del_light('+i+')">Del</button></td>';
 out += '</tr></table>';
     }
 }
 }
 out +='<br>. Scene: <input type="text" name="ar" value="" maxlength="15">';
 out +='<button onclick="add_room()">Add</button><br><br>';
 out += '<button onclick="editData()">-- EDIT --</button></td>';
 document.getElementById('id01').innerHTML = out;
}
function del_light(i){
 if ((document.getElementsByName('d').length) < 5)
 return;
 del = i + 1;
 edit();
 editData();
 del=0;
}
function del_room(i){
 if ((document.getElementsByName('r').length) == 1)
    return;
 rdel = i + 1;
 edit();
 editData();
}
function add_light(a){
 if ((document.getElementsByName('d').length/4) > 14)
 return;
 if (document.getElementsByName('ad')[a*3 + 0].value == '' )
 return;
 data += ';' + (a+1) + ';';
 data += document.getElementsByName('ad')[a*3].value + ';';
 data += document.getElementsByName('ad')[a*3 + 1].value + ';';
 var n = 256;
 var p = 0;
 for (var k = 0; k < 6; k++){
  n=n/2;
  p += n* parseInt(document.getElementsByName('ap')[a*6 + k].value);
 }
 data += p;
 edit();
 editData();
}
function add_room(){
 if ((document.getElementsByName('r').length) > 10)
 return;
 if (document.getElementsByName('ar')[0].value == '' )
 return;
 room += ';' + document.getElementsByName('ar')[0].value;
 edit();
 editData();
}
var http_edit = new XMLHttpRequest();
http_edit.onreadystatechange=function() {
 if (http_edit.readyState == 4 && http_edit.status == 200) {
 
 }
}
function editData(){
 var room_temp = '';
 var request = '';
 var r = document.getElementsByName('r').length;
 var l = document.getElementsByName('d').length;
 
 for (var i=0; i<r; i++){
    room_temp += document.getElementsByName('r')[i].value;
    if (i < (r - 1))
     room_temp += ';';
 }
 room = room_temp;
 
 http_edit.open('GET', 'edit?B:' + room_temp + '/', false);
 http_edit.send();
 for ( var i=0; i < l/3 ; i++){
 request += document.getElementsByName('d')[i*3 + 2].value + ';';
 request += document.getElementsByName('d')[i*3].value + ';';
 request += document.getElementsByName('d')[i*3 + 1].value + ';';
 var n = 256;
 var p = 0;
 for (var k = 0; k < 6; k++){
  n=n/2;
  p += n* parseInt(document.getElementsByName('p')[i*6 + k].value);
 }
 request += p;
 if (i<(l/3-1))
  request += ';';
 }
 data = request;
 var str = request;
 var str1 = str.substring(0,150);
 http_edit.open('GET', 'edit?S:' + str1 + '/', false);
 http_edit.send();
     while (str.length>150){
     str = str.slice(150);
     var str1 = str.substring(0,150);
 http_edit.open('GET', 'edit?s:' + str1 + '/', false);
 http_edit.send();
 }
 alert("Done");
}
</script>
</body>
</html>
)=====";
