async function loadSeats(){

try{

const response=await fetch("/api/seats");

const data=await response.json();

document.getElementById("total").innerHTML=data.total;

document.getElementById("available").innerHTML=data.available;

document.getElementById("occupied").innerHTML=data.occupied;

updateSeat("seat1",data.seat1);

updateSeat("seat2",data.seat2);

updateSeat("seat3",data.seat3);

}

catch(e){

console.log(e);

}

}

function updateSeat(id,status){

const seat=document.getElementById(id);

if(status){

seat.innerHTML="Occupied";

seat.className="occupied";

}

else{

seat.innerHTML="Free";

seat.className="free";

}

}

loadSeats();

setInterval(loadSeats,1000);
