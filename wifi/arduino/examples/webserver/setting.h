PROGMEM char setting[]  = R"=====(

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
var room = '';
var lights = ''
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
 var typeName = ['Buld','Alam','Led','Down light'];
 var typeValue = ['a','b','c','d','e'];
 var cmdName = ['Tog 1','Tog 2','Tog 3','Port 1','Port 2','Port 3','ON ALL','OFF ALL'];
 var cmdValue = ['A','B','C','1','2','3','0','9','a','b','c'];
var xmlhttp = new XMLHttpRequest();
xmlhttp.onreadystatechange=function() {
 if (xmlhttp.readyState == 4 && xmlhttp.status == 200) {
 var data = xmlhttp.responseText.split('\n');
 room = data[0].replace("room: ", "");
 lights = data[1].replace("light: ", "");
 bscene = data[2].replace("scene: ", "");
 ir_data = data[3].replace("remote: ", "");
 }
}
xmlhttp.open('GET', 'light', false);
xmlhttp.send();

edit();

function gethome(){
 var http_home = new XMLHttpRequest();
 http_home.open('GET', 'Home', true);
 http_home.send();
}
var del = 0;
var rdel = 0;
function edit() {
 document.getElementById('id01').innerHTML = ""
 var arr = lights.split(';');
 var room_temp = room.split(';');
 //ROOMs
 document.getElementById("id01").appendChild(document.createTextNode("---------ROOMs----------"))
 var table = document.createElement('TABLE')
 var tableBody = document.createElement('TBODY')
 table.border = '1'
 table.appendChild(tableBody);
 var tr = document.createElement('TR');
 tableBody.appendChild(tr);
 for (var i = 0; i <= room_temp.length; i++){
      var td = document.createElement('TD')
      var input = document.createElement('input')
          input.type = "text";
      if (i<room_temp.length)
      input.value = room_temp[i];
          input.name = "room"
          td.appendChild(input);
          tr.appendChild(td)
  }
document.getElementById("id01").appendChild(table)
document.getElementById("id01").appendChild(document.createElement("BR"))
 //LIGHTs
 document.getElementById("id01").appendChild(document.createTextNode("----------LIGHTs----------"))

 var table = document.createElement('TABLE')
 var tableBody = document.createElement('TBODY')
 table.border = '1'
 table.appendChild(tableBody);
       //TABLE COLUMNS
            var tr = document.createElement('TR');
            tableBody.appendChild(tr);
            for (i = 0; i < heading.length; i++) {
                var th = document.createElement('TH')
                th.width = '75';
                th.appendChild(document.createTextNode(heading[i]));
                tr.appendChild(th);
            }
            //TABLE ROWS
      for (i = 0; i < arr.length + iCollum; i++) {
        if ((i%iCollum) == iRoom) {
          var tr = document.createElement('TR');
          tableBody.appendChild(tr);          
          var td = document.createElement('TD')
          var input = document.createElement('select')
          for (j = 0; j < room_temp.length; j++) {
            var option = document.createElement('option')
            option.text = room_temp[j]
            input.appendChild(option)
          }
          var option = document.createElement('option')
          option.text = "Delete"
          input.appendChild(option)
          input.selectedIndex = arr[i] - 1
          input.name = "edit"
          if (i >= arr.length)
            input.selectedIndex = room_temp.length + 1;
                    td.appendChild(input)
                    tr.appendChild(td)
          
        } else
        if ((i%iCollum) == iType) {       
          var td = document.createElement('TD')
          var input = document.createElement('select')
          var iValue = 0;
          for (j = 0; j < typeName.length; j++) {
            var option = document.createElement('option')
            option.text = typeName[j]
            if (typeValue[j] == arr[i])
              iValue = j;
            input.appendChild(option)
          }
          input.selectedIndex = iValue;
          input.name = "edit"
          if (i >= arr.length)
            input.selectedIndex = typeName.length + 1;
                    td.appendChild(input)
                    tr.appendChild(td)
          
        } else
        if ((i%iCollum) == iCmd) {        
          var td = document.createElement('TD')
          var input = document.createElement('select')
          var iValue = 0;
          for (j = 0; j < cmdName.length; j++) {
            var option = document.createElement('option')
            option.text = cmdName[j]
            if ((cmdValue[j] == arr[i])||(cmdValue[j+8] == arr[i]))
              iValue = j;
            input.appendChild(option)
          }
          input.selectedIndex = iValue;
          input.name = "edit"
          if (i >= arr.length)
            input.selectedIndex = cmdName.length + 1;
                    td.appendChild(input)
                    tr.appendChild(td)
          
        } else
        if ((i%iCollum) == iHome) {
          
          var td = document.createElement('TD')
          var input = document.createElement('input')
          input.type = "checkbox";
          input.checked = arr[i];
          input.name = "edit"
          td.appendChild(input)
                    tr.appendChild(td)
        } else
        if ((i%iCollum) != iStatus){   
                    var td = document.createElement('TD')
          var input = document.createElement('input')
          input.type = "text";
          input.value = arr[i];
          input.name = "edit"
          if ((i%iCollum) == iName) {
            input.maxLength = 15
          }
          if ((i%iCollum) == iSerialNo) {
            input.size = 6
            input.maxLength = 6
          }
          if (i >= arr.length)
            input.value = "";
                    td.appendChild(input);
                    tr.appendChild(td)
        }
      }

            document.getElementById("id01").appendChild(table)
      var bEdit = document.createElement('button')
      bEdit.appendChild(document.createTextNode('Edit'))
      bEdit.addEventListener ("click", editData)
      document.getElementById("id01").appendChild(bEdit)
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
    for (var j = 0; j < (l/(iCollum)); j++){
      if ((document.getElementsByName('edit')[j*(iCollum)].selectedIndex == i)&&(i != roomLength)){
        alert("Cannot delete Room: Need to delete all element of room " + document.getElementsByName('edit')[j*(iCollum)].value)
        request += document.getElementsByName('edit')[j*(iCollum)].value
        if (i < (roomLength-1))
          request += ";"
        break;
      }
    }    
  }  
 }
 room = request
 request = "";
 
 for ( var i=0; i < l ; i++){
  if (((i%(iCollum)) == iRoom)){
  if (document.getElementsByName('edit')[i].selectedIndex == -1)
  break;
  if (i == 0) {
     if (document.getElementsByName('edit')[i].selectedIndex == roomLength)
    i += iCollum
  }
  else{
   
     while (document.getElementsByName('edit')[i].selectedIndex == roomLength) {
    i += iCollum    
   }
   if (document.getElementsByName('edit')[i].selectedIndex == -1)
    break;
    request += ";"
  }
  if (document.getElementsByName('edit')[i].selectedIndex == -1)
    break;   
   request += document.getElementsByName('edit')[i].selectedIndex + 1;
  }else
  if (((i%(iCollum)) == iCmd)){
   request += ';' + cmdValue[document.getElementsByName('edit')[i].selectedIndex];
  }else
  if (((i%(iCollum)) == iType)){
   request += ';' + typeValue[document.getElementsByName('edit')[i].selectedIndex];
  }else
  if (((i%(iCollum)) == iHome)){
   request += ';';
   if (document.getElementsByName('edit')[i].checked)
  request += 1;
   else
    request += 0;
  }else
   request += ';' + document.getElementsByName('edit')[i].value;
 }
 lights = request
 alert(lights)
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
