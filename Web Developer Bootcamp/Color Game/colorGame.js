// set variables
var colors = [];
var squares = document.querySelectorAll(".color-square");
var colorDisplay = document.querySelector("#color-display");
var messageDisplay = document.querySelector("#message");
var h1 = document.querySelector("h1");
var resetBtn = document.querySelector("#resetButton");
var numSquares = 6;
var modeButtons = document.querySelectorAll(".mode");
var pickedColor;

/* Setup the Game*/
init();

function init(){
	setupModeButtons();
	generateSquares();
	reset();
}

// Set up New Colors Button
resetBtn.addEventListener("click", function(){
	reset();
});

/* FUNCTIONS */
function setupModeButtons(){
	for(var i = 0; i < modeButtons.length; i++){
		modeButtons[i].addEventListener("click", function(){
			modeButtons[0].classList.remove("selected");
			modeButtons[1].classList.remove("selected");

			this.classList.add("selected");
			this.textContent === "Easy" ? numSquares = 3: numSquares = 6;
			reset();
		});
	}
}

function reset(){
	// create array for random colors
	colors = generateRandomColors(numSquares);

	// generate random color to match
	pickedColor = pickColor();

	// Handle display
	resetBtn.textContent = "New Colors";
	messageDisplay.textContent = "";

	// Display the color to match
	colorDisplay.textContent = pickedColor;
	
	// reset sqaures
	for(var i = 0; i < squares.length; i++){
		if(colors[i]){
			squares[i].style.display = "block";
			squares[i].style.background = colors[i];
		} else {
			squares[i].style.display = "none";
		}
	}
	h1.style.backgroundColor = "steelblue";
}

function generateSquares(){
	// Set up the squares
	for(var i = 0; i < squares.length; i++){
		// add listener to each
		squares[i].addEventListener("click", function(){
			// change title to reflect chosen color
			 var clickedColor = this.style.backgroundColor;

			// compare color to pickedColor
			if(clickedColor === pickedColor){
				messageDisplay.textContent = "Correct!!!";
				changeColors(clickedColor);
				h1.style.backgroundColor = clickedColor;
				resetBtn.textContent = "Play Again?"; //need toggle
			} else {
				console.log("wrong");
				// remove block from game 
				this.style.backgroundColor = "#232323";
				messageDisplay.textContent = "Try Again";
			}
		});
	} 
}

function changeColors(color){
	//loop through all squares
	for(var i = 0; i < colors.length; i++){
		squares[i].style.backgroundColor = color; 
	}
}

function pickColor(){
	var random = Math.floor(Math.random() * colors.length); 
	//floor cuts off decimals
	return colors[random];
}

function generateRandomColors(num){
	//make an array
	var arr = [];
	for(var i = 0; i < num; i++){
		//get random color and push to arr
		arr.push(randomColor());
	}
	
	//return that array
	return arr;
}

function randomColor(){
	// red from 0 -255
	var r = Math.floor(Math.random() * 256);

	// blue from 0 - 255
	var g = Math.floor(Math.random() * 256);

	// green from 0 - 255
	var b = Math.floor(Math.random() * 256);	

	return "rgb(" + r + ", " + g + ", " + b + ")";
}