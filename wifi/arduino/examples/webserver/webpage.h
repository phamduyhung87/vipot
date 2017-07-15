const PROGMEM  char page[]  = {"HUNG DEP TRAI"};
PROGMEM char webpage[]  = R"=====(

<!DOCTYPE html><html>
<head>
<style>
myButtonGreen {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #639c49), color-stop(1, #57943a));
  background:-moz-linear-gradient(top, #639c49 5%, #57943a 100%);
  background:-webkit-linear-gradient(top, #639c49 5%, #57943a 100%);
  background:-o-linear-gradient(top, #639c49 5%, #57943a 100%);
  background:-ms-linear-gradient(top, #639c49 5%, #57943a 100%);
  background:linear-gradient(to bottom, #639c49 5%, #57943a 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#639c49', endColorstr='#57943a',GradientType=0);
  background-color:#639c49;
  -moz-border-radius:50px;
  -webkit-border-radius:50px;
  border-radius:50px;
  border:1px solid #18ab29;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:50px;
  padding: 10px;
    width: 22.5% !important;
    height: 150px !important;
  text-decoration:none;
    text-align: center;
    vertical-align: middle;
  text-shadow:1px 2px 1px #2f6627;
}
myButtonGreen:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #57943a), color-stop(1, #639c49));
  background:-moz-linear-gradient(top, #57943a 5%, #639c49 100%);
  background:-webkit-linear-gradient(top, #57943a 5%, #639c49 100%);
  background:-o-linear-gradient(top, #57943a 5%, #639c49 100%);
  background:-ms-linear-gradient(top, #57943a 5%, #639c49 100%);
  background:linear-gradient(to bottom, #57943a 5%, #639c49 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#57943a', endColorstr='#639c49',GradientType=0);
  background-color:#57943a;
}
myButtonGreen:active {
  position:relative;
  top:1px;
}
myButtonBlue {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #79bbff), color-stop(1, #378de5));
  background:-moz-linear-gradient(top, #79bbff 5%, #378de5 100%);
  background:-webkit-linear-gradient(top, #79bbff 5%, #378de5 100%);
  background:-o-linear-gradient(top, #79bbff 5%, #378de5 100%);
  background:-ms-linear-gradient(top, #79bbff 5%, #378de5 100%);
  background:linear-gradient(to bottom, #79bbff 5%, #378de5 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#79bbff', endColorstr='#378de5',GradientType=0);
  background-color:#79bbff;
  -moz-border-radius:50px;
  -webkit-border-radius:50px;
  border-radius:50px;
  border:1px solid #337bc4;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:50px;
  padding: 10px;
    width: 22.5% !important;
    height: 150px !important;
  text-decoration:none;
    text-align: center;
    vertical-align: middle;
  text-shadow:1px 2px 1px #2f6627;
}
myButtonBlue:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #378de5), color-stop(1, #79bbff));
  background:-moz-linear-gradient(top, #378de5 5%, #79bbff 100%);
  background:-webkit-linear-gradient(top, #378de5 5%, #79bbff 100%);
  background:-o-linear-gradient(top, #378de5 5%, #79bbff 100%);
  background:-ms-linear-gradient(top, #378de5 5%, #79bbff 100%);
  background:linear-gradient(to bottom, #378de5 5%, #79bbff 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#378de5', endColorstr='#79bbff',GradientType=0);
  background-color:#378de5;
}
myButtonBlue:active {
  position:relative;
  top:1px;
}
myButtonGray {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #b8e356), color-stop(1, #a5cc52));
  background:-moz-linear-gradient(top, #b8e356 5%, #a5cc52 100%);
  background:-webkit-linear-gradient(top, #b8e356 5%, #a5cc52 100%);
  background:-o-linear-gradient(top, #b8e356 5%, #a5cc52 100%);
  background:-ms-linear-gradient(top, #b8e356 5%, #a5cc52 100%);
  background:linear-gradient(to bottom, #b8e356 5%, #a5cc52 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#b8e356', endColorstr='#a5cc52',GradientType=0);
  background-color:#b8e356;
  -moz-border-radius:50px;
  -webkit-border-radius:50px;
  border-radius:50px;
  border:1px solid #337bc4;
  display:inline-block;
  cursor:pointer;
  color:#ffffff;
  font-family:Arial;
  font-size:50px;
  padding: 10px;
    width: 22.5% !important;
    height: 150px !important;
  text-decoration:none;
    text-align: center;
    vertical-align: middle;
  text-shadow:1px 2px 1px #2f6627;
}
myButtonGray:hover {
  background:-webkit-gradient(linear, left top, left bottom, color-stop(0.05, #a5cc52), color-stop(1, #b8e356));
  background:-moz-linear-gradient(top, #a5cc52 5%, #b8e356 100%);
  background:-webkit-linear-gradient(top, #a5cc52 5%, #b8e356 100%);
  background:-o-linear-gradient(top, #a5cc52 5%, #b8e356 100%);
  background:-ms-linear-gradient(top, #a5cc52 5%, #b8e356 100%);
  background:linear-gradient(to bottom, #a5cc52 5%, #b8e356 100%);
  filter:progid:DXImageTransform.Microsoft.gradient(startColorstr='#a5cc52', endColorstr='#b8e356',GradientType=0);
  background-color:#a5cc52;
}
myButtonGray:active {
  position:relative;
  top:1px;
}
center {  
  position: relative;
  top: 50%;
  transform: translateY(-50%); 
}
   btnText {
  vertical-align: middle; 
  display: inline-block;
}
//body {margin:0;}
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
<br>
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
var room = 'AAAAA;BBBBB;CCCCC;DDDDD';
//var lights = '1;pham tuan hung;abcdef;1;a;1;+;1;pham;abcdef;1;a;1;-;1;tuan;abcdef;1;a;1;-;1;hung;abcdef;1;a;1;+;1;aaa;abcdef;1;bbbbbbbbbbbbbbb;1;-;1;cccc cccc;abcdef;1;a;1;+;1;dddd dddd dddddddd;abcdef;1;a;1;+'
var lights = '';
var bscene = '';
var ir_data = ''
 var iRoom = 0;
 var iName = 1;
 var iSerialNo = 2;
 var iCmd = 3;
 var iHome = 5;
 var iType = 4;
 var iStatus = 6; 
 var iCollum = 6;
 var heading = ['Room','Name','Serial No','Cmd','Type','Home'];
 var typeName = ['Std','Alam','Led','Down light'];
 var typeValue = ['a','b','c','d','e'];
 var cmdName = ['ON ALL','Port 1','Port 2','Port 3','ON 1','ON 2','ON 3','OFF 1','OFF 2','OFF 3','OFF ALL'];
 var cmdValue = ['0','1','2','3','A','B','C','a','b','c','9'];
var xmlhttp = new XMLHttpRequest();
xmlhttp.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 var data = xmlhttp.responseText.split('\n');
 room = data[0].replace("room: ", "");
 lights = data[1].replace("light: ", "");
 bscene = data[2].replace("scene: ", "");
 ir_data = data[3].replace("remote: ", "");
 }
 edit();
}
xmlhttp.open('GET', 'light', true);
xmlhttp.send();

function edit() {
 document.getElementById('id01').innerHTML = ""
 var arr = lights.split(';');
 var room_temp = room.split(';');
 document.getElementById("id01").appendChild(document.createElement("BR"));
    document.getElementById("id01").appendChild(document.createElement("BR"));
    for (var i = 0; i < (arr.length/iCollum); i++){
        var curCmd = arr[i*iCollum + iCmd]
    if ((curCmd == '1')||(curCmd == '2')||(curCmd == '3')||(curCmd == '0')||(curCmd == '9'))
      var btn = document.createElement("myButtonBlue");
    else
    if ((curCmd == 'a')||(curCmd == 'b')||(curCmd == 'c'))
      var btn = document.createElement("myButtonGray");
    else
    if ((curCmd == 'A')||(curCmd == 'B')||(curCmd == 'C'))
      var btn = document.createElement("myButtonGreen");
        btn.value= arr[i*iCollum + iSerialNo] + arr[i*iCollum + iCmd];
        var c = document.createElement("center");
        var t = document.createElement("btnText");
        c.appendChild(t)
        t.appendChild(document.createTextNode(arr[i*iCollum + iName]));
        btn.appendChild(c)    
    btn.onclick = function () { click(this.value)}
        document.getElementById("id01").appendChild(btn);
    //nameText.setAttribute("font size=-1");
    }
 //var out ='';
 //out += lights;
 //document.getElementById('id01').innerHTML = out;
}
var http_rf = new XMLHttpRequest();
http_rf.onreadystatechange=function() {
 if (http_rf.readyState == 4 && http_rf.status == 200) {
   xmlhttp.open('GET', 'light', true);
   xmlhttp.send();
 }
}
function click(i){
  http_rf.open('POST', 'sendrf-' + i, true);
  http_rf.send();
}
var http_edit = new XMLHttpRequest();
http_edit.onreadystatechange=function() {
 if (http_edit.readyState == 4 && http_edit.status == 200) {
   alert("Done!!!")
 }
}
function editData(){
  var request = ""
 var l = document.getElementsByName('edit').length;
 var room_temp = room.split(';');
 var roomLength = room_temp.length;
 for (var i = 0; i <= roomLength; i++){
 if (document.getElementsByName('room')[i].value){
    if (i == roomLength)
      request += ";"
    request += document.getElementsByName('room')[i].value
    if (i < (roomLength-1))
      request += ";"
  }
  else{
    for (var j = 0; j < (l/(iCollum-1)); j++){
      if ((document.getElementsByName('edit')[j*(iCollum-1)].selectedIndex == i)&&(i != roomLength)){
        alert("Cannot delete Room: Need to delete all element of room " + document.getElementsByName('edit')[j*(iCollum-1)].value)
        request += document.getElementsByName('edit')[j*(iCollum-1)].value
        if (i < (roomLength-1))
          request += ";"
        break;
      }
    }
    
  }
  
 }
 alert(request) 
 room = request
 request = "";
 
 for ( var i=0; i < l ; i++){
  if (((i%(iCollum-1)) == iRoom)){
   //alert(document.getElementsByName('edit')[i].selectedIndex)
   
  if (document.getElementsByName('edit')[i].selectedIndex == -1)
  break;
  if (i == 0) {
     if (document.getElementsByName('edit')[i].selectedIndex == roomLength)
    i += iCollum - 1
  }
  else{
   
     while (document.getElementsByName('edit')[i].selectedIndex == roomLength) {
    i += iCollum - 1    
   }
   if (document.getElementsByName('edit')[i].selectedIndex == -1)
    break;
    request += ";"
  }
  if (document.getElementsByName('edit')[i].selectedIndex == -1)
    break;   
   request += document.getElementsByName('edit')[i].selectedIndex + 1;
  }else
  if (((i%(iCollum-1)) == iCmd)){
   request += ';' + cmdValue[document.getElementsByName('edit')[i].selectedIndex];
  }else
  if (((i%(iCollum-1)) == iType)){
   request += ';' + typeValue[document.getElementsByName('edit')[i].selectedIndex];
  }else
  if (((i%(iCollum-1)) == iHome)){
   request += ';';
   if (document.getElementsByName('edit')[i].checked)
  request += 1;
   else
    request += 0;
   request += ';+';
  }else
   request += ';' + document.getElementsByName('edit')[i].value;
 }
 lights = request
 edit();
 http_edit.open('POST', 'edit?L:' + request + '/', false);
 http_edit.send();
}
function getEdit(res) {
 data = res;
}
</script>
</body>
</html>
)=====";
