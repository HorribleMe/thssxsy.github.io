var type;//初始化按钮的位置，5种状态
var m_x, m_y;//按钮初始位置
var BackToTop = {
	init:function(para1)
	{
		if(para1.x != undefined)
		{
			m_x = para1.x;
			m_y = para1.y;
			type = 1;
		}
		else if(para1.LeftUp == true)
			type = 2;
		else if(para1.LeftDown == true)
			type = 3;
		else if(para1.RightUp == true)
			type = 4;
		else
			type = 5;
		}
}
BackToTop.init({x:100,y:100});
function googlead()
{
    _dom = document.getElementById("logocont");
    if(_dom == undefined) return;
    _dom.style.position='fixed';

    if(type == 1)
    {
    	_dom.style.left = m_x + 'px';
   		_dom.style.top = m_y + 'px';
    }
    else if(type == 2)
    {
    	_dom.style.left = 0;
   		_dom.style.top = 0;
    }
    else if(type == 3)
    {
    	_dom.style.left = 0;
   		_dom.style.top = (window.innerHeight-_dom.clientHeight)+'px';
   	}
    else if(type == 4)
    {
    	_dom.style.left = (window.innerWidth-_dom.clientWidth-3)+'px';
   		_dom.style.top = 0;
    }
    else
    {
    	_dom.style.left = (window.innerWidth-_dom.clientWidth-3)+'px';
   		_dom.style.top = (window.innerHeight-_dom.clientHeight)+'px';
   	}
   	 var x = document.body.scrollTop;
    if(x > 100)
    	_dom.style.display='block';
   	else
    	_dom.style.display='none';
};
	var scroll = document.getElementById('logocont');
	scroll.click = function (){
		window.scrollBy(0, -33);
	if(document.body.scrollTop == 0)
		return;
	setTimeout(scrollToTop, 3);
	}
(function()
{
    window.onscroll=googlead;
    window.resize=googlead;
    googlead();
})();

function scrollToTop()
{
	window.scrollBy(0, -33);
	if(document.body.scrollTop == 0)
		return;
	setTimeout(scrollToTop, 3);
};