//HorribleMe
//Created on 7.9 2016

var isAdmin = false;
var admin, adminPicPath="./pics/admin.jpg";

function loadDone()
{
	getNew();
	var socket = io.connect("https://wall.cgcgbcbc.com");
	socket.on("new message", function(info){addMessage(info["headimgurl"], info["nickname"], info['content'])});
	socket.on("admin", function(info){
		if(isAdmin == true)
		{
			clearTimeout(admin);
			setUp(1, adminPicPath, info["nickname"], info['content']);
			admin = setTimeout(cancelAdmin, 10000);
		}
		else
		{
			addMessage(adminPicPath, info["nickname"], info['content']);
			admin = setTimeout(cancelAdmin, 10000);
		}
	})
}

window.addEventListener("load", loadDone(), false);

function cancelAdmin(){
	document.getElementById("item1").style.backgroundColor = "black";
	document.getElementById("message1").style.color = "white";
	isAdmin = false;
	getNew();
}

function addMessage(headPic, name, message){
	document.getElementById("item3").style.display = "none";
	var top = 200, length = 150;
	var tops = new Array();
	for(var i = 1;i < 3;i++)
	{
		tops[i] = top + (i-1)*length;
	}
	var scroll = setInterval(function(){
		console.log(isAdmin);
		if(isAdmin == false)
		{
			for(var i = 1;i <= 2;i++)
			{
				tops[i] += 3;
				document.getElementById("item" + i.toString()).style.top = tops[i] + "px";
			}
			if(tops[2] >= top + 2*length)
			{
				for(var i = 3;i >= 1;i--)
					changeItem(i,i+1);
				changeItem(4,1);
				var item = document.getElementById("item1");
				item.style.top = top + "px";
				item.style.display = "block";
				setUp(1, headPic, name, message);
				if(headPic == adminPicPath)
					isAdmin = true;
				clearInterval(scroll);
			}
		}
		else
		{
			tops[2] += 3;
			document.getElementById("item2").style.top = tops[2] + "px";
			if(tops[2] >= top + 2*length)
			{
				for(var i = 3;i >= 2;i--)
					changeItem(i,i+1);
				changeItem(4,2);
				var item = document.getElementById("item2");
				item.style.top = top + length + "px";
				item.style.display = "block";
				setUp(2, headPic, name, message);
				clearInterval(scroll);
			}
		}
	},10)
}

function changeItem(oldItem, newItem)
{
	document.getElementById("item" + oldItem).id = "item" + newItem.toString();
	document.getElementById("name" + oldItem).id = "name" + newItem.toString();
    document.getElementById("headPic" + oldItem).id = "headPic" + newItem.toString();
    document.getElementById("message" + oldItem).id = "message" + newItem.toString();
    for(var i = 1;i <=3;i++)
    	document.getElementById("_circle" + oldItem + i.toString()).id = "_circle" + newItem.toString() + i.toString();
}

function setUp(id, headPic, name, message){
    for(var i = 1;i <=3;i++)
    	document.getElementById("_circle" + id + i.toString()).style.display = "block";
    if(headPic == adminPicPath)
    {
    	document.getElementById("item1").style.backgroundColor = "#2E8B57";
        document.getElementById("message1").style.color = "#FF7F50";
    }
	var _headPic = document.getElementById("headPic" + id);
	var _name = document.getElementById("name" + id);
	var _message = document.getElementById("message" + id);
	_headPic.src = headPic;
	_name.innerText = name;
	_headPic.onload = function()
	{
		_headPic.style.display = "block";
		for(var i = 1;i <=3;i++)
    		document.getElementById("_circle" + id + i.toString()).style.display = "none";
	}
	if(message.length >= 22 && _message.tagName == "DIV")
	{
		_message.parentNode.removeChild(_message);
		var newMessage = document.createElement("marquee");
		newMessage.id = "message" + id;
		newMessage.className = "message";
		newMessage.innerText = message;
		newMessage.behavior="scroll";
		newMessage.scrollAmout = "3";
		newMessage.direction = "left";
		newMessage.scrolldelay="0";
		newMessage.loop="-1";
		newMessage.hspace="10";
		newMessage.vspace="10";
		_headPic.parentNode.appendChild(newMessage);
	}
	else if(message.tagName == "MARQUEE" && message.length < 22)
	{
		_message.parentNode.removeChild(_message);
		var newMessage = document.createElement("div");
		newMessage.id = "message" + id;
		newMessage.className = "message";
		newMessage.innerText = message;
		_headPic.parentNode.appendChild(newMessage);
	}
	else
		_message.innerText = message;
	
	_headPic.onload = function () {
		_headPic.style.display = "block";
		for(var i = 1;i <=3;i++)
    		document.getElementById("_circle" + id + i.toString()).style.display = "none";
	}
}

function getNew(){
	var news = new XMLHttpRequest();
	news.open("get", "https://wall.cgcgbcbc.com/api/messages?num=3", true);
	news.send(null);
	news.onreadystatechange = function(){
		if(news.readyState == 4)
		{
			var info = news.responseText;
			var _info = JSON.parse(info);
			for(var i = 0;i <= 2;i++)
				setUp(i+1, _info[i]["headimgurl"], _info[i]["nickname"], _info[i]['content']);
		}
	}
}