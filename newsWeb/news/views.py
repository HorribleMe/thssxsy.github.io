from django.shortcuts import render
from .models import News
from .models import Comments
from .models import Save
from .forms import CommentsForm, SearchForm, SearchByContent

STATE1 = 'LogIn'
STATE2 = ''
STATE3 = ''
# Create your views here.
def news_list(request):
	global STATE1
	global STATE2
	global STATE3
	if request.method == 'POST':
		form1 = SearchForm(request.POST)
		form2 = SearchByContent(request.POST)
		if form1.is_valid():
			title = form1.cleaned_data['title']
			result = News.objects.filter(title__contains=title)
			num = result.count()
			return render(request, 'news/search.html', {'state1': STATE1, 
		'state2': STATE2, 'state3': STATE3, 'news':result, 'num':num})
		elif form2.is_valid():
			content = form2.cleaned_data['content']
			result = News.objects.filter(content__contains=content)
			num = result.count()
			return render(request, 'news/search.html', {'state1': STATE1, 
		'state2': STATE2, 'state3': STATE3, 'news':result, 'num':num})
	else:
		form1 = SearchForm()
		form2 = SearchByContent()
	check(request)
	news = News.objects.all()
	return render(request, 'news/news_list.html', {'news': news, 'state1': STATE1, 
		'state2': STATE2, 'state3': STATE3, 'form1':form1, 'form2': form2})


def news_show(request):
	newOne = True
	global STATE1
	global STATE2
	global STATE3
	check(request)
	params = request.POST if request.method == 'POST' else None
	if params and params['type'] == 'support':
		ID = params['commentId']
		comment = Comments.objects.get(id = ID)
		comment.support+=1
		comment.save()
	if params and params['type'] == 'save':
		ID = params['newsId']
		new = News.objects.get(id = ID)
		try:
			save = Save.objects.get(user = request.user, news = new)
			newOne = False
		except:
			save = Save()
			newOne = True
		if newOne == True:
			save.user = request.user
			save.news = new
			save.save()
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
		'state1': STATE1, 'state2': STATE2, 'state3': STATE3})


def check(request):
	global STATE1
	global STATE2
	global STATE3
	if request.user.is_anonymous():
		STATE1 = 'LogIn'
		STATE2 = ''
		STATE3 = ''
	else:
		STATE1 = ''
		STATE2 = 'LogOut'
		STATE3 = request.user.get_username()