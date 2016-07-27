from django.shortcuts import render
from .models import News
from .models import Comments
from .forms import CommentsForm

STATE1 = 'LogIn'
STATE2 = ''
# Create your views here.
def news_list(request):
	global STATE1
	global STATE2
	check(request)
	news = News.objects.all()
	return render(request, 'news/news_list.html', {'news': news, 'state1': STATE1, 
		'state2': STATE2})


def news_show(request):
	global STATE1
	global STATE2
	check(request)
	params = request.POST if request.method == 'POST' else None
	form = CommentsForm(params)
	p1 = request.GET.get('title')
	new = News.objects.get(title = p1)
	if form.is_valid():
		post = form.save(commit=False)
		post.author = request.user
		post.news = new
		post.save()
		form = CommentsForm()
	comments = Comments.objects.filter(news = new)
	return render(request, 'news/news.html', {'new': new, 'form': form, 'comments':comments, 
		'state1': STATE1, 'state2': STATE2})


def check(request):
	global STATE1
	global STATE2
	if request.user.is_anonymous():
		STATE1 = 'LogIn'
		STATE2 = ''
	else:
		STATE1 = request.user.get_username()
		STATE2 = 'LogOut'
