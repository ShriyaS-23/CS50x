let date = new Date();
let day = date.getDate();
let month = date.getMonth() + 1;

fetch(`https://history.muffinlabs.com/date/${month}/${day}`)
  .then((res) => res.json())
  .then((data) => {
    let date = data.date;
    document.querySelector("#date").innerHTML = date;

    let event = data.data.Events.reverse();

    for (let item in event) {
      let card = document.createElement("div");
      card.className = "card";
      card.id = `ecard${item}`;
      let eventYr = document.createElement("p");
      eventYr.className = "card-title";
      let eventTxt = document.createElement("p");
      eventTxt.className = "card-text";
      document.querySelector("#card-deckE").appendChild(card);
      eventYr.appendChild(document.createTextNode(event[item]["year"]));
      eventTxt.appendChild(document.createTextNode(event[item]["text"]));
      document.querySelector(`#ecard${item}`).appendChild(eventYr);
      document.querySelector(`#ecard${item}`).appendChild(eventTxt);
    }

    let deaths = data.data.Deaths.reverse();
    for (let item in deaths) {
      let card = document.createElement("div");
      card.className = "card";
      card.id = `dcard${item}`;
      let deathYr = document.createElement("p");
      deathYr.className = "card-title";
      let deathTxt = document.createElement("p");
      deathTxt.className = "card-text";
      document.querySelector("#card-deckD").appendChild(card);
      deathYr.appendChild(document.createTextNode(deaths[item]["year"]));
      deathTxt.appendChild(document.createTextNode(deaths[item]["text"]));
      document.querySelector(`#dcard${item}`).appendChild(deathYr);
      document.querySelector(`#dcard${item}`).appendChild(deathTxt);
    }

    let births = data.data.Births.reverse();
    for (let item in event) {
      let card = document.createElement("div");
      card.className = "card";
      card.id = `bcard${item}`;
      let birthYr = document.createElement("p");
      birthYr.className = "card-title";
      let birthTxt = document.createElement("p");
      birthTxt.className = "card-text";
      document.querySelector("#card-deckB").appendChild(card);
      birthYr.appendChild(document.createTextNode(births[item]["year"]));
      birthTxt.appendChild(document.createTextNode(births[item]["text"]));
      document.querySelector(`#bcard${item}`).appendChild(birthYr);
      document.querySelector(`#bcard${item}`).appendChild(birthTxt);
    }
  });
