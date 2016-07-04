//HorribleMe
//Created on 7.3 2016
// 2014013413

function search(para1, para2)
{
	if((typeof para2) == "string")
	{
		for(var i = 0;i < para1.length;i++)
		{
			if(para2 == para1[i].name)
				return para1[i];
		}
		return false;
	}
	else if((typeof para2) == "number")
	{
		var result = new Array();
		var id = 0;
		for(var i = 0;i < para1.length;i++)
		{
			if(para1[i].age == para2)
			{
				result[id] = para1[i];
				id++;
			}
		}
		if(id == 0)
			return flase;
		else 
			return result;
	}
	else
	{
		var result = new Array();
		if(para2.name != undefined)
		{
			var id = 0;
			for(var i = 0;i < para1.length;i++)
			{
				if(para1[i].name == para2.name)
				{
					if(para2.age != undefined)
					{
						if(para1[i].age == para2.age)
						{
							if(para2.hometown != undefined)
							{
								if(para1[i].hometown == para2.hometown)
								{
									result[id] = para1[i];
									id++;
									}
							}
						}
					}
					else if(para2.hometown != undefined)
					{
						if(para1[i].hometown == para2.hometown)
						{
							result[id] = para1[i];
							id++;
						}
					}
					else
					{
						result[id] = para1[i];
						id++;
					}
				}
			}
			if(id == 0)
				return false;
			else
				return result;
		}
		else if(para2.age != undefined)
		{
			var id = 0;
			for(var i = 0;i < para1.length;i++)
			{
				if(para1[i].age == para2.age)
				{
					if(para2.hometown != undefined)
					{
						if(para1[i].hometown == para2.hometown)
						{
							result[id] = para1[i];
							id++;
						}
					}
					else
					{
						result[id] = para1[i];
						id++;
					}
				}
			}
			if(id == 0)
				return false;
			else
				return result;
		}
		else
		{
			var id = 0;
			for(var i = 0;i < para1.length;i++)
			{
				if(para1[i].hometown == para2.hometown)
				{
					result[id] = para1[i];
					id++;
				}
			}
			if(id == 0)
				return false;
			else
				return result;
		}
	}
}