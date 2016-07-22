from django.shortcuts import render
from .models import News
from .forms import NewsForm

# Create your views here.
def news_list(request):
	params = request.POST if request.method == 'POST' else None
	form = NewsForm(params)
	if form.is_valid():
		post = form.save(commit=False)
		post.author = request.user
		post.save()
		form = NewsForm()
	news = News.objects.all()
	return render(request, 'news/news_list.html', {'news': news, 'form': form})


