from django.shortcuts import render
from .models import UserInfo
from .forms import InfoForm

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
