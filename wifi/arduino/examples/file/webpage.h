const PROGMEM  char page[]  = {"HUNG DEP TRAI"};
const PROGMEM char webpage[]  = R"=====(
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
ul1 {
    list-style-type: none;
    margin: 0;
    padding: 0;
    overflow: hidden;
    background-color: #0a0;
    position: fixed;
    top: 40;
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

<body style='background: #048C04; color: #FFFFFF'>
<br><br><br>
<div id='id03'></div><br><br>
<div id='id02'></div><br>
<div id='id01'></div>
<br><br><br>
<div style='font-size: 15pt'>
<form action='footer' method='get'>
<div align='center'>Designed by Tran - Duy</div>
</div>
</div>
<script>
var b_style = 'style="height:80px; width:180px; font-size:200%; background-color: #0A0; color:white" onclick="'
var response = '';
var data = '';
var room = ''
var bscene = '';
var ir_data = ''
var cur_room = 1;
var ir_button = ['','','TV','FAN','A/C off','1','2','3','SPD','+','4','5','6','OSC','26','7','8','9','RYM','-','*','0','#','TMR','Fan 1','P+','','V+','','OSC ','P-','','V-','','Cool','--','','Mute','','']
var ir_code = 'TxOox123sx456cx789rx*0#t1PxVxxpxvx0/xMxxxxxxx'
var ir_ac_fan = '1'
var ir_ac_mode = '0'
var brand = ['Sony','SamSung','Pana','Misu','Daikin','National','LG'];
var brandVL = ['s','a','p','m','d','n','l'];
var xmlhttp = new XMLHttpRequest();
xmlhttp.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 data = xmlhttp.responseText;
 }
}
var http_bscene = new XMLHttpRequest();
http_bscene.onreadystatechange=function() {
 if (http_bscene.readyState == 4 && http_bscene.status == 200) {
 bscene = http_bscene.responseText;
 }
}
http_bscene.open('GET', 'bscene', false);
http_bscene.send();

var http_ir = new XMLHttpRequest();
http_ir.onreadystatechange=function() {
 if (http_ir.readyState == 4 && http_ir.status == 200) {
 ir_data = http_ir.responseText;
 }
}
xmlhttp.open('GET', 'data', false);
xmlhttp.send();
var xmlhttp_room = new XMLHttpRequest();
xmlhttp_room.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 room = xmlhttp_room.responseText;
 }
}
xmlhttp_room.open('GET', 'room', false);
xmlhttp_room.send();
get_ir();
button();
light(0);
function button(){
 /*var out = '';
 out += '<button ' + b_style + 'light(0)">Home</button>';
 out += '<button ' + b_style + 'light(' + cur_room +')">Light</button>';
 out += '<button ' + b_style + 'scene()">Scenes</button>';
 out += '<button ' + b_style + 'ir(' + cur_room +')">IR</button>';
 out +='';*/
 var out = '<ul>';
  out += '<li><a "" onclick="light(0)">Home</a></li>';
  out += '<li><a onclick="light(' + cur_room +')">Light</a></li>';
  out += '<li><a onclick="scene()">Scene</a></li>';
  out += '<li><a onclick="ir(' + cur_room +')">Remote</a></li>';
  //out += '<li><a href="setting">Setting</a></li>';
  out += '</ul>'; 
 document.getElementById('id03').innerHTML = out;
}
function gethome(){
 var http_home = new XMLHttpRequest();
 http_home.open('GET', 'Home', true);
 http_home.send();
}
function sendRF(rf){
 var http_rf = new XMLHttpRequest();
 http_rf.open('POST', 'sendrf-' + rf + ' ', true);
 http_rf.send();
}
function sendScene(rf){
 var http_rf = new XMLHttpRequest();
 http_rf.open('POST', 'sendScene-' + rf + ' ', true);
 http_rf.send();
}

function scene(){
 document.getElementById('id02').innerHTML = '<br><br><br>';
 var arr = bscene.split(';');
 var i;
 var out ='<table><tr>';
 var rf ='';
 for(i = 0; i < (arr.length); i++) {
 var rf = i + 1;
 out += '<button style="height:160px; width:320px; font-size:400%; background-color:#00B; color:white" onclick=\'sendScene("' + rf + '")\'>';
 out += arr[i] + '</button>';
 }
 out +='</tr></table>';
 document.getElementById('id01').innerHTML = out;
}

function light(r){
 if (r) { cur_room = r; button();}
 room_button(r);
 var arr = data.split(';');
 var i;
 var out ='<table><tr>';
 var rf ='';
 for(i = 0; i < (arr.length / 5); i++) {
    if ((r!=0)&&(r!=arr[i*5])){}
    else
 if ((arr[i*5 + 4] == '1')||r){
 var rf = arr[i*5 + 2] + arr[i*5 + 3];
 out += '<button style="height:160px; width:320px; font-size:400%; background-color:#00B; color:white" onclick=\'sendRF("' + rf + '")\'>';
 out += arr[i*5 + 1] + '</button>';
 }
 }
 out +='</tr></table>';
 document.getElementById('id01').innerHTML = out;
}
function room_button(b){
 var room_temp = room.split(';');
 var i;

 var out ='<table><tr>';
 //var out ='<ul>';
 for (i = 0; i < room_temp.length; i++){
 out += '<button id="b' + (i+1) + '"' + b_style + 'light(' + (i + 1) +')"> ' + room_temp[i] + ' </button>';
 //out += '<li><a id="b' + (i+1) + '" onclick() = "light(' + (i + 1) +')">' + room_temp[i] + '</a></li>';
 }
 out +='</tr></table>';
 //out +='<ul>';
 document.getElementById('id02').innerHTML = out;
 if (b!=0)
 document.getElementById('b' + b).style.backgroundColor = "#0000AA";
}
var del = 0;
var rdel = 0;
function ir_ac(ac){
    var ac_out = ir_room_code + 'a' + ir_room_ac;
    if (ac == 4){
        if (ir_button[4][5] == 'f'){
            ir_button[4] = 'A/C on';
            ac_out += ir_button[14] + ir_ac_fan + ir_ac_mode;
        }
        else {
            ir_button[4] = 'A/C off';
            ac_out += '0000';
        }
    }
    else
    if (ac == 9) {
        ir_button[4] = 'A/C on';
        var n = Number(ir_button[14]) + 1;
        if (n > 30 )
            n = 30;
        ir_button[14] = n.toString();
        ac_out += ir_button[14] + ir_ac_fan + ir_ac_mode;
    }
    else
    if (ac == 19) {
        ir_button[4] = 'A/C on';
        var n = Number(ir_button[14]) - 1;
        if (n < 18 )
            n = 18;
        ir_button[14] = n.toString();
        ac_out += ir_button[14] + ir_ac_fan + ir_ac_mode;
    }
    else
    if (ac == 24) {
        ir_button[4] = 'A/C on';
        switch (ir_button[24][4]){
            case '1':
                ir_button[24] = 'Fan 2';
                ir_ac_fan = '2';
                break;
            case '2':
                ir_button[24] = 'Fan 3';
                ir_ac_fan = '3';
                break;
            case '3':
                ir_button[24] = 'Fan A';
                ir_ac_fan = '0';
                break;
            case 'A':
                ir_button[24] = 'Fan 1';
                ir_ac_fan = '1';
                break;
        }
        ac_out += ir_button[14] + ir_ac_fan + ir_ac_mode;
    }
    else
    if (ac == 29) {
        ac_out += 'os00';
    }
    else
    if (ac == 34) {
        ir_button[4] = 'A/C on';
        switch (ir_button[34]){
            case 'Cool':
                ir_button[34] = 'Fan';
                ir_ac_mode = '1';
                break;
            case 'Fan':
                ir_button[34] = 'Dry';
                ir_ac_mode = '2';
                break;
            case 'Dry':
                ir_button[34] = 'Hot';
                ir_ac_mode = '3';
                break;
            case 'Hot':
                ir_button[34] = 'Cool';
                ir_ac_mode = '0';
                break;
        }
        ac_out += ir_button[14] + ir_ac_fan + ir_ac_mode;
    }
    else
        ac_out += '1100';
    sendRF(ac_out);
    ir(cur_room);
}
function ir_room(i){
 ir_temp = ir_data.split(';');
 ir_room_code = ir_temp[(i-1)*5 + 0];
 ir_room_tv = ir_temp[(i-1)*5 + 1];
 ir_room_fan = ir_temp[(i-1)*5 + 2];
 ir_room_ac = ir_temp[(i-1)*5 + 3];
 if (i) cur_room = i;
 button();
 ir(cur_room);
}
var ir_room_code = 'ir00'
var ir_room_tv = 's'
var ir_room_fan = 'p'
var ir_room_ac = 'l'
function ir_room_button(b){
 var arr = ir_data.split(';');
 var room_temp = room.split(';');
 var i;
 var out ='<table><tr>';
 for (i = 0; i < room_temp.length; i++){
 if (arr[i*5 +4] == '1')
 out += '<button id="b' + (i+1) + '" ' + b_style + 'ir_room(' + (i+1) +')"> ' + room_temp[i] + ' </button>';
 }
 out +='</tr></table>';
 document.getElementById('id02').innerHTML = out;
 if (b)
 document.getElementById('b' + b).style.backgroundColor = "#0000AA";
}
function get_ir(){
 http_ir.open('GET', 'ir', false);
 http_ir.send();
}
function ir(b){
 var arr = ir_data.split(';');
 var i;
 ir_room_button(b);
 var out ='<table><tr>';
 var ir = '';
 for(i = 0; i < 40; i++) {
        if ((i%5) == 3){
            ir = ir_room_code + 'f' + ir_room_fan + ir_code[i];
     out += '<td><button style="height:160px; width:180px; font-size:400%; background-color:#00B; color:white" onclick=\'sendRF("' + ir + '")\'>';
     out += ir_button[i] + '</button></td>';
        }
        else
        if ((i%5) == 4){
    out += '<td><button style="height:160px; width:180px; font-size:400%; background-color:#00B; color:white" onclick=\'ir_ac("' + i + '")\'>';
     out += ir_button[i] + '</button></td>';
        }
        else {
            ir = ir_room_code + 't' + ir_room_tv + ir_code[i];
     out += '<td><button style="height:160px; width:180px; font-size:400%; background-color:#00B; color:white" onclick=\'sendRF("' + ir + '")\'>';
     out += ir_button[i] + '</button></td>';
        }
        if ((i%5) == 4 ){
                if (i == 39) {
                    break;
            }
            else
                out += '</tr><tr>'
        }
 }
 out +='</tr></table>';
 document.getElementById('id01').innerHTML = out;
}
var http_setting = new XMLHttpRequest();
http_setting.onreadystatechange=function() {
 if (http_setting.readyState == 4 && http_setting.status == 200) {
 getSetting(http_setting.responseText);
 }
}
var IP = ['IP Address ','Subnet Mask','IP Gateway'];
function getSetting(res){
 var setting = res.split(';');
 var out = 'IP Setting: <br><table>';
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
 out += '</table><button onclick="editSetting()">Edit</button><br><br><br>';
 document.getElementById('id01').innerHTML = out;
}
function editSetting(){
 var request = '';
 for (var i = 0; i < 12; i++){
 request += document.getElementsByName('a')[i].value;
 if (i<11)
 request +=';';
 }
 http_setting.open('GET', 'setting?' + request, true);
 http_setting.send();
}
function setting(){
 http_setting.open('GET', 'setting', true);
 http_setting.send();
}
</script>
</body>
</html>
)=====";
