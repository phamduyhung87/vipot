PROGMEM char remotepage[]  = R"=====(
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
var ir_data = '';
var room = '';
var brand = ['Sony','SamSung','Pana','Misu','Daikin','National','LG'];
var brandVL = ['s','a','p','m','d','n','l'];
var xmlhttp_room = new XMLHttpRequest();
xmlhttp_room.onreadystatechange=function() {
 if (xmlhttp_room.readyState == 4 && xmlhttp_room.status == 200) {
 room = xmlhttp_room.responseText;
 }
}
xmlhttp_room.open('GET', 'room', false);
xmlhttp_room.send();

var http_ir = new XMLHttpRequest();
http_ir.onreadystatechange=function() {
 if (http_ir.readyState == 4 && http_ir.status == 200) {
 ir_data = http_ir.responseText;
 }
}

get_ir();
ir_edit();
function ir_edit(){
 var arr = ir_data.split(';');
 var room_temp = room.split(';');
 var i;
 var out ='';
 var en = 'checked';
 out +='<table><tr><td>No</td><td>Room</td><td>Code</td><td>TV</td><td>FAN</td><td>A/C</td><td>Enable</td></tr>';
 for(i = 0; i < room_temp.length; i++) {
 if (arr[i*5] == undefined) arr[i*5] = '';
 out += '<tr>';
 out += '<td><input size="1" type="text" name="n" disabled value="' + (i+1).toString() + '"> </td>';
 out +='<td><input type="text" name="n" disabled value="' + room_temp[i] + '" maxlength="15"></td>';
 out +='<td><input type="text" name="i" value="' + arr[i*5] + '" maxlength="4"></td>';
 for (var j = 0; j < 3; j++){
 out +='<td><select name="i" id="br'+ (i*5+j+1) +'">';
 for (var k =0; k < brand.length; k++){
 out += '<option value = "' + brandVL[k] + '">' + brand[k] + '</option>';
 }
 out +=' </td>';
 }
    out += '<td><input type="checkbox" name="i" value="' + arr[i*5+4] +'"';
 if(arr[i*5+4] == '1')
 out += en;
 out += '></td>';   
 out += '</tr>';
 }
 out +='</table>';
 out += '<button onclick="edit_ir()">Edit</button></td>';
 document.getElementById('id01').innerHTML = out;
 i = 0;
 for (var j = 0; j < arr.length;j++){
    if (((j%5) > 0)&&((j%5) < 4)){
     var element = document.getElementById('br'+j);
     element.value = arr[j];
    }
 }
}
var http_edit = new XMLHttpRequest();
http_edit.onreadystatechange=function() {
 if (http_edit.readyState == 4 && http_edit.status == 200) {

 }
}
function edit_ir(){
 var request = '';
 for (var i = 0; i < document.getElementsByName('i').length; i++){
 if ((i%5) == 4){
 if (document.getElementsByName('i')[i].checked)
 request +='1';
 else
 request +='0';
 }
    else 
 request += document.getElementsByName('i')[i].value;
 if (i<document.getElementsByName('i').length - 1)
 request +=';';
 }
 ir_data = request;
 http_edit.open('GET', 'edit?I:' + request + '/', false);
 http_edit.send();
 ir_room_button(cur_room);
 ir_edit();
}
function get_ir(){
 http_ir.open('GET', 'ir', false);
 http_ir.send();
}
</script>
</body>
</html>
)=====";
