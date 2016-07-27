from django.shortcuts import render
from .models import UserInfo
from .forms import InfoForm
from django.contrib.auth import get_user_model

# Create your views here.
def editInfo(request):
	params = request.POST if request.method == 'POST' else None
	form = InfoForm(params)
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
	p1 = request.GET.get('name')
	User = get_user_model()
	author = User.objects.get(username = p1)
	info = UserInfo.objects.get(user = author)
	return render(request, 'account/visit.html', {'info': info})




