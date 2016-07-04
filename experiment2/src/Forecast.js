//HorribleMe
//Created on 7.3 2016
// 2014013413

var Country = ["Swiss", "Poland", "Croatia", "Portugal", "NorthernIreland", "Wales", "Hungary", "Belgium", "Germany", "Slovak", "Italy", "Spain", "France", "Ireland", "England", "Iceland"];
var scores = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];
var winRate = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1];
var countryId = 
{
	Swiss: 0,
	Poland: 1,
	Croatia: 2,
	Portugal: 3,

	NorthernIreland: 4,
	Wales: 5,
	Hungary: 6,
	Belgium: 7,

	
	Germany: 8,
	Slovak: 9,
	Italy: 10,
	Spain: 11,
	
	France: 12,
	Ireland: 13,
	England: 14,
	Iceland: 15
};

function forecast(info, country)
{
	takeApart(info);
	for(var round = 1;round <= 4;round++)
	{
		if(round == 1)
		{
			for(var id = 0;id <= 14;id = id + 2)
			{
				winRate[id] = scores[id]/(scores[id] + scores[id + 1]);
				winRate[id + 1] = 1 - winRate[id];
			}
		}
		if(round == 2)
		{
			for(var id = 0;id <= 15;id++)
			{
				if(id == 0 || id == 4 || id == 8 || id == 12)
				{
					var tem1 = scores[id]/(scores[id] + scores[id + 2]);
					var tem2 = scores[id]/(scores[id] + scores[id + 3]);
					tem1 = tem1 * winRate[id] * winRate[id + 2];
					tem2 = tem2 * winRate[id] * winRate[id + 3];
					winRate[id] = tem1 + tem2;
				}
				else if(id == 1 || id == 5 || id == 9 || id == 13)
				{
					var tem1 = scores[id]/(scores[id] + scores[id + 1]);
					var tem2 = scores[id]/(scores[id] + scores[id + 2]);
					tem1 = tem1 * winRate[id] * winRate[id + 1];
					tem2 = tem2 * winRate[id] * winRate[id + 2];
					winRate[id] = tem1 + tem2;
				}
				else if(id == 2 || id == 6 || id == 10 || id == 14)
				{
					var tem1 = scores[id]/(scores[id] + scores[id - 2]);
					var tem2 = scores[id]/(scores[id] + scores[id - 1]);
					tem1 = tem1 * winRate[id] * winRate[id - 2];
					tem2 = tem2 * winRate[id] * winRate[id - 1];
					winRate[id] = tem1 + tem2;
				}
				else if(id == 3 || id == 7 || id == 11 || id == 15)
				{
					var tem1 = scores[id]/(scores[id] + scores[id - 3]);
					var tem2 = scores[id]/(scores[id] + scores[id - 2]);
					tem1 = tem1 * winRate[id] * winRate[id - 3];
					tem2 = tem2 * winRate[id] * winRate[id - 2];
					winRate[id] = tem1 + tem2;
				}
			}
		}
		if(round == 3)
		{
			for(var id = 0;id <= 15;id++)
			{
				if(id <= 3)
				{
					var tem1 = scores[id]/(scores[id] + scores[4]);
					var tem2 = scores[id]/(scores[id] + scores[5]);
					var tem3 = scores[id]/(scores[id] + scores[6]);
					var tem4 = scores[id]/(scores[id] + scores[7]);
					tem1 = tem1 * winRate[id] * winRate[4];
					tem2 = tem2 * winRate[id] * winRate[5];
					tem3 = tem3 * winRate[id] * winRate[6];
					tem4 = tem4 * winRate[id] * winRate[7];
					winRate[id] = tem1 + tem2 + tem3 + tem4;
				}
				else if(id > 3 && id <= 7)
				{
					var tem1 = scores[id]/(scores[id] + scores[0]);
					var tem2 = scores[id]/(scores[id] + scores[1]);
					var tem3 = scores[id]/(scores[id] + scores[2]);
					var tem4 = scores[id]/(scores[id] + scores[3]);
					tem1 = tem1 * winRate[id] * winRate[0];
					tem2 = tem2 * winRate[id] * winRate[1];
					tem3 = tem3 * winRate[id] * winRate[2];
					tem4 = tem4 * winRate[id] * winRate[3];
					winRate[id] = tem1 + tem2 + tem3 + tem4;
				}
				else if(id > 7 && id <= 11)
				{
					var tem1 = scores[id]/(scores[id] + scores[12]);
					var tem2 = scores[id]/(scores[id] + scores[13]);
					var tem3 = scores[id]/(scores[id] + scores[14]);
					var tem4 = scores[id]/(scores[id] + scores[15]);
					tem1 = tem1 * winRate[id] * winRate[12];
					tem2 = tem2 * winRate[id] * winRate[13];
					tem3 = tem3 * winRate[id] * winRate[14];
					tem4 = tem4 * winRate[id] * winRate[15];
					winRate[id] = tem1 + tem2 + tem3 + tem4;
				}
				else if(id > 11)
				{
					var tem1 = scores[id]/(scores[id] + scores[8]);
					var tem2 = scores[id]/(scores[id] + scores[9]);
					var tem3 = scores[id]/(scores[id] + scores[10]);
					var tem4 = scores[id]/(scores[id] + scores[11]);
					tem1 = tem1 * winRate[id] * winRate[8];
					tem2 = tem2 * winRate[id] * winRate[9];
					tem3 = tem3 * winRate[id] * winRate[10];
					tem4 = tem4 * winRate[id] * winRate[11];
					winRate[id] = tem1 + tem2 + tem3 + tem4;
				}
			}
		}
		if(round == 4)
		{
			for(var id = 0;id <= 15;id++)
			{
				if(id <= 7)
				{
					var tem1 = scores[id]/(scores[id] + scores[8]);
					var tem2 = scores[id]/(scores[id] + scores[9]);
					var tem3 = scores[id]/(scores[id] + scores[10]);
					var tem4 = scores[id]/(scores[id] + scores[11]);
					var tem5 = scores[id]/(scores[id] + scores[12]);
					var tem6 = scores[id]/(scores[id] + scores[13]);
					var tem7 = scores[id]/(scores[id] + scores[14]);
					var tem8 = scores[id]/(scores[id] + scores[15]);
					tem1 = tem1 * winRate[id] * winRate[8];
					tem2 = tem2 * winRate[id] * winRate[9];
					tem3 = tem3 * winRate[id] * winRate[10];
					tem4 = tem4 * winRate[id] * winRate[11];
					tem5 = tem5 * winRate[id] * winRate[12];
					tem6 = tem6 * winRate[id] * winRate[13];
					tem7 = tem7 * winRate[id] * winRate[14];
					tem8 = tem8 * winRate[id] * winRate[15];
					winRate[id] = tem1 + tem2 + tem3 + tem4 + tem5 + tem6 + tem7 + tem8;
				}
				else
				{
					var tem1 = scores[id]/(scores[id] + scores[0]);
					var tem2 = scores[id]/(scores[id] + scores[1]);
					var tem3 = scores[id]/(scores[id] + scores[2]);
					var tem4 = scores[id]/(scores[id] + scores[3]);
					var tem5 = scores[id]/(scores[id] + scores[4]);
					var tem6 = scores[id]/(scores[id] + scores[5]);
					var tem7 = scores[id]/(scores[id] + scores[6]);
					var tem8 = scores[id]/(scores[id] + scores[7]);
					tem1 = tem1 * winRate[id] * winRate[0];
					tem2 = tem2 * winRate[id] * winRate[1];
					tem3 = tem3 * winRate[id] * winRate[2];
					tem4 = tem4 * winRate[id] * winRate[3];
					tem5 = tem5 * winRate[id] * winRate[4];
					tem6 = tem6 * winRate[id] * winRate[5];
					tem7 = tem7 * winRate[id] * winRate[6];
					tem8 = tem8 * winRate[id] * winRate[7];
					winRate[id] = tem1 + tem2 + tem3 + tem4 + tem5 + tem6 + tem7 + tem8;
				}
			}
		}
	}
	return winRate[countryId[country]];
}

function takeApart(info)
{
	for(var i = 0;i < 16;i++)
		scores[i] = info[Country[i]];
}
