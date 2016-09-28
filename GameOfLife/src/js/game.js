var image;
var draw;
var refreshTime = 150;
var cellSize = 10;
var cellNum1 = 50;
var cellNum2 = 50;
var cells = [];
var running = false;

function drawCell(x, y, state){
	var r = cellSize / 2;
	var xLoc = (x - 1) * cellSize + r;
	var yLoc = (y - 1) * cellSize + r;
	if(state && state == 1){
		draw.fillStyle = "Green";
		draw.beginPath();
		draw.arc(xLoc, yLoc, r, 0, Math.PI*2, true);
		draw.closePath();
		draw.fill();
	}
	else{
		draw.clearRect(xLoc - r, yLoc - r, cellSize, cellSize);
	}
}

function getState(x, y){
	var neighbours = [];
	var neighbourLiveNum = 0;
	var currentState = cells[x][y]
	neighbours[0] = cells[(x - 1+cellNum1)%cellNum1][(y - 1 + cellNum2)%cellNum2];
	neighbours[1] = cells[(x - 1+cellNum1)%cellNum1][(y + 1 + cellNum2)%cellNum2];
	neighbours[2] = cells[(x + 1+cellNum1)%cellNum1][(y - 1 + cellNum2)%cellNum2];
	neighbours[3] = cells[(x + 1+cellNum1)%cellNum1][(y + 1 + cellNum2)%cellNum2];
	neighbours[4] = cells[(x+cellNum1)%cellNum1][(y - 1 + cellNum2)%cellNum2];
	neighbours[5] = cells[(x+cellNum1)%cellNum1][(y + 1 + cellNum2)%cellNum2];
	neighbours[6] = cells[(x - 1+cellNum1)%cellNum1][(y + cellNum2)%cellNum2];
	neighbours[7] = cells[(x + 1+cellNum1)%cellNum1][(y + cellNum2)%cellNum2];
	for(var i = 0;i < 8;i++){
		if(neighbours[i] && neighbours[i] == 1)neighbourLiveNum++;
	}
	if(neighbourLiveNum == 3)return 1;
	else if(neighbourLiveNum == 2)return currentState;
	else return 0;
}

function run(){
	var nextGeneration = [];
	for(x = 0;x < cellNum1;x++)
	{
		nextGeneration[x] = [];
		for(y = 0;y < cellNum2;y++)
			 nextGeneration[x][y] = 0;
	}
	for(x = 0;x < cellNum1;x++)
	{
		for(y = 0;y < cellNum2;y++)
			nextGeneration[x][y] = getState(x, y);
	}
	for(x = 0;x < cellNum1;x++)
	{
		for(y = 0;y < cellNum2;y++)
			cells[x][y] = nextGeneration[x][y];
	}
	for(x = 0;x < cellNum1;x++)
	{
		for(y = 0;y < cellNum2;y++)
			drawCell(x, y, cells[x][y]);
	}
	if(running == true)setTimeout(run, refreshTime);
 }

function start(){
	startButton.disabled = true;
	pauseButton.disabled = false;
	running = true;
	run();
}

function pause(){
	running = false;
	startButton.disabled = false;
	pauseButton.disabled = true;
	resetButton.disabled = false;
}

function reset(){
	for(x = 0;x < cellNum1;x++)
	{
		for(y = 0;y < cellNum2;y++)
			cells[x][y] = 0;
			drawCell(x, y, 0);
	}
	random();
}

function random(){
	for(x = 0;x < cellNum1;x++){
		for(y = 0;y < cellNum2;y++){
			s = (Math.random() >= 0.8) ? 1 : 0;
			cells[x][y] = s;
			drawCell(x, y, s);
		}
	}
}

function gameInit(){
	image = document.getElementById('gameArea');
	draw = image.getContext('2d');
	pauseButton.disabled = true;
	resetButton.disabled = true;
	for(x = 0;x < cellNum1;x++)
	{
		cells[x] = [];
		for(y = 0;y < cellNum2;y++)
			 cells[x][y] = 0;
	}
	random();
}

window.addEventListener("load", gameInit, true);