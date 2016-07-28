from django.conf.urls import url
from . import views

urlpatterns = [
	url(r'^$', views.news_list, name='home'),
	url(r'^tagSearch/$', views.tagSearch, name='tagSearch'),
]