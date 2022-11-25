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

       // let typeBois = description[i].type;
                // let origineBois = description[i].origin;
                // let tempsSechage = description[i].dryingTime;
                // let température = description[i].temperature;


var boisChoisi;
var temperature;

function getInfoWood()
{
    var boisChoisi = document.getElementById("typeBois_ListBox_Select").value;
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    
                    for(var i = 0; i < description.length; i++)
                    {
                        let typeBois = description[i].type;
                        let origineBois = description[i].origin;
                        let tempsSechageBois = description[i].dryingTime;
                        let temperatureMinimumBois = description[i].temperature;

                        document.getElementById("typeBois").innerHTML = typeBois;
                        document.getElementById("origineBois").innerHTML = origineBois;
                        document.getElementById("tempsSechageBois").innerHTML = tempsSechageBois;
                        document.getElementById("temperatureMinimumBois").innerHTML = temperatureMinimumBois;
                    }
                    
                    document.getElementById("typeBois_ListBox_Select").addEventListener("change", getInfoWood);
                }
            }
        };

    xhttp.open("GET", "getWoodCaracteristiques?nomBois="+ boisChoisi, true);
    xhttp.send();
}

// function getInfoWood2(){ 
    
//     // on copie getAllWood mais en getCaracteristique, change l'url de la requete qui retourne toutes les caracteristiques,
//     // fonction qui compare la valeur du name du bois select avec celui des valeurs e l'array, et affiche toutes caractéristiques du bois 

//     var x = document.getElementById('typeBois_ListBox_Select');
   
//     var xhttp = new XMLHttpRequest();
//     xhttp.onreadystatechange = function () {
//         if (this.readyState == 4 && this.status == 200 && this.arrayOfStrings.results.length != undefined) {
//             var arrayOfStrings = JSON.parse(this.responseText);
//             for (i = 0; i < arrayOfStrings.results.length; i++) {
//                 if(x.value == arrayOfStrings.results[i].name){

//                     let typeBois = arrayOfStrings[i].type;
//                     let origineBois = arrayOfStrings[i].origin;
//                     let tempsSechageBois = arrayOfStrings[i].dryingTime;
//                     let temperatureMinimumBois = arrayOfStrings[i].temperature;

//                     document.getElementById('nom').innerHTML = arrayOfStrings.results[i].name;
//                     document.getElementById('typeBois').innerHTML = typeBois;
//                     document.getElementById('origine').innerHTML = origineBois;
//                     document.getElementById('tempsSechage').innerHTML = tempsSechageBois;
//                     document.getElementById('tempMin').innerHTML = temperatureMinimumBois;
//                 }
//          }
//      }      
//    } 
//    xhttp.open("GET", "getAllWoodOptions", true);
//    xhttp.send();
//    }

function demarrageFour(){
    document.getElementById("four").addEventListener("click", function(){
        var i = 0;
        var temp = parseInt(temperature);
        if( temp >= boisChoisi.tempMin) {
           var timer = setInterval(function(){
                i++
                document.getElementById("timer").innerHTML = i;
                console.log(i);
                if(i == boisChoisi.dryingTime){
                    clearInterval(timer);
                }
                
            }, 1000);
        } else {
            console.log('non');
        }
        
    });
}

// Appel un GET sur le serveur pour récupérer des données d'un API REST | Fonction getAllWood
window.addEventListener("load", getAllWoodOptions());
function getAllWoodOptions(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    
                    for(var i = 0; i < description.length; i++)
                    {
                        let nomBois = description[i].name;
                        let idBois = description[i].id;
                        
                        document.getElementById("typeBois_ListBox_Select").innerHTML += "<option value='" + idBois + "'>" + nomBois + "</option>";
                        document.getElementById("typeBois_ListBox_Select").style.color = "black";
                    }
                    
                }
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



