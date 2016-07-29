from django.shortcuts import render
from .models import UserInfo
from .models import Like
from .forms import InfoForm
from news.models import Save
from django.contrib.auth import get_user_model

# Create your views here.
def editInfo(request):
	params = request.POST if request.method == 'POST' else None
	if params and params['type'] == 'checkFollow':
		_nickname = params['nickname']
		try:
			_fan = UserInfo.objects.get(nickname = _nickname)
			stars = Like.objects.filter(fan = _fan)
			starsNum = stars.count()
		except:
			stars = None
			starsNum = 0
		return render(request, 'account/follow.html', {'stars':stars, 'starsNum':starsNum})
	if params and params['type'] == 'checkFans':
		_nickname = params['nickname']
		try:
			_star = UserInfo.objects.get(nickname = _nickname)
			fans = Like.objects.filter(star = _star)
			fansNum = fans.count()
		except:
			fans = None
			fansNum = 0
		return render(request, 'account/fans.html', {'fans':fans, 'fansNum':fansNum})
	if params and params['type'] == 'checkSave':
		_nickname = params['nickname']
		_user = request.user
		saves = Save.objects.filter(user = _user)
		savesNum = saves.count()
		return render(request, 'account/saves.html', {'saves':saves, 'savesNum':savesNum})
	form = InfoForm(params, request.FILES)#oh my fucking god
	if form.is_valid():
		try:
			presentInfo = UserInfo.objects.get(user = request.user)
		except:
			presentInfo = UserInfo()
			presentInfo.user = request.user
		post = form.save(commit=False)
		presentInfo.nickname = post.nickname
		presentInfo.email = post.email
		print (post.headPic)
		#print (form.cleaned_data['image'])
		presentInfo.headPic = post.headPic
		presentInfo.save()
	try:
		presentAcc = UserInfo.objects.get(user = request.user)
	except :
		presentAcc = None
	form = InfoForm()
	return render(request, 'account/info.html', {'presentAcc': presentAcc, 'form': form})

def visit(request):
	newOne = True
	exist = True
	params = request.POST if request.method == 'POST' else None
	if params and params['type'] == 'like':
		satrNickname = params['nickname']
		try:
			star = UserInfo.objects.get(nickname = satrNickname)
			try:
				fan = UserInfo.objects.get(user = request.user)
			except :
				fan = UserInfo()
				fan.user = request.user
				fan.save()
			try:
				like = Like.objects.get(star = star, fan = fan)
				newOne = False
			except:
				like = Like()
				newOne = True
			if newOne == True:
				star.fans += 1
				fan.follow += 1
				star.save()
				fan.save()
				like.star = star
				like.fan = fan
				like.save()
		except:
			satrNickname = params['nickname']
	if params and params['type'] == 'unfollow':
		satrNickname = params['nickname']
		try:
			star = UserInfo.objects.get(nickname = satrNickname)
			try:
				fan = UserInfo.objects.get(user = request.user)
			except :
				fan = UserInfo()
				fan.user = request.user
				fan.save()
			try:
				like = Like.objects.get(star = star, fan = fan)
				exist = True
			except:
				exist = False
			if exist == True:
				star.fans -= 1
				fan.follow -= 1
				star.save()
				fan.save()
				like.delete()
		except:
			satrNickname = params['nickname']
	p1 = request.GET.get('name')
	User = get_user_model()
	author = User.objects.get(username = p1)
	try:
		info = UserInfo.objects.get(user = author)
	except:
		info = None
	if author == request.user:
		form = InfoForm()
		return render(request, 'account/info.html', {'presentAcc': info, 'form': form})
	return render(request, 'account/visit.html', {'info': info})




