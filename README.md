# A DAY IN HISTORY
#### Video Demo: https://youtu.be/e-sIf1aKmw4
#### Description:
A website made using HTML, CSS and JavaScript that can display events, deaths and births that have hapened today and on a specific date of the users choosing.

> API Used: https://history.muffinlabs.com/
> Data Taken from Wikipedia.

Consists of two pages 'Today' and 'Choose Date'

##### Today:
Displays events, deaths and births that have happened in history today. All of the informaton is displayed in independentaly scrollable sections to prevent the page from being too long. Information is displayed in a card deck layout with each piece of information on a different card.

##### Choose Date:
Displays events, deaths and births that have happened on any custom date of the user's choosing in history. Layout is similar to the 'Today' page with independently scrollable sections for events, deaths and births and a card deck layout to display the information.

Error checking has been done by putting in checks to prevent the user from putting in invalid dates that won't fetch any data.

#### Code:
The code is distributed in a total of 5 files. index.html, custom.html, static.css, app.js and custom.js.

##### index.html:
This is the html for the today page. It gives a basic layout to the page. It has a section for the Navbar at the top which contains the title of the website on the left side and buttons to toggle to the two different pages on the other side.
It also contains a banner section which displays the current date and three other sections which are filled using javascript with the information that is to be displayed on the website.

##### custom.html:
This is the html for the custom page. It has a section for the Navbar at the top which contains the title of the website on the left side and buttons to toggle to the two different pages on the other side. It contains a form for the user to enter the date and a few empty sections that get populated with the requested data once the users submits their date.

##### static.css:
This is the CSS Stylesheet for the website and contains all of the infomration about the design of everything. It has styling for the card deck architetcture, colour scheme, banners, navbr and footer.

##### app.js:
This is the JavaScript behind the 'Today' page. Here fetch is used to get data about events that have happened on today's date from the muffinlabs API and then display it in the different sections present in the HTML for the page.

##### custom.js:
This is the JavaScript behind the 'Custom' page. It uses the user entered date to fetch data from the muffinlabs API and display it in the empty sections present in the HTML for the page when it is submitted.