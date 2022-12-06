var boisChoisi;
var temperature;


// Fonction qui permet d'obtenir le nom du système (actualisée toutes les secondes)

// Appel un GET sur le serveur pour récupérer des données d'un API REST | Fonction getAllWood
window.addEventListener("load", getAllWoodOptions());
function getAllWoodOptions()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
        {
            if(this.readyState == 4 && this.status == 200) {
                if(this.responseText.length > 0) {            
                    var description = JSON.parse(this.responseText);
                    console.log(description);
                    
                    for(var i = 0; i < description.length; i++)
                    {
                        var nomBois = description[i].name;
                        var idBois = description[i].id;
                        document.getElementById("typeBois_ListBox_Select").innerHTML += "<option value='" + idBois + "'>" + nomBois + "</option>";
                        document.getElementById("typeBois_ListBox_Select").style.color = "black";
                    }
                    
                    document.getElementById("typeBois_ListBox_Select").addEventListener("change", getCaracteristiqueBois);
                    document.getElementById("typeBois_ListBox_Select").addEventListener("load", getFromESP_getWoodCaracteristique);
                }
            }
        };

    xhttp.open("GET", "getAllWoodOptions", true);
    xhttp.send();
}

setInterval(function getFromEsp_TemperatureSensor()
{
    var xhttp = new XMLHttpRequest();
   
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200)
        {
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

// Fonction qui permet d'afficher les caractéristiques du bois choisi en envoyant un GET sur le serveur avec le nom du bois choisi
function getFromESP_getWoodCaracteristique()
{
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function()
    {
        if (this.readyState == 4 && this.status == 200)
        {
            console.log(this.responseText);
            var arrayOfStrings = this.responseText.split("&");
            console.log(arrayOfStrings);
            for (var i = 0; i < arrayOfStrings.length; i++)
            {
                value = arrayOfStrings[i];
                ident = arrayOfStrings[i+1];
                console.log("Value : " + value);
                console.log("Ident : " + ident);

                if (value == "Bois") { document.getElementById("nom").innerHTML = ident; }
                if (value == "Type") { document.getElementById("type").innerHTML = ident; }
                if (value == "Origin") { document.getElementById("origine").innerHTML = ident; }
                if (value == "Sechage")
                {
                    document.getElementById("sechage").innerHTML = ident;
                    document.getElementById("temperatureMinInfo").innerHTML = ident;
                }
                if (value == "Temps")
                {
                    document.getElementById("timer").innerHTML = "0";
                    document.getElementById("temps").innerHTML = ident;
                    document.getElementById("tempsSechageInfo").innerHTML = ident;
                }

            }
            document.getElementById("caracteristiquesBois").style.display = "block";
            document.getElementById("cercleStatut").style.backgroundColor = "red";
        }
    };

    var sel = document.getElementById("typeBois_ListBox_Select");
    var params = String("wood") + String("=") + String(sel.options[sel.selectedIndex].text);
    xhttp.open("POST", "getWoodCaracteristiques", true);
    xhttp.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    xhttp.send(params);
}

// ----------------- Démarrage du Four à bois ----------------------

function demarrageFour()
{
    var i = 0;
    var temp = parseInt(temperature);

    document.getElementById("cercleStatut").style.backgroundColor = "orange";
    if (temp >= document.getElementById("sechage").textContent)
    {
        var timer = setInterval(function()
        {
                i++
                document.getElementById("timer").innerHTML = i;
                
                console.log(i);
                if (i == document.getElementById("temps").textContent || document.getElementById('four').clicked == true)
                {
                    document.getElementById("cercleStatut").style.backgroundColor = "green";
                    clearInterval(timer);
                    alert("Le sechage est finit ! ");
                }
                else if (document.getElementById('four').clicked == true)
                {
                    clearInterval(timer);
                }
        }, 1000);
    }
    else
    {
        alert("La temperature du four n'est pas assez elevee! ");
    }

 



}