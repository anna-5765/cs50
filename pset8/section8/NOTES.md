* HTTP: allows servers and webpages to interact with eachother
* HTML: this is where the content of the webpage is built
* CSS: this holds the styling of your webpage
* JavaScript: this controls how the user can interact with the webpage

scoreboard.html
As seen in lecture, run <http-server> in the folder where scoreboard is to see the page (quit using ctrl+c)
Currently, you can add points to increase the score of two teams
DOM: document object model, a tree that builds the html model top to bottom

(imagine this top to bottom)

document -> html -> head -> title ...
                         -> style ...
                 -> body -> table ...
                         -> script ...

(examining table component in body)

table -> tr -> td -> Team1
            -> td -> Team2
      -> tr -> td -> 0
            -> td -> 0
      -> tr -> td -> button -> +1
            -> td -> button -> +1

features to add:
main, header, footer, h1, p

w3shcools is a great resource to look into more tags

Style with CSS
in the style tag
selector (or .classname)(or #id)
{
    property: value;
    property: value;
}

JavaScript
in the script tag

document.querySelector('#add1') - JS looks for id add1 in tree top to bottom
.onclick - happens once the corresponding button is clicked

use 'let' to set variables

javascript can be embedded directly into the html file, while python needs to use an additional framework (next week)

To create a new file with style changes, move content in html style tag to its own style.css file
Delete style tags in html
link to the file by <link rel="stylesheet" href="styles.css"> in head
save both files and refresh page
