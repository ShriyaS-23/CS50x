let flag = 0;
let custom = document.querySelector("form");
custom.addEventListener("submit", function (e) {
  e.preventDefault();
  if (flag === 0) {
    let deckE = document.createElement("div");
    deckE.id = "Dcard-deckE";
    deckE.className = "card-deck";
    document.querySelector("#Devents").appendChild(deckE);
    let deckD = document.createElement("div");
    deckD.id = "Dcard-deckD";
    deckD.className = "card-deck";
    document.querySelector("#Ddeaths").appendChild(deckD);
    let deckB = document.createElement("div");
    deckB.id = "Dcard-deckB";
    deckB.className = "card-deck";
    document.querySelector("#Dbirths").appendChild(deckB);
    flag = 1;
  } else if (flag === 1) {
    document.querySelector("#Dcard-deckE").innerHTML = "";
    document.querySelector("#Dcard-deckD").innerHTML = "";
    document.querySelector("#Dcard-deckB").innerHTML = "";
  }

  let month = document.querySelector("input#month");
  let day = document.querySelector("input#day");
  fetch(`https://history.muffinlabs.com/date/${month.value}/${day.value}`)
    .then((res) => res.json())
    .then((data) => {
      let date = data.date;
      document.querySelector("#Ddate").innerHTML = date;
      document.querySelector("#eTitle").innerHTML = "Events";

      document.querySelector("#form").style.borderBottom = "3px solid black";
      document.querySelector("#form").style.borderTop = "3px solid black";

      let event = data.data.Events.reverse();
      for (let item in event) {
        //let l = event[item]["links"][0]["link"];
        let card = document.createElement("div");
        card.className = "card";
        card.id = `Decard${item}`;
        let eventYr = document.createElement("p");
        eventYr.className = "card-title";
        let eventTxt = document.createElement("p");
        eventTxt.className = "card-text";
        //let eventLink = document.createElement("a");
        //eventLink.className = "card-link";
        //eventLink.href = l;
        document.querySelector("#Dcard-deckE").appendChild(card);
        eventYr.appendChild(document.createTextNode(event[item]["year"]));
        eventTxt.appendChild(document.createTextNode(event[item]["text"]));
        //console.log(eventTxt);
        //event[item]["no_year_html"]   -----  gives html with links
        //eventTxt.innerHtml += event[item]["no_year_html"];
        document.querySelector(`#Decard${item}`).appendChild(eventYr);
        document.querySelector(`#Decard${item}`).appendChild(eventTxt);
      }

      let deaths = data.data.Deaths.reverse();
      document.querySelector("#dTitle").innerHTML = "Deaths";
      for (let item in deaths) {
        //console.log(item);
        let card = document.createElement("div");
        card.className = "card";
        card.id = `Ddcard${item}`;
        let deathYr = document.createElement("p");
        deathYr.className = "card-title";
        let deathTxt = document.createElement("p");
        deathTxt.className = "card-text";
        document.querySelector("#Dcard-deckD").appendChild(card);
        deathYr.appendChild(document.createTextNode(deaths[item]["year"]));
        deathTxt.appendChild(document.createTextNode(deaths[item]["text"]));
        document.querySelector(`#Ddcard${item}`).appendChild(deathYr);
        document.querySelector(`#Ddcard${item}`).appendChild(deathTxt);
      }

      let births = data.data.Births.reverse();
      document.querySelector("#bTitle").innerHTML = "Births";
      for (let item in event) {
        let card = document.createElement("div");
        card.className = "card";
        card.id = `Dbcard${item}`;
        let birthYr = document.createElement("p");
        birthYr.className = "card-title";
        let birthTxt = document.createElement("p");
        birthTxt.className = "card-text";
        document.querySelector("#Dcard-deckB").appendChild(card);
        birthYr.appendChild(document.createTextNode(births[item]["year"]));
        birthTxt.appendChild(document.createTextNode(births[item]["text"]));
        document.querySelector(`#Dbcard${item}`).appendChild(birthYr);
        document.querySelector(`#Dbcard${item}`).appendChild(birthTxt);
      }
    });
});
