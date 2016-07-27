from django.shortcuts import render
from .models import UserInfo
from .models import Like
from .forms import InfoForm
from news.models import Save
from django.contrib.auth import get_user_model

# Create your views here.
def editInfo(request):
	params = request.POST if request.method == 'POST' else None
	form = InfoForm(params)
	if params and params['type'] == 'checkFollow':
		_nickname = params['nickname']
		_fan = UserInfo.objects.get(nickname = _nickname)
		stars = Like.objects.filter(fan = _fan)
		return render(request, 'account/follow.html', {'stars':stars})
	if params and params['type'] == 'checkFans':
		_nickname = params['nickname']
		_star = UserInfo.objects.get(nickname = _nickname)
		fans = Like.objects.filter(star = _star)
		return render(request, 'account/fans.html', {'fans':fans})
	if params and params['type'] == 'checkSave':
		_nickname = params['nickname']
		_star = UserInfo.objects.get(nickname = _nickname)
		_user = _star.user
		saves = Save.objects.filter(user = _user)
		return render(request, 'account/saves.html', {'saves':saves})
	if form.is_valid():
		try:
			presentInfo = UserInfo.objects.get(user = request.user)
		except:
			presentInfo = UserInfo()
			presentInfo.user = request.user
		post = form.save(commit=False)
		presentInfo.nickname = post.nickname
		presentInfo.email = post.email
		presentInfo.follow = post.follow
		presentInfo.fans = post.fans
		presentInfo.headPic = post.headPic
		presentInfo.save()
		form = InfoForm()
	try:
		presentAcc = UserInfo.objects.get(user = request.user)
	except :
		presentAcc = UserInfo()
	return render(request, 'account/info.html', {'presentAcc': presentAcc, 'form': form})

def visit(request):
	newOne = True
	exist = True
	params = request.POST if request.method == 'POST' else None
	if params and params['type'] == 'like':
		satrNickname = params['nickname']
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
	if params and params['type'] == 'unfollow':
		satrNickname = params['nickname']
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
	p1 = request.GET.get('name')
	User = get_user_model()
	author = User.objects.get(username = p1)
	info = UserInfo.objects.get(user = author)
	return render(request, 'account/visit.html', {'info': info})




