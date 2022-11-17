/**
    Class MyButton : Gestion de la température (senseur) STUB
    @file MyButton.h 
    author Maxence
    version 1.3 04/12/21  
    
    Historique des versions   
                            Versions  Date      Auteur      Description
                            1.0      17/03/21   Ald         Première version de la classe
                            1.1      22/10/21   Maxence     Ajout fonction température Sensor
                            1.2      15/11/21   Maxence     Modification fonction température
                            1.3      01/12/12   Maxence     Ajout de la fonction demarrageFour() et modification de la fonction getInfoWood()         
        
**/

var boisChoisi;
var temperature;

function getInfoWood(){

 var x = document.getElementById('typeBois_ListBox_Select');

 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function () {
     if (this.readyState == 4 && this.status == 200 && this.arrayOfStrings.results.length != undefined) {
         var arrayOfStrings = JSON.parse(this.responseText);
         for (i = 0; i < arrayOfStrings.results.length; i++) {
             if(x.value == arrayOfStrings.results[i].id){
                 boisChoisi = arrayOfStrings.results[i];
                 document.getElementById('nom').innerHTML = arrayOfStrings.results[i].bois;
                 document.getElementById('nom2').innerHTML = arrayOfStrings.results[i].bois;
                 document.getElementById('typeBois').innerHTML = arrayOfStrings.results[i].typeBois;
                 document.getElementById('origine').innerHTML = arrayOfStrings.results[i].origine;
                 document.getElementById('tempsSechage').innerHTML = arrayOfStrings.results[i].tempsSechage;
                 document.getElementById('tempsSechage2').innerHTML = arrayOfStrings.results[i].tempsSechage;
                 document.getElementById('tempMin').innerHTML = arrayOfStrings.results[i].tempMin;
                 document.getElementById('tempMin2').innerHTML = arrayOfStrings.results[i].tempMin;
             }
      }
  }      
} 
xhttp.open("GET", "getAllWoodOptions", true);
xhttp.send();
}

function demarrageFour(){
    document.getElementById("four").addEventListener("click", function(){
        var i = 0;
        var temp = parseInt(temperature);
        if( temp >= boisChoisi.tempMin) {
           var timer = setInterval(function(){
                i++
                document.getElementById("timer").innerHTML = i;
                console.log(i);
                if(i == boisChoisi.drying){
                    clearInterval(timer);
                }
                
            }, 1000);
        } else {
            console.log('non');
        }
        
    });
}

function getFromESP_getAllWoodOptions() {
 var xhttp = new XMLHttpRequest();
 xhttp.onreadystatechange = function () {
     if (this.readyState == 4 && this.status == 200) {
         var arrayOfStrings = JSON.parse(this.responseText);
         for (i = 0; i < arrayOfStrings.results.length; i++) {
             var x = document.getElementById("typeBois_ListBox_Select");
             var option = document.createElement("option");
             option.value = arrayOfStrings.results[i].id;
             option.text = arrayOfStrings.results[i].bois;
             
             x.add(option);
             } 
        

         //Refresh le contenu
         var siteHeader = document.getElementById('typeBois_ListBox_Select');
         siteHeader.style.display='none';
         siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
         siteHeader.style.display='block';

         }
         

 };
 xhttp.open("GET", "getAllWoodOptions", true);
 xhttp.send();
}


setInterval(function getFromEsp_TemperatureSensor(){
 var xhttp = new XMLHttpRequest();

 xhttp.onreadystatechange = function(){
     if(this.readyState == 4 && this.status == 200){
         document.getElementById("temp").innerHTML = this.responseText;
         temperature = this.responseText;
         
     }
 };
 xhttp.open("GET", "getTemperatureSensor", true);
 xhttp.send();
 
 }, 3000);

const apiUrl = "http://api.qc-ca.ovh:2223/api/woods/getAllWoods/";

 function getWood() {
   fetch(apiUrl, {
       method: "get"
     })
     .then(response => response.json())
     .then(data => {
       let allWood = data.result.bois;
       let html = '';
       for (var i = 0; i < allWood.length; i++) {
         html += "<option value=" + allWood[i].id + ">" + allWood[i].nom + "</option>"
         console.log('get Wood running');
       }
       document.getElementById("typeBois_ListBox_Select").innerHTML = html;
     })
 }
 getWood();


