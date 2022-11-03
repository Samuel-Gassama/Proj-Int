

       var boisChoisi;
       var temperature;


// Fonction qui permet d'obtenir le nom du système (actualisée toutes les secondes)

// Appel un GET sur le serveur pour récupérer des données d'un API REST | Fonction getAllWood
function getFromESP_getAllWoodOptions() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function () {
        if (this.readyState == 4 && this.status == 200) {
            var arrayOfStrings = this.responseText.split("&");
            for (i = 0; i < arrayOfStrings.length; i=i+2) {
                var x = document.getElementById("typeBois-Select");
                console.log('It does run');
                var option = document.createElement("option");
                option.value = arrayOfStrings[i];
                option.text = arrayOfStrings[i+1];
                x.add(option);
                } 

            //Refresh le contenu
            var siteHeader = document.getElementById('typeBois-Select');
            siteHeader.style.display='none';
            siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
            siteHeader.style.display='block';

            }
    };
    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
};

setInterval(function getFromEsp_TemperatureSensor(){ //
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

    // Demande le nom du système afin de l’afficher dans la vue HTML

    // function getFromESP_getNom () {
    //     var xhttp = new XMLHttpRequest();
    //     xhttp.onreadystatechange = function () {
    //     if (this.readyState == 4 && this.status == 200) {
    //     document.getElementById("nom").innerHTML = this.responseText;
    //     }
    //     };
    //     xhttp.open("GET", "getNomEsp", true);
    //     xhttp.send();
    //    }


       // Fonction récupérer les infos de l'API Bois


       function getInfoWood(){

        var x = document.getElementById('typeBois-Select');
    
        var xhttp = new XMLHttpRequest();
        xhttp.onreadystatechange = function () {
            if (this.readyState == 4 && this.status == 200) {
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

// Fonction pour démarrer le compte à rebour du four

function demarrageFour(){
    var i = 0;
    var temp = parseInt(temperature);
    if( temp >= boisChoisi.tempMin) {
       var timer = setInterval(function(){
            i++
            document.getElementById("timer").innerHTML = i;
            console.log(i);
            if(i == boisChoisi.tempsSechage){
                clearInterval(timer);
            }
            
        }, 1000);
    } else {
        console.log('non');
    }
    
};


let dropdown = document.getElementById('typeBois-Select');
dropdown.length = 0;

// let defaultOption = document.createElement('option');
// defaultOption.text = 'Choisir le type de bois';

// dropdown.add(defaultOption);
// dropdown.selectedIndex = 0;

const url = 'http://api.qc-ca.ovh:2223/api/bois?limit=10&key=IlBv28V1NT81IvZWXVP126IZ6hJ5xd9fxIMP4gzIbvacr';
const request = new XMLHttpRequest();
request.open('GET', url, true);

request.onload = function getAllWood() {
  if (request.status === 200) {
    const data = JSON.parse(request.responseText);
    let option;
    for (let i = 0; i < data.length; i++) {
    var dropdown = document.getElementById("typeBois-Select");
      option = document.createElement('option');
      console.log(data[i]);
      option.value = data[i].id;
      option.text = data[i].id;
      dropdown.add(option);
    }
   } else {
    // Reached the server, but it returned an error
  }   

  //Refresh le contenu
  var siteHeader = document.getElementById('typeBois-Select');
  siteHeader.style.display='none';
  siteHeader.offsetHeight; // no need to store this anywhere, the reference is enough
  siteHeader.style.display='block';
}

request.onerror = function getAllWood() {
  console.error('An error occurred fetching the JSON from ' + url);
};

request.send();