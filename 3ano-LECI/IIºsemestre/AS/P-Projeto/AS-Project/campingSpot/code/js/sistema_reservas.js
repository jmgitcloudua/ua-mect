var date_start = null;
var date_end = null;
var type = null;
var nPeople = null;

const TENDA_LIMIT = 5; 
const CARAVANA_LIMIT = 10;
const CAMPING_RV_LIMIT = 10;

const PRECO_TENT = 18
const PRECO_CARAVANA = 50
const PRECO_RV = 90

const ANDAR_CAVALO = 5;
const FUTEBOL = 3;
const CAMINHADA = 1.5;
const PESCA = 2;
const BIKE = 5;
const CANOAGEM = 10;

function getInfo() {
    //console.log("getInfo")
    date_start = document.getElementById("start-date-1").value;
    date_end = document.getElementById("end-date-1").value;
    type = document.getElementById("type").value;
    nPeople = document.getElementById("nPeople").value;
    localStorage.setItem("start-date-1",date_start)
    localStorage.setItem("end-date-1",date_end)
    localStorage.setItem("type", type)
    localStorage.setItem("nPeople", nPeople)
}

function getAtividades(){
    var x = document.getElementById("atividades");
    var text = "";
    var cavalo = localStorage.getItem("atividade_cavalo");
    var futebol = localStorage.getItem("atividade_futebol");
    var caminhada = localStorage.getItem("atividade_caminhada");
    var pesca = localStorage.getItem("atividade_pesca");
    var bike = localStorage.getItem("atividade_bike");
    var canoagem = localStorage.getItem("atividade_canoagem");
    if(cavalo!=""){
        text+=" Cavalo: "+ cavalo+"  ";
    }
    if(futebol!=""){
        text+=" Futebol: "+ futebol+"  ";
    }
    if(caminhada!=""){
        text+=" Caminhada: "+ caminhada+"  ";
    }
    if(pesca!=""){
        text+=" Pesca: "+  pesca+"  ";
    }
    if(bike!=""){
        text+="Bicicleta: "+ bike+"  ";
    }
    if(canoagem!=""){
        text+="Canoagem: "+canoagem+"  ";
    }
    if(text==""){
        text = "Nenhuma"
    }
    x.innerHTML = text;
}

function setAtividades(){
    var cavalo = document.getElementById("cavalo").value;
    console.log(cavalo)
    var futebol = document.getElementById("futebol").value;
    console.log(futebol)
    var caminhada = document.getElementById("caminhada").value;
    var pesca = document.getElementById("pesca").value;
    var bike = document.getElementById("bike").value;
    var canoagem = document.getElementById("caiaque").value;
    console.log(canoagem);
    localStorage.setItem("atividade_cavalo",cavalo);
    localStorage.setItem("atividade_futebol",futebol);
    localStorage.setItem("atividade_caminhada",caminhada);
    localStorage.setItem("atividade_pesca",pesca);
    localStorage.setItem("atividade_bike",bike);
    localStorage.setItem("atividade_canoagem",canoagem);
    var button = document.getElementById("pagamento");
    button.setAttribute("href","payment.html")
}

function getVagas (){
   
    var dias = getPeriodOfDays(localStorage.getItem("start-date-1"),localStorage.getItem("end-date-1"))
    var min=null
    if ( localStorage.getItem("type")==1) {
        min = TENDA_LIMIT
    }else if( localStorage.getItem("type")==2){
        min = CARAVANA_LIMIT
    }else if ( localStorage.getItem("type")==3){
        min = CAMPING_RV_LIMIT
    }
    
    for (let index = 0; index < dias.length; index++) {
        var vagas = localStorage.getItem(dias[index]+"::"+ localStorage.getItem("type"))
        
        if(vagas<min){
            min = vagas
        }
    }
    var x = null;
    if(localStorage.getItem("type")==1){
        x = document.getElementById("tenda_vagas")
        x.innerHTML = "Apenas tem " + min + " vagas"
    }else if(localStorage.getItem("type")==2){
        x = document.getElementById("caravana_vagas")
        x.innerHTML = "Apenas tem " + min + " vagas"
    }else if(localStorage.getItem("type")==3){
        x = document.getElementById("camping-rv_vagas")
        x.innerHTML = "Apenas tem " + min + " vagas"
    }
}

function book(){
    console.log("book")
        const periodOfDays = getPeriodOfDays(localStorage.getItem("start-date-1"),localStorage.getItem("end-date-1"))
        for (let index = 0; index < periodOfDays.length; index++) {
            var x = localStorage.getItem(periodOfDays[index]+"::"+ localStorage.getItem("type"))
            localStorage.setItem(periodOfDays[index]+"::"+ localStorage.getItem("type"),x - localStorage.getItem("nPeople"))
        }
        var x = document.getElementById("butao_de_pagar")
        x.setAttribute("href","index.html")
}
function disponibilidade (){
    isAvailable(getPeriodOfDays(localStorage.getItem("start-date-1"),localStorage.getItem("end-date-1")))
}

function completarTabela(){

    var check_in = document.getElementById("check_in")
    var check_out = document.getElementById("check_out")
    var qtd = document.getElementById("qtd")
    var precototal = document.getElementById("precototal")

    var text = localStorage.getItem("start-date-1")
    const array1 = text.split(".")
    check_in.innerHTML = array1[1]+"/"+array1[0]+"/"+array1[2]
    text = localStorage.getItem("end-date-1")
    const array2 = text.split(".")
    check_out.innerHTML = array2[1]+"/"+array2[0]+"/"+array2[2]
    switch (localStorage.getItem("type")) {
        case "1":
           text = "Tenda: " 
         break; 
        case "2":
            text = "Caravana: "    
        break;
        case "3":
            text = "Camping RV: " 
        break;
    
        default:
            break;
    }
    text += localStorage.getItem("nPeople")
    qtd.innerHTML = text
    if(localStorage.getItem("type")=="1"){
        text =  parseInt(localStorage.getItem("nPeople"))*PRECO_TENT
    }else if(localStorage.getItem("type")=="2"){
        text = parseInt(localStorage.getItem("nPeople"))*PRECO_CARAVANA 
    }else if(localStorage.getItem("type")=="3"){
        text = parseInt(localStorage.getItem("nPeople"))*PRECO_RV 
    }

    if(localStorage.getItem("atividade_cavalo")!=""){
        text+= parseInt(localStorage.getItem("atividade_cavalo")) *ANDAR_CAVALO;
    }
    if(localStorage.getItem("atividade_futebol")!=""){
        text+= parseInt(localStorage.getItem("atividade_futebol")) *FUTEBOL;
    }
    if(localStorage.getItem("atividade_caminhada")!=""){
        text+= parseInt(localStorage.getItem("atividade_caminhada")) *CAMINHADA;
    }
    if(localStorage.getItem("atividade_pesca")!=""){
        text+= parseInt(localStorage.getItem("atividade_pesca")) *PESCA;
    }
    if(localStorage.getItem("atividade_bike")!=""){
        text+= parseInt(localStorage.getItem("atividade_bike")) *BIKE;
    }
    if(localStorage.getItem("atividade_canoagem")!=""){
        text+= parseInt(localStorage.getItem("atividade_canoagem")) *CANOAGEM;
    }
    text += " €"; 
    precototal.innerHTML = text
}

function isAvailable(periodOfDays){
    //console.log("isAvailable")
    var available = true
    for (let index = 0; index < periodOfDays.length; index++) {
        var x = localStorage.getItem(periodOfDays[index]+"::"+ localStorage.getItem("type"))
        if(x == null){
            if(localStorage.getItem("type")=="1"){
                localStorage.setItem(periodOfDays[index]+"::"+localStorage.getItem("type"),TENDA_LIMIT);
            }else if( localStorage.getItem("type")=="2"){
                localStorage.setItem(periodOfDays[index]+"::"+localStorage.getItem("type"),CARAVANA_LIMIT);
            }else if( localStorage.getItem("type")=="3"){
                localStorage.setItem(periodOfDays[index]+"::"+localStorage.getItem("type"),CAMPING_RV_LIMIT);
            }
            x = localStorage.getItem(periodOfDays[index]+"::"+localStorage.getItem("type"))
        }
        if(parseInt(x) < parseInt(localStorage.getItem("nPeople"))){
            available=false
        }
        var book = document.getElementById("book")
        if(available){
            if (localStorage.getItem("type")==1) {
                book.setAttribute("href","search-tent.html")
            }else if(localStorage.getItem("type")==2){
                book.setAttribute("href","search-caravan.html")
            }else if (localStorage.getItem("type")==3){
                book.setAttribute("href","search-camping-rv.html")
            }
        }else{
            alert("Não há vagas para a data desejada")
            break;
            }
        }
    return available;
    }
    


function getPeriodOfDays(date_s,date_e){
    //console.log("getPeriodOfDays")
    const array = [];
    array.push(date_s);
    while(date_s!=date_e){
        date_s = incrementDay(date_s);
        array.push(date_s); 
    }
    return array
}

function incrementDay(date){
    //console.log("incrementDay")
    const values = date.split(".")
    var day = parseInt(values[1])
    var month = parseInt(values[0])
    var year = parseInt(values[2])

    if (month == 12 && day == monthDays(month, year)) {
        year++;
        month = 1;
        day = 1;
    } else if (day == monthDays(month, year)) {
        month++;
        day = 1;
    } else {
        day++;
    }

    if(day<10){
        day = 0 + day.toString()
    }

    if(month<10){
        month = 0 + month.toString()
    }

    return month+"."+day+"."+year
}

function monthDays(month, year) {
    const days = [ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];
    if (leapYear(year) && month == 2) {
        return 29;
    }
    return days[month - 1];
}

function leapYear(year) {
    if ((year % 4 == 0 && year % 100 == 0 && year % 400 == 0)) {
        return true;
    } else if (year % 4 == 0 && year % 100 != 0) {
        return true;
    }
    return false;
}