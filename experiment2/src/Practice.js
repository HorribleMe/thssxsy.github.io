//HorribleMe
//Created on 7.3 2016
// 2014013413

//practice 1
var func = {
	getNum: function(){return this.num;},
	num: 1
};

var answer = (function()
{
	return typeof arguments[0]();
})(func.getNum);

console.log(answer);

//practice 2
var x = 0;
function foo()
{
	x++;
	this.x = x;
	return foo;
}

var bar = new new foo;
console.log(bar.x);

//practice 3
function bar3()
{
	return fooo;
	fooo = 10;
	function fooo(){}
	var fooo = '11';
}
//alert(typeof bar3());

//practice 4
var x4 = 3;
var foooo = {
	x4: 2,
	baz: {
		x4: 1,
		bar4:function(){
			return this.x4;
		}
	}
}
var go = foooo.baz.bar4;
//alert(go());
//alert(foooo.baz.bar4());

//practice 5
function aaa()
{
	return
	{
		test: 1
	};
};
alert(typeof aaa());