
var str="<div class=\"grid-container\">"
for(i = 0;i<=133*63;i++){str += "<div id='"+i+"' size='' onmouseover='myfunc("+i+")' ></div>";}
str+= "</div>";
document.getElementById("draw").innerHTML += str;


var freeze=0;
var valgrid="";

valgrid=document.getElementById('tt').value;

if(valgrid.length<133*63-1){    
    //console.log("Here");
    for( i = 0;i<133*63;i++){valgrid+="0";}
    document.getElementById('tt').value = valgrid;
}
else{
    //console.log("YES!");
    //console.log("thiswhole-> "+valgrid+" length="+valgrid.length);
    freezefunc();
    for(i=0;i<valgrid.length;i++){
    //console.log("this-> "+valgrid[i]);
        if(valgrid[i]==1){
            document.getElementById(i).innerHTML='*';
            document.getElementById(i).style.border = '1px solid #000000';
            document.getElementById(i).style.color = '#000000';
        }
        else{
            document.getElementById(i).innerHTML='';
            document.getElementById(i).style.border = '1px solid #ffa94d';
            document.getElementById(i).style.color = 'rgba(255, 255, 255, 0.8)';
        }
    }
    document.getElementById('tt').value = valgrid;
}


function myfunc(i){
    if(freeze==1){return;}
    document.getElementById(i).innerHTML='*';
    document.getElementById(i).style.border = '1px solid #000000';
    document.getElementById(i).style.color = '#000000';
    valgrid=valgrid.substr(0,i)+'1'+valgrid.substr(i+1,valgrid.length-i);
    document.getElementById('tt').value = valgrid;
}

function randomize(){
    if(freeze==1){
        return;
    }
    randx=document.getElementById("randx").value;
    //console.log(randx);
    randx=parseInt(randx);
    //console.log(randx);
    for(i=0;i<valgrid.length;i++){
        var ran=Math.floor(Math.random() * randx);
        //console.log(ran);
        if(ran==1){
            valgrid=valgrid.substr(0,i)+'1'+valgrid.substr(i+1,valgrid.length-i);
            document.getElementById(i).innerHTML='*';
            document.getElementById(i).style.border = '1px solid #000000';
            document.getElementById(i).style.color = '#000000';
        }
        else{
            valgrid=valgrid.substr(0,i)+'0'+valgrid.substr(i+1,valgrid.length-i);
            document.getElementById(i).innerHTML='';
            document.getElementById(i).style.border = '1px solid #ffa94d';
            document.getElementById(i).style.color = 'rgba(255, 255, 255, 0.8)';
        }
    }
    document.getElementById('tt').value = valgrid;
}
function freezefunc(){
    freeze=1-freeze;
    if(freeze==1){
        document.getElementById("fr").innerText= 'Defreeze';
    }
    else{
        document.getElementById("fr").innerText= 'Freeze Space';
    }
}
